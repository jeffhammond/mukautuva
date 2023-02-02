#include <mpi.h>

// This file captures all of the predefined handles
// so that they can be referenced by dlsym, since
// this is not necessarily possible.
//
// MPICH, for example, defines predefined handles in
// the preprocessor, which means there are no symbols
// in the MPICH shared library.

MPI_Comm IMPL_COMM_WORLD = MPI_COMM_WORLD;
