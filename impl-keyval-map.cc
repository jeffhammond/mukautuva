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

// we do not want anything MPI C++ related here
#define OMPI_SKIP_MPICXX
#include <mpi.h>

#include "muk-predefined.h"
#include "wrap-handle-typedefs.h"

std::map<int, std::tuple<WRAP_Comm_copy_attr_function*,WRAP_Comm_delete_attr_function*, void*>> keyval_comm_attr_cb_map{};
std::map<int, std::tuple<WRAP_Type_copy_attr_function*,WRAP_Type_delete_attr_function*, void*>> keyval_type_attr_cb_map{};
std::map<int, std::tuple<WRAP_Win_copy_attr_function* ,WRAP_Win_delete_attr_function* , void*>> keyval_win_attr_cb_map{};

extern "C" {

int add_comm_keyval_callbacks(int keyval, 
                              WRAP_Comm_copy_attr_function   * comm_copy_attr_fn,
                              WRAP_Comm_delete_attr_function * comm_delete_attr_fn,
                              void *extra_state)
{
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    keyval_comm_attr_cb_map.insert_or_assign(keyval,
                                             std::make_tuple(comm_copy_attr_fn,
                                                             comm_delete_attr_fn,
                                                             extra_state));

    return 0;
}


}
