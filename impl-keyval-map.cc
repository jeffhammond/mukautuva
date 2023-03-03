#ifndef __cplusplus
#error Sorry, but you have to use a C++ compiler.
#endif
#if defined(__cplusplus) && (__cplusplus < 201703L)
#error Sorry, but you have to use a C++17 compiler.
#endif

#include <cstdio>
#include <cstdlib>
#include <cstdint>

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

std::map<int, std::tuple<WRAP_Comm_copy_attr_function*,WRAP_Comm_delete_attr_function*, void*>> keyval_comm_attr_cb_map{};
std::map<int, std::tuple<WRAP_Type_copy_attr_function*,WRAP_Type_delete_attr_function*, void*>> keyval_type_attr_cb_map{};
std::map<int, std::tuple<WRAP_Win_copy_attr_function* ,WRAP_Win_delete_attr_function* , void*>> keyval_win_attr_cb_map{};

extern "C" {

// we will use int as the boolean return code to avoid theoretical incompatibilities
// between C and C++ bool

int add_comm_keyval_callbacks(int keyval, 
                              WRAP_Comm_copy_attr_function   * comm_copy_attr_fn,
                              WRAP_Comm_delete_attr_function * comm_delete_attr_fn,
                              void * extra_state) // this argument may not be necessary
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, comm_copy_attr_fn=%p, comm_delete_attr_fn=%p)\n",
            __func__, keyval, comm_copy_attr_fn, comm_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_comm_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_tuple(comm_copy_attr_fn,
                                                                            comm_delete_attr_fn,
                                                                            extra_state));
    return int{rc};
}

int find_comm_keyval_callbacks(int keyval, 
                               WRAP_Comm_copy_attr_function   ** comm_copy_attr_fn,
                               WRAP_Comm_delete_attr_function ** comm_delete_attr_fn,
                               void ** extra_state) // this argument may not be necessary
{
    try {
        auto [copy_fn,delete_fn,state] = keyval_comm_attr_cb_map.at(keyval);
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
        if (extra_state != NULL) {
            *extra_state = state;
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
                              WRAP_Type_delete_attr_function * type_delete_attr_fn,
                              void * extra_state) // this argument may not be necessary
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, type_copy_attr_fn=%p, type_delete_attr_fn=%p)\n",
            __func__, keyval, type_copy_attr_fn, type_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_type_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_tuple(type_copy_attr_fn,
                                                                            type_delete_attr_fn,
                                                                            extra_state));
    return int{rc};
}

int find_type_keyval_callbacks(int keyval, 
                               WRAP_Type_copy_attr_function   ** type_copy_attr_fn,
                               WRAP_Type_delete_attr_function ** type_delete_attr_fn,
                               void ** extra_state) // this argument may not be necessary
{
    try {
        auto [copy_fn,delete_fn,state] = keyval_type_attr_cb_map.at(keyval);
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
        if (extra_state != NULL) {
            *extra_state = state;
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

} // extern "C"
