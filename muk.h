#ifndef MUK_H
#define MUK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "debug.h"

typedef enum {
    MPICH   = 1,
    OMPI    = 2,
    UNKNOWN = 3
} Which_MPI_e;

extern Which_MPI_e whose_mpi;

static inline void * MUK_DLSYM(void * restrict handle, const char * restrict symbol)
{
    void * fp = dlsym(handle, symbol);
    if (fp == NULL) {
        printf("MUK_DLSYM: failed to find %s - %s\n", symbol, dlerror() );
    }
    return fp;
}

// all the MPI functions, as function pointers
int (*MUK_Init)(int*,char***);
int (*MUK_Get_library_version)(char*,int*);

#endif
