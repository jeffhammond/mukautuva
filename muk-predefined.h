#ifndef MUK_PREDEFINED_H
#define MUK_PREDEFINED_H

// error codes
enum {
    MUK_SUCCESS                         =  0,
    MUK_ERR_BUFFER                      =  1,
    MUK_ERR_COUNT                       =  2,
    MUK_ERR_TYPE                        =  3,
    MUK_ERR_TAG                         =  4,
    MUK_ERR_COMM                        =  5,
    MUK_ERR_RANK                        =  6,
    MUK_ERR_REQUEST                     =  7,
    MUK_ERR_ROOT                        =  8,
    MUK_ERR_GROUP                       =  9,
    MUK_ERR_OP                          = 10,
    MUK_ERR_TOPOLOGY                    = 11,
    MUK_ERR_DIMS                        = 12,
    MUK_ERR_ARG                         = 13,
    MUK_ERR_UNKNOWN                     = 14,
    MUK_ERR_TRUNCATE                    = 15,
    MUK_ERR_OTHER                       = 16,
    MUK_ERR_INTERN                      = 17,
    MUK_ERR_PENDING                     = 18,
    MUK_ERR_IN_STATUS                   = 19,
    MUK_ERR_ACCESS                      = 20,
    MUK_ERR_AMODE                       = 21,
    MUK_ERR_ASSERT                      = 22,
    MUK_ERR_BAD_FILE                    = 23,
    MUK_ERR_BASE                        = 24,
    MUK_ERR_CONVERSION                  = 25,
    MUK_ERR_DISP                        = 26,
    MUK_ERR_DUP_DATAREP                 = 27,
    MUK_ERR_FILE_EXISTS                 = 28,
    MUK_ERR_FILE_IN_USE                 = 29,
    MUK_ERR_FILE                        = 30,
    MUK_ERR_INFO_KEY                    = 31,
    MUK_ERR_INFO_NOKEY                  = 32,
    MUK_ERR_INFO_VALUE                  = 33,
    MUK_ERR_INFO                        = 34,
    MUK_ERR_IO                          = 35,
    MUK_ERR_KEYVAL                      = 36,
    MUK_ERR_LOCKTYPE                    = 37,
    MUK_ERR_NAME                        = 38,
    MUK_ERR_NO_MEM                      = 39,
    MUK_ERR_NOT_SAME                    = 40,
    MUK_ERR_NO_SPACE                    = 41,
    MUK_ERR_NO_SUCH_FILE                = 42,
    MUK_ERR_PORT                        = 43,
    MUK_ERR_PROC_ABORTED                = 44,
    MUK_ERR_QUOTA                       = 45,
    MUK_ERR_READ_ONLY                   = 46,
    MUK_ERR_RMA_ATTACH                  = 47,
    MUK_ERR_RMA_CONFLICT                = 48,
    MUK_ERR_RMA_RANGE                   = 49,
    MUK_ERR_RMA_SHARED                  = 50,
    MUK_ERR_RMA_SYNC                    = 51,
    MUK_ERR_RMA_FLAVOR                  = 52,
    MUK_ERR_SERVICE                     = 53,
    MUK_ERR_SESSION                     = 54,
    MUK_ERR_SIZE                        = 55,
    MUK_ERR_SPAWN                       = 56,
    MUK_ERR_UNSUPPORTED_DATAREP         = 57,
    MUK_ERR_UNSUPPORTED_OPERATION       = 58,
    MUK_ERR_VALUE_TOO_LARGE             = 59,
    MUK_ERR_WIN                         = 60,
    MUK_T_ERR_CANNOT_INIT               = 61,
    MUK_T_ERR_NOT_ACCESSIBLE            = 62,
    MUK_T_ERR_NOT_INITIALIZED           = 63,
    MUK_T_ERR_NOT_SUPPORTED             = 64,
    MUK_T_ERR_MEMORY                    = 65,
    MUK_T_ERR_INVALID                   = 66,
    MUK_T_ERR_INVALID_INDEX             = 67,
    MUK_T_ERR_INVALID_ITEM              = 68,
    MUK_T_ERR_INVALID_SESSION           = 69,
    MUK_T_ERR_INVALID_HANDLE            = 70,
    MUK_T_ERR_INVALID_NAME              = 71,
    MUK_T_ERR_OUT_OF_HANDLES            = 72,
    MUK_T_ERR_OUT_OF_SESSIONS           = 73,
    MUK_T_ERR_CVAR_SET_NOT_NOW          = 74,
    MUK_T_ERR_CVAR_SET_NEVER            = 75,
    MUK_T_ERR_PVAR_NO_WRITE             = 76,
    MUK_T_ERR_PVAR_NO_STARTSTOP         = 77,
    MUK_T_ERR_PVAR_NO_ATOMIC            = 78,
    MUK_ERR_LASTCODE                    = 79
};

// Buffer Address Constants

// Assorted Constants
enum {
    // these should be different and never valid ranks
    // MUK and OMPI are the same.  MPICH in parentheses.
    MUK_ANY_SOURCE = -1, // (-2)
    MUK_PROC_NULL  = -2, // (-1)
    MUK_ROOT       = -4  // (-3)
};
enum {
    // MUK, MPICH and OMPI agree on this
    MUK_ANY_TAG    = -1
};
enum {
    // MUK, MPICH and OMPI agree on this
    MUK_UNDEFINED  = -32766
};
enum {
    MUK_BSEND_OVERHEAD = 128
};
enum {
    MUK_KEYVAL_INVALID = -7
};
enum {
    MUK_LOCK_EXCLUSIVE = -8,
    MUK_LOCK_SHARED    = -9
};

//Fortran status array size and reserved index values (C only)
enum {
    // 256-bit Status is proposed
    MUK_F_STATUS_SIZE   = 8,
    // the public fields should come first
    MUK_F_SOURCE        = 0,
    MUK_F_TAG           = 1,
    MUK_F_ERROR         = 2,
    // ignore Fortran for now
    MUK_ADDRESS_KIND    = -1,
    MUK_COUNT_KIND      = -1,
    MUK_INTEGER_KIND    = -1,
    MUK_OFFSET_KIND     = -1
};

// Communicator split type constants
enum {
    MUK_COMM_TYPE_SHARED        = -100,
    MUK_COMM_TYPE_HW_UNGUIDED   = -101,
    MUK_COMM_TYPE_HW_GUIDED     = -102
};

// Results of communicator and group comparisons
enum {
    // MPICH and OMPI agree on this
    MUK_IDENT       = 0,
    MUK_CONGRUENT   = 1,
    MUK_SIMILAR     = 2,
    MUK_UNEQUAL     = 3
};

// Topologies
enum {
    MUK_GRAPH       = -200,
    MUK_CART        = -201,
    MUK_DIST_GRAPH  = -202
};

enum {
    // Environmental inquiry keys
    MUK_TAG_UB,
    MUK_IO,
    MUK_HOST,
    MUK_WTIME_IS_GLOBAL,
    // Predefined Attribute Keys
    MUK_APPNUM,
    MUK_LASTUSEDCODE,
    MUK_UNIVERSE_SIZE,
    MUK_WIN_BASE,
    MUK_WIN_DISP_UNIT,
    MUK_WIN_SIZE,
    MUK_WIN_CREATE_FLAVOR,
    MUK_WIN_MODEL
};

// MPI Window Create Flavors
enum {
    // MPICH and OMPI agree on this
    MUK_WIN_FLAVOR_CREATE   = 1,
    MUK_WIN_FLAVOR_ALLOCATE = 2,
    MUK_WIN_FLAVOR_DYNAMIC  = 3,
    MUK_WIN_FLAVOR_SHARED   = 4
};

// MPI Window Models
enum {
    MUK_WIN_SEPARATE = -300,
    MUK_WIN_UNIFIED  = -301
};

// Mode Constants
// The values of these constants must be defined such that the bitwise OR
// and the sum of any distinct set of these constants is equivalent.
enum {
    // none of these should be 0
    // I/O constants
    MUK_MODE_APPEND             = 1<<1,
    MUK_MODE_CREATE             = 1<<2,
    MUK_MODE_DELETE_ON_CLOSE    = 1<<3,
    MUK_MODE_EXCL               = 1<<4,
    MUK_MODE_RDONLY             = 1<<5,
    MUK_MODE_RDWR               = 1<<6,
    MUK_MODE_SEQUENTIAL         = 1<<7,
    MUK_MODE_UNIQUE_OPEN        = 1<<8,
    MUK_MODE_WRONLY             = 1<<9,
    // RMA constants
    MUK_MODE_NOCHECK            = 1<<15,
    MUK_MODE_NOPRECEDE          = 1<<16,
    MUK_MODE_NOPUT              = 1<<17,
    MUK_MODE_NOSTORE            = 1<<18,
    MUK_MODE_NOSUCCEED          = 1<<19
};

// Datatype Decoding Constants
enum {
    MUK_COMBINER_CONTIGUOUS,
    MUK_COMBINER_DARRAY,
    MUK_COMBINER_DUP,
    MUK_COMBINER_F90_COMPLEX,
    MUK_COMBINER_F90_INTEGER,
    MUK_COMBINER_F90_REAL,
    MUK_COMBINER_HINDEXED,
    MUK_COMBINER_HVECTOR,
    MUK_COMBINER_INDEXED_BLOCK,
    MUK_COMBINER_HINDEXED_BLOCK,
    MUK_COMBINER_INDEXED,
    MUK_COMBINER_NAMED,
    MUK_COMBINER_RESIZED,
    MUK_COMBINER_STRUCT,
    MUK_COMBINER_SUBARRAY,
    MUK_COMBINER_VECTOR
};

// Threads Constants
enum {
    // MPICH and OMPI agree on this
    MUK_THREAD_SINGLE       = 0,
    MUK_THREAD_FUNNELED     = 1,
    MUK_THREAD_SERIALIZED   = 2,
    MUK_THREAD_MULTIPLE     = 3
};

enum {
    // File Operation Constants, Part 1
    MUK_DISPLACEMENT_CURRENT,
    // File Operation Constants, Part 2
    MUK_DISTRIBUTE_BLOCK,
    MUK_DISTRIBUTE_CYCLIC,
    MUK_DISTRIBUTE_DFLT_DARG,
    MUK_DISTRIBUTE_NONE,
    MUK_ORDER_C,
    MUK_ORDER_FORTRAN,
    MUK_SEEK_CUR,
    MUK_SEEK_END,
    MUK_SEEK_SET
};

// F90 Datatype Matching Constants
enum {
    MUK_TYPECLASS_COMPLEX,
    MUK_TYPECLASS_INTEGER,
    MUK_TYPECLASS_REAL
};

#define MUK_BOTTOM ((void *)0)
#define MUK_IN_PLACE ((void *)1)

#endif
