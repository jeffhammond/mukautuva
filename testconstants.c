// SPDX-License-Identifier: MIT

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

// clearly, not ALL of them yet...
static MPI_Comm all_comm_constants [] = {
    MPI_COMM_WORLD,
    MPI_COMM_SELF
};

// clearly, not ALL of them yet...
static MPI_Datatype all_datatype_constants [] = {
     MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_LONG_LONG, MPI_FLOAT, MPI_DOUBLE
};

static int all_integer_constants [] = {
    MPI_SUCCESS,
    MPI_ERR_BUFFER,
    MPI_ERR_COUNT,
    MPI_ERR_TYPE,
    MPI_ERR_TAG,
    MPI_ERR_COMM,
    MPI_ERR_RANK,
    MPI_ERR_REQUEST,
    MPI_ERR_ROOT,
    MPI_ERR_GROUP,
    MPI_ERR_OP,
    MPI_ERR_TOPOLOGY,
    MPI_ERR_DIMS,
    MPI_ERR_ARG,
    MPI_ERR_UNKNOWN,
    MPI_ERR_TRUNCATE,
    MPI_ERR_OTHER,
    MPI_ERR_INTERN,
    MPI_ERR_PENDING,
    MPI_ERR_IN_STATUS,
    MPI_ERR_ACCESS,
    MPI_ERR_AMODE,
    MPI_ERR_ASSERT,
    MPI_ERR_BAD_FILE,
    MPI_ERR_BASE,
    MPI_ERR_CONVERSION,
    MPI_ERR_DISP,
    MPI_ERR_DUP_DATAREP,
    MPI_ERR_FILE_EXISTS,
    MPI_ERR_FILE_IN_USE,
    MPI_ERR_FILE,
    MPI_ERR_INFO_KEY,
    MPI_ERR_INFO_NOKEY,
    MPI_ERR_INFO_VALUE,
    MPI_ERR_INFO,
    MPI_ERR_IO,
    MPI_ERR_KEYVAL,
    MPI_ERR_LOCKTYPE,
    MPI_ERR_NAME,
    MPI_ERR_NO_MEM,
    MPI_ERR_NOT_SAME,
    MPI_ERR_NO_SPACE,
    MPI_ERR_NO_SUCH_FILE,
    MPI_ERR_PORT,
#if MPI_VERSION >= 4
    MPI_ERR_PROC_ABORTED,
#endif
    MPI_ERR_QUOTA,
    MPI_ERR_READ_ONLY,
    MPI_ERR_RMA_ATTACH,
    MPI_ERR_RMA_CONFLICT,
    MPI_ERR_RMA_RANGE,
    MPI_ERR_RMA_SHARED,
    MPI_ERR_RMA_SYNC,
    MPI_ERR_RMA_FLAVOR,
    MPI_ERR_SERVICE,
#if MPI_VERSION >= 4
    MPI_ERR_SESSION,
#endif
    MPI_ERR_SIZE,
    MPI_ERR_SPAWN,
    MPI_ERR_UNSUPPORTED_DATAREP,
    MPI_ERR_UNSUPPORTED_OPERATION,
#if MPI_VERSION >= 4
    MPI_ERR_VALUE_TOO_LARGE,
#endif
    MPI_ERR_WIN,
    MPI_T_ERR_CANNOT_INIT,
#if MPICH_BUG_IS_FIXED
    MPI_T_ERR_NOT_ACCESSIBLE,
#endif
    MPI_T_ERR_NOT_INITIALIZED,
#if MPI_VERSION >= 4
    MPI_T_ERR_NOT_SUPPORTED,
#endif
    MPI_T_ERR_MEMORY,
    MPI_T_ERR_INVALID,
    MPI_T_ERR_INVALID_INDEX,
    MPI_T_ERR_INVALID_ITEM,
    MPI_T_ERR_INVALID_SESSION,
    MPI_T_ERR_INVALID_HANDLE,
    MPI_T_ERR_INVALID_NAME,
    MPI_T_ERR_OUT_OF_HANDLES,
    MPI_T_ERR_OUT_OF_SESSIONS,
    MPI_T_ERR_CVAR_SET_NOT_NOW,
    MPI_T_ERR_CVAR_SET_NEVER,
    MPI_T_ERR_PVAR_NO_WRITE,
    MPI_T_ERR_PVAR_NO_STARTSTOP,
    MPI_T_ERR_PVAR_NO_ATOMIC,
    MPI_ERR_LASTCODE,
    MPI_PROC_NULL,
    MPI_ANY_SOURCE,
    MPI_ROOT,
    MPI_ANY_TAG,
    MPI_UNDEFINED,
    MPI_BSEND_OVERHEAD,
    MPI_KEYVAL_INVALID,
    MPI_LOCK_EXCLUSIVE,
    MPI_LOCK_SHARED,
    MPI_COMM_TYPE_SHARED,
#if MPI_VERSION >= 4
    MPI_COMM_TYPE_HW_UNGUIDED,
    MPI_COMM_TYPE_HW_GUIDED,
#endif
    MPI_IDENT,
    MPI_CONGRUENT,
    MPI_SIMILAR,
    MPI_UNEQUAL,
    MPI_TAG_UB,
    MPI_IO,
    MPI_HOST,
    MPI_WTIME_IS_GLOBAL,
    MPI_GRAPH,
    MPI_CART,
    MPI_DIST_GRAPH,
    MPI_APPNUM,
    MPI_LASTUSEDCODE,
    MPI_UNIVERSE_SIZE,
    MPI_WIN_BASE,
    MPI_WIN_DISP_UNIT,
    MPI_WIN_SIZE,
    MPI_WIN_CREATE_FLAVOR,
    MPI_WIN_MODEL,
    MPI_WIN_FLAVOR_CREATE,
    MPI_WIN_FLAVOR_ALLOCATE,
    MPI_WIN_FLAVOR_DYNAMIC,
    MPI_WIN_FLAVOR_SHARED,
    MPI_WIN_SEPARATE,
    MPI_WIN_UNIFIED,
    MPI_MODE_APPEND,
    MPI_MODE_CREATE,
    MPI_MODE_DELETE_ON_CLOSE,
    MPI_MODE_EXCL,
    MPI_MODE_NOCHECK,
    MPI_MODE_NOPRECEDE,
    MPI_MODE_NOPUT,
    MPI_MODE_NOSTORE,
    MPI_MODE_NOSUCCEED,
    MPI_MODE_RDONLY,
    MPI_MODE_RDWR,
    MPI_MODE_SEQUENTIAL,
    MPI_MODE_UNIQUE_OPEN,
    MPI_MODE_WRONLY,
    MPI_COMBINER_CONTIGUOUS,
    MPI_COMBINER_DARRAY,
    MPI_COMBINER_DUP,
    MPI_COMBINER_HINDEXED,
    MPI_COMBINER_HVECTOR,
    MPI_COMBINER_INDEXED_BLOCK,
    MPI_COMBINER_HINDEXED_BLOCK,
    MPI_COMBINER_INDEXED,
    MPI_COMBINER_NAMED,
    MPI_COMBINER_RESIZED,
    MPI_COMBINER_STRUCT,
    MPI_COMBINER_SUBARRAY,
    MPI_COMBINER_VECTOR,
    MPI_THREAD_FUNNELED,
    MPI_THREAD_MULTIPLE,
    MPI_THREAD_SERIALIZED,
    MPI_THREAD_SINGLE,
    MPI_DISPLACEMENT_CURRENT,
    MPI_DISTRIBUTE_BLOCK,
    MPI_DISTRIBUTE_CYCLIC,
    MPI_DISTRIBUTE_DFLT_DARG,
    MPI_DISTRIBUTE_NONE,
    MPI_ORDER_C,
    MPI_ORDER_FORTRAN,
    MPI_SEEK_CUR,
    MPI_SEEK_END,
    MPI_SEEK_SET,
    MPI_TYPECLASS_COMPLEX,
    MPI_TYPECLASS_INTEGER,
    MPI_TYPECLASS_REAL
};

int main(void)
{
    (void)all_integer_constants;
    (void)all_comm_constants;
    (void)all_datatype_constants;
    return MPI_SUCCESS;
}
