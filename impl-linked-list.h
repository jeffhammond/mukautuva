#ifndef IMPL_LINKED_LIST_H
#define IMPL_LINKED_LIST_H

#include "wrap-handle-typedefs.h"

#define MAYBE_UNUSED __attribute__((unused))

// crazy stuff to support user-defined reductions

// impl-keyval.c
extern int TYPE_HANDLE_KEY;
extern int COMM_EH_HANDLE_KEY;
extern int WIN_EH_HANDLE_KEY;

typedef struct
{
    MPI_Datatype dt;
    union {
        WRAP_User_function   * fp_i;
        WRAP_User_function_c * fp_c;
    } fp;
    bool large_c;
}
reduce_trampoline_cookie_t;

typedef enum {
    Invalid,
    Comm,
    File,
    Win
#if 0
    Session
#endif
} errhandler_kind_e;

#if 0
// first, we bind the callback function pointer to the errhandler id
// in the WRAP_{Comm,File,Session,Win}_create_errhandler.
// second, we bind the errhandler id to an object handle
// in WRAP_{Comm,File,Session,Win}_set_errhandler.
// we can bind the same errhandler id to multiple objects.
// in the errhandler trampoline, we will look up the callback
// function pointer from the object handle.
// we remove list items from the list during WRAP_Errhandler_free.
typedef struct errhandler_tuple_s
{
    // we have to do this because errhandler ids are ref-counted and
    // otherwise we have no idea when we are actually done with a tuple.
    intptr_t refcount;

    // all errhandlers live in the same pool because Errhandler_free
    // frees all of them
    errhandler_kind_e kind;

    union {
        MPI_Comm    comm;
        MPI_File    file;
        MPI_Win     win;
#if 0
        MPI_Session session;
#endif
    } handle;

    MPI_Errhandler                        errhandler;
    union {
        WRAP_Comm_errhandler_function    * comm_fp;
        WRAP_File_errhandler_function    * file_fp;
        WRAP_Win_errhandler_function     * win_fp;
#if 0
        WRAP_Session_errhandler_function * session_fp;
#endif
    } fp;

    struct errhandler_tuple_s * next;
    struct errhandler_tuple_s * prev;
}
errhandler_tuple_t;
#endif

typedef struct
{
    WRAP_Comm_errhandler_function * comm_fp;
}
comm_errh_trampoline_cookie_t;

typedef struct
{
    WRAP_File_errhandler_function * file_fp;
}
file_errh_trampoline_cookie_t;

typedef struct
{
    WRAP_Win_errhandler_function * win_fp;
}
win_errh_trampoline_cookie_t;

#if 0
typedef struct errh_fptr_pair_s
{
    MPI_Errhandler errh;

    // we have to do this because errhandlers can be used after the handles are freed.
    // we only have to do this for File and Session because we can use Comm and Win
    // attributes to store the errh fptr instead.
    intptr_t refcount;

    // all errhandlers live in the same pool because Errhandler_free
    // frees all of them
    errhandler_kind_e kind;

    union {
        WRAP_Comm_errhandler_function    * comm_fp;
        WRAP_File_errhandler_function    * file_fp;
        WRAP_Win_errhandler_function     * win_fp;
#if 0
        WRAP_Session_errhandler_function * session_fp;
#endif
    } fp;

    // for the linked list
    struct errh_fptr_pair_s * next;
    struct errh_fptr_pair_s * prev;
}
errh_fptr_pair_t;
#endif

typedef struct comm_errh_fptr_pair_s
{
    MPI_Errhandler errhandler;
    WRAP_Comm_errhandler_function * comm_fp;

    // for the linked list
    struct comm_errh_fptr_pair_s * next;
    struct comm_errh_fptr_pair_s * prev;
}
comm_errh_fptr_pair_t;

typedef struct file_errh_fptr_pair_s
{
    MPI_Errhandler errhandler;
    WRAP_File_errhandler_function * file_fp;

    // for the linked list
    struct file_errh_fptr_pair_s * next;
    struct file_errh_fptr_pair_s * prev;
}
file_errh_fptr_pair_t;

typedef struct win_errh_fptr_pair_s
{
    MPI_Errhandler errhandler;
    WRAP_Win_errhandler_function * win_fp;

    // for the linked list
    struct win_errh_fptr_pair_s * next;
    struct win_errh_fptr_pair_s * prev;
}
win_errh_fptr_pair_t;

typedef struct op_fptr_pair_s
{
    MPI_Op               op;

    // we need this because Op_free works on both types of Ops.
    bool large_c;

    union {
        WRAP_User_function   * fp_i;
        WRAP_User_function_c * fp_c;
    } fp;

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

// This is to implement the crude garbage collector for cookies
// created by nonblocking alltoallw,
// which cannot be freed until the user function is called
// (or else the lookup will segfault, obviously).
typedef struct req_alltoallw_pair_s
{
    MPI_Request    request;
    MPI_Datatype * sendtypes;
    MPI_Datatype * recvtypes;

    // true if sendtypes is not allocated
    bool           in_place;

    // for the linked list
    struct req_alltoallw_pair_s * next;
    struct req_alltoallw_pair_s * prev;
}
req_alltoallw_pair_t;

// impl-functions.c
extern op_fptr_pair_t        * op_fptr_pair_list;
extern req_cookie_pair_t     * req_cookie_pair_list;
extern req_alltoallw_pair_t  * req_alltoallw_pair_list;
extern comm_errh_fptr_pair_t * comm_errh_fptr_pair_list;
extern file_errh_fptr_pair_t * file_errh_fptr_pair_list;
extern win_errh_fptr_pair_t  * win_errh_fptr_pair_list;

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
    op_fptr_pair_t * pair = calloc(1,sizeof(op_fptr_pair_t));
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
        abort();
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
    reduce_trampoline_cookie_t * cookie = calloc(1,sizeof(reduce_trampoline_cookie_t));
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
static void add_cookie_pair_to_list(const MPI_Request request, reduce_trampoline_cookie_t * cookie)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    req_cookie_pair_t * pair = calloc(1,sizeof(req_cookie_pair_t));
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
static void cleanup_ireduce_trampoline_cookie(reduce_trampoline_cookie_t * cookie, const MPI_Request request, MPI_Datatype * dup)
{
    add_cookie_pair_to_list(request, cookie);
    int rc = IMPL_Type_free(dup);
    if (rc) {
        printf("Type_free failed: %d\n",rc);
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
        //printf("remove_cookie_pair_from_list failed to find the request\n");
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

// errhandler stuff

#if 0
MAYBE_UNUSED
static void add_errhandler_callback(MPI_Errhandler errhandler,
                                    errhandler_kind_e kind,
                                    WRAP_Comm_errhandler_function    * comm_fp,
                                    WRAP_File_errhandler_function    * file_fp,
                                    WRAP_Win_errhandler_function     * win_fp)
                                    //WRAP_Session_errhandler_function * session_fp)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    errhandler_tuple_t * tuple = calloc(1,sizeof(errhandler_tuple_t));
    tuple->refcount = 1;
    printf("%s: tuple=%p refcount=%lx\n",__func__,tuple,tuple->refcount);
    tuple->errhandler = errhandler;
    tuple->kind = kind;
    if (kind == Comm) {
        tuple->fp.comm_fp = comm_fp;
        assert(file_fp == NULL);
        assert(win_fp == NULL);
        //assert(session_fp == NULL);
    }
    else if (kind == File) {
        tuple->fp.file_fp = file_fp;
        assert(comm_fp == NULL);
        assert(win_fp == NULL);
        //assert(session_fp == NULL);
    }
    else if (kind == Win) {
        tuple->fp.win_fp = win_fp;
        assert(comm_fp == NULL);
        assert(file_fp == NULL);
        //assert(session_fp == NULL);
    }
#if 0
    else if (kind == Session) {
        tuple->fp.session_fp = session_fp;
        assert(comm_fp == NULL);
        assert(file_fp == NULL);
        assert(win_fp == NULL);
    }
#endif
    else {
        printf("%s line %d: kind (%d) is invalid\n", __func__, __LINE__, kind);
        abort();
    }
    tuple->prev = NULL;
    tuple->next = NULL;

    if (errhandler_tuple_list == NULL) {
        errhandler_tuple_list = tuple;
    } else {
        errhandler_tuple_t * parent = errhandler_tuple_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = tuple;
        tuple->prev  = parent;
    }
}

MAYBE_UNUSED
static void bind_errhandler_to_object(errhandler_kind_e kind,
                                      MPI_Errhandler errhandler,
                                      MPI_Comm    comm,
                                      MPI_File    file,
                                      MPI_Win     win)
                                      //MPI_Session session)
{

    // Step 1: look up errhandler in the linked list
    if (errhandler_tuple_list == NULL) {
        printf("%s: errhandler_tuple_list is NULL - this should be impossible.\n",__func__);
        abort();
    }

    errhandler_tuple_t * current = errhandler_tuple_list;
    while (current) {
        if (current->errhandler == errhandler) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("%s: current is NULL.\n",__func__);
        return;
    }

    // Step 2: verify the input is consistent
    if (kind != current->kind) {
        printf("%s: current->kind=%d does not match kind=%d\n",__func__, current->kind, kind);
        abort();
    }

    // Step 3: bind the object handle to the relevant tuple
    if (kind == Comm) {
        current->handle.comm = comm;
        assert(file == MPI_FILE_NULL);
        assert(win == MPI_WIN_NULL);
        //assert(session == MPI_SESSION_NULL);
    }
    else if (kind == File) {
        current->handle.file = file;
        assert(comm == MPI_COMM_NULL);
        assert(win == MPI_WIN_NULL);
        //assert(session == MPI_SESSION_NULL);
    }
    else if (kind == Win) {
        current->handle.win = win;
        assert(comm == MPI_COMM_NULL);
        assert(file == MPI_FILE_NULL);
        //assert(session == MPI_SESSION_NULL);
    }
#if 0
    else if (kind == Session) {
        current->handle.session = session;
        assert(comm == MPI_COMM_NULL);
        assert(file == MPI_FILE_NULL);
        assert(win == MPI_WIN_NULL);
    }
#endif
    else {
        printf("%s line %d: kind (%d) is invalid\n", __func__, __LINE__, kind);
        abort();
    }

    current->refcount += 1;
    printf("%s: current=%p refcount=%lx\n",__func__,current,current->refcount);
}

MAYBE_UNUSED
static void lookup_errhandler_callback(errhandler_kind_e kind,
                                       MPI_Comm    comm,
                                       WRAP_Comm_errhandler_function    ** comm_fp,
                                       MPI_File    file,
                                       WRAP_File_errhandler_function    ** file_fp,
                                       MPI_Win     win,
                                       WRAP_Win_errhandler_function     ** win_fp)
                                       //MPI_Session session,
                                       //WRAP_Session_errhandler_function ** session_fp)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 1: look up object handle in the linked list
    if (errhandler_tuple_list == NULL) {
        printf("%s: errhandler_tuple_list is NULL - this should be impossible.\n",__func__);
        abort();
    }
    errhandler_tuple_t * current = errhandler_tuple_list;
    while (current) {
        if ((current->handle.comm != MPI_COMM_NULL) && 
            (current->handle.comm == comm)) {
            assert(kind == Comm);
            break;
        }
        else if ((current->handle.file != MPI_FILE_NULL) && 
                 (current->handle.file == file)) {
            assert(kind == File);
            break;
        }
        else if ((current->handle.win != MPI_WIN_NULL) && 
                 (current->handle.win == win)) {
            assert(kind == Win);
            break;
        }
#if 0
        else if ((current->handle.session != MPI_SESSION_NULL) && 
                 (current->handle.session == session) {
            assert(kind == Session);
            break;
        }
#endif
        current = current->next;
    }

    if (current == NULL) {
        printf("%s: current is NULL.\n",__func__);
        abort();
    }

    // Step 2: set the appropriate function pointer based on the kind
    if (kind == Comm) {
        *comm_fp = current->fp.comm_fp;
    }
    else if (kind == File) {
        *file_fp = current->fp.file_fp;
    }
    else if (kind == Win) {
        *win_fp = current->fp.win_fp;
    }
#if 0
    else if (kind == Session) {
        *session_fp = current->fp.session_ip;
    }
#endif
    else {
        printf("%s line %d: kind (%d) is invalid\n", __func__, __LINE__, kind);
        abort();
    }
}

MAYBE_UNUSED
static void remove_errhandler(MPI_Errhandler errhandler)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 1: look up errhandler in the linked list
    if (errhandler_tuple_list == NULL) {
        printf("%s: errhandler_tuple_list is NULL - this should be impossible.\n",__func__);
    }
    errhandler_tuple_t * current = errhandler_tuple_list;
    while (current) {
        if (current->errhandler == errhandler) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("%s: current is NULL.\n",__func__);
    }

    current->refcount -= 1;
    printf("%s: current=%p refcount=%lx\n",__func__,current,current->refcount);

    if (current->refcount == 0)
    {
        // Step 2: remove current from the list
        if (current->prev == NULL) {
            assert(current == errhandler_tuple_list);
            errhandler_tuple_list = current->next;
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
}

MAYBE_UNUSED
static void remove_errhandler_by_object(errhandler_kind_e kind,
                                        MPI_Comm    comm,
                                        MPI_File    file,
                                        MPI_Win     win)
                                        //MPI_Session session)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.

    // Step 1: look up object in the linked list
    if (errhandler_tuple_list == NULL) {
        printf("%s: errhandler_tuple_list is NULL - this should be impossible.\n",__func__);
    }
    errhandler_tuple_t * current = errhandler_tuple_list;
    while (current) {
        if ((current->handle.comm != MPI_COMM_NULL) && 
            (current->handle.comm == comm)) {
            assert(kind == Comm);
            break;
        }
        else if ((current->handle.file != MPI_FILE_NULL) && 
                 (current->handle.file == file)) {
            assert(kind == File);
            break;
        }
        else if ((current->handle.win != MPI_WIN_NULL) && 
                 (current->handle.win == win)) {
            assert(kind == Win);
            break;
        }
#if 0
        else if ((current->handle.session != MPI_SESSION_NULL) && 
                 (current->handle.session == session) {
            assert(kind == Session);
            break;
        }
#endif
        current = current->next;
    }

    if (current == NULL) {
        printf("%s: current is NULL.\n",__func__);
        return;
    }

    current->refcount -= 1;
    printf("%s: current=%p refcount=%lx\n",__func__,current,current->refcount);

    if (current->refcount == 0)
    {
        // Step 2: remove current from the list
        if (current->prev == NULL) {
            assert(current == errhandler_tuple_list);
            errhandler_tuple_list = current->next;
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
}
#endif

MAYBE_UNUSED
static void add_comm_errh_pair_to_list(MPI_Errhandler errhandler, WRAP_Comm_errhandler_function *comm_errhandler_fn)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    comm_errh_fptr_pair_t * pair = calloc(1,sizeof(comm_errh_fptr_pair_t));
    pair->errhandler = errhandler;
    pair->comm_fp = comm_errhandler_fn;
    printf("%s: errhandler=%lx comm_errhandler_fn=%p\n",__func__,(intptr_t)errhandler,comm_errhandler_fn);

    pair->prev = NULL;
    pair->next = NULL;

    if (comm_errh_fptr_pair_list == NULL) {
        comm_errh_fptr_pair_list = pair;
        printf("%s: comm_errh_fptr_pair_list initialized to pair=%p\n",__func__,pair);
    } else {
        comm_errh_fptr_pair_t * parent = comm_errh_fptr_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
        printf("%s: comm_errh_fptr_pair_list pushed with pair=%p\n",__func__,pair);
    }
}

MAYBE_UNUSED
static bool lookup_comm_errh_pair(MPI_Errhandler errhandler, WRAP_Comm_errhandler_function ** comm_errhandler_fn)
{
    *comm_errhandler_fn = NULL;

    comm_errh_fptr_pair_t * current = comm_errh_fptr_pair_list;
    if (comm_errh_fptr_pair_list == NULL) {
        printf("comm_errh_fptr_pair_list is NULL - this should be impossible.\n");
        return false;
    }

    while (current) {
        if (current->errhandler == errhandler) {
            *comm_errhandler_fn = current->comm_fp;
            return true;
            //break;
        }
        current = current->next;
    }
    return false;
}

MAYBE_UNUSED
static void add_win_errh_pair_to_list(MPI_Errhandler errhandler, WRAP_Win_errhandler_function *win_errhandler_fn)
{
    // this is not thread-safe.  fix or abort if MPI_THREAD_MULTIPLE.
    win_errh_fptr_pair_t * pair = calloc(1,sizeof(win_errh_fptr_pair_t));
    pair->errhandler = errhandler;
    pair->win_fp = win_errhandler_fn;

    pair->prev = NULL;
    pair->next = NULL;

    if (win_errh_fptr_pair_list == NULL) {
        win_errh_fptr_pair_list = pair;
    } else {
        win_errh_fptr_pair_t * parent = win_errh_fptr_pair_list;
        while (parent->next != NULL) {
            parent = parent->next;
        }
        parent->next = pair;
        pair->prev   = parent;
    }
}

MAYBE_UNUSED
static bool lookup_win_errh_pair(MPI_Errhandler errhandler, WRAP_Win_errhandler_function ** win_errhandler_fn)
{
    *win_errhandler_fn = NULL;

    win_errh_fptr_pair_t * current = win_errh_fptr_pair_list;
    if (win_errh_fptr_pair_list == NULL) {
        printf("win_errh_fptr_pair_list is NULL - this should be impossible.\n");
        return false;
    }

    while (current) {
        if (current->errhandler == errhandler) {
            *win_errhandler_fn = current->win_fp;
            return true;
            //break;
        }
        current = current->next;
    }
    return false;
}

#endif
