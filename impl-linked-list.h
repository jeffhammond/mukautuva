#ifndef IMPL_LINKED_LIST_H
#define IMPL_LINKED_LIST_H

#include "wrap-handle-typedefs.h"

#define MAYBE_UNUSED __attribute__((unused))

// crazy stuff to support user-defined reductions

// impl-keyval.c
extern int TYPE_HANDLE_KEY;

typedef struct
{
    MPI_Datatype           dt;
    union {
        WRAP_User_function   * fp_i;
        WRAP_User_function_c * fp_c;
    } fp;
    bool large_c;
}
reduce_trampoline_cookie_t;

typedef struct op_fptr_pair_s
{
    MPI_Op               op;
    union {
        WRAP_User_function   * fp_i;
        WRAP_User_function_c * fp_c;
    } fp;
    bool large_c;

    // for the linked list
    struct op_fptr_pair_s * next;
    struct op_fptr_pair_s * prev;
}
op_fptr_pair_t;

// This is to implement the crude garbage collector for cookies
// created by nonblocking reductions with user-defined ops,
// which cannot be freed until the user function is called
// (or else the lookup will segfault, obviously).
typedef struct req_cookie_pair_s
{
    MPI_Request                  request;
    reduce_trampoline_cookie_t * cookie;

    // for the linked list
    struct req_cookie_pair_s * next;
    struct req_cookie_pair_s * prev;
}
req_cookie_pair_t;

// impl-functions.c
extern op_fptr_pair_t    * op_fptr_pair_list;
extern req_cookie_pair_t * req_cookie_pair_list;

MAYBE_UNUSED
static bool lookup_op_pair(const MPI_Op op, WRAP_User_function ** fn_i, WRAP_User_function_c ** fn_c , bool * is_large)
{
    *fn_i = NULL;
    *fn_c = NULL;
    *is_large  = false;

    op_fptr_pair_t * current = op_fptr_pair_list;
    if (op_fptr_pair_list == NULL) {
        printf("op_fptr_pair_list is NULL - this should be impossible.\n");
        return false;
    }

    while (current) {
        if (current->op == op) {
            if (current->large_c) {
                *is_large  = true;
                *fn_c = current->fp.fp_c;
            } else {
                *is_large  = false;
                *fn_i = current->fp.fp_i;
            }
            return true;
            //break;
        }
        current = current->next;
    }
    return false;
}

MAYBE_UNUSED
static void add_op_pair_to_list(bool is_large, MPI_Op op, WRAP_User_function *user_fn_i, WRAP_User_function_c *user_fn_c)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    op_fptr_pair_t * pair = malloc(sizeof(op_fptr_pair_t));
    pair->op = op;
    if (is_large) {
        assert(user_fn_i == NULL);
        pair->fp.fp_c = user_fn_c;
    } else {
        assert(user_fn_c == NULL);
        pair->fp.fp_i = user_fn_i;
    }
    pair->large_c = is_large;
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

MAYBE_UNUSED
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

MAYBE_UNUSED
static reduce_trampoline_cookie_t * bake_reduce_trampoline_cookie(MPI_Op op, MPI_Datatype datatype, MPI_Datatype * dup)
{
    int rc;

    // Part 1: look up the user function associated with the MPI_Op argument
    //WRAP_User_function * user_fn = lookup_op_pair(op);
    WRAP_User_function   * user_fn_i = NULL;;
    WRAP_User_function_c * user_fn_c = NULL;
    bool is_large = false;
    bool found = lookup_op_pair(op, &user_fn_i, &user_fn_c, &is_large);
    if (found == false) {
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
    if (is_large) {
        cookie->fp.fp_c = user_fn_c;
    } else {
        cookie->fp.fp_i = user_fn_i;
    }
    cookie->large_c = is_large;
    rc = IMPL_Type_set_attr(*dup, TYPE_HANDLE_KEY, cookie);
    if (rc) {
        printf("bake_reduce_trampoline_cookie: Type_set_attr failed\n");
        IMPL_Type_free(dup);
        free(cookie);
        return NULL;
    }

    return cookie;
}

MAYBE_UNUSED
static void cleanup_reduce_trampoline_cookie(reduce_trampoline_cookie_t * cookie, MPI_Datatype * dup)
{
    free(cookie);
    int rc = IMPL_Type_free(dup);
    if (rc) {
        printf("Type_free failed: %d\n",rc);
    }
}

MAYBE_UNUSED
static void add_cookie_pair_to_list(const MPI_Request request, reduce_trampoline_cookie_t * cookie)
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
MAYBE_UNUSED
static inline void remove_cookie_pair_from_list(const MPI_Request request)
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

MAYBE_UNUSED
static void cleanup_ireduce_trampoline_cookie(reduce_trampoline_cookie_t * cookie, const MPI_Request request, MPI_Datatype * dup)
{
    add_cookie_pair_to_list(request, cookie);
    int rc = IMPL_Type_free(dup);
    if (rc) {
        printf("Type_free failed: %d\n",rc);
    }
}

#endif
