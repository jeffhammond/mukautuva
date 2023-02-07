// error codes
extern int MPI_SUCCESS;
extern int MPI_ERR_BUFFER;
extern int MPI_ERR_COUNT;
extern int MPI_ERR_TYPE;
extern int MPI_ERR_TAG;
extern int MPI_ERR_COMM;
extern int MPI_ERR_RANK;
extern int MPI_ERR_REQUEST;
extern int MPI_ERR_ROOT;
extern int MPI_ERR_GROUP;
extern int MPI_ERR_OP;
extern int MPI_ERR_TOPOLOGY;
extern int MPI_ERR_DIMS;
extern int MPI_ERR_ARG;
extern int MPI_ERR_UNKNOWN;
extern int MPI_ERR_TRUNCATE;
extern int MPI_ERR_OTHER;
extern int MPI_ERR_INTERN;
extern int MPI_ERR_PENDING;
extern int MPI_ERR_IN_STATUS;
extern int MPI_ERR_ACCESS;
extern int MPI_ERR_AMODE;
extern int MPI_ERR_ASSERT;
extern int MPI_ERR_BAD_FILE;
extern int MPI_ERR_BASE;
extern int MPI_ERR_CONVERSION;
extern int MPI_ERR_DISP;
extern int MPI_ERR_DUP_DATAREP;
extern int MPI_ERR_FILE_EXISTS;
extern int MPI_ERR_FILE_IN_USE;
extern int MPI_ERR_FILE;
extern int MPI_ERR_INFO_KEY;
extern int MPI_ERR_INFO_NOKEY;
extern int MPI_ERR_INFO_VALUE;
extern int MPI_ERR_INFO;
extern int MPI_ERR_IO;
extern int MPI_ERR_KEYVAL;
extern int MPI_ERR_LOCKTYPE;
extern int MPI_ERR_NAME;
extern int MPI_ERR_NO_MEM;
extern int MPI_ERR_NOT_SAME;
extern int MPI_ERR_NO_SPACE;
extern int MPI_ERR_NO_SUCH_FILE;
extern int MPI_ERR_PORT;
#if MPI_VERSION >= 4
extern int MPI_ERR_PROC_ABORTED;
#endif
extern int MPI_ERR_QUOTA;
extern int MPI_ERR_READ_ONLY;
extern int MPI_ERR_RMA_ATTACH;
extern int MPI_ERR_RMA_CONFLICT;
extern int MPI_ERR_RMA_RANGE;
extern int MPI_ERR_RMA_SHARED;
extern int MPI_ERR_RMA_SYNC;
extern int MPI_ERR_RMA_FLAVOR;
extern int MPI_ERR_SERVICE;
#if MPI_VERSION >= 4
extern int MPI_ERR_SESSION;
#endif
extern int MPI_ERR_SIZE;
extern int MPI_ERR_SPAWN;
extern int MPI_ERR_UNSUPPORTED_DATAREP;
extern int MPI_ERR_UNSUPPORTED_OPERATION;
#if MPI_VERSION >= 4
extern int MPI_ERR_VALUE_TOO_LARGE;
#endif
extern int MPI_ERR_WIN;
extern int MPI_T_ERR_CANNOT_INIT;
#if 0
extern int MPI_T_ERR_NOT_ACCESSIBLE;
#endif
extern int MPI_T_ERR_NOT_INITIALIZED;
#if MPI_VERSION >= 4
extern int MPI_T_ERR_NOT_SUPPORTED;
#endif
extern int MPI_T_ERR_MEMORY;
extern int MPI_T_ERR_INVALID;
extern int MPI_T_ERR_INVALID_INDEX;
extern int MPI_T_ERR_INVALID_ITEM;
extern int MPI_T_ERR_INVALID_SESSION;
extern int MPI_T_ERR_INVALID_HANDLE;
extern int MPI_T_ERR_INVALID_NAME;
extern int MPI_T_ERR_OUT_OF_HANDLES;
extern int MPI_T_ERR_OUT_OF_SESSIONS;
extern int MPI_T_ERR_CVAR_SET_NOT_NOW;
extern int MPI_T_ERR_CVAR_SET_NEVER;
extern int MPI_T_ERR_PVAR_NO_WRITE;
extern int MPI_T_ERR_PVAR_NO_STARTSTOP;
extern int MPI_T_ERR_PVAR_NO_ATOMIC;
extern int MPI_ERR_LASTCODE;

// Buffer Address Constants
extern void * MPI_BOTTOM;
extern void * MPI_IN_PLACE;

// Assorted Constants
extern int MPI_PROC_NULL;
extern int MPI_ANY_SOURCE;
extern int MPI_ANY_TAG;
extern int MPI_UNDEFINED;
extern int MPI_BSEND_OVERHEAD;
extern int MPI_KEYVAL_INVALID;
extern int MPI_LOCK_EXCLUSIVE;
extern int MPI_LOCK_SHARED;
extern int MPI_ROOT;

// No Process Message Handle
extern MPI_Message MPI_MESSAGE_NO_PROC;

#if 0
//Fortran status array size and reserved index values (C only)
extern int MPI_F_STATUS_SIZE;
int MPI_F_SOURCE;
int MPI_F_TAG;
int MPI_F_ERROR;
extern int MPI_ADDRESS_KIND;
extern int MPI_COUNT_KIND;
extern int MPI_INTEGER_KIND;
extern int MPI_OFFSET_KIND;
#endif

// Error-handling specifiers
extern MPI_Errhandler MPI_ERRORS_ARE_FATAL;
#if MPI_VERSION >= 4
extern MPI_Errhandler MPI_ERRORS_ABORT;
#endif
extern MPI_Errhandler MPI_ERRORS_RETURN;

// Named Predefined Datatypes
extern MPI_Datatype MPI_CHAR;
extern MPI_Datatype MPI_SHORT;
extern MPI_Datatype MPI_INT;
extern MPI_Datatype MPI_LONG;
extern MPI_Datatype MPI_LONG_LONG_INT;
extern MPI_Datatype MPI_LONG_LONG;
extern MPI_Datatype MPI_SIGNED_CHAR;
extern MPI_Datatype MPI_UNSIGNED_CHAR;
extern MPI_Datatype MPI_UNSIGNED_SHORT;
extern MPI_Datatype MPI_UNSIGNED;
extern MPI_Datatype MPI_UNSIGNED_LONG;
extern MPI_Datatype MPI_UNSIGNED_LONG_LONG;
extern MPI_Datatype MPI_FLOAT;
extern MPI_Datatype MPI_DOUBLE;
extern MPI_Datatype MPI_LONG_DOUBLE;
extern MPI_Datatype MPI_WCHAR;
extern MPI_Datatype MPI_C_BOOL;

extern MPI_Datatype MPI_INT8_T;
extern MPI_Datatype MPI_INT16_T;
extern MPI_Datatype MPI_INT32_T;
extern MPI_Datatype MPI_INT64_T;
extern MPI_Datatype MPI_UINT8_T;
extern MPI_Datatype MPI_UINT16_T;
extern MPI_Datatype MPI_UINT32_T;
extern MPI_Datatype MPI_UINT64_T;
extern MPI_Datatype MPI_AINT;
extern MPI_Datatype MPI_COUNT;
extern MPI_Datatype MPI_OFFSET;
extern MPI_Datatype MPI_C_COMPLEX;
extern MPI_Datatype MPI_C_FLOAT_COMPLEX;
extern MPI_Datatype MPI_C_DOUBLE_COMPLEX;
extern MPI_Datatype MPI_C_LONG_DOUBLE_COMPLEX;

extern MPI_Datatype MPI_BYTE;
extern MPI_Datatype MPI_PACKED;

extern MPI_Datatype MPI_INTEGER;
extern MPI_Datatype MPI_REAL;
extern MPI_Datatype MPI_DOUBLE_PRECISION;
extern MPI_Datatype MPI_COMPLEX;
extern MPI_Datatype MPI_LOGICAL;
extern MPI_Datatype MPI_CHARACTER;

extern MPI_Datatype MPI_CXX_BOOL;
extern MPI_Datatype MPI_CXX_FLOAT_COMPLEX;
extern MPI_Datatype MPI_CXX_DOUBLE_COMPLEX;
extern MPI_Datatype MPI_CXX_LONG_DOUBLE_COMPLEX;

#if 0
extern MPI_Datatype MPI_DOUBLE_COMPLEX;
extern MPI_Datatype MPI_INTEGER1;
extern MPI_Datatype MPI_INTEGER2;
extern MPI_Datatype MPI_INTEGER4;
extern MPI_Datatype MPI_INTEGER8;
extern MPI_Datatype MPI_INTEGER16;
extern MPI_Datatype MPI_REAL2;
extern MPI_Datatype MPI_REAL4;
extern MPI_Datatype MPI_REAL8;
extern MPI_Datatype MPI_REAL16;
extern MPI_Datatype MPI_COMPLEX4;
extern MPI_Datatype MPI_COMPLEX8;
extern MPI_Datatype MPI_COMPLEX16;
extern MPI_Datatype MPI_COMPLEX32;
#endif

extern MPI_Datatype MPI_FLOAT_INT;
extern MPI_Datatype MPI_DOUBLE_INT;
extern MPI_Datatype MPI_LONG_INT;
extern MPI_Datatype MPI_2INT;
extern MPI_Datatype MPI_SHORT_INT;
extern MPI_Datatype MPI_LONG_DOUBLE_INT;

extern MPI_Datatype MPI_2REAL;
extern MPI_Datatype MPI_2DOUBLE_PRECISION;
extern MPI_Datatype MPI_2INTEGER;

// Reserved communicators
extern MPI_Comm MPI_COMM_WORLD;
MPI_Comm MPI_COMM_SELF;

// Communicator split type constants
extern int MPI_COMM_TYPE_SHARED;
#if MPI_VERSION >= 4
extern int MPI_COMM_TYPE_HW_UNGUIDED;
extern int MPI_COMM_TYPE_HW_GUIDED;
#endif

// Results of communicator and group comparisons
extern int MPI_IDENT;
extern int MPI_CONGRUENT;
extern int MPI_SIMILAR;
extern int MPI_UNEQUAL;

// Environmental inquiry info key
extern MPI_Info MPI_INFO_ENV;

// Environmental inquiry keys
extern int MPI_TAG_UB;
extern int MPI_IO;
extern int MPI_HOST;
extern int MPI_WTIME_IS_GLOBAL;

// Collective Operations
extern MPI_Op MPI_MAX;
extern MPI_Op MPI_MIN;
extern MPI_Op MPI_SUM;
extern MPI_Op MPI_PROD;
extern MPI_Op MPI_LAND;
extern MPI_Op MPI_BAND;
extern MPI_Op MPI_LOR;
extern MPI_Op MPI_BOR;
extern MPI_Op MPI_LXOR;
extern MPI_Op MPI_BXOR;
extern MPI_Op MPI_MAXLOC;
extern MPI_Op MPI_MINLOC;
extern MPI_Op MPI_REPLACE;
extern MPI_Op MPI_NO_OP;

// Null Handles
extern MPI_Group MPI_GROUP_NULL;
extern MPI_Comm MPI_COMM_NULL;
extern MPI_Datatype MPI_DATATYPE_NULL;
extern MPI_Request MPI_REQUEST_NULL;
extern MPI_Op MPI_OP_NULL;
extern MPI_Errhandler MPI_ERRHANDLER_NULL;
extern MPI_File MPI_FILE_NULL;
extern MPI_Info MPI_INFO_NULL;
#if MPI_VERSION >= 4
extern MPI_Session MPI_SESSION_NULL;
#endif
extern MPI_Win  MPI_WIN_NULL;
extern MPI_Message MPI_MESSAGE_NULL;

// Empty group
extern MPI_Group MPI_GROUP_EMPTY;

// Topologies
extern int MPI_GRAPH;
extern int MPI_CART;
extern int MPI_DIST_GRAPH;

// Predefined functions
// TODO
// Deprecated predefined functions
// TODO

// Predefined Attribute Keys
extern int MPI_APPNUM;
extern int MPI_LASTUSEDCODE;
extern int MPI_UNIVERSE_SIZE;
extern int MPI_WIN_BASE;
extern int MPI_WIN_DISP_UNIT;
extern int MPI_WIN_SIZE;
extern int MPI_WIN_CREATE_FLAVOR;
extern int MPI_WIN_MODEL;

// MPI Window Create Flavors
extern int MPI_WIN_FLAVOR_CREATE;
extern int MPI_WIN_FLAVOR_ALLOCATE;
extern int MPI_WIN_FLAVOR_DYNAMIC;
extern int MPI_WIN_FLAVOR_SHARED;

// MPI Window Models
extern int MPI_WIN_SEPARATE;
extern int MPI_WIN_UNIFIED;
            
// Mode Constants
extern int MPI_MODE_APPEND;
extern int MPI_MODE_CREATE;
extern int MPI_MODE_DELETE_ON_CLOSE;
extern int MPI_MODE_EXCL;
extern int MPI_MODE_NOCHECK;
extern int MPI_MODE_NOPRECEDE;
extern int MPI_MODE_NOPUT;
extern int MPI_MODE_NOSTORE;
extern int MPI_MODE_NOSUCCEED;
extern int MPI_MODE_RDONLY;
extern int MPI_MODE_RDWR;
extern int MPI_MODE_SEQUENTIAL;
extern int MPI_MODE_UNIQUE_OPEN;
extern int MPI_MODE_WRONLY;

// Datatype Decoding Constants
extern int MPI_COMBINER_CONTIGUOUS;
extern int MPI_COMBINER_DARRAY;
extern int MPI_COMBINER_DUP;
extern int MPI_COMBINER_F90_COMPLEX;
extern int MPI_COMBINER_F90_INTEGER;
extern int MPI_COMBINER_F90_REAL;
extern int MPI_COMBINER_HINDEXED;
extern int MPI_COMBINER_HVECTOR;
extern int MPI_COMBINER_INDEXED_BLOCK;
extern int MPI_COMBINER_HINDEXED_BLOCK;
extern int MPI_COMBINER_INDEXED;
extern int MPI_COMBINER_NAMED;
extern int MPI_COMBINER_RESIZED;
extern int MPI_COMBINER_STRUCT;
extern int MPI_COMBINER_SUBARRAY;
extern int MPI_COMBINER_VECTOR;

// Threads Constants
extern int MPI_THREAD_FUNNELED;
extern int MPI_THREAD_MULTIPLE;
extern int MPI_THREAD_SERIALIZED;
extern int MPI_THREAD_SINGLE;

// File Operation Constants, Part 1
extern int MPI_DISPLACEMENT_CURRENT;

// File Operation Constants, Part 2
extern int MPI_DISTRIBUTE_BLOCK;
extern int MPI_DISTRIBUTE_CYCLIC;
extern int MPI_DISTRIBUTE_DFLT_DARG;
extern int MPI_DISTRIBUTE_NONE;
extern int MPI_ORDER_C;
extern int MPI_ORDER_FORTRAN;
extern int MPI_SEEK_CUR;
extern int MPI_SEEK_END;
extern int MPI_SEEK_SET;

// F90 Datatype Matching Constants
extern int MPI_TYPECLASS_COMPLEX;
extern int MPI_TYPECLASS_INTEGER;
extern int MPI_TYPECLASS_REAL;

// Constants Specifying Empty or Ignored Input
extern char *** MPI_ARGVS_NULL;
extern char ** MPI_ARGV_NULL;
extern int * MPI_ERRCODES_IGNORE;
extern MPI_Status * MPI_STATUSES_IGNORE;
extern MPI_Status * MPI_STATUS_IGNORE;
#ifndef MPICH
extern int * MPI_UNWEIGHTED;
extern int * MPI_WEIGHTS_EMPTY;
#endif
