// SPDX-License-Identifier: MIT

#ifndef MUK_H
#define MUK_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <dlfcn.h>

typedef enum {
    MPICH   = 1,
    OMPI    = 2,
    INTEL   = 3,
    UNKNOWN = 4
} Which_MPI_e;

extern Which_MPI_e whose_mpi;

int (*MUK_Load_functions)(void * restrict h, int major, int minor);
int (*MUK_Load_predefined)(void * restrict h);

#endif
