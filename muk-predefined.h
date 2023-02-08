#ifndef MUK_PREDEFINED_H
#define MUK_PREDEFINED_H

// error codes
enum {
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
    MUK_PROC_NULL  = -2,
    MUK_ANY_SOURCE = -3,
    MUK_ROOT       = -4
};
enum {
    MUK_ANY_TAG    = -5
};
enum {
    MUK_UNDEFINED  = -6
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
    MUK_F_STATUS_SIZE,
    MUK_F_SOURCE,
    MUK_F_TAG,
    MUK_F_ERROR,
    MUK_ADDRESS_KIND,
    MUK_COUNT_KIND,
    MUK_INTEGER_KIND,
    MUK_OFFSET_KIND
};

// Communicator split type constants
enum {
    MUK_COMM_TYPE_SHARED        = -100,
    MUK_COMM_TYPE_HW_UNGUIDED   = -101,
    MUK_COMM_TYPE_HW_GUIDED     = -102
};

// Results of communicator and group comparisons
enum {
    MUK_IDENT,
    MUK_CONGRUENT,
    MUK_SIMILAR,
    MUK_UNEQUAL
};

// Environmental inquiry keys
enum {
    MUK_TAG_UB,
    MUK_IO,
    MUK_HOST,
    MUK_WTIME_IS_GLOBAL
};

// Topologies
enum {
    MUK_GRAPH,
    MUK_CART,
    MUK_DIST_GRAPH
};

// Predefined Attribute Keys
enum {
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
    MUK_WIN_FLAVOR_CREATE,
    MUK_WIN_FLAVOR_ALLOCATE,
    MUK_WIN_FLAVOR_DYNAMIC,
    MUK_WIN_FLAVOR_SHARED
};

// MPI Window Models
enum {
    MUK_WIN_SEPARATE,
    MUK_WIN_UNIFIED
};

// Mode Constants
enum {
    MUK_MODE_APPEND,
    MUK_MODE_CREATE,
    MUK_MODE_DELETE_ON_CLOSE,
    MUK_MODE_EXCL,
    MUK_MODE_NOCHECK,
    MUK_MODE_NOPRECEDE,
    MUK_MODE_NOPUT,
    MUK_MODE_NOSTORE,
    MUK_MODE_NOSUCCEED,
    MUK_MODE_RDONLY,
    MUK_MODE_RDWR,
    MUK_MODE_SEQUENTIAL,
    MUK_MODE_UNIQUE_OPEN,
    MUK_MODE_WRONLY
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
    MUK_THREAD_FUNNELED,
    MUK_THREAD_MULTIPLE,
    MUK_THREAD_SERIALIZED,
    MUK_THREAD_SINGLE
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

#endif
