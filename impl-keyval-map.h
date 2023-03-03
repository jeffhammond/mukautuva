#ifndef IMPL_KEYVAL_MAP_H
#define IMPL_KEYVAL_MAP_H

// C declarations of the map stuff written in C++ in impl-keyval-map.cc

// this header is only used to determine the MPI ABI we are compiling against,
// and then only the scalar types (impl-scalar-types.h) it seems.
#include <mpi.h>

#include "muk-predefined.h"
#include "wrap-handle-typedefs.h"

// return values are 0=failure 1=success but are int not bool because C and C++ bool
// are not guaranteed to be the same.

// OP USERFN

int add_comm_op_callback(MPI_Op op,
                         WRAP_User_function   * user_fn,
                         WRAP_User_function_c * user_fn_c);

int find_comm_op_callback(MPI_Op op,
                          WRAP_User_function   ** user_fn,
                          WRAP_User_function_c ** user_fn_c);

int remove_comm_op_callback(MPI_Op op);

// COMM KEYVAL

int add_comm_keyval_callbacks(int keyval,
                              WRAP_Comm_copy_attr_function   * comm_copy_attr_fn,
                              WRAP_Comm_delete_attr_function * comm_delete_attr_fn);

int find_comm_keyval_callbacks(int keyval,
                               WRAP_Comm_copy_attr_function   ** comm_copy_attr_fn,
                               WRAP_Comm_delete_attr_function ** comm_delete_attr_fn);

int remove_comm_keyval_callbacks(int keyval);

// TYPE KEYVAL

int add_type_keyval_callbacks(int keyval,
                              WRAP_Type_copy_attr_function   * type_copy_attr_fn,
                              WRAP_Type_delete_attr_function * type_delete_attr_fn);

int find_type_keyval_callbacks(int keyval,
                               WRAP_Type_copy_attr_function   ** type_copy_attr_fn,
                               WRAP_Type_delete_attr_function ** type_delete_attr_fn);

int remove_type_keyval_callbacks(int keyval);

// WIN KEYVAL

int add_win_keyval_callbacks(int keyval,
                             WRAP_Win_copy_attr_function   * win_copy_attr_fn,
                             WRAP_Win_delete_attr_function * win_delete_attr_fn);

int find_win_keyval_callbacks(int keyval,
                              WRAP_Win_copy_attr_function   ** win_copy_attr_fn,
                              WRAP_Win_delete_attr_function ** win_delete_attr_fn);

int remove_win_keyval_callbacks(int keyval);

#endif // IMPL_KEYVAL_MAP_H
