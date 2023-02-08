#ifndef MUK_MPI_PREDEFINED_H
#define MUK_MPI_PREDEFINED_H

#ifndef MUK_EXTERN
#error You must define MUK_EXTERN outside of this header!
#endif

#include "muk-predefined.h"

// error codes
enum {
    // "Note that MPI_SUCCESS = 0 is necessary to be consistent with C practice..."
    MPI_SUCCESS                        = 0,
    MPI_ERR_BUFFER                     = MUK_ERR_BUFFER,
    MPI_ERR_COUNT                      = MUK_ERR_COUNT,
    MPI_ERR_TYPE                       = MUK_ERR_TYPE,
    MPI_ERR_TAG                        = MUK_ERR_TAG,
    MPI_ERR_COMM                       = MUK_ERR_COMM,
    MPI_ERR_RANK                       = MUK_ERR_RANK,
    MPI_ERR_REQUEST                    = MUK_ERR_REQUEST,
    MPI_ERR_ROOT                       = MUK_ERR_ROOT,
    MPI_ERR_GROUP                      = MUK_ERR_GROUP,
    MPI_ERR_OP                         = MUK_ERR_OP,
    MPI_ERR_TOPOLOGY                   = MUK_ERR_TOPOLOGY,
    MPI_ERR_DIMS                       = MUK_ERR_DIMS,
    MPI_ERR_ARG                        = MUK_ERR_ARG,
    MPI_ERR_UNKNOWN                    = MUK_ERR_UNKNOWN,
    MPI_ERR_TRUNCATE                   = MUK_ERR_TRUNCATE,
    MPI_ERR_OTHER                      = MUK_ERR_OTHER,
    MPI_ERR_INTERN                     = MUK_ERR_INTERN,
    MPI_ERR_PENDING                    = MUK_ERR_PENDING,
    MPI_ERR_IN_STATUS                  = MUK_ERR_IN_STATUS,
    MPI_ERR_ACCESS                     = MUK_ERR_ACCESS,
    MPI_ERR_AMODE                      = MUK_ERR_AMODE,
    MPI_ERR_ASSERT                     = MUK_ERR_ASSERT,
    MPI_ERR_BAD_FILE                   = MUK_ERR_BAD_FILE,
    MPI_ERR_BASE                       = MUK_ERR_BASE,
    MPI_ERR_CONVERSION                 = MUK_ERR_CONVERSION,
    MPI_ERR_DISP                       = MUK_ERR_DISP,
    MPI_ERR_DUP_DATAREP                = MUK_ERR_DUP_DATAREP,
    MPI_ERR_FILE_EXISTS                = MUK_ERR_FILE_EXISTS,
    MPI_ERR_FILE_IN_USE                = MUK_ERR_FILE_IN_USE,
    MPI_ERR_FILE                       = MUK_ERR_FILE,
    MPI_ERR_INFO_KEY                   = MUK_ERR_INFO_KEY,
    MPI_ERR_INFO_NOKEY                 = MUK_ERR_INFO_NOKEY,
    MPI_ERR_INFO_VALUE                 = MUK_ERR_INFO_VALUE,
    MPI_ERR_INFO                       = MUK_ERR_INFO,
    MPI_ERR_IO                         = MUK_ERR_IO,
    MPI_ERR_KEYVAL                     = MUK_ERR_KEYVAL,
    MPI_ERR_LOCKTYPE                   = MUK_ERR_LOCKTYPE,
    MPI_ERR_NAME                       = MUK_ERR_NAME,
    MPI_ERR_NO_MEM                     = MUK_ERR_NO_MEM,
    MPI_ERR_NOT_SAME                   = MUK_ERR_NOT_SAME,
    MPI_ERR_NO_SPACE                   = MUK_ERR_NO_SPACE,
    MPI_ERR_NO_SUCH_FILE               = MUK_ERR_NO_SUCH_FILE,
    MPI_ERR_PORT                       = MUK_ERR_PORT,
#if MPI_VERSION >= 4
    MPI_ERR_PROC_ABORTED               = MUK_ERR_PROC_ABORTED,
#endif
    MPI_ERR_QUOTA                      = MUK_ERR_QUOTA,
    MPI_ERR_READ_ONLY                  = MUK_ERR_READ_ONLY,
    MPI_ERR_RMA_ATTACH                 = MUK_ERR_RMA_ATTACH,
    MPI_ERR_RMA_CONFLICT               = MUK_ERR_RMA_CONFLICT,
    MPI_ERR_RMA_RANGE                  = MUK_ERR_RMA_RANGE,
    MPI_ERR_RMA_SHARED                 = MUK_ERR_RMA_SHARED,
    MPI_ERR_RMA_SYNC                   = MUK_ERR_RMA_SYNC,
    MPI_ERR_RMA_FLAVOR                 = MUK_ERR_RMA_FLAVOR,
    MPI_ERR_SERVICE                    = MUK_ERR_SERVICE,
#if MPI_VERSION >= 4
    MPI_ERR_SESSION                    = MUK_ERR_SESSION,
#endif
    MPI_ERR_SIZE                       = MUK_ERR_SIZE,
    MPI_ERR_SPAWN                      = MUK_ERR_SPAWN,
    MPI_ERR_UNSUPPORTED_DATAREP        = MUK_ERR_UNSUPPORTED_DATAREP,
    MPI_ERR_UNSUPPORTED_OPERATION      = MUK_ERR_UNSUPPORTED_OPERATION,
#if MPI_VERSION >= 4
    MPI_ERR_VALUE_TOO_LARGE            = MUK_ERR_VALUE_TOO_LARGE,
#endif
    MPI_ERR_WIN                        = MUK_ERR_WIN,
    MPI_T_ERR_CANNOT_INIT              = MUK_T_ERR_CANNOT_INIT,
#if 0
    MPI_T_ERR_NOT_ACCESSIBLE           = MUK_T_ERR_NOT_ACCESSIBLE,
#endif
    MPI_T_ERR_NOT_INITIALIZED          = MUK_T_ERR_NOT_INITIALIZED,
#if MPI_VERSION >= 4
    MPI_T_ERR_NOT_SUPPORTED            = MUK_T_ERR_NOT_SUPPORTED,
#endif
    MPI_T_ERR_MEMORY                   = MUK_T_ERR_MEMORY,
    MPI_T_ERR_INVALID                  = MUK_T_ERR_INVALID,
    MPI_T_ERR_INVALID_INDEX            = MUK_T_ERR_INVALID_INDEX,
    MPI_T_ERR_INVALID_ITEM             = MUK_T_ERR_INVALID_ITEM,
    MPI_T_ERR_INVALID_SESSION          = MUK_T_ERR_INVALID_SESSION,
    MPI_T_ERR_INVALID_HANDLE           = MUK_T_ERR_INVALID_HANDLE,
    MPI_T_ERR_INVALID_NAME             = MUK_T_ERR_INVALID_NAME,
    MPI_T_ERR_OUT_OF_HANDLES           = MUK_T_ERR_OUT_OF_HANDLES,
    MPI_T_ERR_OUT_OF_SESSIONS          = MUK_T_ERR_OUT_OF_SESSIONS,
    MPI_T_ERR_CVAR_SET_NOT_NOW         = MUK_T_ERR_CVAR_SET_NOT_NOW,
    MPI_T_ERR_CVAR_SET_NEVER           = MUK_T_ERR_CVAR_SET_NEVER,
    MPI_T_ERR_PVAR_NO_WRITE            = MUK_T_ERR_PVAR_NO_WRITE,
    MPI_T_ERR_PVAR_NO_STARTSTOP        = MUK_T_ERR_PVAR_NO_STARTSTOP,
    MPI_T_ERR_PVAR_NO_ATOMIC           = MUK_T_ERR_PVAR_NO_ATOMIC,
    MPI_ERR_LASTCODE                   = MUK_ERR_LASTCODE
};

// Buffer Address Constants
MUK_EXTERN void * MPI_BOTTOM;
MUK_EXTERN void * MPI_IN_PLACE;

// Assorted Constants
enum {
    // these should be different
    MPI_PROC_NULL   = MUK_PROC_NULL,
    MPI_ANY_SOURCE  = MUK_ANY_SOURCE,
    MPI_ROOT        = MUK_ROOT
};
enum {
    MPI_ANY_TAG     = MUK_ANY_TAG
};
enum {
    MPI_UNDEFINED   = MUK_UNDEFINED
};
enum {
    MPI_BSEND_OVERHEAD  = MUK_BSEND_OVERHEAD
};
enum {
    MPI_KEYVAL_INVALID  = MUK_KEYVAL_INVALID
};
enum {
    MPI_LOCK_EXCLUSIVE  = MUK_LOCK_EXCLUSIVE,
    MPI_LOCK_SHARED     = MUK_LOCK_SHARED
};

// No Process Message Handle
MUK_EXTERN MPI_Message MPI_MESSAGE_NO_PROC;

#if 0
//Fortran status array size and reserved index values (C only)
enum {
    MPI_F_STATUS_SIZE,
    MPI_F_SOURCE,
    MPI_F_TAG,
    MPI_F_ERROR,
    MPI_ADDRESS_KIND,
    MPI_COUNT_KIND,
    MPI_INTEGER_KIND,
    MPI_OFFSET_KIND
};
#endif

// Error-handling specifiers
MUK_EXTERN MPI_Errhandler MPI_ERRORS_ARE_FATAL;
#if MPI_VERSION >= 4
MUK_EXTERN MPI_Errhandler MPI_ERRORS_ABORT;
#endif
MUK_EXTERN MPI_Errhandler MPI_ERRORS_RETURN;

// Named Predefined Datatypes
MUK_EXTERN MPI_Datatype MPI_CHAR;
MUK_EXTERN MPI_Datatype MPI_SHORT;
MUK_EXTERN MPI_Datatype MPI_INT;
MUK_EXTERN MPI_Datatype MPI_LONG;
MUK_EXTERN MPI_Datatype MPI_LONG_LONG_INT;
MUK_EXTERN MPI_Datatype MPI_LONG_LONG;
MUK_EXTERN MPI_Datatype MPI_SIGNED_CHAR;
MUK_EXTERN MPI_Datatype MPI_UNSIGNED_CHAR;
MUK_EXTERN MPI_Datatype MPI_UNSIGNED_SHORT;
MUK_EXTERN MPI_Datatype MPI_UNSIGNED;
MUK_EXTERN MPI_Datatype MPI_UNSIGNED_LONG;
MUK_EXTERN MPI_Datatype MPI_UNSIGNED_LONG_LONG;
MUK_EXTERN MPI_Datatype MPI_FLOAT;
MUK_EXTERN MPI_Datatype MPI_DOUBLE;
MUK_EXTERN MPI_Datatype MPI_LONG_DOUBLE;
MUK_EXTERN MPI_Datatype MPI_WCHAR;
MUK_EXTERN MPI_Datatype MPI_C_BOOL;

MUK_EXTERN MPI_Datatype MPI_INT8_T;
MUK_EXTERN MPI_Datatype MPI_INT16_T;
MUK_EXTERN MPI_Datatype MPI_INT32_T;
MUK_EXTERN MPI_Datatype MPI_INT64_T;
MUK_EXTERN MPI_Datatype MPI_UINT8_T;
MUK_EXTERN MPI_Datatype MPI_UINT16_T;
MUK_EXTERN MPI_Datatype MPI_UINT32_T;
MUK_EXTERN MPI_Datatype MPI_UINT64_T;
MUK_EXTERN MPI_Datatype MPI_AINT;
MUK_EXTERN MPI_Datatype MPI_COUNT;
MUK_EXTERN MPI_Datatype MPI_OFFSET;
MUK_EXTERN MPI_Datatype MPI_C_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_C_FLOAT_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_C_DOUBLE_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_C_LONG_DOUBLE_COMPLEX;

MUK_EXTERN MPI_Datatype MPI_BYTE;
MUK_EXTERN MPI_Datatype MPI_PACKED;

MUK_EXTERN MPI_Datatype MPI_INTEGER;
MUK_EXTERN MPI_Datatype MPI_REAL;
MUK_EXTERN MPI_Datatype MPI_DOUBLE_PRECISION;
MUK_EXTERN MPI_Datatype MPI_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_LOGICAL;
MUK_EXTERN MPI_Datatype MPI_CHARACTER;

MUK_EXTERN MPI_Datatype MPI_CXX_BOOL;
MUK_EXTERN MPI_Datatype MPI_CXX_FLOAT_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_CXX_DOUBLE_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_CXX_LONG_DOUBLE_COMPLEX;

#if 0
MUK_EXTERN MPI_Datatype MPI_DOUBLE_COMPLEX;
MUK_EXTERN MPI_Datatype MPI_INTEGER1;
MUK_EXTERN MPI_Datatype MPI_INTEGER2;
MUK_EXTERN MPI_Datatype MPI_INTEGER4;
MUK_EXTERN MPI_Datatype MPI_INTEGER8;
MUK_EXTERN MPI_Datatype MPI_INTEGER16;
MUK_EXTERN MPI_Datatype MPI_REAL2;
MUK_EXTERN MPI_Datatype MPI_REAL4;
MUK_EXTERN MPI_Datatype MPI_REAL8;
MUK_EXTERN MPI_Datatype MPI_REAL16;
MUK_EXTERN MPI_Datatype MPI_COMPLEX4;
MUK_EXTERN MPI_Datatype MPI_COMPLEX8;
MUK_EXTERN MPI_Datatype MPI_COMPLEX16;
MUK_EXTERN MPI_Datatype MPI_COMPLEX32;
#endif

MUK_EXTERN MPI_Datatype MPI_FLOAT_INT;
MUK_EXTERN MPI_Datatype MPI_DOUBLE_INT;
MUK_EXTERN MPI_Datatype MPI_LONG_INT;
MUK_EXTERN MPI_Datatype MPI_2INT;
MUK_EXTERN MPI_Datatype MPI_SHORT_INT;
MUK_EXTERN MPI_Datatype MPI_LONG_DOUBLE_INT;

MUK_EXTERN MPI_Datatype MPI_2REAL;
MUK_EXTERN MPI_Datatype MPI_2DOUBLE_PRECISION;
MUK_EXTERN MPI_Datatype MPI_2INTEGER;

// Reserved communicators
MUK_EXTERN MPI_Comm MPI_COMM_WORLD;
MUK_EXTERN MPI_Comm MPI_COMM_SELF;

// Communicator split type constants
enum {
    MPI_COMM_TYPE_SHARED        = MUK_COMM_TYPE_SHARED,
#if MPI_VERSION >= 4
    MPI_COMM_TYPE_HW_UNGUIDED   = MUK_COMM_TYPE_HW_UNGUIDED,
    MPI_COMM_TYPE_HW_GUIDED     = MUK_COMM_TYPE_HW_GUIDED
#endif
};

// Results of communicator and group comparisons
enum {
    MPI_IDENT       = MUK_IDENT,
    MPI_CONGRUENT   = MUK_CONGRUENT,
    MPI_SIMILAR     = MUK_SIMILAR,
    MPI_UNEQUAL     = MUK_UNEQUAL   
};

// Environmental inquiry info key
MUK_EXTERN MPI_Info MPI_INFO_ENV;

// Collective Operations
MUK_EXTERN MPI_Op MPI_MAX;
MUK_EXTERN MPI_Op MPI_MIN;
MUK_EXTERN MPI_Op MPI_SUM;
MUK_EXTERN MPI_Op MPI_PROD;
MUK_EXTERN MPI_Op MPI_LAND;
MUK_EXTERN MPI_Op MPI_BAND;
MUK_EXTERN MPI_Op MPI_LOR;
MUK_EXTERN MPI_Op MPI_BOR;
MUK_EXTERN MPI_Op MPI_LXOR;
MUK_EXTERN MPI_Op MPI_BXOR;
MUK_EXTERN MPI_Op MPI_MAXLOC;
MUK_EXTERN MPI_Op MPI_MINLOC;
MUK_EXTERN MPI_Op MPI_REPLACE;
MUK_EXTERN MPI_Op MPI_NO_OP;

// Null Handles
MUK_EXTERN MPI_Group MPI_GROUP_NULL;
MUK_EXTERN MPI_Comm MPI_COMM_NULL;
MUK_EXTERN MPI_Datatype MPI_DATATYPE_NULL;
MUK_EXTERN MPI_Request MPI_REQUEST_NULL;
MUK_EXTERN MPI_Op MPI_OP_NULL;
MUK_EXTERN MPI_Errhandler MPI_ERRHANDLER_NULL;
MUK_EXTERN MPI_File MPI_FILE_NULL;
MUK_EXTERN MPI_Info MPI_INFO_NULL;
#if MPI_VERSION >= 4
MUK_EXTERN MPI_Session MPI_SESSION_NULL;
#endif
MUK_EXTERN MPI_Win MPI_WIN_NULL;
MUK_EXTERN MPI_Message MPI_MESSAGE_NULL;

// Empty group
MUK_EXTERN MPI_Group MPI_GROUP_EMPTY;

// Topologies
enum {
    MPI_GRAPH,
    MPI_CART,
    MPI_DIST_GRAPH
};

// Predefined functions
// TODO
// Deprecated predefined functions
// TODO

enum {
    // Environmental inquiry keys
    MPI_TAG_UB                      = MUK_TAG_UB,
    MPI_IO                          = MUK_IO,
    MPI_HOST                        = MUK_HOST,
    MPI_WTIME_IS_GLOBAL             = MUK_WTIME_IS_GLOBAL,
    // Predefined Attribute Keys
    MPI_APPNUM                      = MUK_APPNUM,
    MPI_LASTUSEDCODE                = MUK_LASTUSEDCODE,
    MPI_UNIVERSE_SIZE               = MUK_UNIVERSE_SIZE,
    MPI_WIN_BASE                    = MUK_WIN_BASE,
    MPI_WIN_DISP_UNIT               = MUK_WIN_DISP_UNIT,
    MPI_WIN_SIZE                    = MUK_WIN_SIZE,
    MPI_WIN_CREATE_FLAVOR           = MUK_WIN_CREATE_FLAVOR,
    MPI_WIN_MODEL                   = MUK_WIN_MODEL
};

// MPI Window Create Flavors
enum {
    MPI_WIN_FLAVOR_CREATE   = MUK_WIN_FLAVOR_CREATE,
    MPI_WIN_FLAVOR_ALLOCATE = MUK_WIN_FLAVOR_ALLOCATE,
    MPI_WIN_FLAVOR_DYNAMIC  = MUK_WIN_FLAVOR_DYNAMIC,
    MPI_WIN_FLAVOR_SHARED   = MUK_WIN_FLAVOR_SHARED
};

// MPI Window Models
enum {
    MPI_WIN_SEPARATE = MUK_WIN_SEPARATE,
    MPI_WIN_UNIFIED  = MUK_WIN_UNIFIED
};
      
// Mode Constants
enum {
    MPI_MODE_APPEND          = MUK_MODE_APPEND,
    MPI_MODE_CREATE          = MUK_MODE_CREATE,
    MPI_MODE_DELETE_ON_CLOSE = MUK_MODE_DELETE_ON_CLOSE,
    MPI_MODE_EXCL            = MUK_MODE_EXCL,
    MPI_MODE_NOCHECK         = MUK_MODE_NOCHECK,
    MPI_MODE_NOPRECEDE       = MUK_MODE_NOPRECEDE,
    MPI_MODE_NOPUT           = MUK_MODE_NOPUT,
    MPI_MODE_NOSTORE         = MUK_MODE_NOSTORE,
    MPI_MODE_NOSUCCEED       = MUK_MODE_NOSUCCEED,
    MPI_MODE_RDONLY          = MUK_MODE_RDONLY,
    MPI_MODE_RDWR            = MUK_MODE_RDWR,
    MPI_MODE_SEQUENTIAL      = MUK_MODE_SEQUENTIAL,
    MPI_MODE_UNIQUE_OPEN     = MUK_MODE_UNIQUE_OPEN,
    MPI_MODE_WRONLY          = MUK_MODE_WRONLY
};

// Datatype Decoding Constants
enum {
    MPI_COMBINER_CONTIGUOUS     = MUK_COMBINER_CONTIGUOUS,
    MPI_COMBINER_DARRAY         = MUK_COMBINER_DARRAY,
    MPI_COMBINER_DUP            = MUK_COMBINER_DUP,
    MPI_COMBINER_F90_COMPLEX    = MUK_COMBINER_F90_COMPLEX,
    MPI_COMBINER_F90_INTEGER    = MUK_COMBINER_F90_INTEGER,
    MPI_COMBINER_F90_REAL       = MUK_COMBINER_F90_REAL,
    MPI_COMBINER_HINDEXED       = MUK_COMBINER_HINDEXED,
    MPI_COMBINER_HVECTOR        = MUK_COMBINER_HVECTOR,
    MPI_COMBINER_INDEXED_BLOCK  = MUK_COMBINER_INDEXED_BLOCK,
    MPI_COMBINER_HINDEXED_BLOCK = MUK_COMBINER_HINDEXED_BLOCK,
    MPI_COMBINER_INDEXED        = MUK_COMBINER_INDEXED,
    MPI_COMBINER_NAMED          = MUK_COMBINER_NAMED,
    MPI_COMBINER_RESIZED        = MUK_COMBINER_RESIZED,
    MPI_COMBINER_STRUCT         = MUK_COMBINER_STRUCT,
    MPI_COMBINER_SUBARRAY       = MUK_COMBINER_SUBARRAY,
    MPI_COMBINER_VECTOR         = MUK_COMBINER_VECTOR
};

// Threads Constants
enum {
    MPI_THREAD_FUNNELED   = MUK_THREAD_FUNNELED,
    MPI_THREAD_MULTIPLE   = MUK_THREAD_MULTIPLE,
    MPI_THREAD_SERIALIZED = MUK_THREAD_SERIALIZED,
    MPI_THREAD_SINGLE     = MUK_THREAD_SINGLE
};

enum {
    // File Operation Constants, Part 1
    MPI_DISPLACEMENT_CURRENT = MUK_DISPLACEMENT_CURRENT,
    // File Operation Constants, Part 2
    MPI_DISTRIBUTE_BLOCK     = MUK_DISTRIBUTE_BLOCK,
    MPI_DISTRIBUTE_CYCLIC    = MUK_DISTRIBUTE_CYCLIC,
    MPI_DISTRIBUTE_DFLT_DARG = MUK_DISTRIBUTE_DFLT_DARG,
    MPI_DISTRIBUTE_NONE      = MUK_DISTRIBUTE_NONE,
    MPI_ORDER_C              = MUK_ORDER_C,
    MPI_ORDER_FORTRAN        = MUK_ORDER_FORTRAN,
    MPI_SEEK_CUR             = MUK_SEEK_CUR,
    MPI_SEEK_END             = MUK_SEEK_END,
    MPI_SEEK_SET             = MUK_SEEK_SET
};

// F90 Datatype Matching Constants
enum {
    MPI_TYPECLASS_COMPLEX = MUK_TYPECLASS_COMPLEX,
    MPI_TYPECLASS_INTEGER = MUK_TYPECLASS_INTEGER,
    MPI_TYPECLASS_REAL    = MUK_TYPECLASS_REAL
};

// Constants Specifying Empty or Ignored Input
MUK_EXTERN char *** MPI_ARGVS_NULL;
MUK_EXTERN char ** MPI_ARGV_NULL;
MUK_EXTERN int * MPI_ERRCODES_IGNORE;
MUK_EXTERN MPI_Status * MPI_STATUSES_IGNORE;
MUK_EXTERN MPI_Status * MPI_STATUS_IGNORE;
#if 0 //ndef MPICH
MUK_EXTERN int * MPI_UNWEIGHTED;
MUK_EXTERN int * MPI_WEIGHTS_EMPTY;
#endif

#endif
