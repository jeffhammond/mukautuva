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

int MPICH_Load_functions(void * restrict h, int major, int minor);
int OMPI_Load_functions(void * restrict h, int major, int minor);
int OMPI_Load_predefined(void * restrict h);

// this is for function symbols, or other symbols that are not optional.
static inline void * MUK_DLSYM(void * restrict handle, const char * restrict symbol)
{
    void * fp = dlsym(handle, symbol);
    if (fp == NULL) {
        printf("MUK_DLSYM: failed to find %s - %s\n", symbol, dlerror() );
    }
    return fp;
}

// this is for cases where symbols are optional, i.e. predefined handles,
// where we provide the value to use where the symbol is not found.
static inline void * MUK_DLSYM_OPT(void * restrict handle, const char * restrict symbol, void * fallback)
{
    void * p = dlsym(handle, symbol);
    if (p == NULL) {
        p = fallback;
    }
    return p;
}

// these symbols are ABI-agnostic and are needed before anything else can be loaded
int (*MUK_Init)(int *argc, char ***argv);
int (*MUK_Get_library_version)(char *version, int *resultlen);
int (*MUK_Get_version)(int *version, int *subversion);

// these symbols are ABI-agnostic
int (*MUK_Finalize)(void);
int (*MUK_Finalized)(int*);
int (*MUK_Init_thread)(int*,char***,int,int*);
int (*MUK_Initialized)(int*);
int (*MUK_Is_thread_main)(int*);
int (*MUK_Query_thread)(int*);
int (*MUK_Get_processor_name)(char*,int*);

#endif
