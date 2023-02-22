#ifndef IMPL_LINKED_LIST_H
#define IMPL_LINKED_LIST_H

// crazy stuff to support user-defined reductions

// impl-keyval.c
extern int TYPE_HANDLE_KEY;

typedef struct
{
    MPI_Datatype         dt;
    WRAP_User_function * fp;
}
reduce_trampoline_cookie_t;

typedef struct op_fptr_pair_s
{
    // from MUK
    MPI_Op               op;
    WRAP_User_function * fp;

    // for the linked list
    struct op_fptr_pair_s * next;
    struct op_fptr_pair_s * prev;
}
op_fptr_pair_t;

// impl-functions.c
extern op_fptr_pair_t * op_fptr_pair_list;

// This is to implement the crude garbage collector for cookies
// created by nonblocking reductions with user-defined ops,
// which cannot be freed until the user function is called
// (or else the lookup will segfault, obviously).
typedef struct req_cookie_pair_s
{
    const MPI_Request          * request;
    reduce_trampoline_cookie_t * cookie;

    // for the linked list
    struct req_cookie_pair_s * next;
    struct req_cookie_pair_s * prev;
}
req_cookie_pair_t;

// impl-functions.c
extern req_cookie_pair_t * req_cookie_pair_list;

#if 0
static WRAP_User_function * lookup_op_pair(MPI_Op op)
{
    WRAP_User_function * user_fn = NULL;
    op_fptr_pair_t * current = op_fptr_pair_list;
    if (op_fptr_pair_list == NULL) {
        printf("op_fptr_pair_list is NULL - this should be impossible.\n");
    }
    while (current) {
        if (current->op == op) {
            user_fn = current->fp;
            break;
        }
        current = current->next;
    }
    return user_fn;
}

static void add_op_pair_to_list(WRAP_User_function *user_fn, MPI_Op op)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    op_fptr_pair_t * pair = malloc(sizeof(op_fptr_pair_t));
    pair->op = op;
    pair->fp = user_fn;
    pair->prev = NULL;
    pair->next = NULL;

    if (op_fptr_pair_list == NULL) {
        op_fptr_pair_list = pair;
    } else {
        op_fptr_pair_t * parent = op_fptr_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
    }
}

static void remove_op_pair_from_list(MPI_Op op)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 1: look up op in the linked list
    if (op_fptr_pair_list == NULL) {
        printf("remove_op_pair_from_list: op_fptr_pair_list is NULL - this should be impossible.\n");
    }
    op_fptr_pair_t * current = op_fptr_pair_list;
    while (current) {
        if (current->op == op) {
            break;
        }
        current = current->next;
    }

    // Step 2: remove current from the list
    if (current->prev == NULL) {
        assert(current == op_fptr_pair_list);
        op_fptr_pair_list = current->next;
        if (current->next != NULL) {
            current->next->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    // Step 3: free the memory
    free(current);
}

static reduce_trampoline_cookie_t * bake_reduce_trampoline_cookie(MPI_Op op, MPI_Datatype datatype, MPI_Datatype * dup)
{
    int rc;

    // Part 1: look up the user function associated with the MPI_Op argument
    WRAP_User_function * user_fn = lookup_op_pair(op);
    if (user_fn == NULL) {
        printf("bake_reduce_trampoline_cookie: failed to find valid op<->fn mapping.\n");
        return NULL;
    }

    // Part 2: duplicate the datatype so there can be no collision of keyvals
    rc = IMPL_Type_dup(datatype,dup);
    if (rc) {
        printf("bake_reduce_trampoline_cookie: Type_dup failed\n");
        return NULL;
    }

    // Part 3: bake the cookie
    reduce_trampoline_cookie_t * cookie = malloc(sizeof(reduce_trampoline_cookie_t));
    cookie->dt = datatype;
    cookie->fp = user_fn;
    rc = IMPL_Type_set_attr(*dup, TYPE_HANDLE_KEY, cookie);
    if (rc) {
        printf("bake_reduce_trampoline_cookie: Type_set_attr failed\n");
        IMPL_Type_free(dup);
        free(cookie);
        return NULL;
    }

    return cookie;
}

static void cleanup_reduce_trampoline_cookie(reduce_trampoline_cookie_t * cookie, MPI_Datatype * dup)
{
    free(cookie);
    int rc = IMPL_Type_free(dup);
    if (rc) {
        printf("Type_free failed: %d\n",rc);
    }
}

static void add_cookie_pair_to_list(const MPI_Request * request, reduce_trampoline_cookie_t * cookie)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    req_cookie_pair_t * pair = malloc(sizeof(req_cookie_pair_t));
    pair->request = request;
    pair->cookie  = cookie;
    pair->prev = NULL;
    pair->next = NULL;

    if (req_cookie_pair_list == NULL) {
        req_cookie_pair_list = pair;
    } else {
        req_cookie_pair_t * parent = req_cookie_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
    }
}

// this is the only one of these functions that is called
// in a performance-critical way (in a loop in e.g. Waitall)
// so ideally it should be inlined.
static inline void remove_cookie_pair_from_list(const MPI_Request * request)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 0: it is likely that this will be null, because it is only
    //         non-null when there is a outstanding nonblocking reduction
    //         with a user-defined op.
    if (req_cookie_pair_list == NULL) {
        return;
    }

    // Step 1: look up op in the linked list
    req_cookie_pair_t * current = req_cookie_pair_list;
    while (current) {
        if (current->request == request) {
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        printf("remove_cookie_pair_from_list failed to find the request\n");
        return;
    }

    // Step 2: free the cookie that we found
    if (current->cookie != NULL) {
        free(current->cookie);
    } else {
        printf("remove_cookie_from_list: current->cookie is NULL\n");
    }

    // Step 3: remove current from the list
    if (current->prev == NULL) {
        assert(current == req_cookie_pair_list);
        req_cookie_pair_list = current->next;
        if (current->next != NULL) {
            current->next->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    // Step 3: free the memory
    free(current);
}

static void cleanup_ireduce_trampoline_cookie(reduce_trampoline_cookie_t * cookie, const MPI_Request * request, MPI_Datatype * dup)
{
    add_cookie_pair_to_list(request, cookie);
    int rc = IMPL_Type_free(dup);
    if (rc) {
        printf("Type_free failed: %d\n",rc);
    }
}

#endif

#endif
