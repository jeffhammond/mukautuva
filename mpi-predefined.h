#ifndef MUK_MPI_PREDEFINED_H
#define MUK_MPI_PREDEFINED_H

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
#define MPI_ERRHANDLER_NULL (MPI_Errhandler)0
#define MPI_ERRORS_ARE_FATAL (MPI_Errhandler)1
#define MPI_ERRORS_RETURN (MPI_Errhandler) 2
#define MPI_ERRORS_ABORT (MPI_Errhandler) 3

// Named Predefined Datatypes
#define MPI_DATATYPE_NULL ((MPI_Datatype)MUK_DATATYPE_NULL)
#define MPI_CHAR ((MPI_Datatype)MUK_CHAR)
#define MPI_SHORT ((MPI_Datatype)MUK_SHORT)
#define MPI_INT ((MPI_Datatype)MUK_INT)
#define MPI_LONG ((MPI_Datatype)MUK_LONG)
#define MPI_LONG_LONG_INT ((MPI_Datatype)MUK_LONG_LONG_INT)
#define MPI_LONG_LONG ((MPI_Datatype)MUK_LONG_LONG)
#define MPI_SIGNED_CHAR ((MPI_Datatype)MUK_SIGNED_CHAR)
#define MPI_UNSIGNED_CHAR ((MPI_Datatype)MUK_UNSIGNED_CHAR)
#define MPI_UNSIGNED_SHORT ((MPI_Datatype)MUK_UNSIGNED_SHORT)
#define MPI_UNSIGNED ((MPI_Datatype)MUK_UNSIGNED)
#define MPI_UNSIGNED_LONG ((MPI_Datatype)MUK_UNSIGNED_LONG)
#define MPI_UNSIGNED_LONG_LONG ((MPI_Datatype)MUK_UNSIGNED_LONG_LONG)
#define MPI_FLOAT ((MPI_Datatype)MUK_FLOAT)
#define MPI_DOUBLE ((MPI_Datatype)MUK_DOUBLE)
#define MPI_LONG_DOUBLE ((MPI_Datatype)MUK_LONG_DOUBLE)
#define MPI_WCHAR ((MPI_Datatype)MUK_WCHAR)
#define MPI_C_BOOL ((MPI_Datatype)MUK_C_BOOL)
#define MPI_INT8_T ((MPI_Datatype)MUK_INT8_T)
#define MPI_INT16_T ((MPI_Datatype)MUK_INT16_T)
#define MPI_INT32_T ((MPI_Datatype)MUK_INT32_T)
#define MPI_INT64_T ((MPI_Datatype)MUK_INT64_T)
#define MPI_UINT8_T ((MPI_Datatype)MUK_UINT8_T)
#define MPI_UINT16_T ((MPI_Datatype)MUK_UINT16_T)
#define MPI_UINT32_T ((MPI_Datatype)MUK_UINT32_T)
#define MPI_UINT64_T ((MPI_Datatype)MUK_UINT64_T)
#define MPI_AINT ((MPI_Datatype)MUK_AINT)
#define MPI_COUNT ((MPI_Datatype)MUK_COUNT)
#define MPI_OFFSET ((MPI_Datatype)MUK_OFFSET)
#define MPI_C_COMPLEX ((MPI_Datatype)MUK_C_COMPLEX)
#define MPI_C_FLOAT_COMPLEX ((MPI_Datatype)MUK_C_FLOAT_COMPLEX)
#define MPI_C_DOUBLE_COMPLEX ((MPI_Datatype)MUK_C_DOUBLE_COMPLEX)
#define MPI_C_LONG_DOUBLE_COMPLEX ((MPI_Datatype)MUK_C_LONG_DOUBLE_COMPLEX)
#define MPI_BYTE ((MPI_Datatype)MUK_BYTE)
#define MPI_PACKED ((MPI_Datatype)MUK_PACKED)
#define MPI_CXX_BOOL ((MPI_Datatype)MUK_CXX_BOOL)
#define MPI_CXX_FLOAT_COMPLEX ((MPI_Datatype)MUK_CXX_FLOAT_COMPLEX)
#define MPI_CXX_DOUBLE_COMPLEX ((MPI_Datatype)MUK_CXX_DOUBLE_COMPLEX)
#define MPI_CXX_LONG_DOUBLE_COMPLEX ((MPI_Datatype)MUK_CXX_LONG_DOUBLE_COMPLEX)
#define MPI_INTEGER ((MPI_Datatype)MUK_INTEGER)
#define MPI_REAL ((MPI_Datatype)MUK_REAL)
#define MPI_DOUBLE_PRECISION ((MPI_Datatype)MUK_DOUBLE_PRECISION)
#define MPI_COMPLEX ((MPI_Datatype)MUK_COMPLEX)
#define MPI_LOGICAL ((MPI_Datatype)MUK_LOGICAL)
#define MPI_CHARACTER ((MPI_Datatype)MUK_CHARACTER)
#define MPI_DOUBLE_COMPLEX ((MPI_Datatype)MUK_DOUBLE_COMPLEX)
#define MPI_INTEGER1 ((MPI_Datatype)MUK_INTEGER1)
#define MPI_INTEGER2 ((MPI_Datatype)MUK_INTEGER2)
#define MPI_INTEGER4 ((MPI_Datatype)MUK_INTEGER4)
#define MPI_INTEGER8 ((MPI_Datatype)MUK_INTEGER8)
#define MPI_INTEGER16 ((MPI_Datatype)MUK_INTEGER16)
#define MPI_REAL2 ((MPI_Datatype)MUK_REAL2)
#define MPI_REAL4 ((MPI_Datatype)MUK_REAL4)
#define MPI_REAL8 ((MPI_Datatype)MUK_REAL8)
#define MPI_REAL16 ((MPI_Datatype)MUK_REAL16)
#define MPI_COMPLEX4 ((MPI_Datatype)MUK_COMPLEX4)
#define MPI_COMPLEX8 ((MPI_Datatype)MUK_COMPLEX8)
#define MPI_COMPLEX16 ((MPI_Datatype)MUK_COMPLEX16)
#define MPI_COMPLEX32 ((MPI_Datatype)MUK_COMPLEX32)
#define MPI_FLOAT_INT ((MPI_Datatype)MUK_FLOAT_INT)
#define MPI_DOUBLE_INT ((MPI_Datatype)MUK_DOUBLE_INT)
#define MPI_LONG_INT ((MPI_Datatype)MUK_LONG_INT)
#define MPI_2INT ((MPI_Datatype)MUK_2INT)
#define MPI_SHORT_INT ((MPI_Datatype)MUK_SHORT_INT)
#define MPI_LONG_DOUBLE_INT ((MPI_Datatype)MUK_LONG_DOUBLE_INT)
#define MPI_2REAL ((MPI_Datatype)MUK_2REAL)
#define MPI_2DOUBLE_PRECISION ((MPI_Datatype)MUK_2DOUBLE_PRECISION)
#define MPI_2INTEGER ((MPI_Datatype)MUK_2INTEGER)
#define MPI_LB ((MPI_Datatype)MUK_LB)
#define MPI_UB ((MPI_Datatype)MUK_UB)

// Reserved communicators
#define MPI_COMM_NULL  ((MPI_Comm)MUK_COMM_NULL)
#define MPI_COMM_SELF  ((MPI_Comm)MUK_COMM_SELF)
#define MPI_COMM_WORLD ((MPI_Comm)MUK_COMM_WORLD)

// Reserved groups
#define MPI_GROUP_NULL  ((MPI_Group)MUK_GROUP_NULL)
#define MPI_GROUP_EMPTY ((MPI_Group)MUK_GROUP_EMPTY)

// Communicator split type constants
enum {
    MPI_COMM_TYPE_SHARED        = MUK_COMM_TYPE_SHARED,
#if 1 //MPI_VERSION >= 4
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
#define MPI_INFO_NULL (MPI_Info)MUK_INFO_NULL
#define MPI_INFO_ENV  (MPI_Info)MUK_INFO_ENV

// Collective Operations
#define MPI_OP_NULL ((MPI_Op)MUK_OP_NULL)
#define MPI_MAX ((MPI_Op)MUK_MAX)
#define MPI_MIN ((MPI_Op)MUK_MIN)
#define MPI_SUM ((MPI_Op)MUK_SUM)
#define MPI_PROD ((MPI_Op)MUK_PROD)
#define MPI_LAND ((MPI_Op)MUK_LAND)
#define MPI_BAND ((MPI_Op)MUK_BAND)
#define MPI_LOR ((MPI_Op)MUK_LOR)
#define MPI_BOR ((MPI_Op)MUK_BOR)
#define MPI_LXOR ((MPI_Op)MUK_LXOR)
#define MPI_BXOR ((MPI_Op)MUK_BXOR)
#define MPI_MAXLOC ((MPI_Op)MUK_MAXLOC)
#define MPI_MINLOC ((MPI_Op)MUK_MINLOC)
#define MPI_REPLACE ((MPI_Op)MUK_REPLACE)
#define MPI_NO_OP ((MPI_Op)MUK_NO_OP)

// Predefined message handles
#define MPI_MESSAGE_NULL ((MPI_Message)MUK_MESSAGE_NULL)
#define MPI_MESSAGE_NO_PROC ((MPI_Message)MUK_MESSAGE_NO_PROC)

// Null Handles
#define MPI_REQUEST_NULL ((MPI_Request)MUK_REQUEST_NULL)
#define MPI_FILE_NULL ((MPI_File)MUK_FILE_NULL)
#define MPI_WIN_NULL ((MPI_Win)MUK_WIN_NULL)
#if 1 //MPI_VERSION >= 4
#define MPI_SESSION_NULL ((MPI_Session)MUK_SESSION_NULL)
#endif

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
    // I/O
    MPI_MODE_APPEND          = MUK_MODE_APPEND,
    MPI_MODE_CREATE          = MUK_MODE_CREATE,
    MPI_MODE_DELETE_ON_CLOSE = MUK_MODE_DELETE_ON_CLOSE,
    MPI_MODE_EXCL            = MUK_MODE_EXCL,
    MPI_MODE_RDONLY          = MUK_MODE_RDONLY,
    MPI_MODE_RDWR            = MUK_MODE_RDWR,
    MPI_MODE_SEQUENTIAL      = MUK_MODE_SEQUENTIAL,
    MPI_MODE_UNIQUE_OPEN     = MUK_MODE_UNIQUE_OPEN,
    MPI_MODE_WRONLY          = MUK_MODE_WRONLY,
    // RMA
    MPI_MODE_NOCHECK         = MUK_MODE_NOCHECK,
    MPI_MODE_NOPRECEDE       = MUK_MODE_NOPRECEDE,
    MPI_MODE_NOPUT           = MUK_MODE_NOPUT,
    MPI_MODE_NOSTORE         = MUK_MODE_NOSTORE,
    MPI_MODE_NOSUCCEED       = MUK_MODE_NOSUCCEED,
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

// Buffer Address Constants
#define MPI_BOTTOM   MUK_BOTTOM
#define MPI_IN_PLACE MUK_IN_PLACE

// Constants Specifying Empty or Ignored Input
#define MPI_ARGV_NULL       MUK_ARGV_NULL
#define MPI_ARGVS_NULL      MUK_ARGVS_NULL
#define MPI_ERRCODES_IGNORE MUK_ERRCODES_IGNORE
#define MPI_STATUSES_IGNORE MUK_STATUSES_IGNORE
#define MPI_STATUS_IGNORE   MUK_STATUS_IGNORE
#define MPI_UNWEIGHTED      MUK_UNWEIGHTED
#define MPI_WEIGHTS_EMPTY   MUK_WEIGHTS_EMPTY

#define MPI_NULL_COPY_FN        ((MPI_Copy_function*)NULL)
#define MPI_DUP_FN              ((MPI_Copy_function*)NULL)
#define MPI_NULL_DELETE_FN      ((MPI_Delete_function*)NULL)
#define MPI_COMM_NULL_COPY_FN   ((MPI_Comm_copy_attr_function*)NULL)
#define MPI_COMM_DUP_FN         ((MPI_Comm_copy_attr_function*)NULL)
#define MPI_COMM_NULL_DELETE_FN ((MPI_Comm_delete_attr_function*)NULL)
#define MPI_TYPE_NULL_COPY_FN   ((MPI_Type_copy_attr_function*)NULL)
#define MPI_TYPE_NULL_COPY_FN   ((MPI_Type_copy_attr_function*)NULL)
#define MPI_TYPE_NULL_DELETE_FN ((MPI_Type_delete_attr_function*)NULL)
#define MPI_WIN_NULL_COPY_FN    ((MPI_Win_copy_attr_function*)NULL)
#define MPI_WIN_NULL_COPY_FN    ((MPI_Win_copy_attr_function*)NULL)
#define MPI_WIN_NULL_DELETE_FN  ((MPI_Win_delete_attr_function*)NULL)

#endif
