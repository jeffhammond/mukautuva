#ifndef MUK_DL_H
#define MUK_DL_H

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include <dlfcn.h>

//#include "debug.h"

// this is for function symbols, or other symbols that are not optional.
static inline void * MUK_DLSYM(void * restrict handle, const char * restrict symbol)
{
    void * fp = dlsym(handle, symbol);
    if (fp == NULL) {
        //fprintf(stderr, "MUK_DLSYM: failed to find %s - %s\n", symbol, dlerror() );
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

#endif
