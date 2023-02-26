#ifndef MUK_PREDEFINED_H
#define MUK_PREDEFINED_H

// handle this better
typedef struct MUK_ABI_Comm * MUK_Comm;
typedef struct MUK_ABI_Datatype * MUK_Datatype;
typedef struct MUK_ABI_Errhandler * MUK_Errhandler;
typedef struct MUK_ABI_File * MUK_File;
typedef struct MUK_ABI_Group * MUK_Group;
typedef struct MUK_ABI_Info * MUK_Info;
typedef struct MUK_ABI_Message * MUK_Message;
typedef struct MUK_ABI_Op * MUK_Op;
typedef struct MUK_ABI_Request * MUK_Request;
typedef struct MUK_ABI_Session * MUK_Session;
typedef struct MUK_ABI_Win * MUK_Win;

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

#if FORTRAN
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
#endif

// Error-handling specifiers
#define MUK_ERRHANDLER_NULL (MUK_Errhandler)0
#define MUK_ERRORS_ARE_FATAL (MUK_Errhandler)1
#define MUK_ERRORS_RETURN (MUK_Errhandler) 2
#define MUK_ERRORS_ABORT (MUK_Errhandler) 3

// Named Predefined Datatypes
#define MUK_DATATYPE_NULL ((MUK_Datatype)0)
#define MUK_CHAR ((MUK_Datatype)1)
#define MUK_SHORT ((MUK_Datatype)2)
#define MUK_INT ((MUK_Datatype)3)
#define MUK_LONG ((MUK_Datatype)4)
#define MUK_LONG_LONG_INT ((MUK_Datatype)5)
#define MUK_LONG_LONG ((MUK_Datatype)6)
#define MUK_SIGNED_CHAR ((MUK_Datatype)7)
#define MUK_UNSIGNED_CHAR ((MUK_Datatype)8)
#define MUK_UNSIGNED_SHORT ((MUK_Datatype)9)
#define MUK_UNSIGNED ((MUK_Datatype)10)
#define MUK_UNSIGNED_LONG ((MUK_Datatype)11)
#define MUK_UNSIGNED_LONG_LONG ((MUK_Datatype)12)
#define MUK_FLOAT ((MUK_Datatype)13)
#define MUK_DOUBLE ((MUK_Datatype)14)
#define MUK_LONG_DOUBLE ((MUK_Datatype)15)
#define MUK_WCHAR ((MUK_Datatype)16)
#define MUK_C_BOOL ((MUK_Datatype)17)
#define MUK_INT8_T ((MUK_Datatype)18)
#define MUK_INT16_T ((MUK_Datatype)19)
#define MUK_INT32_T ((MUK_Datatype)20)
#define MUK_INT64_T ((MUK_Datatype)21)
#define MUK_UINT8_T ((MUK_Datatype)22)
#define MUK_UINT16_T ((MUK_Datatype)23)
#define MUK_UINT32_T ((MUK_Datatype)24)
#define MUK_UINT64_T ((MUK_Datatype)25)
#define MUK_AINT ((MUK_Datatype)26)
#define MUK_COUNT ((MUK_Datatype)27)
#define MUK_OFFSET ((MUK_Datatype)28)
#define MUK_C_COMPLEX ((MUK_Datatype)29)
#define MUK_C_FLOAT_COMPLEX ((MUK_Datatype)30)
#define MUK_C_DOUBLE_COMPLEX ((MUK_Datatype)31)
#define MUK_C_LONG_DOUBLE_COMPLEX ((MUK_Datatype)32)
#define MUK_BYTE ((MUK_Datatype)33)
#define MUK_PACKED ((MUK_Datatype)34)
#define MUK_CXX_BOOL ((MUK_Datatype)35)
#define MUK_CXX_FLOAT_COMPLEX ((MUK_Datatype)36)
#define MUK_CXX_DOUBLE_COMPLEX ((MUK_Datatype)37)
#define MUK_CXX_LONG_DOUBLE_COMPLEX ((MUK_Datatype)38)
#define MUK_INTEGER ((MUK_Datatype)39)
#define MUK_REAL ((MUK_Datatype)40)
#define MUK_DOUBLE_PRECISION ((MUK_Datatype)41)
#define MUK_COMPLEX ((MUK_Datatype)42)
#define MUK_LOGICAL ((MUK_Datatype)43)
#define MUK_CHARACTER ((MUK_Datatype)44)
#define MUK_DOUBLE_COMPLEX ((MUK_Datatype)45)
#define MUK_INTEGER1 ((MUK_Datatype)46)
#define MUK_INTEGER2 ((MUK_Datatype)47)
#define MUK_INTEGER4 ((MUK_Datatype)48)
#define MUK_INTEGER8 ((MUK_Datatype)49)
#define MUK_INTEGER16 ((MUK_Datatype)50)
#define MUK_REAL2 ((MUK_Datatype)51)
#define MUK_REAL4 ((MUK_Datatype)52)
#define MUK_REAL8 ((MUK_Datatype)53)
#define MUK_REAL16 ((MUK_Datatype)54)
#define MUK_COMPLEX4 ((MUK_Datatype)55)
#define MUK_COMPLEX8 ((MUK_Datatype)56)
#define MUK_COMPLEX16 ((MUK_Datatype)57)
#define MUK_COMPLEX32 ((MUK_Datatype)58)
#define MUK_FLOAT_INT ((MUK_Datatype)59)
#define MUK_DOUBLE_INT ((MUK_Datatype)60)
#define MUK_LONG_INT ((MUK_Datatype)61)
#define MUK_2INT ((MUK_Datatype)62)
#define MUK_SHORT_INT ((MUK_Datatype)63)
#define MUK_LONG_DOUBLE_INT ((MUK_Datatype)64)
#define MUK_2REAL ((MUK_Datatype)65)
#define MUK_2DOUBLE_PRECISION ((MUK_Datatype)66)
#define MUK_2INTEGER ((MUK_Datatype)67)
#define MUK_LB ((MUK_Datatype)68)
#define MUK_UB ((MUK_Datatype)69)

// Reserved communicators
#define MUK_COMM_NULL  ((MUK_Comm)0)
#define MUK_COMM_SELF  ((MUK_Comm)1)
#define MUK_COMM_WORLD ((MUK_Comm)2)

// Reserved groups
#define MUK_GROUP_NULL  ((MUK_Group)0)
#define MUK_GROUP_EMPTY ((MUK_Group)1)

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

// Environmental inquiry info key
#define MUK_INFO_NULL (MUK_Info)0
#define MUK_INFO_ENV  (MUK_Info)1

// Collective Operations
#define MUK_OP_NULL ((MUK_Op)0)
#define MUK_MAX ((MUK_Op)1)
#define MUK_MIN ((MUK_Op)2)
#define MUK_SUM ((MUK_Op)3)
#define MUK_PROD ((MUK_Op)4)
#define MUK_LAND ((MUK_Op)5)
#define MUK_BAND ((MUK_Op)6)
#define MUK_LOR ((MUK_Op)7)
#define MUK_BOR ((MUK_Op)8)
#define MUK_LXOR ((MUK_Op)9)
#define MUK_BXOR ((MUK_Op)10)
#define MUK_MAXLOC ((MUK_Op)11)
#define MUK_MINLOC ((MUK_Op)12)
#define MUK_REPLACE ((MUK_Op)13)
#define MUK_NO_OP ((MUK_Op)14)

// Predefined message handles
#define MUK_MESSAGE_NULL (MUK_Message)0
#define MUK_MESSAGE_NO_PROC ((MUK_Message)1)

// Null Handles
#define MUK_REQUEST_NULL (MUK_Request)0
#define MUK_FILE_NULL (MUK_File)0
#define MUK_WIN_NULL (MUK_Win)0
#if 1 //MUK_VERSION >= 4
#define MUK_SESSION_NULL (MUK_Session)0
#endif

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
    MUK_DISPLACEMENT_CURRENT = -2,
    // File Operation Constants, Part 2
    // use MPICH values
    MUK_DISTRIBUTE_BLOCK  = 121,
    MUK_DISTRIBUTE_CYCLIC = 122,
    MUK_DISTRIBUTE_NONE   = 123,
    // This one has to be negative
    MUK_DISTRIBUTE_DFLT_DARG = -1,
    // Values are descriptive
    MUK_ORDER_C        = 4321,
    MUK_ORDER_FORTRAN  = 1234,
    // use OMPI values
    MUK_SEEK_CUR = 600,
    MUK_SEEK_END = 602,
    MUK_SEEK_SET = 604
};

// F90 Datatype Matching Constants
enum {
    MUK_TYPECLASS_COMPLEX,
    MUK_TYPECLASS_INTEGER,
    MUK_TYPECLASS_REAL
};

// Buffer Address Constants
// MPICH, OMPI and MUK agree
#define MUK_BOTTOM   ((void *)0)
// OMPI and MUK agree.  MPICH is -1
#define MUK_IN_PLACE ((void *)1)

// Constants Specifying Empty or Ignored Input
// These match MPICH and OMPI
#define MUK_ARGV_NULL  ((char**)0)
#define MUK_ARGVS_NULL ((char***)0)
#define MUK_ERRCODES_IGNORE ((int*)0)

// These match OMPI (MPICH sets to 1)
#define MUK_STATUSES_IGNORE ((void*)0)
#define MUK_STATUS_IGNORE   ((void*)0)

// These match OMPI (MPICH sets to extern-something)
#define MUK_UNWEIGHTED    ((int*)2)
#define MUK_WEIGHTS_EMPTY ((int*)3)

#include <stddef.h>

// basic typedefs
typedef ptrdiff_t MUK_Aint;
typedef ptrdiff_t MUK_Count;
typedef ptrdiff_t MUK_Offset;

// status typedef
typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
MUK_Status;

typedef void MUK_User_function(void *invec, void *inoutvec, int *len, MUK_Datatype *datatype);
typedef void MUK_User_function_c(void *invec, void *inoutvec, MUK_Count *len, MUK_Datatype *datatype);
typedef int MUK_Comm_copy_attr_function(MUK_Comm oldcomm, int comm_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MUK_Comm_delete_attr_function(MUK_Comm comm, int comm_keyval, void *attribute_val, void *extra_state);
typedef int MUK_Win_copy_attr_function(MUK_Win oldwin, int win_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MUK_Win_delete_attr_function(MUK_Win win, int win_keyval, void *attribute_val, void *extra_state);
typedef int MUK_Type_copy_attr_function(MUK_Datatype oldtype, int type_keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MUK_Type_delete_attr_function(MUK_Datatype datatype, int type_keyval, void *attribute_val, void *extra_state);
typedef void MUK_Comm_errhandler_function(MUK_Comm *comm, int *error_code, ...);
typedef void MUK_Win_errhandler_function(MUK_Win *win, int *error_code, ...);
typedef void MUK_File_errhandler_function(MUK_File *file, int *error_code, ...);
typedef void MUK_Session_errhandler_function(MUK_Session *session, int *error_code, ...);
typedef int MUK_Grequest_query_function(void *extra_state, MUK_Status *status);
typedef int MUK_Grequest_free_function(void *extra_state);
typedef int MUK_Grequest_cancel_function(void *extra_state, int complete);
typedef int MUK_Datarep_extent_function(MUK_Datatype datatype, MUK_Aint *extent, void *extra_state);
typedef int MUK_Datarep_conversion_function(void *userbuf, MUK_Datatype datatype, int count, void *filebuf, MUK_Offset position, void *extra_state);
typedef int MUK_Datarep_conversion_function_c(void *userbuf, MUK_Datatype datatype, MUK_Count count, void *filebuf, MUK_Offset position, void *extra_state);

// these are deprecated
typedef int MUK_Copy_function(MUK_Comm oldcomm, int keyval, void *extra_state, void *attribute_val_in, void *attribute_val_out, int *flag);
typedef int MUK_Delete_function(MUK_Comm comm, int keyval, void *attribute_val, void *extra_state);

#define MUK_NULL_COPY_FN        ((MUK_Copy_function*)NULL)
#define MUK_DUP_FN              ((MUK_Copy_function*)NULL)
#define MUK_NULL_DELETE_FN      ((MUK_Delete_function*)NULL)
#define MUK_COMM_NULL_COPY_FN   ((MUK_Comm_copy_attr_function*)NULL)
#define MUK_COMM_DUP_FN         ((MUK_Comm_copy_attr_function*)NULL)
#define MUK_COMM_NULL_DELETE_FN ((MUK_Comm_delete_attr_function*)NULL)
#define MUK_TYPE_NULL_COPY_FN   ((MUK_Type_copy_attr_function*)NULL)
#define MUK_TYPE_NULL_COPY_FN   ((MUK_Type_copy_attr_function*)NULL)
#define MUK_TYPE_NULL_DELETE_FN ((MUK_Type_delete_attr_function*)NULL)
#define MUK_WIN_NULL_COPY_FN    ((MUK_Win_copy_attr_function*)NULL)
#define MUK_WIN_NULL_COPY_FN    ((MUK_Win_copy_attr_function*)NULL)
#define MUK_WIN_NULL_DELETE_FN  ((MUK_Win_delete_attr_function*)NULL)

#endif
