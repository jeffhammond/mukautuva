#ifndef __cplusplus
#error Sorry, but you have to use a C++ compiler.
#endif
#if defined(__cplusplus) && (__cplusplus < 201703L)
#error Sorry, but you have to use a C++17 compiler.
#endif

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <string>
#include <utility>
#include <map>

extern "C" {

// we do not want anything MPI C++ related here.
// this header is only used to determine the MPI ABI we are compiling against,
// and then only the scalar types (impl-scalar-types.h) it seems.
#define OMPI_SKIP_MPICXX
#define MPICH_SKIP_MPICXX
#include <mpi.h>

#include "muk-predefined.h"
#include "wrap-handle-typedefs.h"

}

// we will not try to purge the callback mappings when handle keys are no longer used
// because that will require reference counting.  instead, we will just keep
// them around forever, which has the potential to waste a trivial amount of memory -
// it is key and two pointers worth of storage (20 or 24 bytes) per entry.
// the lookup cost of a std::map is logarithmic in the size of the container, which
// is a price worth paying to avoid dealing with the use-after-free situation.


// for attributes
std::map<int, std::pair<WRAP_Comm_copy_attr_function*,WRAP_Comm_delete_attr_function*>> keyval_comm_attr_cb_map{};
std::map<int, std::pair<WRAP_Type_copy_attr_function*,WRAP_Type_delete_attr_function*>> keyval_type_attr_cb_map{};
std::map<int, std::pair<WRAP_Win_copy_attr_function* ,WRAP_Win_delete_attr_function*>>  keyval_win_attr_cb_map{};

// for user-defined reductions - TODO
std::map<MPI_Op, std::pair<WRAP_User_function*, WRAP_User_function_c*>> op_user_function_map{};

// for errhandlers - TODO
std::map<MPI_Errhandler, WRAP_Comm_errhandler_function*> errhandler_comm_cb_map{};
std::map<MPI_Errhandler, WRAP_File_errhandler_function*> errhandler_file_cb_map{};
std::map<MPI_Errhandler, WRAP_Win_errhandler_function*>  errhandler_win_cb_map{};

// for nonblocking alltoallw - TODO
std::map<MPI_Request, std::pair<MPI_Datatype*, MPI_Datatype*>> request_type_array_map{};

extern "C" {

// we use int as the boolean return code to avoid theoretical incompatibilities
// between C and C++ bool

#include "impl-keyval-map-commattr.h"
#include "impl-keyval-map-typeattr.h"
#include "impl-keyval-map-winattr.h"

#if 0

int add_comm_keyval_callbacks(int keyval,
                              WRAP_Comm_copy_attr_function   * comm_copy_attr_fn,
                              WRAP_Comm_delete_attr_function * comm_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, comm_copy_attr_fn=%p, comm_delete_attr_fn=%p)\n",
            __func__, keyval, comm_copy_attr_fn, comm_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_comm_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(comm_copy_attr_fn,
                                                                           comm_delete_attr_fn));
    return int{rc};
}

int find_comm_keyval_callbacks(int keyval,
                               WRAP_Comm_copy_attr_function   ** comm_copy_attr_fn,
                               WRAP_Comm_delete_attr_function ** comm_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_comm_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [comm_copy_attr_fn=%p, comm_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (comm_copy_attr_fn != NULL) {
            *comm_copy_attr_fn = copy_fn;
        }
        if (comm_delete_attr_fn != NULL) {
            *comm_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_comm_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_comm_attr_cb_map.erase(keyval);
}

int add_type_keyval_callbacks(int keyval,
                              WRAP_Type_copy_attr_function   * type_copy_attr_fn,
                              WRAP_Type_delete_attr_function * type_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, type_copy_attr_fn=%p, type_delete_attr_fn=%p)\n",
            __func__, keyval, type_copy_attr_fn, type_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_type_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(type_copy_attr_fn,
                                                                           type_delete_attr_fn));
    return int{rc};
}

int find_type_keyval_callbacks(int keyval,
                               WRAP_Type_copy_attr_function   ** type_copy_attr_fn,
                               WRAP_Type_delete_attr_function ** type_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_type_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [type_copy_attr_fn=%p, type_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (type_copy_attr_fn != NULL) {
            *type_copy_attr_fn = copy_fn;
        }
        if (type_delete_attr_fn != NULL) {
            *type_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_type_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_type_attr_cb_map.erase(keyval);
}

int add_win_keyval_callbacks(int keyval,
                              WRAP_Win_copy_attr_function   * win_copy_attr_fn,
                              WRAP_Win_delete_attr_function * win_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, win_copy_attr_fn=%p, win_delete_attr_fn=%p)\n",
            __func__, keyval, win_copy_attr_fn, win_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_win_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(win_copy_attr_fn,
                                                                           win_delete_attr_fn));
    return int{rc};
}

int find_win_keyval_callbacks(int keyval,
                               WRAP_Win_copy_attr_function   ** win_copy_attr_fn,
                               WRAP_Win_delete_attr_function ** win_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_win_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [win_copy_attr_fn=%p, win_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (win_copy_attr_fn != NULL) {
            *win_copy_attr_fn = copy_fn;
        }
        if (win_delete_attr_fn != NULL) {
            *win_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_win_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_win_attr_cb_map.erase(keyval);
}

#endif

} // extern "C"
