// SPDX-License-Identifier: MIT

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
typedef struct MUK_ABI_T_enum * MUK_T_enum;
typedef struct MUK_ABI_T_cvar_handle * MUK_T_cvar_handle;
typedef struct MUK_ABI_T_pvar_handle * MUK_T_pvar_handle;
typedef struct MUK_ABI_T_pvar_session * MUK_T_pvar_session;
typedef struct MUK_ABI_T_event_registration * MUK_T_event_registration;
typedef struct MUK_ABI_T_event_instance * MUK_T_event_instance;

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
    MUK_ERR_QUOTA                       = 44,
    MUK_ERR_READ_ONLY                   = 45,
    MUK_ERR_RMA_ATTACH                  = 46,
    MUK_ERR_RMA_CONFLICT                = 47,
    MUK_ERR_RMA_RANGE                   = 48,
    MUK_ERR_RMA_SHARED                  = 49,
    MUK_ERR_RMA_SYNC                    = 50,
    MUK_ERR_SERVICE                     = 51,
    MUK_ERR_SIZE                        = 52,
    MUK_ERR_SPAWN                       = 53,
    MUK_ERR_UNSUPPORTED_DATAREP         = 54,
    MUK_ERR_UNSUPPORTED_OPERATION       = 55,
    MUK_ERR_WIN                         = 56,
    MUK_ERR_RMA_FLAVOR                  = 57,
    MUK_ERR_PROC_ABORTED                = 58,
    MUK_ERR_VALUE_TOO_LARGE             = 59,
    MUK_ERR_SESSION                     = 60,
    MUK_ERR_ERRHANDLER                  = 61,
    MUK_ERR_ABI                         = 62,
    MUK_T_ERR_CANNOT_INIT               = 1001,
    MUK_T_ERR_NOT_ACCESSIBLE            = 1002,
    MUK_T_ERR_NOT_INITIALIZED           = 1003,
    MUK_T_ERR_NOT_SUPPORTED             = 1004,
    MUK_T_ERR_MEMORY                    = 1005,
    MUK_T_ERR_INVALID                   = 1006,
    MUK_T_ERR_INVALID_INDEX             = 1007,
    MUK_T_ERR_INVALID_ITEM              = 1008,
    MUK_T_ERR_INVALID_SESSION           = 1009,
    MUK_T_ERR_INVALID_HANDLE            = 1010,
    MUK_T_ERR_INVALID_NAME              = 1011,
    MUK_T_ERR_OUT_OF_HANDLES            = 1012,
    MUK_T_ERR_OUT_OF_SESSIONS           = 1013,
    MUK_T_ERR_CVAR_SET_NOT_NOW          = 1014,
    MUK_T_ERR_CVAR_SET_NEVER            = 1015,
    MUK_T_ERR_PVAR_NO_WRITE             = 1016,
    MUK_T_ERR_PVAR_NO_STARTSTOP         = 1017,
    MUK_T_ERR_PVAR_NO_ATOMIC            = 1018,
    MUK_ERR_LASTCODE                    = 0x3fff
};

// Buffer Address Constants

// Assorted Constants
enum {
    // these should be different and never valid ranks
    MUK_ANY_SOURCE = -1,
    MUK_PROC_NULL  = -3,
    MUK_ROOT       = -4
};
enum {
    MUK_ANY_TAG    = -2
};
enum {
    // MUK, MPICH and OMPI agree on this
    MUK_UNDEFINED  = -32766
};
enum {
    MUK_BSEND_OVERHEAD = 512
};
enum {
    MUK_KEYVAL_INVALID = 0
};
enum {
    MUK_LOCK_EXCLUSIVE = 301,
    MUK_LOCK_SHARED    = 302
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
#define MUK_ERRHANDLER_NULL ((MUK_Errhandler)0x00000140)
#define MUK_ERRORS_ARE_FATAL ((MUK_Errhandler)0x00000141)
#define MUK_ERRORS_ABORT ((MUK_Errhandler)0x00000142)
#define MUK_ERRORS_RETURN ((MUK_Errhandler)0x00000143)

// Named Predefined Datatypes
#define MUK_DATATYPE_NULL ((MUK_Datatype)0x00000200)
#define MUK_AINT ((MUK_Datatype)0x00000201)
#define MUK_COUNT ((MUK_Datatype)0x00000202)
#define MUK_OFFSET ((MUK_Datatype)0x00000203)
#define MUK_PACKED ((MUK_Datatype)0x00000207)
#define MUK_SHORT ((MUK_Datatype)0x00000208)
#define MUK_INT ((MUK_Datatype)0x00000209)
#define MUK_LONG ((MUK_Datatype)0x0000020a)
#define MUK_LONG_LONG ((MUK_Datatype)0x0000020b)
#define MUK_LONG_LONG_INT MUK_LONG_LONG
#define MUK_UNSIGNED_SHORT ((MUK_Datatype)0x0000020c)
#define MUK_UNSIGNED ((MUK_Datatype)0x0000020d)
#define MUK_UNSIGNED_LONG ((MUK_Datatype)0x0000020e)
#define MUK_UNSIGNED_LONG_LONG ((MUK_Datatype)0x0000020f)
#define MUK_FLOAT ((MUK_Datatype)0x00000210)
#define MUK_C_FLOAT_COMPLEX ((MUK_Datatype)0x00000212)
#define MUK_C_COMPLEX MUK_C_FLOAT_COMPLEX
#define MUK_CXX_FLOAT_COMPLEX ((MUK_Datatype)0x00000213)
#define MUK_DOUBLE ((MUK_Datatype)0x00000214)
#define MUK_C_DOUBLE_COMPLEX ((MUK_Datatype)0x00000216)
#define MUK_CXX_DOUBLE_COMPLEX ((MUK_Datatype)0x00000217)
#define MUK_LOGICAL ((MUK_Datatype)0x00000218)
#define MUK_INTEGER ((MUK_Datatype)0x00000219)
#define MUK_REAL ((MUK_Datatype)0x0000021a)
#define MUK_COMPLEX ((MUK_Datatype)0x0000021b)
#define MUK_DOUBLE_PRECISION ((MUK_Datatype)0x0000021c)
#define MUK_DOUBLE_COMPLEX ((MUK_Datatype)0x0000021d)
#define MUK_CHARACTER ((MUK_Datatype)0x0000021e)
#define MUK_LONG_DOUBLE ((MUK_Datatype)0x00000220)
#define MUK_C_LONG_DOUBLE_COMPLEX ((MUK_Datatype)0x00000224)
#define MUK_CXX_LONG_DOUBLE_COMPLEX ((MUK_Datatype)0x00000225)
#define MUK_FLOAT_INT ((MUK_Datatype)0x00000228)
#define MUK_DOUBLE_INT ((MUK_Datatype)0x00000229)
#define MUK_LONG_INT ((MUK_Datatype)0x0000022a)
#define MUK_2INT ((MUK_Datatype)0x0000022b)
#define MUK_SHORT_INT ((MUK_Datatype)0x0000022c)
#define MUK_LONG_DOUBLE_INT ((MUK_Datatype)0x0000022d)
#define MUK_2REAL ((MUK_Datatype)0x00000230)
#define MUK_2DOUBLE_PRECISION ((MUK_Datatype)0x00000231)
#define MUK_2INTEGER ((MUK_Datatype)0x00000232)
#define MUK_C_BOOL ((MUK_Datatype)0x00000238)
#define MUK_CXX_BOOL ((MUK_Datatype)0x00000239)
#define MUK_WCHAR ((MUK_Datatype)0x0000023c)
#define MUK_INT8_T ((MUK_Datatype)0x00000240)
#define MUK_UINT8_T ((MUK_Datatype)0x00000241)
#define MUK_CHAR ((MUK_Datatype)0x00000243)
#define MUK_SIGNED_CHAR ((MUK_Datatype)0x00000244)
#define MUK_UNSIGNED_CHAR ((MUK_Datatype)0x00000245)
#define MUK_BYTE ((MUK_Datatype)0x00000247)
#define MUK_INT16_T ((MUK_Datatype)0x00000248)
#define MUK_UINT16_T ((MUK_Datatype)0x00000249)
#define MUK_INT32_T ((MUK_Datatype)0x00000250)
#define MUK_UINT32_T ((MUK_Datatype)0x00000251)
#define MUK_INT64_T ((MUK_Datatype)0x00000258)
#define MUK_UINT64_T ((MUK_Datatype)0x00000259)
#define MUK_LOGICAL1 ((MUK_Datatype)0x000002c0)
#define MUK_INTEGER1 ((MUK_Datatype)0x000002c1)
#define MUK_LOGICAL2 ((MUK_Datatype)0x000002c8)
#define MUK_INTEGER2 ((MUK_Datatype)0x000002c9)
#define MUK_REAL2 ((MUK_Datatype)0x000002ca)
#define MUK_LOGICAL4 ((MUK_Datatype)0x000002d0)
#define MUK_INTEGER4 ((MUK_Datatype)0x000002d1)
#define MUK_REAL4 ((MUK_Datatype)0x000002d2)
#define MUK_COMPLEX4 ((MUK_Datatype)0x000002d3)
#define MUK_LOGICAL8 ((MUK_Datatype)0x000002d8)
#define MUK_INTEGER8 ((MUK_Datatype)0x000002d9)
#define MUK_REAL8 ((MUK_Datatype)0x000002da)
#define MUK_COMPLEX8 ((MUK_Datatype)0x000002db)
#define MUK_LOGICAL16 ((MUK_Datatype)0x000002e0)
#define MUK_INTEGER16 ((MUK_Datatype)0x000002e1)
#define MUK_REAL16 ((MUK_Datatype)0x000002e2)
#define MUK_COMPLEX16 ((MUK_Datatype)0x000002e3)
#define MUK_COMPLEX32 ((MUK_Datatype)0x000002eb)
#define MUK_LB ((MUK_Datatype)0x000002f0)
#define MUK_UB ((MUK_Datatype)0x000002f1)

// Reserved communicators
#define MUK_COMM_NULL  ((MUK_Comm)0x00000100)
#define MUK_COMM_WORLD ((MUK_Comm)0x00000101)
#define MUK_COMM_SELF  ((MUK_Comm)0x00000102)

// Reserved groups
#define MUK_GROUP_NULL  ((MUK_Group)0x00000108)
#define MUK_GROUP_EMPTY ((MUK_Group)0x00000109)

// Communicator split type constants
enum {
    MUK_COMM_TYPE_SHARED          = 221,
    MUK_COMM_TYPE_HW_UNGUIDED     = 222,
    MUK_COMM_TYPE_HW_GUIDED       = 223,
    MUK_COMM_TYPE_RESOURCE_GUIDED = 224
};

// Results of communicator and group comparisons
enum {
    MUK_IDENT       = 201,
    MUK_CONGRUENT   = 202,
    MUK_SIMILAR     = 203,
    MUK_UNEQUAL     = 204
};

// Environmental inquiry info key
#define MUK_INFO_NULL ((MUK_Info)0x00000130)
#define MUK_INFO_ENV  ((MUK_Info)0x00000131)

// Collective Operations
#define MUK_OP_NULL ((MUK_Op)0x00000020)
#define MUK_SUM ((MUK_Op)0x00000021)
#define MUK_MIN ((MUK_Op)0x00000022)
#define MUK_MAX ((MUK_Op)0x00000023)
#define MUK_PROD ((MUK_Op)0x00000024)
#define MUK_BAND ((MUK_Op)0x00000028)
#define MUK_BOR ((MUK_Op)0x00000029)
#define MUK_BXOR ((MUK_Op)0x0000002a)
#define MUK_LAND ((MUK_Op)0x00000030)
#define MUK_LOR ((MUK_Op)0x00000031)
#define MUK_LXOR ((MUK_Op)0x00000032)
#define MUK_MINLOC ((MUK_Op)0x00000038)
#define MUK_MAXLOC ((MUK_Op)0x00000039)
#define MUK_REPLACE ((MUK_Op)0x0000003c)
#define MUK_NO_OP ((MUK_Op)0x0000003d)

// Predefined message handles
#define MUK_MESSAGE_NULL ((MUK_Message)0x00000128)
#define MUK_MESSAGE_NO_PROC ((MUK_Message)0x00000129)

// Null Handles
#define MUK_REQUEST_NULL ((MUK_Request)0x00000180)
#define MUK_FILE_NULL ((MUK_File)0x00000118)
#define MUK_WIN_NULL ((MUK_Win)0x00000110)
#if 1 //MUK_VERSION >= 4
#define MUK_SESSION_NULL ((MUK_Session)0x00000120)
#endif

// Topologies
enum {
    MUK_CART        = 211,
    MUK_GRAPH       = 212,
    MUK_DIST_GRAPH  = 213
};

enum {
    // Environmental inquiry keys
    MUK_TAG_UB           = 501,
    MUK_IO               = 502,
    MUK_HOST             = 503,
    MUK_WTIME_IS_GLOBAL  = 504,
    // Predefined Attribute Keys
    MUK_APPNUM           = 505,
    MUK_LASTUSEDCODE     = 506,
    MUK_UNIVERSE_SIZE    = 507,
    MUK_WIN_BASE         = 601,
    MUK_WIN_DISP_UNIT    = 602,
    MUK_WIN_SIZE         = 603,
    MUK_WIN_CREATE_FLAVOR = 604,
    MUK_WIN_MODEL        = 605
};

// MPI Window Create Flavors
enum {
    MUK_WIN_FLAVOR_CREATE   = 311,
    MUK_WIN_FLAVOR_ALLOCATE = 312,
    MUK_WIN_FLAVOR_DYNAMIC  = 313,
    MUK_WIN_FLAVOR_SHARED   = 314
};

// MPI Window Models
enum {
    MUK_WIN_UNIFIED  = 321,
    MUK_WIN_SEPARATE = 322
};

// Mode Constants
// The values of these constants must be defined such that the bitwise OR
// and the sum of any distinct set of these constants is equivalent.
enum {
    // none of these should be 0
    // I/O constants
    MUK_MODE_APPEND             = 1,
    MUK_MODE_CREATE             = 2,
    MUK_MODE_DELETE_ON_CLOSE    = 4,
    MUK_MODE_EXCL               = 8,
    MUK_MODE_RDONLY             = 16,
    MUK_MODE_RDWR               = 32,
    MUK_MODE_SEQUENTIAL         = 64,
    MUK_MODE_UNIQUE_OPEN        = 128,
    MUK_MODE_WRONLY             = 256,
    // RMA constants
    MUK_MODE_NOCHECK            = 1024,
    MUK_MODE_NOPRECEDE          = 2048,
    MUK_MODE_NOPUT              = 4096,
    MUK_MODE_NOSTORE            = 8192,
    MUK_MODE_NOSUCCEED          = 16384
};

// Datatype Decoding Constants
enum {
    MUK_COMBINER_NAMED         = 101,
    MUK_COMBINER_DUP           = 102,
    MUK_COMBINER_CONTIGUOUS    = 103,
    MUK_COMBINER_VECTOR        = 104,
    MUK_COMBINER_HVECTOR       = 105,
    MUK_COMBINER_INDEXED       = 106,
    MUK_COMBINER_HINDEXED      = 107,
    MUK_COMBINER_INDEXED_BLOCK = 108,
    MUK_COMBINER_HINDEXED_BLOCK = 109,
    MUK_COMBINER_STRUCT        = 110,
    MUK_COMBINER_SUBARRAY      = 111,
    MUK_COMBINER_DARRAY        = 112,
    MUK_COMBINER_F90_REAL      = 113,
    MUK_COMBINER_F90_COMPLEX   = 114,
    MUK_COMBINER_F90_INTEGER   = 115,
    MUK_COMBINER_RESIZED       = 116,
    MUK_COMBINER_VALUE_INDEX   = 117
};

// Threads Constants
enum {
    MUK_THREAD_SINGLE       = 0,
    MUK_THREAD_FUNNELED     = 1024,
    MUK_THREAD_SERIALIZED   = 2048,
    MUK_THREAD_MULTIPLE     = 4096
};

enum {
    // File Operation Constants, Part 1
    MUK_DISPLACEMENT_CURRENT = -1,
    // File Operation Constants, Part 2
    MUK_DISTRIBUTE_NONE      = 16,
    MUK_DISTRIBUTE_BLOCK     = 17,
    MUK_DISTRIBUTE_CYCLIC    = 18,
    MUK_DISTRIBUTE_DFLT_DARG = 19,
    MUK_ORDER_C              = 0xC,
    MUK_ORDER_FORTRAN        = 0xF,
    MUK_SEEK_CUR             = 401,
    MUK_SEEK_END             = 402,
    MUK_SEEK_SET             = 403
};

// F90 Datatype Matching Constants
enum {
    MUKX_TYPECLASS_LOGICAL = 191,
    MUK_TYPECLASS_INTEGER  = 192,
    MUK_TYPECLASS_REAL     = 193,
    MUK_TYPECLASS_COMPLEX  = 194
};

// Buffer Address Constants
// MPICH, OMPI and MUK agree
#define MUK_BOTTOM   ((void *)0)
// OMPI and MUK agree.  MPICH is -1
#define MUK_IN_PLACE ((void *)1)
#define MUK_BUFFER_AUTOMATIC ((void *)2)

// Constants Specifying Empty or Ignored Input
// These match MPICH and OMPI
#define MUK_ARGV_NULL  ((char**)0)
#define MUK_ARGVS_NULL ((char***)0)
#define MUK_ERRCODES_IGNORE ((int*)0)

// These match OMPI (MPICH sets to 1)
#define MUK_STATUSES_IGNORE ((void*)0)
#define MUK_STATUS_IGNORE   ((void*)0)

// These are translated to implementation-specific sentinels when needed.
#define MUK_UNWEIGHTED    ((int*)10)
#define MUK_WEIGHTS_EMPTY ((int*)11)

// MPI_T handles and constants
#define MUK_T_ENUM_NULL ((MUK_T_enum)0)
#define MUK_T_CVAR_HANDLE_NULL ((MUK_T_cvar_handle)0)
#define MUK_T_PVAR_SESSION_NULL ((MUK_T_pvar_session)0)
#define MUK_T_PVAR_HANDLE_NULL ((MUK_T_pvar_handle)0)
#define MUK_T_PVAR_ALL_HANDLES ((MUK_T_pvar_handle)1)

enum {
    MUK_T_CB_REQUIRE_NONE              = 0x00,
    MUK_T_CB_REQUIRE_MPI_RESTRICTED    = 0x03,
    MUK_T_CB_REQUIRE_THREAD_SAFE       = 0x0F,
    MUK_T_CB_REQUIRE_ASYNC_SIGNAL_SAFE = 0x3F
};

enum {
    MUK_T_SOURCE_ORDERED   = 1,
    MUK_T_SOURCE_UNORDERED = 2
};

enum {
    MUK_T_VERBOSITY_USER_BASIC   = 0x09,
    MUK_T_VERBOSITY_USER_DETAIL  = 0x0a,
    MUK_T_VERBOSITY_USER_ALL     = 0x0c,
    MUK_T_VERBOSITY_TUNER_BASIC  = 0x11,
    MUK_T_VERBOSITY_TUNER_DETAIL = 0x12,
    MUK_T_VERBOSITY_TUNER_ALL    = 0x14,
    MUK_T_VERBOSITY_MPIDEV_BASIC = 0x21,
    MUK_T_VERBOSITY_MPIDEV_DETAIL = 0x22,
    MUK_T_VERBOSITY_MPIDEV_ALL   = 0x24
};

enum {
    MUK_T_BIND_NO_OBJECT       = 1,
    MUK_T_BIND_MPI_COMM       = 2,
    MUK_T_BIND_MPI_DATATYPE   = 3,
    MUK_T_BIND_MPI_ERRHANDLER = 4,
    MUK_T_BIND_MPI_FILE       = 5,
    MUK_T_BIND_MPI_GROUP      = 6,
    MUK_T_BIND_MPI_OP         = 7,
    MUK_T_BIND_MPI_REQUEST    = 8,
    MUK_T_BIND_MPI_WIN        = 9,
    MUK_T_BIND_MPI_MESSAGE    = 10,
    MUK_T_BIND_MPI_INFO       = 11,
    MUK_T_BIND_MPI_SESSION    = 12
};

enum {
    MUK_T_SCOPE_CONSTANT = 1,
    MUK_T_SCOPE_READONLY = 2,
    MUK_T_SCOPE_LOCAL    = 3,
    MUK_T_SCOPE_GROUP    = 4,
    MUK_T_SCOPE_GROUP_EQ = 5,
    MUK_T_SCOPE_ALL      = 6,
    MUK_T_SCOPE_ALL_EQ   = 7
};

enum {
    MUK_T_PVAR_CLASS_STATE         = 1,
    MUK_T_PVAR_CLASS_LEVEL         = 2,
    MUK_T_PVAR_CLASS_SIZE          = 3,
    MUK_T_PVAR_CLASS_PERCENTAGE    = 4,
    MUK_T_PVAR_CLASS_HIGHWATERMARK = 5,
    MUK_T_PVAR_CLASS_LOWWATERMARK  = 6,
    MUK_T_PVAR_CLASS_COUNTER       = 7,
    MUK_T_PVAR_CLASS_AGGREGATE     = 8,
    MUK_T_PVAR_CLASS_TIMER         = 9,
    MUK_T_PVAR_CLASS_GENERIC       = 10
};

#include <stddef.h>
#include <stdint.h>

// basic typedefs
typedef intptr_t MUK_Aint;
typedef int64_t MUK_Offset;
typedef MUK_Offset MUK_Count;

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
#define MUK_DUP_FN              ((MUK_Copy_function*)0x1)
#define MUK_NULL_DELETE_FN      ((MUK_Delete_function*)NULL)
#define MUK_COMM_NULL_COPY_FN   ((MUK_Comm_copy_attr_function*)NULL)
#define MUK_COMM_DUP_FN         ((MUK_Comm_copy_attr_function*)0x1)
#define MUK_COMM_NULL_DELETE_FN ((MUK_Comm_delete_attr_function*)NULL)
#define MUK_TYPE_NULL_COPY_FN   ((MUK_Type_copy_attr_function*)NULL)
#define MUK_TYPE_DUP_FN         ((MUK_Type_copy_attr_function*)0x1)
#define MUK_TYPE_NULL_DELETE_FN ((MUK_Type_delete_attr_function*)NULL)
#define MUK_WIN_NULL_COPY_FN    ((MUK_Win_copy_attr_function*)NULL)
#define MUK_WIN_DUP_FN          ((MUK_Win_copy_attr_function*)0x1)
#define MUK_WIN_NULL_DELETE_FN  ((MUK_Win_delete_attr_function*)NULL)

#endif
