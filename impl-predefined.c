// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <assert.h>
#include "mpi.h"
#include "muk-predefined.h"

// Buffer Address Constants
#if ( __STDC_VERSION__ >= 201112L) && !defined(__clang__)
// Clang refuses to do this
_Static_assert(MPI_BOTTOM == NULL , "MPI_BOTTOM == NULL" );
#endif
void * IMPL_BOTTOM = MPI_BOTTOM;
void * IMPL_IN_PLACE = MPI_IN_PLACE;

// we avoid converting thread levels because every known implementation uses
// the same values for them, but we explicitly verify the assumption here.
#if ( __STDC_VERSION__ >= 201112L)
_Static_assert( (int)MUK_UNDEFINED == (int)MPI_UNDEFINED , "MUK_UNDEFINED == MPI_UNDEFINED" );
#endif

// we avoid converting thread levels because every known implementation uses
// the same values for them, but we explicitly verify the assumption here.
#if ( __STDC_VERSION__ >= 201112L)
_Static_assert( (int)MUK_IDENT     == (int)MPI_IDENT     , "MUK_IDENT     == MPI_IDENT"     );
_Static_assert( (int)MUK_CONGRUENT == (int)MPI_CONGRUENT , "MUK_CONGRUENT == MPI_CONGRUENT" );
_Static_assert( (int)MUK_SIMILAR   == (int)MPI_SIMILAR   , "MUK_SIMILAR   == MPI_SIMILAR"   );
_Static_assert( (int)MUK_UNEQUAL   == (int)MPI_UNEQUAL   , "MUK_UNEQUAL   == MPI_UNEQUAL"   );
#endif

// Results of communicator and group comparisons
int IMPL_IDENT     = MPI_IDENT;
int IMPL_CONGRUENT = MPI_CONGRUENT;
int IMPL_SIMILAR   = MPI_SIMILAR;
int IMPL_UNEQUAL   = MPI_UNEQUAL;

// Environmental inquiry keys
int IMPL_TAG_UB = MPI_TAG_UB;
int IMPL_IO = MPI_IO;
int IMPL_HOST = MPI_HOST;
int IMPL_WTIME_IS_GLOBAL = MPI_WTIME_IS_GLOBAL;

// Topologies
int IMPL_GRAPH = MPI_GRAPH;
int IMPL_CART = MPI_CART;
int IMPL_DIST_GRAPH = MPI_DIST_GRAPH;

// Predefined functions
// TODO
// Deprecated predefined functions
// TODO

// Predefined Attribute Keys
int IMPL_APPNUM = MPI_APPNUM;
int IMPL_LASTUSEDCODE = MPI_LASTUSEDCODE;
int IMPL_UNIVERSE_SIZE = MPI_UNIVERSE_SIZE;
int IMPL_WIN_BASE = MPI_WIN_BASE;
int IMPL_WIN_DISP_UNIT = MPI_WIN_DISP_UNIT;
int IMPL_WIN_SIZE = MPI_WIN_SIZE;
int IMPL_WIN_CREATE_FLAVOR = MPI_WIN_CREATE_FLAVOR;
int IMPL_WIN_MODEL = MPI_WIN_MODEL;

// MPI Window Create Flavors
int IMPL_WIN_FLAVOR_CREATE = MPI_WIN_FLAVOR_CREATE;
int IMPL_WIN_FLAVOR_ALLOCATE = MPI_WIN_FLAVOR_ALLOCATE;
int IMPL_WIN_FLAVOR_DYNAMIC = MPI_WIN_FLAVOR_DYNAMIC;
int IMPL_WIN_FLAVOR_SHARED = MPI_WIN_FLAVOR_SHARED;

// MPI Window Models
int IMPL_WIN_SEPARATE = MPI_WIN_SEPARATE;
int IMPL_WIN_UNIFIED = MPI_WIN_UNIFIED;
            
// Mode Constants
int IMPL_MODE_APPEND = MPI_MODE_APPEND;
int IMPL_MODE_CREATE = MPI_MODE_CREATE;
int IMPL_MODE_DELETE_ON_CLOSE = MPI_MODE_DELETE_ON_CLOSE;
int IMPL_MODE_EXCL = MPI_MODE_EXCL;
int IMPL_MODE_NOCHECK = MPI_MODE_NOCHECK;
int IMPL_MODE_NOPRECEDE = MPI_MODE_NOPRECEDE;
int IMPL_MODE_NOPUT = MPI_MODE_NOPUT;
int IMPL_MODE_NOSTORE = MPI_MODE_NOSTORE;
int IMPL_MODE_NOSUCCEED = MPI_MODE_NOSUCCEED;
int IMPL_MODE_RDONLY = MPI_MODE_RDONLY;
int IMPL_MODE_RDWR = MPI_MODE_RDWR;
int IMPL_MODE_SEQUENTIAL = MPI_MODE_SEQUENTIAL;
int IMPL_MODE_UNIQUE_OPEN = MPI_MODE_UNIQUE_OPEN;
int IMPL_MODE_WRONLY = MPI_MODE_WRONLY;

// Datatype Decoding Constants
int IMPL_COMBINER_CONTIGUOUS = MPI_COMBINER_CONTIGUOUS;
int IMPL_COMBINER_DARRAY = MPI_COMBINER_DARRAY;
int IMPL_COMBINER_DUP = MPI_COMBINER_DUP;
int IMPL_COMBINER_F90_COMPLEX = MPI_COMBINER_F90_COMPLEX;
int IMPL_COMBINER_F90_INTEGER = MPI_COMBINER_F90_INTEGER;
int IMPL_COMBINER_F90_REAL = MPI_COMBINER_F90_REAL;
int IMPL_COMBINER_HINDEXED = MPI_COMBINER_HINDEXED;
int IMPL_COMBINER_HVECTOR = MPI_COMBINER_HVECTOR;
int IMPL_COMBINER_INDEXED_BLOCK = MPI_COMBINER_INDEXED_BLOCK;
int IMPL_COMBINER_HINDEXED_BLOCK = MPI_COMBINER_HINDEXED_BLOCK;
int IMPL_COMBINER_INDEXED = MPI_COMBINER_INDEXED;
int IMPL_COMBINER_NAMED = MPI_COMBINER_NAMED;
int IMPL_COMBINER_RESIZED = MPI_COMBINER_RESIZED;
int IMPL_COMBINER_STRUCT = MPI_COMBINER_STRUCT;
int IMPL_COMBINER_SUBARRAY = MPI_COMBINER_SUBARRAY;
int IMPL_COMBINER_VECTOR = MPI_COMBINER_VECTOR;


// we avoid converting thread levels because every known implementation uses
// the same values for them, but we explicitly verify the assumption here.
#if ( __STDC_VERSION__ >= 201112L)
_Static_assert( (int)MUK_THREAD_FUNNELED   == (int)MPI_THREAD_FUNNELED   , "MUK_THREAD_FUNNELED   == MPI_THREAD_FUNNELED  " );
_Static_assert( (int)MUK_THREAD_MULTIPLE   == (int)MPI_THREAD_MULTIPLE   , "MUK_THREAD_MULTIPLE   == MPI_THREAD_MULTIPLE  " );
_Static_assert( (int)MUK_THREAD_SERIALIZED == (int)MPI_THREAD_SERIALIZED , "MUK_THREAD_SERIALIZED == MPI_THREAD_SERIALIZED" );
_Static_assert( (int)MUK_THREAD_SINGLE     == (int)MPI_THREAD_SINGLE     , "MUK_THREAD_SINGLE     == MPI_THREAD_SINGLE    " );
#endif

// Threads Constants
int IMPL_THREAD_FUNNELED = MPI_THREAD_FUNNELED;
int IMPL_THREAD_MULTIPLE = MPI_THREAD_MULTIPLE;
int IMPL_THREAD_SERIALIZED = MPI_THREAD_SERIALIZED;
int IMPL_THREAD_SINGLE = MPI_THREAD_SINGLE;

// File Operation Constants, Part 1
int IMPL_DISPLACEMENT_CURRENT = MPI_DISPLACEMENT_CURRENT;

// File Operation Constants, Part 2
int IMPL_DISTRIBUTE_BLOCK = MPI_DISTRIBUTE_BLOCK;
int IMPL_DISTRIBUTE_CYCLIC = MPI_DISTRIBUTE_CYCLIC;
int IMPL_DISTRIBUTE_DFLT_DARG = MPI_DISTRIBUTE_DFLT_DARG;
int IMPL_DISTRIBUTE_NONE = MPI_DISTRIBUTE_NONE;
int IMPL_ORDER_C = MPI_ORDER_C;
int IMPL_ORDER_FORTRAN = MPI_ORDER_FORTRAN;
int IMPL_SEEK_CUR = MPI_SEEK_CUR;
int IMPL_SEEK_END = MPI_SEEK_END;
int IMPL_SEEK_SET = MPI_SEEK_SET;

// F90 Datatype Matching Constants
int IMPL_TYPECLASS_COMPLEX = MPI_TYPECLASS_COMPLEX;
int IMPL_TYPECLASS_INTEGER = MPI_TYPECLASS_INTEGER;
int IMPL_TYPECLASS_REAL    = MPI_TYPECLASS_REAL;
