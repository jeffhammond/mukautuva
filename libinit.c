#include "muk.h"
#include "muk-dl.h"

#if defined(__linux__) && defined(__x86_64__)
#define LIBMPI_NAME "/usr/lib/x86_64-linux-gnu/libmpi.so"
#elif defined(__MACH__)
#define LIBMPI_NAME "/opt/homebrew/lib/libmpi.dylib"
#else
#warning No default MPI library path.
#endif

Which_MPI_e whose_mpi = UNKNOWN;

#define MUK_INTERNAL
#include "mpi-handle-typedefs.h"

#include "mpi-typedefs.h"

#define MUK_EXTERN
#include "mpi-predefined.h"

#include "mpi-prototypes.h"

#include "muk-function-pointers.h"

#include "impl-predefined.h"

// end of type stuff

int (*WRAP_Load_functions)(void * restrict h, int major, int minor);
int (*WRAP_CODE_IMPL_TO_MUK)(int error_c);

// I need these for null handle versions.
// The impl layer sets *handle = &IMPL_HANDLE_NULL,
// which is pmuk_mpi_handle_null.  Then I detect
// that and change it to MUK_HANDLE_NULL.
void ** pmuk_mpi_request_null = NULL;
static inline void MUK_REQUEST_NULLIFY(MPI_Request * r)
{
    if (*r == pmuk_mpi_request_null) {
        *r = &muk_mpi_request_null;
    }
}

// alkaa = start
static int MUK_Alkaa(int * argc, char *** argv, int requested, int * provided)
{
    int rc;

    char * soname;
    char * env = getenv("MPI_LIB");
    if (env == NULL) {
        soname = LIBMPI_NAME;
    } else {
        soname = env;
    }
    printf("soname = %s\n", soname);

    void * h = dlopen(soname, RTLD_LAZY | RTLD_LOCAL);
    if (h == NULL) {
        printf("dlopen of %s failed: %s\n", soname, dlerror() );
        abort();
    }

    MUK_Init = MUK_DLSYM(h,"MPI_Init");
    MUK_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    if (provided == NULL) {
        rc = MUK_Init(argc,argv);
    } else {
        rc = MUK_Init_thread(argc,argv,requested,provided);
    }

    char * wrapname = "/dev/null";
    // figure out which library i am using
    MUK_Get_library_version = MUK_DLSYM(h,"MPI_Get_library_version");
    {
        char lib_version[16384] = {0};
        int  lib_version_length;
        rc = MUK_Get_library_version(lib_version, &lib_version_length);
        //printf("MPI_Get_library_version = %s\n", lib_version);

        char * pos;
        pos = strstr(lib_version, "Open MPI");
        if (pos != NULL) {
            whose_mpi = OMPI;
            printf("Open-MPI\n");
        }
        pos = strstr(lib_version, "MPICH");
        if (pos != NULL) {
            whose_mpi = MPICH;
            printf("MPICH\n");
        }
    if (whose_mpi == OMPI) {
        wrapname = "ompi-wrap.so";
    } else if (whose_mpi == MPICH) {
        wrapname = "mpich-wrap.so";
    }

    }

    // these are ABI-agnostic and important, so why not load them now...
    MUK_Finalize = MUK_DLSYM(h,"MPI_Finalize");
    MUK_Finalized = MUK_DLSYM(h,"MPI_Finalized");
    MUK_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    MUK_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    MUK_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    MUK_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");
    MUK_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    MUK_Wtick = MUK_DLSYM(h,"MPI_Wtick");

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    void * wrap_so_handle = dlopen(wrapname, RTLD_LAZY);
    if (wrap_so_handle == NULL) {
        printf("dlopen of %s failed: %s\n", wrapname, dlerror() );
        abort();
    }

#if 0
    // error codes
    // MPI_SUCCESS is defined to be 0 and thus is omitted
    int* pIMPL_ERR_BUFFER = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_BUFFER");
    IMPL_ERR_BUFFER = *pIMPL_ERR_BUFFER;
    int* pIMPL_ERR_COUNT = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_COUNT");
    IMPL_ERR_COUNT = *pIMPL_ERR_COUNT;
    int* pIMPL_ERR_TYPE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_TYPE");
    IMPL_ERR_TYPE = *pIMPL_ERR_TYPE;
    int* pIMPL_ERR_TAG = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_TAG");
    IMPL_ERR_TAG = *pIMPL_ERR_TAG;
    int* pIMPL_ERR_COMM = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_COMM");
    IMPL_ERR_COMM = *pIMPL_ERR_COMM;
    int* pIMPL_ERR_RANK = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RANK");
    IMPL_ERR_RANK = *pIMPL_ERR_RANK;
    int* pIMPL_ERR_REQUEST = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_REQUEST");
    IMPL_ERR_REQUEST = *pIMPL_ERR_REQUEST;
    int* pIMPL_ERR_ROOT = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_ROOT");
    IMPL_ERR_ROOT = *pIMPL_ERR_ROOT;
    int* pIMPL_ERR_GROUP = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_GROUP");
    IMPL_ERR_GROUP = *pIMPL_ERR_GROUP;
    int* pIMPL_ERR_OP = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_OP");
    IMPL_ERR_OP = *pIMPL_ERR_OP;
    int* pIMPL_ERR_TOPOLOGY = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_TOPOLOGY");
    IMPL_ERR_TOPOLOGY = *pIMPL_ERR_TOPOLOGY;
    int* pIMPL_ERR_DIMS = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_DIMS");
    IMPL_ERR_DIMS = *pIMPL_ERR_DIMS;
    int* pIMPL_ERR_ARG = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_ARG");
    IMPL_ERR_ARG = *pIMPL_ERR_ARG;
    int* pIMPL_ERR_UNKNOWN = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_UNKNOWN");
    IMPL_ERR_UNKNOWN = *pIMPL_ERR_UNKNOWN;
    int* pIMPL_ERR_TRUNCATE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_TRUNCATE");
    IMPL_ERR_TRUNCATE = *pIMPL_ERR_TRUNCATE;
    int* pIMPL_ERR_OTHER = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_OTHER");
    IMPL_ERR_OTHER = *pIMPL_ERR_OTHER;
    int* pIMPL_ERR_INTERN = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_INTERN");
    IMPL_ERR_INTERN = *pIMPL_ERR_INTERN;
    int* pIMPL_ERR_PENDING = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_PENDING");
    IMPL_ERR_PENDING = *pIMPL_ERR_PENDING;
    int* pIMPL_ERR_IN_STATUS = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_IN_STATUS");
    IMPL_ERR_IN_STATUS = *pIMPL_ERR_IN_STATUS;
    int* pIMPL_ERR_ACCESS = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_ACCESS");
    IMPL_ERR_ACCESS = *pIMPL_ERR_ACCESS;
    int* pIMPL_ERR_AMODE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_AMODE");
    IMPL_ERR_AMODE = *pIMPL_ERR_AMODE;
    int* pIMPL_ERR_ASSERT = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_ASSERT");
    IMPL_ERR_ASSERT = *pIMPL_ERR_ASSERT;
    int* pIMPL_ERR_BAD_FILE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_BAD_FILE");
    IMPL_ERR_BAD_FILE = *pIMPL_ERR_BAD_FILE;
    int* pIMPL_ERR_BASE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_BASE");
    IMPL_ERR_BASE = *pIMPL_ERR_BASE;
    int* pIMPL_ERR_CONVERSION = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_CONVERSION");
    IMPL_ERR_CONVERSION = *pIMPL_ERR_CONVERSION;
    int* pIMPL_ERR_DISP = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_DISP");
    IMPL_ERR_DISP = *pIMPL_ERR_DISP;
    int* pIMPL_ERR_DUP_DATAREP = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_DUP_DATAREP");
    IMPL_ERR_DUP_DATAREP = *pIMPL_ERR_DUP_DATAREP;
    int* pIMPL_ERR_FILE_EXISTS = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_FILE_EXISTS");
    IMPL_ERR_FILE_EXISTS = *pIMPL_ERR_FILE_EXISTS;
    int* pIMPL_ERR_FILE_IN_USE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_FILE_IN_USE");
    IMPL_ERR_FILE_IN_USE = *pIMPL_ERR_FILE_IN_USE;
    int* pIMPL_ERR_FILE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_FILE");
    IMPL_ERR_FILE = *pIMPL_ERR_FILE;
    int* pIMPL_ERR_INFO_KEY = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_INFO_KEY");
    IMPL_ERR_INFO_KEY = *pIMPL_ERR_INFO_KEY;
    int* pIMPL_ERR_INFO_NOKEY = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_INFO_NOKEY");
    IMPL_ERR_INFO_NOKEY = *pIMPL_ERR_INFO_NOKEY;
    int* pIMPL_ERR_INFO_VALUE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_INFO_VALUE");
    IMPL_ERR_INFO_VALUE = *pIMPL_ERR_INFO_VALUE;
    int* pIMPL_ERR_INFO = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_INFO");
    IMPL_ERR_INFO = *pIMPL_ERR_INFO;
    int* pIMPL_ERR_IO = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_IO");
    IMPL_ERR_IO = *pIMPL_ERR_IO;
    int* pIMPL_ERR_KEYVAL = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_KEYVAL");
    IMPL_ERR_KEYVAL = *pIMPL_ERR_KEYVAL;
    int* pIMPL_ERR_LOCKTYPE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_LOCKTYPE");
    IMPL_ERR_LOCKTYPE = *pIMPL_ERR_LOCKTYPE;
    int* pIMPL_ERR_NAME = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_NAME");
    IMPL_ERR_NAME = *pIMPL_ERR_NAME;
    int* pIMPL_ERR_NO_MEM = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_NO_MEM");
    IMPL_ERR_NO_MEM = *pIMPL_ERR_NO_MEM;
    int* pIMPL_ERR_NOT_SAME = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_NOT_SAME");
    IMPL_ERR_NOT_SAME = *pIMPL_ERR_NOT_SAME;
    int* pIMPL_ERR_NO_SPACE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_NO_SPACE");
    IMPL_ERR_NO_SPACE = *pIMPL_ERR_NO_SPACE;
    int* pIMPL_ERR_NO_SUCH_FILE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_NO_SUCH_FILE");
    IMPL_ERR_NO_SUCH_FILE = *pIMPL_ERR_NO_SUCH_FILE;
    int* pIMPL_ERR_PORT = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_PORT");
    IMPL_ERR_PORT = *pIMPL_ERR_PORT;
#if MPI_VERSION >= 4
    int* pIMPL_ERR_PROC_ABORTED = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_PROC_ABORTED");
    IMPL_ERR_PROC_ABORTED = *pIMPL_ERR_PROC_ABORTED;
#endif
    int* pIMPL_ERR_QUOTA = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_QUOTA");
    IMPL_ERR_QUOTA = *pIMPL_ERR_QUOTA;
    int* pIMPL_ERR_READ_ONLY = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_READ_ONLY");
    IMPL_ERR_READ_ONLY = *pIMPL_ERR_READ_ONLY;
    int* pIMPL_ERR_RMA_ATTACH = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_ATTACH");
    IMPL_ERR_RMA_ATTACH = *pIMPL_ERR_RMA_ATTACH;
    int* pIMPL_ERR_RMA_CONFLICT = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_CONFLICT");
    IMPL_ERR_RMA_CONFLICT = *pIMPL_ERR_RMA_CONFLICT;
    int* pIMPL_ERR_RMA_RANGE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_RANGE");
    IMPL_ERR_RMA_RANGE = *pIMPL_ERR_RMA_RANGE;
    int* pIMPL_ERR_RMA_SHARED = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_SHARED");
    IMPL_ERR_RMA_SHARED = *pIMPL_ERR_RMA_SHARED;
    int* pIMPL_ERR_RMA_SYNC = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_SYNC");
    IMPL_ERR_RMA_SYNC = *pIMPL_ERR_RMA_SYNC;
    int* pIMPL_ERR_RMA_FLAVOR = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_RMA_FLAVOR");
    IMPL_ERR_RMA_FLAVOR = *pIMPL_ERR_RMA_FLAVOR;
    int* pIMPL_ERR_SERVICE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_SERVICE");
    IMPL_ERR_SERVICE = *pIMPL_ERR_SERVICE;
#if MPI_VERSION >= 4
    int* pIMPL_ERR_SESSION = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_SESSION");
    IMPL_ERR_SESSION = *pIMPL_ERR_SESSION;
#endif
    int* pIMPL_ERR_SIZE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_SIZE");
    IMPL_ERR_SIZE = *pIMPL_ERR_SIZE;
    int* pIMPL_ERR_SPAWN = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_SPAWN");
    IMPL_ERR_SPAWN = *pIMPL_ERR_SPAWN;
    int* pIMPL_ERR_UNSUPPORTED_DATAREP = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_UNSUPPORTED_DATAREP");
    IMPL_ERR_UNSUPPORTED_DATAREP = *pIMPL_ERR_UNSUPPORTED_DATAREP;
    int* pIMPL_ERR_UNSUPPORTED_OPERATION = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_UNSUPPORTED_OPERATION");
    IMPL_ERR_UNSUPPORTED_OPERATION = *pIMPL_ERR_UNSUPPORTED_OPERATION;
#if MPI_VERSION >= 4
    int* pIMPL_ERR_VALUE_TOO_LARGE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_VALUE_TOO_LARGE");
    IMPL_ERR_VALUE_TOO_LARGE = *pIMPL_ERR_VALUE_TOO_LARGE;
#endif
    int* pIMPL_ERR_WIN = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_WIN");
    IMPL_ERR_WIN = *pIMPL_ERR_WIN;
    int* pIMPL_T_ERR_CANNOT_INIT = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_CANNOT_INIT");
    IMPL_T_ERR_CANNOT_INIT = *pIMPL_T_ERR_CANNOT_INIT;
#if 0
    int* pIMPL_T_ERR_NOT_ACCESSIBLE = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_NOT_ACCESSIBLE");
    IMPL_T_ERR_NOT_ACCESSIBLE = *pIMPL_T_ERR_NOT_ACCESSIBLE;
#endif
    int* pIMPL_T_ERR_NOT_INITIALIZED = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_NOT_INITIALIZED");
    IMPL_T_ERR_NOT_INITIALIZED = *pIMPL_T_ERR_NOT_INITIALIZED;
#if MPI_VERSION >= 4
    int* pIMPL_T_ERR_NOT_SUPPORTED = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_NOT_SUPPORTED");
    IMPL_T_ERR_NOT_SUPPORTED = *pIMPL_T_ERR_NOT_SUPPORTED;
#endif
    int* pIMPL_T_ERR_MEMORY = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_MEMORY");
    IMPL_T_ERR_MEMORY = *pIMPL_T_ERR_MEMORY;
    int* pIMPL_T_ERR_INVALID = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID");
    IMPL_T_ERR_INVALID = *pIMPL_T_ERR_INVALID;
    int* pIMPL_T_ERR_INVALID_INDEX = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID_INDEX");
    IMPL_T_ERR_INVALID_INDEX = *pIMPL_T_ERR_INVALID_INDEX;
    int* pIMPL_T_ERR_INVALID_ITEM = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID_ITEM");
    IMPL_T_ERR_INVALID_ITEM = *pIMPL_T_ERR_INVALID_ITEM;
    int* pIMPL_T_ERR_INVALID_SESSION = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID_SESSION");
    IMPL_T_ERR_INVALID_SESSION = *pIMPL_T_ERR_INVALID_SESSION;
    int* pIMPL_T_ERR_INVALID_HANDLE = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID_HANDLE");
    IMPL_T_ERR_INVALID_HANDLE = *pIMPL_T_ERR_INVALID_HANDLE;
    int* pIMPL_T_ERR_INVALID_NAME = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_INVALID_NAME");
    IMPL_T_ERR_INVALID_NAME = *pIMPL_T_ERR_INVALID_NAME;
    int* pIMPL_T_ERR_OUT_OF_HANDLES = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_OUT_OF_HANDLES");
    IMPL_T_ERR_OUT_OF_HANDLES = *pIMPL_T_ERR_OUT_OF_HANDLES;
    int* pIMPL_T_ERR_OUT_OF_SESSIONS = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_OUT_OF_SESSIONS");
    IMPL_T_ERR_OUT_OF_SESSIONS = *pIMPL_T_ERR_OUT_OF_SESSIONS;
    int* pIMPL_T_ERR_CVAR_SET_NOT_NOW = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_CVAR_SET_NOT_NOW");
    IMPL_T_ERR_CVAR_SET_NOT_NOW = *pIMPL_T_ERR_CVAR_SET_NOT_NOW;
    int* pIMPL_T_ERR_CVAR_SET_NEVER = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_CVAR_SET_NEVER");
    IMPL_T_ERR_CVAR_SET_NEVER = *pIMPL_T_ERR_CVAR_SET_NEVER;
    int* pIMPL_T_ERR_PVAR_NO_WRITE = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_PVAR_NO_WRITE");
    IMPL_T_ERR_PVAR_NO_WRITE = *pIMPL_T_ERR_PVAR_NO_WRITE;
    int* pIMPL_T_ERR_PVAR_NO_STARTSTOP = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_PVAR_NO_STARTSTOP");
    IMPL_T_ERR_PVAR_NO_STARTSTOP = *pIMPL_T_ERR_PVAR_NO_STARTSTOP;
    int* pIMPL_T_ERR_PVAR_NO_ATOMIC = MUK_DLSYM(wrap_so_handle,"IMPL_T_ERR_PVAR_NO_ATOMIC");
    IMPL_T_ERR_PVAR_NO_ATOMIC = *pIMPL_T_ERR_PVAR_NO_ATOMIC;
    int* pIMPL_ERR_LASTCODE = MUK_DLSYM(wrap_so_handle,"IMPL_ERR_LASTCODE");
    IMPL_ERR_LASTCODE = *pIMPL_ERR_LASTCODE;
#endif

    // Buffer Address Constants
    void ** pMPI_BOTTOM   = MUK_DLSYM(wrap_so_handle,"IMPL_BOTTOM");
    MPI_BOTTOM = *pMPI_BOTTOM;
    void ** pMPI_IN_PLACE = MUK_DLSYM(wrap_so_handle,"IMPL_IN_PLACE");
    MPI_IN_PLACE = *pMPI_IN_PLACE;

#if 0
    // Assorted Constants
    int* pMPI_PROC_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_PROC_NULL");
    MPI_PROC_NULL = *pMPI_PROC_NULL;
    int* pMPI_ANY_SOURCE = MUK_DLSYM(wrap_so_handle,"IMPL_ANY_SOURCE");
    MPI_ANY_SOURCE = *pMPI_ANY_SOURCE;
    int* pMPI_ANY_TAG = MUK_DLSYM(wrap_so_handle,"IMPL_ANY_TAG");
    MPI_ANY_TAG = *pMPI_ANY_TAG;
    int* pMPI_UNDEFINED = MUK_DLSYM(wrap_so_handle,"IMPL_UNDEFINED");
    MPI_UNDEFINED = *pMPI_UNDEFINED;
    int* pMPI_BSEND_OVERHEAD = MUK_DLSYM(wrap_so_handle,"IMPL_BSEND_OVERHEAD");
    MPI_BSEND_OVERHEAD = *pMPI_BSEND_OVERHEAD;
    int* pMPI_KEYVAL_INVALID = MUK_DLSYM(wrap_so_handle,"IMPL_KEYVAL_INVALID");
    MPI_KEYVAL_INVALID = *pMPI_KEYVAL_INVALID;
    int* pMPI_LOCK_EXCLUSIVE = MUK_DLSYM(wrap_so_handle,"IMPL_LOCK_EXCLUSIVE");
    MPI_LOCK_EXCLUSIVE = *pMPI_LOCK_EXCLUSIVE;
    int* pMPI_LOCK_SHARED = MUK_DLSYM(wrap_so_handle,"IMPL_LOCK_SHARED");
    MPI_LOCK_SHARED = *pMPI_LOCK_SHARED;
    int* pMPI_ROOT = MUK_DLSYM(wrap_so_handle,"IMPL_ROOT");
    MPI_ROOT = *pMPI_ROOT;
#endif

    // No Process Message Handle
    //void ** pMPI_MESSAGE_NO_PROC = MUK_DLSYM(wrap_so_handle,"IMPL_MESSAGE_NO_PROC");
    //MPI_MESSAGE_NO_PROC = *pMPI_MESSAGE_NO_PROC;
    //    MPI_MESSAGE_NO_PROC = MUK_DLSYM(wrap_so_handle,"IMPL_MESSAGE_NO_PROC");
    void ** pmuk_mpi_message_no_proc = MUK_DLSYM(wrap_so_handle,"IMPL_MESSAGE_NO_PROC");
    muk_mpi_message_no_proc = *pmuk_mpi_message_no_proc;


#if 0
    //Fortran status array size and reserved index values (C only)
    int* pMPI_F_STATUS_SIZE = MUK_DLSYM(wrap_so_handle,"IMPL_F_STATUS_SIZE");
    MPI_F_STATUS_SIZE = *pMPI_F_STATUS_SIZE;
    int* pMPI_F_SOURCE = MUK_DLSYM(wrap_so_handle,"IMPL_F_SOURCE");
    MPI_F_SOURCE = *pMPI_F_SOURCE;
    int* pMPI_F_TAG = MUK_DLSYM(wrap_so_handle,"IMPL_F_TAG");
    MPI_F_TAG = *pMPI_F_TAG;
    int* pMPI_F_ERROR = MUK_DLSYM(wrap_so_handle,"IMPL_F_ERROR");
    MPI_F_ERROR = *pMPI_F_ERROR;
    int* pMPI_ADDRESS_KIND = MUK_DLSYM(wrap_so_handle,"IMPL_ADDRESS_KIND");
    MPI_ADDRESS_KIND = *pMPI_ADDRESS_KIND;
    int* pMPI_COUNT_KIND = MUK_DLSYM(wrap_so_handle,"IMPL_COUNT_KIND");
    MPI_COUNT_KIND = *pMPI_COUNT_KIND;
    int* pMPI_INTEGER_KIND = MUK_DLSYM(wrap_so_handle,"IMPL_INTEGER_KIND");
    MPI_INTEGER_KIND = *pMPI_INTEGER_KIND;
    int* pMPI_OFFSET_KIND = MUK_DLSYM(wrap_so_handle,"IMPL_OFFSET_KIND");
    MPI_OFFSET_KIND = *pMPI_OFFSET_KIND;
#endif

    // Error-handling specifiers
    //    MPI_ERRORS_ARE_FATAL = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_ARE_FATAL");
    void ** pmuk_mpi_errors_are_fatal = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_ARE_FATAL");
    muk_mpi_errors_are_fatal = *pmuk_mpi_errors_are_fatal;
#if 0 && MPI_VERSION >= 4
    //    MPI_ERRORS_ABORT = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_ABORT");
    void ** pmuk_mpi_errors_abort = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_ABORT");
    muk_mpi_errors_abort = *pmuk_mpi_errors_abort;
#endif
    //    MPI_ERRORS_RETURN = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_RETURN");
    void ** pmuk_mpi_errors_return = MUK_DLSYM(wrap_so_handle,"IMPL_ERRORS_RETURN");
    muk_mpi_errors_return = *pmuk_mpi_errors_return;

    // Named Predefined Datatypes
    //    MPI_CHAR = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CHAR",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_char = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CHAR",MPI_DATATYPE_NULL);
    muk_mpi_char = *pmuk_mpi_char;
    //    MPI_SHORT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SHORT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_short = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SHORT",MPI_DATATYPE_NULL);
    muk_mpi_short = *pmuk_mpi_short;
    //    MPI_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT",MPI_DATATYPE_NULL);
    muk_mpi_int = *pmuk_mpi_int;
    //    MPI_LONG = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG",MPI_DATATYPE_NULL);
    muk_mpi_long = *pmuk_mpi_long;
    //    MPI_LONG_LONG_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_LONG_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long_long_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_LONG_INT",MPI_DATATYPE_NULL);
    muk_mpi_long_long_int = *pmuk_mpi_long_long_int;
    //    MPI_LONG_LONG = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_LONG",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long_long = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_LONG",MPI_DATATYPE_NULL);
    muk_mpi_long_long = *pmuk_mpi_long_long;
    //    MPI_SIGNED_CHAR = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SIGNED_CHAR",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_signed_char = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SIGNED_CHAR",MPI_DATATYPE_NULL);
    muk_mpi_signed_char = *pmuk_mpi_signed_char;
    //    MPI_UNSIGNED_CHAR = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_CHAR",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_unsigned_char = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_CHAR",MPI_DATATYPE_NULL);
    muk_mpi_unsigned_char = *pmuk_mpi_unsigned_char;
    //    MPI_UNSIGNED_SHORT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_SHORT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_unsigned_short = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_SHORT",MPI_DATATYPE_NULL);
    muk_mpi_unsigned_short = *pmuk_mpi_unsigned_short;
    //    MPI_UNSIGNED = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_unsigned = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED",MPI_DATATYPE_NULL);
    muk_mpi_unsigned = *pmuk_mpi_unsigned;
    //    MPI_UNSIGNED_LONG = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_LONG",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_unsigned_long = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_LONG",MPI_DATATYPE_NULL);
    muk_mpi_unsigned_long = *pmuk_mpi_unsigned_long;
    //    MPI_UNSIGNED_LONG_LONG = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_LONG_LONG",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_unsigned_long_long = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UNSIGNED_LONG_LONG",MPI_DATATYPE_NULL);
    muk_mpi_unsigned_long_long = *pmuk_mpi_unsigned_long_long;
    //    MPI_FLOAT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_FLOAT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_float = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_FLOAT",MPI_DATATYPE_NULL);
    muk_mpi_float = *pmuk_mpi_float;
    //    MPI_DOUBLE = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_double = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE",MPI_DATATYPE_NULL);
    muk_mpi_double = *pmuk_mpi_double;
    //    MPI_LONG_DOUBLE = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_DOUBLE",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long_double = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_DOUBLE",MPI_DATATYPE_NULL);
    muk_mpi_long_double = *pmuk_mpi_long_double;
    //    MPI_WCHAR = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_WCHAR",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_wchar = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_WCHAR",MPI_DATATYPE_NULL);
    muk_mpi_wchar = *pmuk_mpi_wchar;
    //    MPI_C_BOOL = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_BOOL",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_c_bool = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_BOOL",MPI_DATATYPE_NULL);
    muk_mpi_c_bool = *pmuk_mpi_c_bool;

    //    MPI_INT8_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT8_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_int8_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT8_T",MPI_DATATYPE_NULL);
    muk_mpi_int8_t = *pmuk_mpi_int8_t;
    //    MPI_INT16_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT16_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_int16_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT16_T",MPI_DATATYPE_NULL);
    muk_mpi_int16_t = *pmuk_mpi_int16_t;
    //    MPI_INT32_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT32_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_int32_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT32_T",MPI_DATATYPE_NULL);
    muk_mpi_int32_t = *pmuk_mpi_int32_t;
    //    MPI_INT64_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT64_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_int64_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INT64_T",MPI_DATATYPE_NULL);
    muk_mpi_int64_t = *pmuk_mpi_int64_t;
    //    MPI_UINT8_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT8_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_uint8_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT8_T",MPI_DATATYPE_NULL);
    muk_mpi_uint8_t = *pmuk_mpi_uint8_t;
    //    MPI_UINT16_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT16_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_uint16_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT16_T",MPI_DATATYPE_NULL);
    muk_mpi_uint16_t = *pmuk_mpi_uint16_t;
    //    MPI_UINT32_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT32_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_uint32_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT32_T",MPI_DATATYPE_NULL);
    muk_mpi_uint32_t = *pmuk_mpi_uint32_t;
    //    MPI_UINT64_T = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT64_T",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_uint64_t = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_UINT64_T",MPI_DATATYPE_NULL);
    muk_mpi_uint64_t = *pmuk_mpi_uint64_t;
    //    MPI_AINT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_AINT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_aint = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_AINT",MPI_DATATYPE_NULL);
    muk_mpi_aint = *pmuk_mpi_aint;
    //    MPI_COUNT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COUNT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_count = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COUNT",MPI_DATATYPE_NULL);
    muk_mpi_count = *pmuk_mpi_count;
    //    MPI_OFFSET = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_OFFSET",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_offset = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_OFFSET",MPI_DATATYPE_NULL);
    muk_mpi_offset = *pmuk_mpi_offset;
    //    MPI_C_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_c_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_c_complex = *pmuk_mpi_c_complex;
    //    MPI_C_FLOAT_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_FLOAT_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_c_float_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_FLOAT_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_c_float_complex = *pmuk_mpi_c_float_complex;
    //    MPI_C_DOUBLE_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_c_double_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_c_double_complex = *pmuk_mpi_c_double_complex;
    //    MPI_C_LONG_DOUBLE_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_LONG_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_c_long_double_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_C_LONG_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_c_long_double_complex = *pmuk_mpi_c_long_double_complex;

    //    MPI_BYTE = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_BYTE",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_byte = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_BYTE",MPI_DATATYPE_NULL);
    muk_mpi_byte = *pmuk_mpi_byte;
    //    MPI_PACKED = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_PACKED",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_packed = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_PACKED",MPI_DATATYPE_NULL);
    muk_mpi_packed = *pmuk_mpi_packed;

    //    MPI_INTEGER = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER",MPI_DATATYPE_NULL);
    muk_mpi_integer = *pmuk_mpi_integer;
    //    MPI_REAL = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_real = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL",MPI_DATATYPE_NULL);
    muk_mpi_real = *pmuk_mpi_real;
    //    MPI_DOUBLE_PRECISION = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_PRECISION",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_double_precision = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_PRECISION",MPI_DATATYPE_NULL);
    muk_mpi_double_precision = *pmuk_mpi_double_precision;
    //    MPI_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_complex = *pmuk_mpi_complex;
    //    MPI_LOGICAL = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LOGICAL",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_logical = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LOGICAL",MPI_DATATYPE_NULL);
    muk_mpi_logical = *pmuk_mpi_logical;
    //    MPI_CHARACTER = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CHARACTER",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_character = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CHARACTER",MPI_DATATYPE_NULL);
    muk_mpi_character = *pmuk_mpi_character;

    //    MPI_CXX_BOOL = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_BOOL",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_cxx_bool = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_BOOL",MPI_DATATYPE_NULL);
    muk_mpi_cxx_bool = *pmuk_mpi_cxx_bool;
    //    MPI_CXX_FLOAT_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_FLOAT_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_cxx_float_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_FLOAT_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_cxx_float_complex = *pmuk_mpi_cxx_float_complex;
    //    MPI_CXX_DOUBLE_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_cxx_double_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_cxx_double_complex = *pmuk_mpi_cxx_double_complex;
    //    MPI_CXX_LONG_DOUBLE_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_LONG_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_cxx_long_double_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_CXX_LONG_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_cxx_long_double_complex = *pmuk_mpi_cxx_long_double_complex;

#if 0
    //    MPI_DOUBLE_COMPLEX = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_double_complex = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_COMPLEX",MPI_DATATYPE_NULL);
    muk_mpi_double_complex = *pmuk_mpi_double_complex;
    //    MPI_INTEGER1 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER1",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer1 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER1",MPI_DATATYPE_NULL);
    muk_mpi_integer1 = *pmuk_mpi_integer1;
    //    MPI_INTEGER2 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER2",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer2 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER2",MPI_DATATYPE_NULL);
    muk_mpi_integer2 = *pmuk_mpi_integer2;
    //    MPI_INTEGER4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER4",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER4",MPI_DATATYPE_NULL);
    muk_mpi_integer4 = *pmuk_mpi_integer4;
    //    MPI_INTEGER8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER8",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER8",MPI_DATATYPE_NULL);
    muk_mpi_integer8 = *pmuk_mpi_integer8;
    //    MPI_INTEGER16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER16",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_integer16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_INTEGER16",MPI_DATATYPE_NULL);
    muk_mpi_integer16 = *pmuk_mpi_integer16;
    //    MPI_REAL2 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL2",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_real2 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL2",MPI_DATATYPE_NULL);
    muk_mpi_real2 = *pmuk_mpi_real2;
    //    MPI_REAL4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL4",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_real4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL4",MPI_DATATYPE_NULL);
    muk_mpi_real4 = *pmuk_mpi_real4;
    //    MPI_REAL8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL8",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_real8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL8",MPI_DATATYPE_NULL);
    muk_mpi_real8 = *pmuk_mpi_real8;
    //    MPI_REAL16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL16",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_real16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_REAL16",MPI_DATATYPE_NULL);
    muk_mpi_real16 = *pmuk_mpi_real16;
    //    MPI_COMPLEX4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX4",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_complex4 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX4",MPI_DATATYPE_NULL);
    muk_mpi_complex4 = *pmuk_mpi_complex4;
    //    MPI_COMPLEX8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX8",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_complex8 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX8",MPI_DATATYPE_NULL);
    muk_mpi_complex8 = *pmuk_mpi_complex8;
    //    MPI_COMPLEX16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX16",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_complex16 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX16",MPI_DATATYPE_NULL);
    muk_mpi_complex16 = *pmuk_mpi_complex16;
    //    MPI_COMPLEX32 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX32",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_complex32 = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_COMPLEX32",MPI_DATATYPE_NULL);
    muk_mpi_complex32 = *pmuk_mpi_complex32;
#endif

    //    MPI_FLOAT_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_FLOAT_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_float_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_FLOAT_INT",MPI_DATATYPE_NULL);
    muk_mpi_float_int = *pmuk_mpi_float_int;
    //    MPI_DOUBLE_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_double_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_DOUBLE_INT",MPI_DATATYPE_NULL);
    muk_mpi_double_int = *pmuk_mpi_double_int;
    //    MPI_LONG_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_INT",MPI_DATATYPE_NULL);
    muk_mpi_long_int = *pmuk_mpi_long_int;
    //    MPI_2INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_2int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2INT",MPI_DATATYPE_NULL);
    muk_mpi_2int = *pmuk_mpi_2int;
    //    MPI_SHORT_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SHORT_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_short_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_SHORT_INT",MPI_DATATYPE_NULL);
    muk_mpi_short_int = *pmuk_mpi_short_int;
    //    MPI_LONG_DOUBLE_INT = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_DOUBLE_INT",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_long_double_int = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_LONG_DOUBLE_INT",MPI_DATATYPE_NULL);
    muk_mpi_long_double_int = *pmuk_mpi_long_double_int;

    //    MPI_2REAL = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2REAL",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_2real = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2REAL",MPI_DATATYPE_NULL);
    muk_mpi_2real = *pmuk_mpi_2real;
    //    MPI_2DOUBLE_PRECISION = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2DOUBLE_PRECISION",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_2double_precision = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2DOUBLE_PRECISION",MPI_DATATYPE_NULL);
    muk_mpi_2double_precision = *pmuk_mpi_2double_precision;
    //    MPI_2INTEGER = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2INTEGER",MPI_DATATYPE_NULL);
    void ** pmuk_mpi_2integer = MUK_DLSYM_OPT(wrap_so_handle,"IMPL_2INTEGER",MPI_DATATYPE_NULL);
    muk_mpi_2integer = *pmuk_mpi_2integer;

    // Reserved communicators
    //MPI_COMM_WORLD = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_WORLD");
    //muk_mpi_comm_world = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_WORLD");
    void ** pmuk_mpi_comm_world = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_WORLD");
    muk_mpi_comm_world = *pmuk_mpi_comm_world;

    //    MPI_COMM_SELF = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_SELF");
    void ** pmuk_mpi_comm_self = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_SELF");
    muk_mpi_comm_self = *pmuk_mpi_comm_self;

#if 0
    // Communicator split type constants
    int* pMPI_COMM_TYPE_SHARED = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_TYPE_SHARED");
    MPI_COMM_TYPE_SHARED = *pMPI_COMM_TYPE_SHARED;
#if MPI_VERSION >= 4
    int* pMPI_COMM_TYPE_HW_UNGUIDED = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_TYPE_HW_UNGUIDED");
    MPI_COMM_TYPE_HW_UNGUIDED = *pMPI_COMM_TYPE_HW_UNGUIDED;
    int* pMPI_COMM_TYPE_HW_GUIDED = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_TYPE_HW_GUIDED");
    MPI_COMM_TYPE_HW_GUIDED = *pMPI_COMM_TYPE_HW_GUIDED;
#endif
#endif

#if 0
    // Results of communicator and group comparisons
    int* pMPI_IDENT = MUK_DLSYM(wrap_so_handle,"IMPL_IDENT");
    MPI_IDENT = *pMPI_IDENT;
    int* pMPI_CONGRUENT = MUK_DLSYM(wrap_so_handle,"IMPL_CONGRUENT");
    MPI_CONGRUENT = *pMPI_CONGRUENT;
    int* pMPI_SIMILAR = MUK_DLSYM(wrap_so_handle,"IMPL_SIMILAR");
    MPI_SIMILAR = *pMPI_SIMILAR;
    int* pMPI_UNEQUAL = MUK_DLSYM(wrap_so_handle,"IMPL_UNEQUAL");
    MPI_UNEQUAL = *pMPI_UNEQUAL;
#endif

    // Environmental inquiry info key
    //MPI_Info* pMPI_INFO_ENV = MUK_DLSYM(wrap_so_handle,"IMPL_INFO_ENV");
    //MPI_INFO_ENV = *pMPI_INFO_ENV;
    //    MPI_INFO_ENV = MUK_DLSYM(wrap_so_handle,"IMPL_INFO_ENV");
    void ** pmuk_mpi_info_env = MUK_DLSYM(wrap_so_handle,"IMPL_INFO_ENV");
    muk_mpi_info_env = *pmuk_mpi_info_env;

#if 0
    // Environmental inquiry keys
    int* pMPI_TAG_UB = MUK_DLSYM(wrap_so_handle,"IMPL_TAG_UB");
    MPI_TAG_UB = *pMPI_TAG_UB;
    int* pMPI_IO = MUK_DLSYM(wrap_so_handle,"IMPL_IO");
    MPI_IO = *pMPI_IO;
    int* pMPI_HOST = MUK_DLSYM(wrap_so_handle,"IMPL_HOST");
    MPI_HOST = *pMPI_HOST;
    int* pMPI_WTIME_IS_GLOBAL = MUK_DLSYM(wrap_so_handle,"IMPL_WTIME_IS_GLOBAL");
    MPI_WTIME_IS_GLOBAL = *pMPI_WTIME_IS_GLOBAL;
#endif

    // Collective Operations
    //    MPI_MAX = MUK_DLSYM(wrap_so_handle,"IMPL_MAX");
    void ** pmuk_mpi_max = MUK_DLSYM(wrap_so_handle,"IMPL_MAX");
    muk_mpi_max = *pmuk_mpi_max;
    //    MPI_MIN = MUK_DLSYM(wrap_so_handle,"IMPL_MIN");
    void ** pmuk_mpi_min = MUK_DLSYM(wrap_so_handle,"IMPL_MIN");
    muk_mpi_min = *pmuk_mpi_min;
    //    MPI_SUM = MUK_DLSYM(wrap_so_handle,"IMPL_SUM");
    void ** pmuk_mpi_sum = MUK_DLSYM(wrap_so_handle,"IMPL_SUM");
    muk_mpi_sum = *pmuk_mpi_sum;
    //    MPI_PROD = MUK_DLSYM(wrap_so_handle,"IMPL_PROD");
    void ** pmuk_mpi_prod = MUK_DLSYM(wrap_so_handle,"IMPL_PROD");
    muk_mpi_prod = *pmuk_mpi_prod;
    //    MPI_LAND = MUK_DLSYM(wrap_so_handle,"IMPL_LAND");
    void ** pmuk_mpi_land = MUK_DLSYM(wrap_so_handle,"IMPL_LAND");
    muk_mpi_land = *pmuk_mpi_land;
    //    MPI_BAND = MUK_DLSYM(wrap_so_handle,"IMPL_BAND");
    void ** pmuk_mpi_band = MUK_DLSYM(wrap_so_handle,"IMPL_BAND");
    muk_mpi_band = *pmuk_mpi_band;
    //    MPI_LOR = MUK_DLSYM(wrap_so_handle,"IMPL_LOR");
    void ** pmuk_mpi_lor = MUK_DLSYM(wrap_so_handle,"IMPL_LOR");
    muk_mpi_lor = *pmuk_mpi_lor;
    //    MPI_BOR = MUK_DLSYM(wrap_so_handle,"IMPL_BOR");
    void ** pmuk_mpi_bor = MUK_DLSYM(wrap_so_handle,"IMPL_BOR");
    muk_mpi_bor = *pmuk_mpi_bor;
    //    MPI_LXOR = MUK_DLSYM(wrap_so_handle,"IMPL_LXOR");
    void ** pmuk_mpi_lxor = MUK_DLSYM(wrap_so_handle,"IMPL_LXOR");
    muk_mpi_lxor = *pmuk_mpi_lxor;
    //    MPI_BXOR = MUK_DLSYM(wrap_so_handle,"IMPL_BXOR");
    void ** pmuk_mpi_bxor = MUK_DLSYM(wrap_so_handle,"IMPL_BXOR");
    muk_mpi_bxor = *pmuk_mpi_bxor;
    //    MPI_MAXLOC = MUK_DLSYM(wrap_so_handle,"IMPL_MAXLOC");
    void ** pmuk_mpi_maxloc = MUK_DLSYM(wrap_so_handle,"IMPL_MAXLOC");
    muk_mpi_maxloc = *pmuk_mpi_maxloc;
    //    MPI_MINLOC = MUK_DLSYM(wrap_so_handle,"IMPL_MINLOC");
    void ** pmuk_mpi_minloc = MUK_DLSYM(wrap_so_handle,"IMPL_MINLOC");
    muk_mpi_minloc = *pmuk_mpi_minloc;
    //    MPI_REPLACE = MUK_DLSYM(wrap_so_handle,"IMPL_REPLACE");
    void ** pmuk_mpi_replace = MUK_DLSYM(wrap_so_handle,"IMPL_REPLACE");
    muk_mpi_replace = *pmuk_mpi_replace;
    //    MPI_NO_OP = MUK_DLSYM(wrap_so_handle,"IMPL_NO_OP");
    void ** pmuk_mpi_no_op = MUK_DLSYM(wrap_so_handle,"IMPL_NO_OP");
    muk_mpi_no_op = *pmuk_mpi_no_op;

    // Null Handles
    //    MPI_GROUP_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_GROUP_NULL");
    void ** pmuk_mpi_group_null = MUK_DLSYM(wrap_so_handle,"IMPL_GROUP_NULL");
    muk_mpi_group_null = *pmuk_mpi_group_null;
    //    MPI_COMM_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_NULL");
    void ** pmuk_mpi_comm_null = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_NULL");
    muk_mpi_comm_null = *pmuk_mpi_comm_null;
    //    MPI_DATATYPE_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_DATATYPE_NULL");
    void ** pmuk_mpi_datatype_null = MUK_DLSYM(wrap_so_handle,"IMPL_DATATYPE_NULL");
    muk_mpi_datatype_null = *pmuk_mpi_datatype_null;
    //    MPI_REQUEST_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_REQUEST_NULL");
    pmuk_mpi_request_null = MUK_DLSYM(wrap_so_handle,"IMPL_REQUEST_NULL");
    muk_mpi_request_null = *pmuk_mpi_request_null;
    // This is the address inside the impl SO, i.e. &IMPL_REQUEST_NULL
    //printf("libinit: pmuk_mpi_request_null=%p\n",pmuk_mpi_request_null);
    // This is the value inside of the impl SO - the actual type with MPICH
    // is int so dereferencing pmuk_mpi_request_null is bad.
    //printf("libinit:  muk_mpi_request_null=%p\n",muk_mpi_request_null);
    // This is the value of MPI_REQUEST_NULL that the application sees - use it.
    // MPI_REQUEST_NULL = &muk_mpi_request_null
    //printf("libinit: &muk_mpi_request_null=%p\n",&muk_mpi_request_null);
    //    MPI_OP_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_OP_NULL");
    void ** pmuk_mpi_op_null = MUK_DLSYM(wrap_so_handle,"IMPL_OP_NULL");
    muk_mpi_op_null = *pmuk_mpi_op_null;
    //    MPI_ERRHANDLER_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_ERRHANDLER_NULL");
    void ** pmuk_mpi_errhandler_null = MUK_DLSYM(wrap_so_handle,"IMPL_ERRHANDLER_NULL");
    muk_mpi_errhandler_null = *pmuk_mpi_errhandler_null;
    //    MPI_FILE_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_FILE_NULL");
    void ** pmuk_mpi_file_null = MUK_DLSYM(wrap_so_handle,"IMPL_FILE_NULL");
    muk_mpi_file_null = *pmuk_mpi_file_null;
    //    MPI_INFO_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_INFO_NULL");
    void ** pmuk_mpi_info_null = MUK_DLSYM(wrap_so_handle,"IMPL_INFO_NULL");
    muk_mpi_info_null = *pmuk_mpi_info_null;
#if 0 && MPI_VERSION >= 4
    //    MPI_SESSION_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_SESSION_NULL");
    void ** pmuk_mpi_session_null = MUK_DLSYM(wrap_so_handle,"IMPL_SESSION_NULL");
    muk_mpi_session_null = *pmuk_mpi_session_null;
#endif
    //    MPI_WIN_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_NULL");
    void ** pmuk_mpi_win_null = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_NULL");
    muk_mpi_win_null = *pmuk_mpi_win_null;
    //    MPI_MESSAGE_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_MESSAGE_NULL");
    void ** pmuk_mpi_message_null = MUK_DLSYM(wrap_so_handle,"IMPL_MESSAGE_NULL");
    muk_mpi_message_null = *pmuk_mpi_message_null;

    // Empty group
    //    MPI_GROUP_EMPTY = MUK_DLSYM(wrap_so_handle,"IMPL_GROUP_EMPTY");
    void ** pmuk_mpi_group_empty = MUK_DLSYM(wrap_so_handle,"IMPL_GROUP_EMPTY");
    muk_mpi_group_empty = *pmuk_mpi_group_empty;
    //printf("libint: MPI_GROUP_EMPTY=%p *MPI_GROUP_EMPTY=%lx\n", MPI_GROUP_EMPTY, (intptr_t)*(void**)MPI_GROUP_EMPTY);

#if 0
    // Topologies
    int* pMPI_GRAPH = MUK_DLSYM(wrap_so_handle,"IMPL_GRAPH");
    MPI_GRAPH = *pMPI_GRAPH;
    int* pMPI_CART = MUK_DLSYM(wrap_so_handle,"IMPL_CART");
    MPI_CART = *pMPI_CART;
    int* pMPI_DIST_GRAPH = MUK_DLSYM(wrap_so_handle,"IMPL_DIST_GRAPH");
    MPI_DIST_GRAPH = *pMPI_DIST_GRAPH;
#endif

    // Predefined functions
    // TODO
    // Deprecated predefined functions
    // TODO

#if 0
    // Predefined Attribute Keys
    int* pMPI_APPNUM = MUK_DLSYM(wrap_so_handle,"IMPL_APPNUM");
    MPI_APPNUM = *pMPI_APPNUM;
    int* pMPI_LASTUSEDCODE = MUK_DLSYM(wrap_so_handle,"IMPL_LASTUSEDCODE");
    MPI_LASTUSEDCODE = *pMPI_LASTUSEDCODE;
    int* pMPI_UNIVERSE_SIZE = MUK_DLSYM(wrap_so_handle,"IMPL_UNIVERSE_SIZE");
    MPI_UNIVERSE_SIZE = *pMPI_UNIVERSE_SIZE;
    int* pMPI_WIN_BASE = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_BASE");
    MPI_WIN_BASE = *pMPI_WIN_BASE;
    int* pMPI_WIN_DISP_UNIT = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_DISP_UNIT");
    MPI_WIN_DISP_UNIT = *pMPI_WIN_DISP_UNIT;
    int* pMPI_WIN_SIZE = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_SIZE");
    MPI_WIN_SIZE = *pMPI_WIN_SIZE;
    int* pMPI_WIN_CREATE_FLAVOR = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_CREATE_FLAVOR");
    MPI_WIN_CREATE_FLAVOR = *pMPI_WIN_CREATE_FLAVOR;
    int* pMPI_WIN_MODEL = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_MODEL");
    MPI_WIN_MODEL = *pMPI_WIN_MODEL;

    // MPI Window Create Flavors
    int* pMPI_WIN_FLAVOR_CREATE = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_FLAVOR_CREATE");
    MPI_WIN_FLAVOR_CREATE = *pMPI_WIN_FLAVOR_CREATE;
    int* pMPI_WIN_FLAVOR_ALLOCATE = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_FLAVOR_ALLOCATE");
    MPI_WIN_FLAVOR_ALLOCATE = *pMPI_WIN_FLAVOR_ALLOCATE;
    int* pMPI_WIN_FLAVOR_DYNAMIC = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_FLAVOR_DYNAMIC");
    MPI_WIN_FLAVOR_DYNAMIC = *pMPI_WIN_FLAVOR_DYNAMIC;
    int* pMPI_WIN_FLAVOR_SHARED = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_FLAVOR_SHARED");
    MPI_WIN_FLAVOR_SHARED = *pMPI_WIN_FLAVOR_SHARED;

    // MPI Window Models
    int* pMPI_WIN_SEPARATE = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_SEPARATE");
    MPI_WIN_SEPARATE = *pMPI_WIN_SEPARATE;
    int* pMPI_WIN_UNIFIED = MUK_DLSYM(wrap_so_handle,"IMPL_WIN_UNIFIED");
    MPI_WIN_UNIFIED = *pMPI_WIN_UNIFIED;
                
    // Mode Constants
    int* pMPI_MODE_APPEND = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_APPEND");
    MPI_MODE_APPEND = *pMPI_MODE_APPEND;
    int* pMPI_MODE_CREATE = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_CREATE");
    MPI_MODE_CREATE = *pMPI_MODE_CREATE;
    int* pMPI_MODE_DELETE_ON_CLOSE = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_DELETE_ON_CLOSE");
    MPI_MODE_DELETE_ON_CLOSE = *pMPI_MODE_DELETE_ON_CLOSE;
    int* pMPI_MODE_EXCL = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_EXCL");
    MPI_MODE_EXCL = *pMPI_MODE_EXCL;
    int* pMPI_MODE_NOCHECK = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_NOCHECK");
    MPI_MODE_NOCHECK = *pMPI_MODE_NOCHECK;
    int* pMPI_MODE_NOPRECEDE = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_NOPRECEDE");
    MPI_MODE_NOPRECEDE = *pMPI_MODE_NOPRECEDE;
    int* pMPI_MODE_NOPUT = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_NOPUT");
    MPI_MODE_NOPUT = *pMPI_MODE_NOPUT;
    int* pMPI_MODE_NOSTORE = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_NOSTORE");
    MPI_MODE_NOSTORE = *pMPI_MODE_NOSTORE;
    int* pMPI_MODE_NOSUCCEED = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_NOSUCCEED");
    MPI_MODE_NOSUCCEED = *pMPI_MODE_NOSUCCEED;
    int* pMPI_MODE_RDONLY = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_RDONLY");
    MPI_MODE_RDONLY = *pMPI_MODE_RDONLY;
    int* pMPI_MODE_RDWR = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_RDWR");
    MPI_MODE_RDWR = *pMPI_MODE_RDWR;
    int* pMPI_MODE_SEQUENTIAL = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_SEQUENTIAL");
    MPI_MODE_SEQUENTIAL = *pMPI_MODE_SEQUENTIAL;
    int* pMPI_MODE_UNIQUE_OPEN = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_UNIQUE_OPEN");
    MPI_MODE_UNIQUE_OPEN = *pMPI_MODE_UNIQUE_OPEN;
    int* pMPI_MODE_WRONLY = MUK_DLSYM(wrap_so_handle,"IMPL_MODE_WRONLY");
    MPI_MODE_WRONLY = *pMPI_MODE_WRONLY;

    // Datatype Decoding Constants
    int* pMPI_COMBINER_CONTIGUOUS = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_CONTIGUOUS");
    MPI_COMBINER_CONTIGUOUS = *pMPI_COMBINER_CONTIGUOUS;
    int* pMPI_COMBINER_DARRAY = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_DARRAY");
    MPI_COMBINER_DARRAY = *pMPI_COMBINER_DARRAY;
    int* pMPI_COMBINER_DUP = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_DUP");
    MPI_COMBINER_DUP = *pMPI_COMBINER_DUP;
    int* pMPI_COMBINER_F90_COMPLEX = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_F90_COMPLEX");
    MPI_COMBINER_F90_COMPLEX = *pMPI_COMBINER_F90_COMPLEX;
    int* pMPI_COMBINER_F90_INTEGER = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_F90_INTEGER");
    MPI_COMBINER_F90_INTEGER = *pMPI_COMBINER_F90_INTEGER;
    int* pMPI_COMBINER_F90_REAL = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_F90_REAL");
    MPI_COMBINER_F90_REAL = *pMPI_COMBINER_F90_REAL;
    int* pMPI_COMBINER_HINDEXED = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_HINDEXED");
    MPI_COMBINER_HINDEXED = *pMPI_COMBINER_HINDEXED;
    int* pMPI_COMBINER_HVECTOR = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_HVECTOR");
    MPI_COMBINER_HVECTOR = *pMPI_COMBINER_HVECTOR;
    int* pMPI_COMBINER_INDEXED_BLOCK = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_INDEXED_BLOCK");
    MPI_COMBINER_INDEXED_BLOCK = *pMPI_COMBINER_INDEXED_BLOCK;
    int* pMPI_COMBINER_HINDEXED_BLOCK = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_HINDEXED_BLOCK");
    MPI_COMBINER_HINDEXED_BLOCK = *pMPI_COMBINER_HINDEXED_BLOCK;
    int* pMPI_COMBINER_INDEXED = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_INDEXED");
    MPI_COMBINER_INDEXED = *pMPI_COMBINER_INDEXED;
    int* pMPI_COMBINER_NAMED = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_NAMED");
    MPI_COMBINER_NAMED = *pMPI_COMBINER_NAMED;
    int* pMPI_COMBINER_RESIZED = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_RESIZED");
    MPI_COMBINER_RESIZED = *pMPI_COMBINER_RESIZED;
    int* pMPI_COMBINER_STRUCT = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_STRUCT");
    MPI_COMBINER_STRUCT = *pMPI_COMBINER_STRUCT;
    int* pMPI_COMBINER_SUBARRAY = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_SUBARRAY");
    MPI_COMBINER_SUBARRAY = *pMPI_COMBINER_SUBARRAY;
    int* pMPI_COMBINER_VECTOR = MUK_DLSYM(wrap_so_handle,"IMPL_COMBINER_VECTOR");
    MPI_COMBINER_VECTOR = *pMPI_COMBINER_VECTOR;

    // Threads Constants
    int* pMPI_THREAD_FUNNELED = MUK_DLSYM(wrap_so_handle,"IMPL_THREAD_FUNNELED");
    MPI_THREAD_FUNNELED = *pMPI_THREAD_FUNNELED;
    int* pMPI_THREAD_MULTIPLE = MUK_DLSYM(wrap_so_handle,"IMPL_THREAD_MULTIPLE");
    MPI_THREAD_MULTIPLE = *pMPI_THREAD_MULTIPLE;
    int* pMPI_THREAD_SERIALIZED = MUK_DLSYM(wrap_so_handle,"IMPL_THREAD_SERIALIZED");
    MPI_THREAD_SERIALIZED = *pMPI_THREAD_SERIALIZED;
    int* pMPI_THREAD_SINGLE = MUK_DLSYM(wrap_so_handle,"IMPL_THREAD_SINGLE");
    MPI_THREAD_SINGLE = *pMPI_THREAD_SINGLE;

    // File Operation Constants, Part 1
    int* pMPI_DISPLACEMENT_CURRENT = MUK_DLSYM(wrap_so_handle,"IMPL_DISPLACEMENT_CURRENT");
    MPI_DISPLACEMENT_CURRENT = *pMPI_DISPLACEMENT_CURRENT;

    // File Operation Constants, Part 2
    int* pMPI_DISTRIBUTE_BLOCK = MUK_DLSYM(wrap_so_handle,"IMPL_DISTRIBUTE_BLOCK");
    MPI_DISTRIBUTE_BLOCK = *pMPI_DISTRIBUTE_BLOCK;
    int* pMPI_DISTRIBUTE_CYCLIC = MUK_DLSYM(wrap_so_handle,"IMPL_DISTRIBUTE_CYCLIC");
    MPI_DISTRIBUTE_CYCLIC = *pMPI_DISTRIBUTE_CYCLIC;
    int* pMPI_DISTRIBUTE_DFLT_DARG = MUK_DLSYM(wrap_so_handle,"IMPL_DISTRIBUTE_DFLT_DARG");
    MPI_DISTRIBUTE_DFLT_DARG = *pMPI_DISTRIBUTE_DFLT_DARG;
    int* pMPI_DISTRIBUTE_NONE = MUK_DLSYM(wrap_so_handle,"IMPL_DISTRIBUTE_NONE");
    MPI_DISTRIBUTE_NONE = *pMPI_DISTRIBUTE_NONE;
    int* pMPI_ORDER_C = MUK_DLSYM(wrap_so_handle,"IMPL_ORDER_C");
    MPI_ORDER_C = *pMPI_ORDER_C;
    int* pMPI_ORDER_FORTRAN = MUK_DLSYM(wrap_so_handle,"IMPL_ORDER_FORTRAN");
    MPI_ORDER_FORTRAN = *pMPI_ORDER_FORTRAN;
    int* pMPI_SEEK_CUR = MUK_DLSYM(wrap_so_handle,"IMPL_SEEK_CUR");
    MPI_SEEK_CUR = *pMPI_SEEK_CUR;
    int* pMPI_SEEK_END = MUK_DLSYM(wrap_so_handle,"IMPL_SEEK_END");
    MPI_SEEK_END = *pMPI_SEEK_END;
    int* pMPI_SEEK_SET = MUK_DLSYM(wrap_so_handle,"IMPL_SEEK_SET");
    MPI_SEEK_SET = *pMPI_SEEK_SET;

    // F90 Datatype Matching Constants
    int* pMPI_TYPECLASS_COMPLEX = MUK_DLSYM(wrap_so_handle,"IMPL_TYPECLASS_COMPLEX");
    MPI_TYPECLASS_COMPLEX = *pMPI_TYPECLASS_COMPLEX;
    int* pMPI_TYPECLASS_INTEGER = MUK_DLSYM(wrap_so_handle,"IMPL_TYPECLASS_INTEGER");
    MPI_TYPECLASS_INTEGER = *pMPI_TYPECLASS_INTEGER;
    int* pMPI_TYPECLASS_REAL = MUK_DLSYM(wrap_so_handle,"IMPL_TYPECLASS_REAL");
    MPI_TYPECLASS_REAL = *pMPI_TYPECLASS_REAL;
#endif

    // Constants Specifying Empty or Ignored Input
    MPI_ARGVS_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_ARGVS_NULL");
    MPI_ARGV_NULL = MUK_DLSYM(wrap_so_handle,"IMPL_ARGV_NULL");
    MPI_ERRCODES_IGNORE = MUK_DLSYM(wrap_so_handle,"IMPL_ERRCODES_IGNORE");
    void ** pMPI_STATUS_IGNORE   = MUK_DLSYM(wrap_so_handle,"IMPL_STATUS_IGNORE");
    void ** pMPI_STATUSES_IGNORE = MUK_DLSYM(wrap_so_handle,"IMPL_STATUSES_IGNORE");
    MPI_STATUS_IGNORE   = *pMPI_STATUS_IGNORE;
    MPI_STATUSES_IGNORE = *pMPI_STATUSES_IGNORE;
#if 0
    int * MPI_UNWEIGHTED = MUK_DLSYM(wrap_so_handle,"IMPL_UNWEIGHTED");
    int * MPI_WEIGHTS_EMPTY = MUK_DLSYM(wrap_so_handle,"IMPL_WEIGHTS_EMPTY");
#endif

    // all the functions
    MUK_Abort = MUK_DLSYM(wrap_so_handle,"WRAP_Abort");
    MUK_Comm_rank = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_rank");
    MUK_Comm_size = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_size");
    MUK_Accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Accumulate");
    MUK_Accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Accumulate_c");
    MUK_Add_error_class = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_class");
    MUK_Add_error_code = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_code");
    MUK_Add_error_string = MUK_DLSYM(wrap_so_handle, "WRAP_Add_error_string");
    MUK_Address = MUK_DLSYM(wrap_so_handle, "WRAP_Address");
    MUK_Allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather");
    MUK_Allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_c");
    MUK_Allgather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_init");
    MUK_Allgather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgather_init_c");
    MUK_Allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv");
    MUK_Allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_c");
    MUK_Allgatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_init");
    MUK_Allgatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allgatherv_init_c");
    MUK_Alloc_mem = MUK_DLSYM(wrap_so_handle, "WRAP_Alloc_mem");
    MUK_Allreduce = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce");
    MUK_Allreduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_c");
    MUK_Allreduce_init = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_init");
    MUK_Allreduce_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Allreduce_init_c");
    MUK_Alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall");
    MUK_Alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_c");
    MUK_Alltoall_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_init");
    MUK_Alltoall_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoall_init_c");
    MUK_Alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv");
    MUK_Alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_c");
    MUK_Alltoallv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_init");
    MUK_Alltoallv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallv_init_c");
    MUK_Alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw");
    MUK_Alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_c");
    MUK_Alltoallw_init = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_init");
    MUK_Alltoallw_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Alltoallw_init_c");
    MUK_Attr_delete = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_delete");
    MUK_Attr_get = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_get");
    MUK_Attr_put = MUK_DLSYM(wrap_so_handle, "WRAP_Attr_put");
    MUK_Barrier = MUK_DLSYM(wrap_so_handle, "WRAP_Barrier");
    MUK_Barrier_init = MUK_DLSYM(wrap_so_handle, "WRAP_Barrier_init");
    MUK_Bcast = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast");
    MUK_Bcast_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_c");
    MUK_Bcast_init = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_init");
    MUK_Bcast_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bcast_init_c");
    MUK_Bsend = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend");
    MUK_Bsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_c");
    MUK_Bsend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_init");
    MUK_Bsend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Bsend_init_c");
    MUK_Buffer_attach = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_attach");
    MUK_Buffer_attach_c = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_attach_c");
    MUK_Buffer_detach = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_detach");
    MUK_Buffer_detach_c = MUK_DLSYM(wrap_so_handle, "WRAP_Buffer_detach_c");
    MUK_Cancel = MUK_DLSYM(wrap_so_handle, "WRAP_Cancel");
    MUK_Cart_coords = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_coords");
    MUK_Cart_create = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_create");
    MUK_Cart_get = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_get");
    MUK_Cart_map = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_map");
    MUK_Cart_rank = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_rank");
    MUK_Cart_shift = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_shift");
    MUK_Cart_sub = MUK_DLSYM(wrap_so_handle, "WRAP_Cart_sub");
    MUK_Cartdim_get = MUK_DLSYM(wrap_so_handle, "WRAP_Cartdim_get");
    MUK_Close_port = MUK_DLSYM(wrap_so_handle, "WRAP_Close_port");
    MUK_Comm_accept = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_accept");
    MUK_Comm_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_call_errhandler");
    MUK_Comm_compare = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_compare");
    MUK_Comm_connect = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_connect");
    MUK_Comm_create = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create");
    MUK_Comm_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_errhandler");
    MUK_Comm_create_from_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_from_group");
    MUK_Comm_create_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_group");
    MUK_Comm_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_create_keyval");
    MUK_Comm_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_delete_attr");
    MUK_Comm_disconnect = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_disconnect");
    MUK_Comm_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_dup");
    MUK_Comm_dup_with_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_dup_with_info");
    MUK_Comm_free = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_free");
    MUK_Comm_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_free_keyval");
    MUK_Comm_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_attr");
    MUK_Comm_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_errhandler");
    MUK_Comm_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_info");
    MUK_Comm_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_name");
    MUK_Comm_get_parent = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_get_parent");
    MUK_Comm_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_group");
    MUK_Comm_idup = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_idup");
    MUK_Comm_idup_with_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_idup_with_info");
    MUK_Comm_join = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_join");
    MUK_Comm_remote_group = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_remote_group");
    MUK_Comm_remote_size = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_remote_size");
    MUK_Comm_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_attr");
    MUK_Comm_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_errhandler");
    MUK_Comm_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_info");
    MUK_Comm_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_set_name");
    MUK_Comm_split = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_split");
    MUK_Comm_split_type = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_split_type");
    MUK_Comm_test_inter = MUK_DLSYM(wrap_so_handle, "WRAP_Comm_test_inter");
    MUK_Compare_and_swap = MUK_DLSYM(wrap_so_handle, "WRAP_Compare_and_swap");
    MUK_Dims_create = MUK_DLSYM(wrap_so_handle, "WRAP_Dims_create");
    MUK_Dist_graph_create = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_create");
    MUK_Dist_graph_create_adjacent = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_create_adjacent");
    MUK_Dist_graph_neighbors = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_neighbors");
    MUK_Dist_graph_neighbors_count = MUK_DLSYM(wrap_so_handle, "WRAP_Dist_graph_neighbors_count");
    MUK_Errhandler_create = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_create");
    MUK_Errhandler_free = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_free");
    MUK_Errhandler_get = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_get");
    MUK_Errhandler_set = MUK_DLSYM(wrap_so_handle, "WRAP_Errhandler_set");
    MUK_Error_class = MUK_DLSYM(wrap_so_handle, "WRAP_Error_class");
    MUK_Error_string = MUK_DLSYM(wrap_so_handle, "WRAP_Error_string");
    MUK_Exscan = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan");
    MUK_Exscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_c");
    MUK_Exscan_init = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_init");
    MUK_Exscan_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Exscan_init_c");
    MUK_Fetch_and_op = MUK_DLSYM(wrap_so_handle, "WRAP_Fetch_and_op");
    MUK_File_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_call_errhandler");
    MUK_File_close = MUK_DLSYM(wrap_so_handle, "WRAP_File_close");
    MUK_File_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_create_errhandler");
    MUK_File_delete = MUK_DLSYM(wrap_so_handle, "WRAP_File_delete");
    MUK_File_get_amode = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_amode");
    MUK_File_get_atomicity = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_atomicity");
    MUK_File_get_byte_offset = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_byte_offset");
    MUK_File_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_errhandler");
    MUK_File_get_group = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_group");
    MUK_File_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_info");
    MUK_File_get_position = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_position");
    MUK_File_get_position_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_position_shared");
    MUK_File_get_size = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_size");
    MUK_File_get_type_extent = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_type_extent");
    MUK_File_get_type_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_type_extent_c");
    MUK_File_get_view = MUK_DLSYM(wrap_so_handle, "WRAP_File_get_view");
    MUK_File_iread = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread");
    MUK_File_iread_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_all");
    MUK_File_iread_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_all_c");
    MUK_File_iread_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at");
    MUK_File_iread_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_all");
    MUK_File_iread_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_all_c");
    MUK_File_iread_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_at_c");
    MUK_File_iread_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_c");
    MUK_File_iread_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_shared");
    MUK_File_iread_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iread_shared_c");
    MUK_File_iwrite = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite");
    MUK_File_iwrite_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_all");
    MUK_File_iwrite_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_all_c");
    MUK_File_iwrite_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at");
    MUK_File_iwrite_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_all");
    MUK_File_iwrite_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_all_c");
    MUK_File_iwrite_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_at_c");
    MUK_File_iwrite_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_c");
    MUK_File_iwrite_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_shared");
    MUK_File_iwrite_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_iwrite_shared_c");
    MUK_File_open = MUK_DLSYM(wrap_so_handle, "WRAP_File_open");
    MUK_File_preallocate = MUK_DLSYM(wrap_so_handle, "WRAP_File_preallocate");
    MUK_File_read = MUK_DLSYM(wrap_so_handle, "WRAP_File_read");
    MUK_File_read_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all");
    MUK_File_read_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_begin");
    MUK_File_read_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_begin_c");
    MUK_File_read_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_c");
    MUK_File_read_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_all_end");
    MUK_File_read_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at");
    MUK_File_read_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all");
    MUK_File_read_at_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_begin");
    MUK_File_read_at_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_begin_c");
    MUK_File_read_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_c");
    MUK_File_read_at_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_all_end");
    MUK_File_read_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_at_c");
    MUK_File_read_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_c");
    MUK_File_read_ordered = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered");
    MUK_File_read_ordered_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_begin");
    MUK_File_read_ordered_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_begin_c");
    MUK_File_read_ordered_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_c");
    MUK_File_read_ordered_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_ordered_end");
    MUK_File_read_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_shared");
    MUK_File_read_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_read_shared_c");
    MUK_File_seek = MUK_DLSYM(wrap_so_handle, "WRAP_File_seek");
    MUK_File_seek_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_seek_shared");
    MUK_File_set_atomicity = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_atomicity");
    MUK_File_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_errhandler");
    MUK_File_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_info");
    MUK_File_set_size = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_size");
    MUK_File_set_view = MUK_DLSYM(wrap_so_handle, "WRAP_File_set_view");
    MUK_File_sync = MUK_DLSYM(wrap_so_handle, "WRAP_File_sync");
    MUK_File_write = MUK_DLSYM(wrap_so_handle, "WRAP_File_write");
    MUK_File_write_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all");
    MUK_File_write_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_begin");
    MUK_File_write_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_begin_c");
    MUK_File_write_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_c");
    MUK_File_write_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_all_end");
    MUK_File_write_at = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at");
    MUK_File_write_at_all = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all");
    MUK_File_write_at_all_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_begin");
    MUK_File_write_at_all_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_begin_c");
    MUK_File_write_at_all_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_c");
    MUK_File_write_at_all_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_all_end");
    MUK_File_write_at_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_at_c");
    MUK_File_write_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_c");
    MUK_File_write_ordered = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered");
    MUK_File_write_ordered_begin = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_begin");
    MUK_File_write_ordered_begin_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_begin_c");
    MUK_File_write_ordered_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_c");
    MUK_File_write_ordered_end = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_ordered_end");
    MUK_File_write_shared = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_shared");
    MUK_File_write_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_File_write_shared_c");
    MUK_Free_mem = MUK_DLSYM(wrap_so_handle, "WRAP_Free_mem");
    MUK_Gather = MUK_DLSYM(wrap_so_handle, "WRAP_Gather");
    MUK_Gather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_c");
    MUK_Gather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_init");
    MUK_Gather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gather_init_c");
    MUK_Gatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv");
    MUK_Gatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_c");
    MUK_Gatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_init");
    MUK_Gatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Gatherv_init_c");
    MUK_Get = MUK_DLSYM(wrap_so_handle, "WRAP_Get");
    MUK_Get_accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Get_accumulate");
    MUK_Get_accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_accumulate_c");
    MUK_Get_address = MUK_DLSYM(wrap_so_handle, "WRAP_Get_address");
    MUK_Get_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_c");
    MUK_Get_count = MUK_DLSYM(wrap_so_handle, "WRAP_Get_count");
    MUK_Get_count_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_count_c");
    MUK_Get_elements = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements");
    MUK_Get_elements_c = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements_c");
    MUK_Get_elements_x = MUK_DLSYM(wrap_so_handle, "WRAP_Get_elements_x");
    MUK_Graph_create = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_create");
    MUK_Graph_get = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_get");
    MUK_Graph_map = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_map");
    MUK_Graph_neighbors = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_neighbors");
    MUK_Graph_neighbors_count = MUK_DLSYM(wrap_so_handle, "WRAP_Graph_neighbors_count");
    MUK_Graphdims_get = MUK_DLSYM(wrap_so_handle, "WRAP_Graphdims_get");
    MUK_Grequest_complete = MUK_DLSYM(wrap_so_handle, "WRAP_Grequest_complete");
    MUK_Grequest_start = MUK_DLSYM(wrap_so_handle, "WRAP_Grequest_start");
    MUK_Group_compare = MUK_DLSYM(wrap_so_handle, "WRAP_Group_compare");
    MUK_Group_difference = MUK_DLSYM(wrap_so_handle, "WRAP_Group_difference");
    MUK_Group_excl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_excl");
    MUK_Group_free = MUK_DLSYM(wrap_so_handle, "WRAP_Group_free");
    MUK_Group_from_session_pset = MUK_DLSYM(wrap_so_handle, "WRAP_Group_from_session_pset");
    MUK_Group_incl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_incl");
    MUK_Group_intersection = MUK_DLSYM(wrap_so_handle, "WRAP_Group_intersection");
    MUK_Group_range_excl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_range_excl");
    MUK_Group_range_incl = MUK_DLSYM(wrap_so_handle, "WRAP_Group_range_incl");
    MUK_Group_rank = MUK_DLSYM(wrap_so_handle, "WRAP_Group_rank");
    MUK_Group_size = MUK_DLSYM(wrap_so_handle, "WRAP_Group_size");
    MUK_Group_translate_ranks = MUK_DLSYM(wrap_so_handle, "WRAP_Group_translate_ranks");
    MUK_Group_union = MUK_DLSYM(wrap_so_handle, "WRAP_Group_union");
    MUK_Iallgather = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgather");
    MUK_Iallgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgather_c");
    MUK_Iallgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgatherv");
    MUK_Iallgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallgatherv_c");
    MUK_Iallreduce = MUK_DLSYM(wrap_so_handle, "WRAP_Iallreduce");
    MUK_Iallreduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iallreduce_c");
    MUK_Ialltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoall");
    MUK_Ialltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoall_c");
    MUK_Ialltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallv");
    MUK_Ialltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallv_c");
    MUK_Ialltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallw");
    MUK_Ialltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ialltoallw_c");
    MUK_Ibarrier = MUK_DLSYM(wrap_so_handle, "WRAP_Ibarrier");
    MUK_Ibcast = MUK_DLSYM(wrap_so_handle, "WRAP_Ibcast");
    MUK_Ibcast_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ibcast_c");
    MUK_Ibsend = MUK_DLSYM(wrap_so_handle, "WRAP_Ibsend");
    MUK_Ibsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ibsend_c");
    MUK_Iexscan = MUK_DLSYM(wrap_so_handle, "WRAP_Iexscan");
    MUK_Iexscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iexscan_c");
    MUK_Igather = MUK_DLSYM(wrap_so_handle, "WRAP_Igather");
    MUK_Igather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Igather_c");
    MUK_Igatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Igatherv");
    MUK_Igatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Igatherv_c");
    MUK_Improbe = MUK_DLSYM(wrap_so_handle, "WRAP_Improbe");
    MUK_Imrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Imrecv");
    MUK_Imrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Imrecv_c");
    MUK_Ineighbor_allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgather");
    MUK_Ineighbor_allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgather_c");
    MUK_Ineighbor_allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgatherv");
    MUK_Ineighbor_allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_allgatherv_c");
    MUK_Ineighbor_alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoall");
    MUK_Ineighbor_alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoall_c");
    MUK_Ineighbor_alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallv");
    MUK_Ineighbor_alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallv_c");
    MUK_Ineighbor_alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallw");
    MUK_Ineighbor_alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ineighbor_alltoallw_c");
    MUK_Info_create = MUK_DLSYM(wrap_so_handle, "WRAP_Info_create");
    MUK_Info_create_env = MUK_DLSYM(wrap_so_handle, "WRAP_Info_create_env");
    MUK_Info_delete = MUK_DLSYM(wrap_so_handle, "WRAP_Info_delete");
    MUK_Info_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Info_dup");
    MUK_Info_free = MUK_DLSYM(wrap_so_handle, "WRAP_Info_free");
    MUK_Info_get = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get");
    MUK_Info_get_nkeys = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_nkeys");
    MUK_Info_get_nthkey = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_nthkey");
    MUK_Info_get_string = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_string");
    MUK_Info_get_valuelen = MUK_DLSYM(wrap_so_handle, "WRAP_Info_get_valuelen");
    MUK_Info_set = MUK_DLSYM(wrap_so_handle, "WRAP_Info_set");
    MUK_Intercomm_create = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_create");
    MUK_Intercomm_create_from_groups = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_create_from_groups");
    MUK_Intercomm_merge = MUK_DLSYM(wrap_so_handle, "WRAP_Intercomm_merge");
    MUK_Iprobe = MUK_DLSYM(wrap_so_handle, "WRAP_Iprobe");
    MUK_Irecv = MUK_DLSYM(wrap_so_handle, "WRAP_Irecv");
    MUK_Irecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Irecv_c");
    MUK_Ireduce = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce");
    MUK_Ireduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_c");
    MUK_Ireduce_scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter");
    MUK_Ireduce_scatter_block = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_block");
    MUK_Ireduce_scatter_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_block_c");
    MUK_Ireduce_scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ireduce_scatter_c");
    MUK_Irsend = MUK_DLSYM(wrap_so_handle, "WRAP_Irsend");
    MUK_Irsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Irsend_c");
    MUK_Iscan = MUK_DLSYM(wrap_so_handle, "WRAP_Iscan");
    MUK_Iscan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscan_c");
    MUK_Iscatter = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatter");
    MUK_Iscatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatter_c");
    MUK_Iscatterv = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatterv");
    MUK_Iscatterv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Iscatterv_c");
    MUK_Isend = MUK_DLSYM(wrap_so_handle, "WRAP_Isend");
    MUK_Isend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isend_c");
    MUK_Isendrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv");
    MUK_Isendrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_c");
    MUK_Isendrecv_replace = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_replace");
    MUK_Isendrecv_replace_c = MUK_DLSYM(wrap_so_handle, "WRAP_Isendrecv_replace_c");
    MUK_Issend = MUK_DLSYM(wrap_so_handle, "WRAP_Issend");
    MUK_Issend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Issend_c");
#if 0
    MUK_Keyval_create = MUK_DLSYM(wrap_so_handle, "WRAP_Keyval_create");
    MUK_Keyval_free = MUK_DLSYM(wrap_so_handle, "WRAP_Keyval_free");
#endif
    MUK_Lookup_name = MUK_DLSYM(wrap_so_handle, "WRAP_Lookup_name");
    MUK_Mprobe = MUK_DLSYM(wrap_so_handle, "WRAP_Mprobe");
    MUK_Mrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Mrecv");
    MUK_Mrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Mrecv_c");
    MUK_Neighbor_allgather = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather");
    MUK_Neighbor_allgather_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_c");
    MUK_Neighbor_allgather_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_init");
    MUK_Neighbor_allgather_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgather_init_c");
    MUK_Neighbor_allgatherv = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv");
    MUK_Neighbor_allgatherv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_c");
    MUK_Neighbor_allgatherv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_init");
    MUK_Neighbor_allgatherv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_allgatherv_init_c");
    MUK_Neighbor_alltoall = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall");
    MUK_Neighbor_alltoall_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_c");
    MUK_Neighbor_alltoall_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_init");
    MUK_Neighbor_alltoall_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoall_init_c");
    MUK_Neighbor_alltoallv = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv");
    MUK_Neighbor_alltoallv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_c");
    MUK_Neighbor_alltoallv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_init");
    MUK_Neighbor_alltoallv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallv_init_c");
    MUK_Neighbor_alltoallw = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw");
    MUK_Neighbor_alltoallw_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_c");
    MUK_Neighbor_alltoallw_init = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_init");
    MUK_Neighbor_alltoallw_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Neighbor_alltoallw_init_c");
    MUK_Op_commutative = MUK_DLSYM(wrap_so_handle, "WRAP_Op_commutative");
    MUK_Op_create = MUK_DLSYM(wrap_so_handle, "WRAP_Op_create");
    MUK_Op_create_c = MUK_DLSYM(wrap_so_handle, "WRAP_Op_create_c");
    MUK_Op_free = MUK_DLSYM(wrap_so_handle, "WRAP_Op_free");
    MUK_Open_port = MUK_DLSYM(wrap_so_handle, "WRAP_Open_port");
    MUK_Pack = MUK_DLSYM(wrap_so_handle, "WRAP_Pack");
    MUK_Pack_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_c");
    MUK_Pack_external = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external");
    MUK_Pack_external_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_c");
    MUK_Pack_external_size = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_size");
    MUK_Pack_external_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_external_size_c");
    MUK_Pack_size = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_size");
    MUK_Pack_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Pack_size_c");
    MUK_Parrived = MUK_DLSYM(wrap_so_handle, "WRAP_Parrived");
    MUK_Pcontrol = MUK_DLSYM(wrap_so_handle, "WRAP_Pcontrol");
    MUK_Pready = MUK_DLSYM(wrap_so_handle, "WRAP_Pready");
    MUK_Pready_list = MUK_DLSYM(wrap_so_handle, "WRAP_Pready_list");
    MUK_Pready_range = MUK_DLSYM(wrap_so_handle, "WRAP_Pready_range");
    MUK_Precv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Precv_init");
    MUK_Probe = MUK_DLSYM(wrap_so_handle, "WRAP_Probe");
    MUK_Psend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Psend_init");
    MUK_Publish_name = MUK_DLSYM(wrap_so_handle, "WRAP_Publish_name");
    MUK_Put = MUK_DLSYM(wrap_so_handle, "WRAP_Put");
    MUK_Put_c = MUK_DLSYM(wrap_so_handle, "WRAP_Put_c");
    MUK_Raccumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Raccumulate");
    MUK_Raccumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Raccumulate_c");
    MUK_Recv = MUK_DLSYM(wrap_so_handle, "WRAP_Recv");
    MUK_Recv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_c");
    MUK_Recv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_init");
    MUK_Recv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Recv_init_c");
    MUK_Reduce = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce");
    MUK_Reduce_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_c");
    MUK_Reduce_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_init");
    MUK_Reduce_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_init_c");
    MUK_Reduce_local = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_local");
    MUK_Reduce_local_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_local_c");
    MUK_Reduce_scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter");
    MUK_Reduce_scatter_block = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block");
    MUK_Reduce_scatter_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_c");
    MUK_Reduce_scatter_block_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_init");
    MUK_Reduce_scatter_block_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_block_init_c");
    MUK_Reduce_scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_c");
    MUK_Reduce_scatter_init = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_init");
    MUK_Reduce_scatter_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Reduce_scatter_init_c");
    MUK_Register_datarep = MUK_DLSYM(wrap_so_handle, "WRAP_Register_datarep");
    MUK_Register_datarep_c = MUK_DLSYM(wrap_so_handle, "WRAP_Register_datarep_c");
    MUK_Request_free = MUK_DLSYM(wrap_so_handle, "WRAP_Request_free");
    MUK_Request_get_status = MUK_DLSYM(wrap_so_handle, "WRAP_Request_get_status");
    MUK_Rget = MUK_DLSYM(wrap_so_handle, "WRAP_Rget");
    MUK_Rget_accumulate = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_accumulate");
    MUK_Rget_accumulate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_accumulate_c");
    MUK_Rget_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rget_c");
    MUK_Rput = MUK_DLSYM(wrap_so_handle, "WRAP_Rput");
    MUK_Rput_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rput_c");
    MUK_Rsend = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend");
    MUK_Rsend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_c");
    MUK_Rsend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_init");
    MUK_Rsend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Rsend_init_c");
    MUK_Scan = MUK_DLSYM(wrap_so_handle, "WRAP_Scan");
    MUK_Scan_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_c");
    MUK_Scan_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_init");
    MUK_Scan_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scan_init_c");
    MUK_Scatter = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter");
    MUK_Scatter_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_c");
    MUK_Scatter_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_init");
    MUK_Scatter_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatter_init_c");
    MUK_Scatterv = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv");
    MUK_Scatterv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_c");
    MUK_Scatterv_init = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_init");
    MUK_Scatterv_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Scatterv_init_c");
    MUK_Send = MUK_DLSYM(wrap_so_handle, "WRAP_Send");
    MUK_Send_c = MUK_DLSYM(wrap_so_handle, "WRAP_Send_c");
    MUK_Send_init = MUK_DLSYM(wrap_so_handle, "WRAP_Send_init");
    MUK_Send_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Send_init_c");
    MUK_Sendrecv = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv");
    MUK_Sendrecv_c = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_c");
    MUK_Sendrecv_replace = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_replace");
    MUK_Sendrecv_replace_c = MUK_DLSYM(wrap_so_handle, "WRAP_Sendrecv_replace_c");
    MUK_Session_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_call_errhandler");
    MUK_Session_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_create_errhandler");
    MUK_Session_finalize = MUK_DLSYM(wrap_so_handle, "WRAP_Session_finalize");
    MUK_Session_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_errhandler");
    MUK_Session_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_info");
    MUK_Session_get_nth_pset = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_nth_pset");
    MUK_Session_get_num_psets = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_num_psets");
    MUK_Session_get_pset_info = MUK_DLSYM(wrap_so_handle, "WRAP_Session_get_pset_info");
    MUK_Session_init = MUK_DLSYM(wrap_so_handle, "WRAP_Session_init");
    MUK_Session_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Session_set_errhandler");
    MUK_Ssend = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend");
    MUK_Ssend_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_c");
    MUK_Ssend_init = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_init");
    MUK_Ssend_init_c = MUK_DLSYM(wrap_so_handle, "WRAP_Ssend_init_c");
    MUK_Start = MUK_DLSYM(wrap_so_handle, "WRAP_Start");
    MUK_Startall = MUK_DLSYM(wrap_so_handle, "WRAP_Startall");
#ifdef SUPPORT_F08
    MUK_Status_f082c = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f082c");
    MUK_Status_f082f = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f082f");
    MUK_Status_f2f08 = MUK_DLSYM(wrap_so_handle, "WRAP_Status_f2f08");
#endif
    MUK_Status_set_cancelled = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_cancelled");
    MUK_Status_set_elements = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_elements");
    MUK_Status_set_elements_c = MUK_DLSYM_OPT(wrap_so_handle, "WRAP_Status_set_elements_c", "WRAP_Status_set_elements");
    MUK_Status_set_elements_x = MUK_DLSYM(wrap_so_handle, "WRAP_Status_set_elements_x");
    MUK_Test = MUK_DLSYM(wrap_so_handle, "WRAP_Test");
    MUK_Test_cancelled = MUK_DLSYM(wrap_so_handle, "WRAP_Test_cancelled");
    MUK_Testall = MUK_DLSYM(wrap_so_handle, "WRAP_Testall");
    MUK_Testany = MUK_DLSYM(wrap_so_handle, "WRAP_Testany");
    MUK_Testsome = MUK_DLSYM(wrap_so_handle, "WRAP_Testsome");
    MUK_Topo_test = MUK_DLSYM(wrap_so_handle, "WRAP_Topo_test");
    MUK_Type_commit = MUK_DLSYM(wrap_so_handle, "WRAP_Type_commit");
    MUK_Type_contiguous = MUK_DLSYM(wrap_so_handle, "WRAP_Type_contiguous");
    MUK_Type_contiguous_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_contiguous_c");
    MUK_Type_create_darray = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_darray");
    MUK_Type_create_darray_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_darray_c");
    MUK_Type_create_f90_complex = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_complex");
    MUK_Type_create_f90_integer = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_integer");
    MUK_Type_create_f90_real = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_f90_real");
    MUK_Type_create_hindexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed");
    MUK_Type_create_hindexed_block = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_block");
    MUK_Type_create_hindexed_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_block_c");
    MUK_Type_create_hindexed_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hindexed_c");
    MUK_Type_create_hvector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hvector");
    MUK_Type_create_hvector_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_hvector_c");
    MUK_Type_create_indexed_block = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_indexed_block");
    MUK_Type_create_indexed_block_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_indexed_block_c");
    MUK_Type_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_keyval");
    MUK_Type_create_resized = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_resized");
    MUK_Type_create_resized_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_resized_c");
    MUK_Type_create_struct = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_struct");
    MUK_Type_create_struct_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_struct_c");
    MUK_Type_create_subarray = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_subarray");
    MUK_Type_create_subarray_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_create_subarray_c");
    MUK_Type_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_delete_attr");
    MUK_Type_dup = MUK_DLSYM(wrap_so_handle, "WRAP_Type_dup");
    MUK_Type_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_extent");
    MUK_Type_free = MUK_DLSYM(wrap_so_handle, "WRAP_Type_free");
    MUK_Type_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Type_free_keyval");
    MUK_Type_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_attr");
    MUK_Type_get_contents = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_contents");
    MUK_Type_get_contents_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_contents_c");
    MUK_Type_get_envelope = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_envelope");
    MUK_Type_get_envelope_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_envelope_c");
    MUK_Type_get_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent");
    MUK_Type_get_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent_c");
    MUK_Type_get_extent_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_extent_x");
    MUK_Type_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_name");
    MUK_Type_get_true_extent = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent");
    MUK_Type_get_true_extent_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent_c");
    MUK_Type_get_true_extent_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_get_true_extent_x");
    MUK_Type_hindexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_hindexed");
    MUK_Type_hvector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_hvector");
    MUK_Type_indexed = MUK_DLSYM(wrap_so_handle, "WRAP_Type_indexed");
    MUK_Type_indexed_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_indexed_c");
    MUK_Type_lb = MUK_DLSYM(wrap_so_handle, "WRAP_Type_lb");
    MUK_Type_match_size = MUK_DLSYM(wrap_so_handle, "WRAP_Type_match_size");
    MUK_Type_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Type_set_attr");
    MUK_Type_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Type_set_name");
    MUK_Type_size = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size");
    MUK_Type_size_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size_c");
    MUK_Type_size_x = MUK_DLSYM(wrap_so_handle, "WRAP_Type_size_x");
    MUK_Type_struct = MUK_DLSYM(wrap_so_handle, "WRAP_Type_struct");
    MUK_Type_ub = MUK_DLSYM(wrap_so_handle, "WRAP_Type_ub");
    MUK_Type_vector = MUK_DLSYM(wrap_so_handle, "WRAP_Type_vector");
    MUK_Type_vector_c = MUK_DLSYM(wrap_so_handle, "WRAP_Type_vector_c");
    MUK_Unpack = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack");
    MUK_Unpack_c = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_c");
    MUK_Unpack_external = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_external");
    MUK_Unpack_external_c = MUK_DLSYM(wrap_so_handle, "WRAP_Unpack_external_c");
    MUK_Unpublish_name = MUK_DLSYM(wrap_so_handle, "WRAP_Unpublish_name");
    MUK_Wait = MUK_DLSYM(wrap_so_handle, "WRAP_Wait");
    MUK_Waitall = MUK_DLSYM(wrap_so_handle, "WRAP_Waitall");
    MUK_Waitany = MUK_DLSYM(wrap_so_handle, "WRAP_Waitany");
    MUK_Waitsome = MUK_DLSYM(wrap_so_handle, "WRAP_Waitsome");
    MUK_Win_allocate = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate");
    MUK_Win_allocate_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_c");
    MUK_Win_allocate_shared = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_shared");
    MUK_Win_allocate_shared_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_allocate_shared_c");
    MUK_Win_attach = MUK_DLSYM(wrap_so_handle, "WRAP_Win_attach");
    MUK_Win_call_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_call_errhandler");
    MUK_Win_complete = MUK_DLSYM(wrap_so_handle, "WRAP_Win_complete");
    MUK_Win_create = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create");
    MUK_Win_create_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_c");
    MUK_Win_create_dynamic = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_dynamic");
    MUK_Win_create_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_errhandler");
    MUK_Win_create_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Win_create_keyval");
    MUK_Win_delete_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_delete_attr");
    MUK_Win_detach = MUK_DLSYM(wrap_so_handle, "WRAP_Win_detach");
    MUK_Win_fence = MUK_DLSYM(wrap_so_handle, "WRAP_Win_fence");
    MUK_Win_flush = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush");
    MUK_Win_flush_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_all");
    MUK_Win_flush_local = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_local");
    MUK_Win_flush_local_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_flush_local_all");
    MUK_Win_free = MUK_DLSYM(wrap_so_handle, "WRAP_Win_free");
    MUK_Win_free_keyval = MUK_DLSYM(wrap_so_handle, "WRAP_Win_free_keyval");
    MUK_Win_get_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_attr");
    MUK_Win_get_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_errhandler");
    MUK_Win_get_group = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_group");
    MUK_Win_get_info = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_info");
    MUK_Win_get_name = MUK_DLSYM(wrap_so_handle, "WRAP_Win_get_name");
    MUK_Win_lock = MUK_DLSYM(wrap_so_handle, "WRAP_Win_lock");
    MUK_Win_lock_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_lock_all");
    MUK_Win_post = MUK_DLSYM(wrap_so_handle, "WRAP_Win_post");
    MUK_Win_set_attr = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_attr");
    MUK_Win_set_errhandler = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_errhandler");
    MUK_Win_set_info = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_info");
    MUK_Win_set_name = MUK_DLSYM(wrap_so_handle, "WRAP_Win_set_name");
    MUK_Win_shared_query = MUK_DLSYM(wrap_so_handle, "WRAP_Win_shared_query");
    MUK_Win_shared_query_c = MUK_DLSYM(wrap_so_handle, "WRAP_Win_shared_query_c");
    MUK_Win_start = MUK_DLSYM(wrap_so_handle, "WRAP_Win_start");
    MUK_Win_sync = MUK_DLSYM(wrap_so_handle, "WRAP_Win_sync");
    MUK_Win_test = MUK_DLSYM(wrap_so_handle, "WRAP_Win_test");
    MUK_Win_unlock = MUK_DLSYM(wrap_so_handle, "WRAP_Win_unlock");
    MUK_Win_unlock_all = MUK_DLSYM(wrap_so_handle, "WRAP_Win_unlock_all");
    MUK_Win_wait = MUK_DLSYM(wrap_so_handle, "WRAP_Win_wait");

    WRAP_Load_functions = MUK_DLSYM(wrap_so_handle,"WRAP_Load_functions");
    rc = WRAP_Load_functions(h,major,minor);

    WRAP_CODE_IMPL_TO_MUK = MUK_DLSYM(wrap_so_handle,"ERROR_CODE_IMPL_TO_MUK");

    return rc;
}

int MPI_Init(int * argc, char *** argv)
{
    int rc = MUK_Alkaa(argc,argv,-1,NULL);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Init_thread(int * argc, char *** argv, int requested, int * provided)
{
    // no thread conversion here because MUK, MPICH and OMPI all agree
    int rc = MUK_Alkaa(argc,argv,requested,provided);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Get_library_version(char *version, int *resultlen)
{
    // calling this function before MPI initialization is allowed.
    // we should dlopen the MPI implementation when this is called,
    // but that is not what we are implementing for now.
    if (MUK_Get_library_version == NULL) {
        *resultlen = 1 + sprintf(version,"MUKAUTUVA: the underlying MPI library is not initialized.\n");
    }
    int rc = MUK_Get_library_version(version, resultlen);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Finalize(void)
{
    int rc = MUK_Finalize();
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Finalized(int * flag)
{
    // calling this function before MPI initialization is allowed.
    if (MUK_Finalized == NULL) {
        *flag = 0;
        return MPI_SUCCESS;
    }
    int rc = MUK_Finalized(flag);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Initialized(int * flag)
{
    // calling this function before MPI initialization is allowed.
    if (MUK_Initialized == NULL) {
        *flag = 0;
        return MPI_SUCCESS;
    }
    int rc = MUK_Initialized(flag);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Is_thread_main(int * flag)
{
    int rc = MUK_Is_thread_main(flag);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Query_thread(int * provided)
{
    // no thread conversion here because MUK, MPICH and OMPI all agree
    int rc = MUK_Query_thread(provided);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Get_processor_name(char *name, int *resultlen)
{
    int rc = MUK_Get_processor_name(name, resultlen);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Get_version(int * major, int * minor)
{
    // calling this function before MPI initialization is allowed.
    // we should dlopen the MPI implementation when this is called,
    // but that is not what we are implementing for now.
    if (MUK_Get_version == NULL) {
        *major = 3;
        *minor = 1;
        return MPI_SUCCESS;
    }
    int rc = MUK_Get_version(major, minor);
    return WRAP_CODE_IMPL_TO_MUK(rc);
}

int MPI_Abort(MPI_Comm comm, int errorcode)
{
    return MUK_Abort(comm, errorcode);
}

int MPI_Comm_rank(MPI_Comm comm, int * rank)
{
    return MUK_Comm_rank(comm, rank);
}

int MPI_Comm_size(MPI_Comm comm, int * size)
{
    return MUK_Comm_size(comm, size);
}

int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return MUK_Accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return MUK_Accumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Add_error_class(int *errorclass)
{
    return MUK_Add_error_class(errorclass);
}

int MPI_Add_error_code(int errorclass, int *errorcode)
{
    return MUK_Add_error_code(errorclass, errorcode);
}

int MPI_Add_error_string(int errorcode, const char *string)
{
    return MUK_Add_error_string(errorcode, string);
}

int MPI_Address(void *location, MPI_Aint *address)
{
    return MUK_Address(location, address);
}

int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr)
{
    return MUK_Alloc_mem(size, info, baseptr);
}

int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Allreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Allreduce_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Allreduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allreduce_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Allreduce_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Allreduce_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return MUK_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return MUK_Alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Alltoallw_init(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Attr_delete(MPI_Comm comm, int keyval)
{
    return MUK_Attr_delete(comm, keyval);
}

int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag)
{
    return MUK_Attr_get(comm, keyval, attribute_val, flag);
}

int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val)
{
    return MUK_Attr_put(comm, keyval, attribute_val);
}

int MPI_Barrier(MPI_Comm comm)
{
    return MUK_Barrier(comm);
}

int MPI_Barrier_init(MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Barrier_init(comm, info, request);
}

int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    return MUK_Bcast(buffer, count, datatype, root, comm);
}

int MPI_Bcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    return MUK_Bcast_c(buffer, count, datatype, root, comm);
}

int MPI_Bcast_init(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Bcast_init(buffer, count, datatype, root, comm, info, request);
}

int MPI_Bcast_init_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Bcast_init_c(buffer, count, datatype, root, comm, info, request);
}

int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Bsend(buf, count, datatype, dest, tag, comm);
}

int MPI_Bsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Bsend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Bsend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Bsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Bsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Buffer_attach(void *buffer, int size)
{
    return MUK_Buffer_attach(buffer, size);
}

int MPI_Buffer_attach_c(void *buffer, MPI_Count size)
{
    return MUK_Buffer_attach_c(buffer, size);
}

int MPI_Buffer_detach(void *buffer_addr, int *size)
{
    return MUK_Buffer_detach(buffer_addr, size);
}

int MPI_Buffer_detach_c(void *buffer_addr, MPI_Count *size)
{
    return MUK_Buffer_detach_c(buffer_addr, size);
}

int MPI_Cancel(MPI_Request *request)
{
    return MUK_Cancel(request);
}

int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[])
{
    return MUK_Cart_coords(comm, rank, maxdims, coords);
}

int MPI_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart)
{
    return MUK_Cart_create(comm_old, ndims, dims, periods, reorder, comm_cart);
}

int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    return MUK_Cart_get(comm, maxdims, dims, periods, coords);
}

int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank)
{
    return MUK_Cart_map(comm, ndims, dims, periods, newrank);
}

int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank)
{
    return MUK_Cart_rank(comm, coords, rank);
}

int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest)
{
    return MUK_Cart_shift(comm, direction, disp, rank_source, rank_dest);
}

int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *newcomm)
{
    return MUK_Cart_sub(comm, remain_dims, newcomm);
}

int MPI_Cartdim_get(MPI_Comm comm, int *ndims)
{
    return MUK_Cartdim_get(comm, ndims);
}

int MPI_Close_port(const char *port_name)
{
    return MUK_Close_port(port_name);
}

int MPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm)
{
    return MUK_Comm_accept(port_name, info, root, comm, newcomm);
}

int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode)
{
    return MUK_Comm_call_errhandler(comm, errorcode);
}

int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result)
{
    return MUK_Comm_compare(comm1, comm2, result);
}

int MPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm)
{
    return MUK_Comm_connect(port_name, info, root, comm, newcomm);
}

int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
{
    return MUK_Comm_create(comm, group, newcomm);
}

int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler)
{
    return MUK_Comm_create_errhandler(comm_errhandler_fn, errhandler);
}

int MPI_Comm_create_from_group(MPI_Group group, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newcomm)
{
    return MUK_Comm_create_from_group(group, stringtag, info, errhandler, newcomm);
}

int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm)
{
    return MUK_Comm_create_group(comm, group, tag, newcomm);
}

int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state)
{
    return MUK_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
}

int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
    return MUK_Comm_delete_attr(comm, comm_keyval);
}

int MPI_Comm_disconnect(MPI_Comm *comm)
{
    return MUK_Comm_disconnect(comm);
}

int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm)
{
    return MUK_Comm_dup(comm, newcomm);
}

int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm)
{
    return MUK_Comm_dup_with_info(comm, info, newcomm);
}

int MPI_Comm_free(MPI_Comm *comm)
{
    int rc = MUK_Comm_free(comm);
    return rc;
}

int MPI_Comm_free_keyval(int *comm_keyval)
{
    return MUK_Comm_free_keyval(comm_keyval);
}

int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag)
{
    return MUK_Comm_get_attr(comm, comm_keyval, attribute_val, flag);
}

int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *errhandler)
{
    return MUK_Comm_get_errhandler(comm, errhandler);
}

int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used)
{
    return MUK_Comm_get_info(comm, info_used);
}

int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen)
{
    return MUK_Comm_get_name(comm, comm_name, resultlen);
}

int MPI_Comm_get_parent(MPI_Comm *parent)
{
    return MUK_Comm_get_parent(parent);
}

int MPI_Comm_group(MPI_Comm comm, MPI_Group *group)
{
    return MUK_Comm_group(comm, group);
}

int MPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request)
{
    return MUK_Comm_idup(comm, newcomm, request);
}

int MPI_Comm_idup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, MPI_Request *request)
{
    return MUK_Comm_idup_with_info(comm, info, newcomm, request);
}

int MPI_Comm_join(int fd, MPI_Comm *intercomm)
{
    return MUK_Comm_join(fd, intercomm);
}

int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group)
{
    return MUK_Comm_remote_group(comm, group);
}

int MPI_Comm_remote_size(MPI_Comm comm, int *size)
{
    return MUK_Comm_remote_size(comm, size);
}

int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val)
{
    return MUK_Comm_set_attr(comm, comm_keyval, attribute_val);
}

int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
    return MUK_Comm_set_errhandler(comm, errhandler);
}

int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info)
{
    return MUK_Comm_set_info(comm, info);
}

int MPI_Comm_set_name(MPI_Comm comm, const char *comm_name)
{
    return MUK_Comm_set_name(comm, comm_name);
}

int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm)
{
    return MUK_Comm_split(comm, color, key, newcomm);
}

int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm)
{
    return MUK_Comm_split_type(comm, split_type, key, info, newcomm);
}

int MPI_Comm_test_inter(MPI_Comm comm, int *flag)
{
    return MUK_Comm_test_inter(comm, flag);
}

int MPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win)
{
    return MUK_Compare_and_swap(origin_addr, compare_addr, result_addr, datatype, target_rank, target_disp, win);
}

int MPI_Dims_create(int nnodes, int ndims, int dims[])
{
    return MUK_Dims_create(nnodes, ndims, dims);
}

int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[], const int destinations[], const int weights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph)
{
    return MUK_Dist_graph_create(comm_old, n, sources, degrees, destinations, weights, info, reorder, comm_dist_graph);
}

int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph)
{
    return MUK_Dist_graph_create_adjacent(comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights, info, reorder, comm_dist_graph);
}

int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    return MUK_Dist_graph_neighbors(comm, maxindegree, sources, sourceweights, maxoutdegree, destinations, destweights);
}

int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int *indegree, int *outdegree, int *weighted)
{
    return MUK_Dist_graph_neighbors_count(comm, indegree, outdegree, weighted);
}

int MPI_Errhandler_create(MPI_Comm_errhandler_function *comm_errhandler_fn, MPI_Errhandler *errhandler)
{
    return MUK_Errhandler_create(comm_errhandler_fn, errhandler);
}

int MPI_Errhandler_free(MPI_Errhandler *errhandler)
{
    return MUK_Errhandler_free(errhandler);
}

int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler)
{
    return MUK_Errhandler_get(comm, errhandler);
}

int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler)
{
    return MUK_Errhandler_set(comm, errhandler);
}

int MPI_Error_class(int errorcode, int *errorclass)
{
    return MUK_Error_class(errorcode, errorclass);
}

int MPI_Error_string(int errorcode, char *string, int *resultlen)
{
    return MUK_Error_string(errorcode, string, resultlen);
}

int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Exscan(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Exscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Exscan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Exscan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Exscan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Exscan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Exscan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win)
{
    return MUK_Fetch_and_op(origin_addr, result_addr, datatype, target_rank, target_disp, op, win);
}

int MPI_File_call_errhandler(MPI_File fh, int errorcode)
{
    return MUK_File_call_errhandler(fh, errorcode);
}

int MPI_File_close(MPI_File *fh)
{
    return MUK_File_close(fh);
}

int MPI_File_create_errhandler(MPI_File_errhandler_function *file_errhandler_fn, MPI_Errhandler *errhandler)
{
    return MUK_File_create_errhandler(file_errhandler_fn, errhandler);
}

int MPI_File_delete(const char *filename, MPI_Info info)
{
    return MUK_File_delete(filename, info);
}

int MPI_File_get_amode(MPI_File fh, int *amode)
{
    return MUK_File_get_amode(fh, amode);
}

int MPI_File_get_atomicity(MPI_File fh, int *flag)
{
    return MUK_File_get_atomicity(fh, flag);
}

int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp)
{
    return MUK_File_get_byte_offset(fh, offset, disp);
}

int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler)
{
    return MUK_File_get_errhandler(file, errhandler);
}

int MPI_File_get_group(MPI_File fh, MPI_Group *group)
{
    return MUK_File_get_group(fh, group);
}

int MPI_File_get_info(MPI_File fh, MPI_Info *info_used)
{
    return MUK_File_get_info(fh, info_used);
}

int MPI_File_get_position(MPI_File fh, MPI_Offset *offset)
{
    return MUK_File_get_position(fh, offset);
}

int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset)
{
    return MUK_File_get_position_shared(fh, offset);
}

int MPI_File_get_size(MPI_File fh, MPI_Offset *size)
{
    return MUK_File_get_size(fh, size);
}

int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent)
{
    return MUK_File_get_type_extent(fh, datatype, extent);
}

int MPI_File_get_type_extent_c(MPI_File fh, MPI_Datatype datatype, MPI_Count *extent)
{
    return MUK_File_get_type_extent_c(fh, datatype, extent);
}

int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep)
{
    return MUK_File_get_view(fh, disp, etype, filetype, datarep);
}

int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread(fh, buf, count, datatype, request);
}

int MPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_all(fh, buf, count, datatype, request);
}

int MPI_File_iread_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_all_c(fh, buf, count, datatype, request);
}

int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_at_all(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_at_all_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_at_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_c(fh, buf, count, datatype, request);
}

int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_shared(fh, buf, count, datatype, request);
}

int MPI_File_iread_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iread_shared_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_all(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_all_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_at_all(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_at_all_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_at_c(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_c(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_shared(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Request *request)
{
    return MUK_File_iwrite_shared_c(fh, buf, count, datatype, request);
}

int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh)
{
    return MUK_File_open(comm, filename, amode, info, fh);
}

int MPI_File_preallocate(MPI_File fh, MPI_Offset size)
{
    return MUK_File_preallocate(fh, size);
}

int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read(fh, buf, count, datatype, status);
}

int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_all(fh, buf, count, datatype, status);
}

int MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_read_all_begin(fh, buf, count, datatype);
}

int MPI_File_read_all_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_read_all_begin_c(fh, buf, count, datatype);
}

int MPI_File_read_all_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_all_c(fh, buf, count, datatype, status);
}

int MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status)
{
    return MUK_File_read_all_end(fh, buf, status);
}

int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_at(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_at_all(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_read_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_read_at_all_begin_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_read_at_all_begin_c(fh, offset, buf, count, datatype);
}

int MPI_File_read_at_all_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_at_all_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status)
{
    return MUK_File_read_at_all_end(fh, buf, status);
}

int MPI_File_read_at_c(MPI_File fh, MPI_Offset offset, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_at_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_read_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_c(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_ordered(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_read_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_read_ordered_begin_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_read_ordered_begin_c(fh, buf, count, datatype);
}

int MPI_File_read_ordered_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_ordered_c(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status)
{
    return MUK_File_read_ordered_end(fh, buf, status);
}

int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_shared(fh, buf, count, datatype, status);
}

int MPI_File_read_shared_c(MPI_File fh, void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_read_shared_c(fh, buf, count, datatype, status);
}

int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence)
{
    return MUK_File_seek(fh, offset, whence);
}

int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence)
{
    return MUK_File_seek_shared(fh, offset, whence);
}

int MPI_File_set_atomicity(MPI_File fh, int flag)
{
    return MUK_File_set_atomicity(fh, flag);
}

int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler)
{
    return MUK_File_set_errhandler(file, errhandler);
}

int MPI_File_set_info(MPI_File fh, MPI_Info info)
{
    return MUK_File_set_info(fh, info);
}

int MPI_File_set_size(MPI_File fh, MPI_Offset size)
{
    return MUK_File_set_size(fh, size);
}

int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info)
{
    return MUK_File_set_view(fh, disp, etype, filetype, datarep, info);
}

int MPI_File_sync(MPI_File fh)
{
    return MUK_File_sync(fh);
}

int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write(fh, buf, count, datatype, status);
}

int MPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_all(fh, buf, count, datatype, status);
}

int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_write_all_begin(fh, buf, count, datatype);
}

int MPI_File_write_all_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_write_all_begin_c(fh, buf, count, datatype);
}

int MPI_File_write_all_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_all_c(fh, buf, count, datatype, status);
}

int MPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status)
{
    return MUK_File_write_all_end(fh, buf, status);
}

int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_at(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_at_all(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_write_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_write_at_all_begin_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_write_at_all_begin_c(fh, offset, buf, count, datatype);
}

int MPI_File_write_at_all_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_at_all_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status)
{
    return MUK_File_write_at_all_end(fh, buf, status);
}

int MPI_File_write_at_c(MPI_File fh, MPI_Offset offset, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_at_c(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_c(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_ordered(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype)
{
    return MUK_File_write_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_write_ordered_begin_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype)
{
    return MUK_File_write_ordered_begin_c(fh, buf, count, datatype);
}

int MPI_File_write_ordered_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_ordered_c(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status)
{
    return MUK_File_write_ordered_end(fh, buf, status);
}

int MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_shared(fh, buf, count, datatype, status);
}

int MPI_File_write_shared_c(MPI_File fh, const void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Status *status)
{
    return MUK_File_write_shared_c(fh, buf, count, datatype, status);
}

int MPI_Free_mem(void *base)
{
    return MUK_Free_mem(base);
}

int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Gather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Gather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Gather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Gather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Gather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Gather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int MPI_Gatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Gatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}

int MPI_Gatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Gatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int MPI_Gatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Gatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, info, request);
}

int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return MUK_Get(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return MUK_Get_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Get_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    return MUK_Get_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}

int MPI_Get_address(const void *location, MPI_Aint *address)
{
    return MUK_Get_address(location, address);
}

int MPI_Get_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return MUK_Get_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count)
{
    return MUK_Get_count(status, datatype, count);
}

int MPI_Get_count_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count)
{
    return MUK_Get_count_c(status, datatype, count);
}

int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count)
{
    return MUK_Get_elements(status, datatype, count);
}

int MPI_Get_elements_c(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count)
{
    return MUK_Get_elements_c(status, datatype, count);
}

int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count)
{
    return MUK_Get_elements_x(status, datatype, count);
}

int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int indx[], const int edges[], int reorder, MPI_Comm *comm_graph)
{
    return MUK_Graph_create(comm_old, nnodes, indx, edges, reorder, comm_graph);
}

int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int indx[], int edges[])
{
    return MUK_Graph_get(comm, maxindex, maxedges, indx, edges);
}

int MPI_Graph_map(MPI_Comm comm, int nnodes, const int indx[], const int edges[], int *newrank)
{
    return MUK_Graph_map(comm, nnodes, indx, edges, newrank);
}

int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    return MUK_Graph_neighbors(comm, rank, maxneighbors, neighbors);
}

int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors)
{
    return MUK_Graph_neighbors_count(comm, rank, nneighbors);
}

int MPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges)
{
    return MUK_Graphdims_get(comm, nnodes, nedges);
}

int MPI_Grequest_complete(MPI_Request request)
{
    return MUK_Grequest_complete(request);
}

int MPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request)
{
    return MUK_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, request);
}

int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result)
{
    return MUK_Group_compare(group1, group2, result);
}

int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return MUK_Group_difference(group1, group2, newgroup);
}

int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup)
{
    return MUK_Group_excl(group, n, ranks, newgroup);
}

int MPI_Group_free(MPI_Group *group)
{
    return MUK_Group_free(group);
}

int MPI_Group_from_session_pset(MPI_Session session, const char *pset_name, MPI_Group *newgroup)
{
    return MUK_Group_from_session_pset(session, pset_name, newgroup);
}

int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup)
{
    return MUK_Group_incl(group, n, ranks, newgroup);
}

int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return MUK_Group_intersection(group1, group2, newgroup);
}

int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup)
{
    return MUK_Group_range_excl(group, n, ranges, newgroup);
}

int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup)
{
    return MUK_Group_range_incl(group, n, ranges, newgroup);
}

int MPI_Group_rank(MPI_Group group, int *rank)
{
    return MUK_Group_rank(group, rank);
}

int MPI_Group_size(MPI_Group group, int *size)
{
    return MUK_Group_size(group, size);
}

int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[])
{
    return MUK_Group_translate_ranks(group1, n, ranks1, group2, ranks2);
}

int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup)
{
    return MUK_Group_union(group1, group2, newgroup);
}

int MPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Iallgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Iallgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iallreduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iallreduce_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ialltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ialltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ialltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ialltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ibarrier(comm, request);
}

int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ibcast(buffer, count, datatype, root, comm, request);
}

int MPI_Ibcast_c(void *buffer, MPI_Count count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ibcast_c(buffer, count, datatype, root, comm, request);
}

int MPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ibsend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Ibsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ibsend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iexscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iexscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iexscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Igather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Igather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Igather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Igatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int MPI_Igatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Igatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
}

int MPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status)
{
    return MUK_Improbe(source, tag, comm, flag, message, status);
}

int MPI_Imrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request)
{
    return MUK_Imrecv(buf, count, datatype, message, request);
}

int MPI_Imrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Request *request)
{
    return MUK_Imrecv_c(buf, count, datatype, message, request);
}

int MPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Ineighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}

int MPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}

int MPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Ineighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ineighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}

int MPI_Info_create(MPI_Info *info)
{
    return MUK_Info_create(info);
}

int MPI_Info_create_env(int argc, char *argv[], MPI_Info *info)
{
    return MUK_Info_create_env(argc, argv, info);
}

int MPI_Info_delete(MPI_Info info, const char *key)
{
    return MUK_Info_delete(info, key);
}

int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo)
{
    return MUK_Info_dup(info, newinfo);
}

int MPI_Info_free(MPI_Info *info)
{
    return MUK_Info_free(info);
}

int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag)
{
    return MUK_Info_get(info, key, valuelen, value, flag);
}

int MPI_Info_get_nkeys(MPI_Info info, int *nkeys)
{
    return MUK_Info_get_nkeys(info, nkeys);
}

int MPI_Info_get_nthkey(MPI_Info info, int n, char *key)
{
    return MUK_Info_get_nthkey(info, n, key);
}

int MPI_Info_get_string(MPI_Info info, const char *key, int *buflen, char *value, int *flag)
{
    return MUK_Info_get_string(info, key, buflen, value, flag);
}

int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag)
{
    return MUK_Info_get_valuelen(info, key, valuelen, flag);
}

int MPI_Info_set(MPI_Info info, const char *key, const char *value)
{
    return MUK_Info_set(info, key, value);
}

int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *newintercomm)
{
    return MUK_Intercomm_create(local_comm, local_leader, peer_comm, remote_leader, tag, newintercomm);
}

int MPI_Intercomm_create_from_groups(MPI_Group local_group, int local_leader, MPI_Group remote_group, int remote_leader, const char *stringtag, MPI_Info info, MPI_Errhandler errhandler, MPI_Comm *newintercomm)
{
    return MUK_Intercomm_create_from_groups(local_group, local_leader, remote_group, remote_leader, stringtag, info, errhandler, newintercomm);
}

int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm)
{
    return MUK_Intercomm_merge(intercomm, high, newintracomm);
}

int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status)
{
    return MUK_Iprobe(source, tag, comm, flag, status);
}

int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Irecv(buf, count, datatype, source, tag, comm, request);
}

int MPI_Irecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Irecv_c(buf, count, datatype, source, tag, comm, request);
}

int MPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int MPI_Ireduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce_c(sendbuf, recvbuf, count, datatype, op, root, comm, request);
}

int MPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}

int MPI_Ireduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ireduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}

int MPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Irsend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Irsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Irsend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscan(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iscan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscan_c(sendbuf, recvbuf, count, datatype, op, comm, request);
}

int MPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Iscatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Iscatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}

int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Isend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isend_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Isendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int MPI_Isendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, request);
}

int MPI_Isendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int MPI_Isendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Isendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, request);
}

int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Issend(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Issend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Issend_c(buf, count, datatype, dest, tag, comm, request);
}

#if 0
int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state)
{
    return MUK_Keyval_create(copy_fn, delete_fn, keyval, extra_state);
}

int MPI_Keyval_free(int *keyval)
{
    return MUK_Keyval_free(keyval);
}
#endif

int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name)
{
    return MUK_Lookup_name(service_name, info, port_name);
}

int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status)
{
    return MUK_Mprobe(source, tag, comm, message, status);
}

int MPI_Mrecv(void *buf, int count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status)
{
    return MUK_Mrecv(buf, count, datatype, message, status);
}

int MPI_Mrecv_c(void *buf, MPI_Count count, MPI_Datatype datatype, MPI_Message *message, MPI_Status *status)
{
    return MUK_Mrecv_c(buf, count, datatype, message, status);
}

int MPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_allgather_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_allgather_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_allgather_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_allgather_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_allgather_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_allgather_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Neighbor_allgatherv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_allgatherv_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
}

int MPI_Neighbor_allgatherv_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_allgatherv_init(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Neighbor_allgatherv_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_allgatherv_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_alltoall_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_alltoall_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}

int MPI_Neighbor_alltoall_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoall_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoall_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoall_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Neighbor_alltoallv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    return MUK_Neighbor_alltoallv_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

int MPI_Neighbor_alltoallv_init(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoallv_init(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], MPI_Datatype sendtype, void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoallv_init_c(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request);
}

int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return MUK_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Neighbor_alltoallw_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    return MUK_Neighbor_alltoallw_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
}

int MPI_Neighbor_alltoallw_init(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoallw_init(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Neighbor_alltoallw_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const MPI_Count recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Neighbor_alltoallw_init_c(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, info, request);
}

int MPI_Op_commutative(MPI_Op op, int *commute)
{
    return MUK_Op_commutative(op, commute);
}

int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op)
{
    return MUK_Op_create(user_fn, commute, op);
}

int MPI_Op_create_c(MPI_User_function_c *user_fn, int commute, MPI_Op *op)
{
    return MUK_Op_create_c(user_fn, commute, op);
}

int MPI_Op_free(MPI_Op *op)
{
    return MUK_Op_free(op);
}

int MPI_Open_port(MPI_Info info, char *port_name)
{
    return MUK_Open_port(info, port_name);
}

int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm)
{
    return MUK_Pack(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int MPI_Pack_c(const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position, MPI_Comm comm)
{
    return MUK_Pack_c(inbuf, incount, datatype, outbuf, outsize, position, comm);
}

int MPI_Pack_external(const char *datarep, const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position)
{
    return MUK_Pack_external(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int MPI_Pack_external_c(const char *datarep, const void *inbuf, MPI_Count incount, MPI_Datatype datatype, void *outbuf, MPI_Count outsize, MPI_Count *position)
{
    return MUK_Pack_external_c(datarep, inbuf, incount, datatype, outbuf, outsize, position);
}

int MPI_Pack_external_size(const char *datarep, int incount, MPI_Datatype datatype, MPI_Aint *size)
{
    return MUK_Pack_external_size(datarep, incount, datatype, size);
}

int MPI_Pack_external_size_c(const char *datarep, MPI_Count incount, MPI_Datatype datatype, MPI_Count *size)
{
    return MUK_Pack_external_size_c(datarep, incount, datatype, size);
}

int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size)
{
    return MUK_Pack_size(incount, datatype, comm, size);
}

int MPI_Pack_size_c(MPI_Count incount, MPI_Datatype datatype, MPI_Comm comm, MPI_Count *size)
{
    return MUK_Pack_size_c(incount, datatype, comm, size);
}

int MPI_Parrived(MPI_Request request, int partition, int *flag)
{
    return MUK_Parrived(request, partition, flag);
}

int MPI_Pcontrol(const int level, ...)
{
    return MUK_Pcontrol(level);
}

int MPI_Pready(int partition, MPI_Request request)
{
    return MUK_Pready(partition, request);
}

int MPI_Pready_list(int length, const int array_of_partitions[], MPI_Request request)
{
    return MUK_Pready_list(length, array_of_partitions, request);
}

int MPI_Pready_range(int partition_low, int partition_high, MPI_Request request)
{
    return MUK_Pready_range(partition_low, partition_high, request);
}

int MPI_Precv_init(void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Precv_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Probe(source, tag, comm, status);
}

int MPI_Psend_init(const void *buf, int partitions, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Psend_init(buf, partitions, count, datatype, dest, tag, comm, info, request);
}

int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name)
{
    return MUK_Publish_name(service_name, info, port_name);
}

int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return MUK_Put(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Put_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    return MUK_Put_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}

int MPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return MUK_Raccumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Raccumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return MUK_Raccumulate_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Recv(buf, count, datatype, source, tag, comm, status);
}

int MPI_Recv_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Recv_c(buf, count, datatype, source, tag, comm, status);
}

int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Recv_init(buf, count, datatype, source, tag, comm, request);
}

int MPI_Recv_init_c(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Recv_init_c(buf, count, datatype, source, tag, comm, request);
}

int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
    return MUK_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int MPI_Reduce_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
    return MUK_Reduce_c(sendbuf, recvbuf, count, datatype, op, root, comm);
}

int MPI_Reduce_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_init(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int MPI_Reduce_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_init_c(sendbuf, recvbuf, count, datatype, op, root, comm, info, request);
}

int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op)
{
    return MUK_Reduce_local(inbuf, inoutbuf, count, datatype, op);
}

int MPI_Reduce_local_c(const void *inbuf, void *inoutbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op)
{
    return MUK_Reduce_local_c(inbuf, inoutbuf, count, datatype, op);
}

int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Reduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int MPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Reduce_scatter_block(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int MPI_Reduce_scatter_block_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Reduce_scatter_block_c(sendbuf, recvbuf, recvcount, datatype, op, comm);
}

int MPI_Reduce_scatter_block_init(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_scatter_block_init(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_block_init_c(const void *sendbuf, void *recvbuf, MPI_Count recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_scatter_block_init_c(sendbuf, recvbuf, recvcount, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Reduce_scatter_c(sendbuf, recvbuf, recvcounts, datatype, op, comm);
}

int MPI_Reduce_scatter_init(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_scatter_init(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int MPI_Reduce_scatter_init_c(const void *sendbuf, void *recvbuf, const MPI_Count recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Reduce_scatter_init_c(sendbuf, recvbuf, recvcounts, datatype, op, comm, info, request);
}

int MPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return MUK_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}

int MPI_Register_datarep_c(const char *datarep, MPI_Datarep_conversion_function_c *read_conversion_fn, MPI_Datarep_conversion_function_c *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state)
{
    return MUK_Register_datarep_c(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}

int MPI_Request_free(MPI_Request *request)
{
    int rc = MUK_Request_free(request);
    MUK_REQUEST_NULLIFY(request);
    return rc;
}

int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status)
{
    return MUK_Request_get_status(request, flag, status);
}

int MPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return MUK_Rget(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return MUK_Rget_accumulate(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Rget_accumulate_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, void *result_addr, MPI_Count result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request)
{
    return MUK_Rget_accumulate_c(origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}

int MPI_Rget_c(void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return MUK_Rget_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return MUK_Rput(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rput_c(const void *origin_addr, MPI_Count origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, MPI_Count target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request)
{
    return MUK_Rput_c(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, request);
}

int MPI_Rsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Rsend(buf, count, datatype, dest, tag, comm);
}

int MPI_Rsend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Rsend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Rsend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Rsend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Rsend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Scan(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Scan_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    return MUK_Scan_c(sendbuf, recvbuf, count, datatype, op, comm);
}

int MPI_Scan_init(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scan_init(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Scan_init_c(const void *sendbuf, void *recvbuf, MPI_Count count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scan_init_c(sendbuf, recvbuf, count, datatype, op, comm, info, request);
}

int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatter_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Scatter_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatter_init(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scatter_init(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatter_init_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scatter_init_c(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatterv_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    return MUK_Scatterv_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}

int MPI_Scatterv_init(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scatterv_init(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Scatterv_init_c(const void *sendbuf, const MPI_Count sendcounts[], const MPI_Aint displs[], MPI_Datatype sendtype, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Info info, MPI_Request *request)
{
    return MUK_Scatterv_init_c(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, info, request);
}

int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Send(buf, count, datatype, dest, tag, comm);
}

int MPI_Send_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Send_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Send_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Send_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Send_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
}

int MPI_Sendrecv_c(const void *sendbuf, MPI_Count sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, MPI_Count recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Sendrecv_c(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
}

int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Sendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
}

int MPI_Sendrecv_replace_c(void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status)
{
    return MUK_Sendrecv_replace_c(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
}

int MPI_Session_call_errhandler(MPI_Session session, int errorcode)
{
    return MUK_Session_call_errhandler(session, errorcode);
}

int MPI_Session_create_errhandler(MPI_Session_errhandler_function *session_errhandler_fn, MPI_Errhandler *errhandler)
{
    return MUK_Session_create_errhandler(session_errhandler_fn, errhandler);
}

int MPI_Session_finalize(MPI_Session *session)
{
    return MUK_Session_finalize(session);
}

int MPI_Session_get_errhandler(MPI_Session session, MPI_Errhandler *errhandler)
{
    return MUK_Session_get_errhandler(session, errhandler);
}

int MPI_Session_get_info(MPI_Session session, MPI_Info *info_used)
{
    return MUK_Session_get_info(session, info_used);
}

int MPI_Session_get_nth_pset(MPI_Session session, MPI_Info info, int n, int *pset_len, char *pset_name)
{
    return MUK_Session_get_nth_pset(session, info, n, pset_len, pset_name);
}

int MPI_Session_get_num_psets(MPI_Session session, MPI_Info info, int *npset_names)
{
    return MUK_Session_get_num_psets(session, info, npset_names);
}

int MPI_Session_get_pset_info(MPI_Session session, const char *pset_name, MPI_Info *info)
{
    return MUK_Session_get_pset_info(session, pset_name, info);
}

int MPI_Session_init(MPI_Info info, MPI_Errhandler errhandler, MPI_Session *session)
{
    return MUK_Session_init(info, errhandler, session);
}

int MPI_Session_set_errhandler(MPI_Session session, MPI_Errhandler errhandler)
{
    return MUK_Session_set_errhandler(session, errhandler);
}

int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Ssend(buf, count, datatype, dest, tag, comm);
}

int MPI_Ssend_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    return MUK_Ssend_c(buf, count, datatype, dest, tag, comm);
}

int MPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ssend_init(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Ssend_init_c(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
    return MUK_Ssend_init_c(buf, count, datatype, dest, tag, comm, request);
}

int MPI_Start(MPI_Request *request)
{
    return MUK_Start(request);
}

int MPI_Startall(int count, MPI_Request array_of_requests[])
{
    return MUK_Startall(count, array_of_requests);
}

#ifdef SUPPORT_F08
int MPI_Status_f082c(const MUK_F08_status *f08_status, MPI_Status *c_status)
{
    return MUK_Status_f082c(f08_status, c_status);
}

int MPI_Status_f082f(const MUK_F08_status *f08_status, MUK_Fint *f_status)
{
    return MUK_Status_f082f(f08_status, f_status);
}

int MPI_Status_f2f08(const MUK_Fint *f_status, MUK_F08_status *f08_status)
{
    return MUK_Status_f2f08(f_status, f08_status);
}
#endif

int MPI_Status_set_cancelled(MPI_Status *status, int flag)
{
    return MUK_Status_set_cancelled(status, flag);
}

int MPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count)
{
    return MUK_Status_set_elements(status, datatype, count);
}

int MPI_Status_set_elements_c(MPI_Status *status, MPI_Datatype datatype, MPI_Count count)
{
    return MUK_Status_set_elements_c(status, datatype, count);
}

int MPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count)
{
    return MUK_Status_set_elements_x(status, datatype, count);
}

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status)
{
    int rc = MUK_Test(request, flag, status);
    MUK_REQUEST_NULLIFY(request);
    return rc;
}

int MPI_Test_cancelled(const MPI_Status *status, int *flag)
{
    return MUK_Test_cancelled(status, flag);
}

int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[])
{
    int rc = MUK_Testall(count, array_of_requests, flag, array_of_statuses);
    for (int i=0; i<count; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Testany(int count, MPI_Request array_of_requests[], int *indx, int *flag, MPI_Status *status)
{
    int rc = MUK_Testany(count, array_of_requests, indx, flag, status);
    for (int i=0; i<count; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[])
{
    int rc = MUK_Testsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
    for (int i=0; i<incount; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Topo_test(MPI_Comm comm, int *status)
{
    return MUK_Topo_test(comm, status);
}

int MPI_Type_commit(MPI_Datatype *datatype)
{
    return MUK_Type_commit(datatype);
}

int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_contiguous(count, oldtype, newtype);
}

int MPI_Type_contiguous_c(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_contiguous_c(count, oldtype, newtype);
}

int MPI_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int MPI_Type_create_darray_c(int size, int rank, int ndims, const MPI_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
}

int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype)
{
    return MUK_Type_create_f90_complex(p, r, newtype);
}

int MPI_Type_create_f90_integer(int r, MPI_Datatype *newtype)
{
    return MUK_Type_create_f90_integer(r, newtype);
}

int MPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype)
{
    return MUK_Type_create_f90_real(p, r, newtype);
}

int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hindexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hindexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hvector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_create_hvector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_hvector_c(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_indexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_indexed_block_c(MPI_Count count, MPI_Count blocklength, const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_indexed_block_c(count, blocklength, array_of_displacements, oldtype, newtype);
}

int MPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    return MUK_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
}

int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype)
{
    return MUK_Type_create_resized(oldtype, lb, extent, newtype);
}

int MPI_Type_create_resized_c(MPI_Datatype oldtype, MPI_Count lb, MPI_Count extent, MPI_Datatype *newtype)
{
    return MUK_Type_create_resized_c(oldtype, lb, extent, newtype);
}

int MPI_Type_create_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return MUK_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_create_struct_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return MUK_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int MPI_Type_create_subarray_c(int ndims, const MPI_Count array_of_sizes[], const MPI_Count array_of_subsizes[], const MPI_Count array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
}

int MPI_Type_delete_attr(MPI_Datatype datatype, int type_keyval)
{
    return MUK_Type_delete_attr(datatype, type_keyval);
}

int MPI_Type_dup(MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_dup(oldtype, newtype);
}

int MPI_Type_extent(MPI_Datatype datatype, MPI_Aint *extent)
{
    return MUK_Type_extent(datatype, extent);
}

int MPI_Type_free(MPI_Datatype *datatype)
{
    return MUK_Type_free(datatype);
}

int MPI_Type_free_keyval(int *type_keyval)
{
    return MUK_Type_free_keyval(type_keyval);
}

int MPI_Type_get_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val, int *flag)
{
    return MUK_Type_get_attr(datatype, type_keyval, attribute_val, flag);
}

int MPI_Type_get_contents(MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[])
{
    return MUK_Type_get_contents(datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
}

int MPI_Type_get_contents_c(MPI_Datatype datatype, MPI_Count max_integers, MPI_Count max_addresses, MPI_Count max_large_counts, MPI_Count max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Count array_of_large_counts[], MPI_Datatype array_of_datatypes[])
{
    return MUK_Type_get_contents_c(datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, array_of_datatypes);
}

int MPI_Type_get_envelope(MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    return MUK_Type_get_envelope(datatype, num_integers, num_addresses, num_datatypes, combiner);
}

int MPI_Type_get_envelope_c(MPI_Datatype datatype, MPI_Count *num_integers, MPI_Count *num_addresses, MPI_Count *num_large_counts, MPI_Count *num_datatypes, int *combiner)
{
    return MUK_Type_get_envelope_c(datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
}

int MPI_Type_get_extent(MPI_Datatype datatype, MPI_Aint *lb, MPI_Aint *extent)
{
    return MUK_Type_get_extent(datatype, lb, extent);
}

int MPI_Type_get_extent_c(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent)
{
    return MUK_Type_get_extent_c(datatype, lb, extent);
}

int MPI_Type_get_extent_x(MPI_Datatype datatype, MPI_Count *lb, MPI_Count *extent)
{
    return MUK_Type_get_extent_x(datatype, lb, extent);
}

int MPI_Type_get_name(MPI_Datatype datatype, char *type_name, int *resultlen)
{
    return MUK_Type_get_name(datatype, type_name, resultlen);
}

int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent)
{
    return MUK_Type_get_true_extent(datatype, true_lb, true_extent);
}

int MPI_Type_get_true_extent_c(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent)
{
    return MUK_Type_get_true_extent_c(datatype, true_lb, true_extent);
}

int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent)
{
    return MUK_Type_get_true_extent_x(datatype, true_lb, true_extent);
}

int MPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_hvector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_indexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_indexed_c(MPI_Count count, const MPI_Count array_of_blocklengths[], const MPI_Count array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}

int MPI_Type_lb(MPI_Datatype datatype, MPI_Aint *displacement)
{
    return MUK_Type_lb(datatype, displacement);
}

int MPI_Type_match_size(int typeclass, int size, MPI_Datatype *datatype)
{
    return MUK_Type_match_size(typeclass, size, datatype);
}

int MPI_Type_set_attr(MPI_Datatype datatype, int type_keyval, void *attribute_val)
{
    return MUK_Type_set_attr(datatype, type_keyval, attribute_val);
}

int MPI_Type_set_name(MPI_Datatype datatype, const char *type_name)
{
    return MUK_Type_set_name(datatype, type_name);
}

int MPI_Type_size(MPI_Datatype datatype, int *size)
{
    return MUK_Type_size(datatype, size);
}

int MPI_Type_size_c(MPI_Datatype datatype, MPI_Count *size)
{
    return MUK_Type_size_c(datatype, size);
}

int MPI_Type_size_x(MPI_Datatype datatype, MPI_Count *size)
{
    return MUK_Type_size_x(datatype, size);
}

int MPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype)
{
    return MUK_Type_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
}

int MPI_Type_ub(MPI_Datatype datatype, MPI_Aint *displacement)
{
    return MUK_Type_ub(datatype, displacement);
}

int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_vector(count, blocklength, stride, oldtype, newtype);
}

int MPI_Type_vector_c(MPI_Count count, MPI_Count blocklength, MPI_Count stride, MPI_Datatype oldtype, MPI_Datatype *newtype)
{
    return MUK_Type_vector_c(count, blocklength, stride, oldtype, newtype);
}

int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm)
{
    return MUK_Unpack(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int MPI_Unpack_c(const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype, MPI_Comm comm)
{
    return MUK_Unpack_c(inbuf, insize, position, outbuf, outcount, datatype, comm);
}

int MPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype)
{
    return MUK_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int MPI_Unpack_external_c(const char datarep[], const void *inbuf, MPI_Count insize, MPI_Count *position, void *outbuf, MPI_Count outcount, MPI_Datatype datatype)
{
    return MUK_Unpack_external_c(datarep, inbuf, insize, position, outbuf, outcount, datatype);
}

int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name)
{
    return MUK_Unpublish_name(service_name, info, port_name);
}

int MPI_Wait(MPI_Request *request, MPI_Status *status)
{
    int rc = MUK_Wait(request, status);
    MUK_REQUEST_NULLIFY(request);
    return rc;
}

int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[])
{
    int rc = MUK_Waitall(count, array_of_requests, array_of_statuses);
    for (int i=0; i<count; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Waitany(int count, MPI_Request array_of_requests[], int *indx, MPI_Status *status)
{
    int rc = MUK_Waitany(count, array_of_requests, indx, status);
    for (int i=0; i<count; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[])
{
    int rc = MUK_Waitsome(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
    for (int i=0; i<incount; i++) {
        MUK_REQUEST_NULLIFY(&array_of_requests[i]);
    }
    return rc;
}

int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return MUK_Win_allocate(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return MUK_Win_allocate_c(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return MUK_Win_allocate_shared(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_allocate_shared_c(MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win)
{
    return MUK_Win_allocate_shared_c(size, disp_unit, info, comm, baseptr, win);
}

int MPI_Win_attach(MPI_Win win, void *base, MPI_Aint size)
{
    return MUK_Win_attach(win, base, size);
}

int MPI_Win_call_errhandler(MPI_Win win, int errorcode)
{
    return MUK_Win_call_errhandler(win, errorcode);
}

int MPI_Win_complete(MPI_Win win)
{
    return MUK_Win_complete(win);
}

int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return MUK_Win_create(base, size, disp_unit, info, comm, win);
}

int MPI_Win_create_c(void *base, MPI_Aint size, MPI_Aint disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return MUK_Win_create_c(base, size, disp_unit, info, comm, win);
}

int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win)
{
    return MUK_Win_create_dynamic(info, comm, win);
}

int MPI_Win_create_errhandler(MPI_Win_errhandler_function *win_errhandler_fn, MPI_Errhandler *errhandler)
{
    return MUK_Win_create_errhandler(win_errhandler_fn, errhandler);
}

int MPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state)
{
    return MUK_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
}

int MPI_Win_delete_attr(MPI_Win win, int win_keyval)
{
    return MUK_Win_delete_attr(win, win_keyval);
}

int MPI_Win_detach(MPI_Win win, const void *base)
{
    return MUK_Win_detach(win, base);
}

int MPI_Win_fence(int assert, MPI_Win win)
{
    return MUK_Win_fence(assert, win);
}

int MPI_Win_flush(int rank, MPI_Win win)
{
    return MUK_Win_flush(rank, win);
}

int MPI_Win_flush_all(MPI_Win win)
{
    return MUK_Win_flush_all(win);
}

int MPI_Win_flush_local(int rank, MPI_Win win)
{
    return MUK_Win_flush_local(rank, win);
}

int MPI_Win_flush_local_all(MPI_Win win)
{
    return MUK_Win_flush_local_all(win);
}

int MPI_Win_free(MPI_Win *win)
{
    return MUK_Win_free(win);
}

int MPI_Win_free_keyval(int *win_keyval)
{
    return MUK_Win_free_keyval(win_keyval);
}

int MPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag)
{
    return MUK_Win_get_attr(win, win_keyval, attribute_val, flag);
}

int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler)
{
    return MUK_Win_get_errhandler(win, errhandler);
}

int MPI_Win_get_group(MPI_Win win, MPI_Group *group)
{
    return MUK_Win_get_group(win, group);
}

int MPI_Win_get_info(MPI_Win win, MPI_Info *info_used)
{
    return MUK_Win_get_info(win, info_used);
}

int MPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen)
{
    return MUK_Win_get_name(win, win_name, resultlen);
}

int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win)
{
    return MUK_Win_lock(lock_type, rank, assert, win);
}

int MPI_Win_lock_all(int assert, MPI_Win win)
{
    return MUK_Win_lock_all(assert, win);
}

int MPI_Win_post(MPI_Group group, int assert, MPI_Win win)
{
    return MUK_Win_post(group, assert, win);
}

int MPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val)
{
    return MUK_Win_set_attr(win, win_keyval, attribute_val);
}

int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler)
{
    return MUK_Win_set_errhandler(win, errhandler);
}

int MPI_Win_set_info(MPI_Win win, MPI_Info info)
{
    return MUK_Win_set_info(win, info);
}

int MPI_Win_set_name(MPI_Win win, const char *win_name)
{
    return MUK_Win_set_name(win, win_name);
}

int MPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr)
{
    return MUK_Win_shared_query(win, rank, size, disp_unit, baseptr);
}

int MPI_Win_shared_query_c(MPI_Win win, int rank, MPI_Aint *size, MPI_Aint *disp_unit, void *baseptr)
{
    return MUK_Win_shared_query_c(win, rank, size, disp_unit, baseptr);
}

int MPI_Win_start(MPI_Group group, int assert, MPI_Win win)
{
    return MUK_Win_start(group, assert, win);
}

int MPI_Win_sync(MPI_Win win)
{
    return MUK_Win_sync(win);
}

int MPI_Win_test(MPI_Win win, int *flag)
{
    return MUK_Win_test(win, flag);
}

int MPI_Win_unlock(int rank, MPI_Win win)
{
    return MUK_Win_unlock(rank, win);
}

int MPI_Win_unlock_all(MPI_Win win)
{
    return MUK_Win_unlock_all(win);
}

int MPI_Win_wait(MPI_Win win)
{
    return MUK_Win_wait(win);
}

double MPI_Wtime(void) { return MUK_Wtime(); }
double MPI_Wtick(void) { return MUK_Wtick(); }
