#ifndef MUK_H
#define MUK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "debug.h"

#include "mpich.h"
#include "ompi.h"

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

// these symbols are ABI-agnostic and are needed before anything else can be loaded
int (*MUK_Init)(int *argc, char ***argv);
int (*MUK_Get_library_version)(char *version, int *resultlen);
int (*MUK_Get_version)(int *version, int *subversion);

// technically, these are not required to be symbols, but we know they are.
// we can work around the theoretical problem if necessary.
double (*MUK_Wtime)(void);
double (*MUK_Wtick)(void);

#endif
