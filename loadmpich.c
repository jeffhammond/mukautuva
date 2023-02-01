#include "muk-dl.h"

#define USE_MUK_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_FUNCTION_POINTERS_EXTERN
#include "muk-mpi-functions.h"

#include "muk-builtin-handles.h"

typedef struct __MPICH_Status__
{
    int count_lo;
    int count_hi_and_cancelled;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
}
MPICH_Status;

int MUK_Load_functions(void * restrict h, int major, int minor)
{
    (void)minor;

    MUK_Abort = MUK_DLSYM(h,"MPI_Abort");

    MUK_Comm_rank = MUK_DLSYM(h,"MPI_Comm_rank");
    MUK_Comm_size = MUK_DLSYM(h,"MPI_Comm_size");

    MUK_Alloc_mem = MUK_DLSYM(h,"MPI_Alloc_mem");
    MUK_Free_mem = MUK_DLSYM(h,"MPI_Free_mem");

    MUK_Add_error_class = MUK_DLSYM(h,"MPI_Add_error_class");
    MUK_Add_error_code = MUK_DLSYM(h,"MPI_Add_error_code");
    MUK_Add_error_string = MUK_DLSYM(h,"MPI_Add_error_string");

    MUK_Comm_call_errhandler = MUK_DLSYM(h,"MPI_Comm_call_errhandler");
    MUK_Comm_create_errhandler = MUK_DLSYM(h,"MPI_Comm_create_errhandler");
    MUK_Comm_get_errhandler = MUK_DLSYM(h,"MPI_Comm_get_errhandler");
    MUK_Comm_set_errhandler = MUK_DLSYM(h,"MPI_Comm_set_errhandler");

    MUK_Errhandler_free = MUK_DLSYM(h,"MPI_Errhandler_free");
    MUK_Error_class = MUK_DLSYM(h,"MPI_Error_class");
    MUK_Error_string = MUK_DLSYM(h,"MPI_Error_string");

    MUK_File_call_errhandler = MUK_DLSYM(h,"MPI_File_call_errhandler");
    MUK_File_create_errhandler = MUK_DLSYM(h,"MPI_File_create_errhandler");
    MUK_File_get_errhandler = MUK_DLSYM(h,"MPI_File_get_errhandler");
    MUK_File_set_errhandler = MUK_DLSYM(h,"MPI_File_set_errhandler");

    MUK_Win_call_errhandler = MUK_DLSYM(h,"MPI_Win_call_errhandler");
    MUK_Win_create_errhandler = MUK_DLSYM(h,"MPI_Win_create_errhandler");
    MUK_Win_get_errhandler = MUK_DLSYM(h,"MPI_Win_get_errhandler");
    MUK_Win_set_errhandler = MUK_DLSYM(h,"MPI_Win_set_errhandler");

    MUK_Close_port = MUK_DLSYM(h,"MPI_Close_port");
    MUK_Comm_disconnect = MUK_DLSYM(h,"MPI_Comm_disconnect");
    MUK_Lookup_name = MUK_DLSYM(h,"MPI_Lookup_name");
    MUK_Open_port = MUK_DLSYM(h,"MPI_Open_port");
    MUK_Publish_name = MUK_DLSYM(h,"MPI_Publish_name");
    MUK_Unpublish_name = MUK_DLSYM(h,"MPI_Unpublish_name");

    MUK_Info_create = MUK_DLSYM(h,"MPI_Info_create");
    MUK_Info_dup = MUK_DLSYM(h,"MPI_Info_dup");
    MUK_Info_free = MUK_DLSYM(h,"MPI_Info_free");
    MUK_Info_get_nkeys = MUK_DLSYM(h,"MPI_Info_get_nkeys");
    MUK_Info_get_nthkey = MUK_DLSYM(h,"MPI_Info_get_nthkey");
    MUK_Info_set = MUK_DLSYM(h,"MPI_Info_set");
    if (major >= 4) {
        MUK_Info_get_string = MUK_DLSYM(h,"MPI_Info_get_string");
    }

    MUK_Comm_accept = MUK_DLSYM(h,"MPI_Comm_accept");
    MUK_Comm_connect = MUK_DLSYM(h,"MPI_Comm_connect");
    MUK_Comm_get_parent = MUK_DLSYM(h,"MPI_Comm_get_parent");
    MUK_Comm_join = MUK_DLSYM(h,"MPI_Comm_join");
    MUK_Comm_spawn = MUK_DLSYM(h,"MPI_Comm_spawn");
    MUK_Comm_spawn_multiple = MUK_DLSYM(h,"MPI_Comm_spawn_multiple");

    if (major >= 4) {
        MUK_Session_finalize = MUK_DLSYM(h,"MPI_Session_finalize");
        MUK_Session_get_nth_pset = MUK_DLSYM(h,"MPI_Session_get_nth_pset");
        MUK_Session_get_info = MUK_DLSYM(h,"MPI_Session_get_info");
        MUK_Session_get_num_psets = MUK_DLSYM(h,"MPI_Session_get_num_psets");
        MUK_Session_get_pset_info = MUK_DLSYM(h,"MPI_Session_get_pset_info");
        MUK_Session_init = MUK_DLSYM(h,"MPI_Session_init");
        MUK_Session_call_errhandler = MUK_DLSYM(h,"MPI_Session_call_errhandler");
        MUK_Session_create_errhandler = MUK_DLSYM(h,"MPI_Session_create_errhandler");
        MUK_Session_get_errhandler = MUK_DLSYM(h,"MPI_Session_get_errhandler");
        MUK_Session_set_errhandler = MUK_DLSYM(h,"MPI_Session_set_errhandler");
    }

    return 0;
}

int MUK_Load_predefined(void * restrict h)
{
    (void)h;
#if 0
    MUK_REQUEST_NULL    = MUK_DLSYM(h,"ompi_mpi_request_null");
    MUK_ERRHANDLER_NULL = MUK_DLSYM(h,"ompi_mpi_errhandler_null");
    MUK_INFO_NULL       = MUK_DLSYM(h,"ompi_mpi_info_null");
    MUK_WIN_NULL        = MUK_DLSYM(h,"ompi_mpi_win_null");
    MUK_FILE_NULL       = MUK_DLSYM(h,"ompi_mpi_file_null");

    MUK_COMM_NULL  = MUK_DLSYM(h,"ompi_mpi_comm_null");
    MUK_COMM_WORLD = MUK_DLSYM(h,"ompi_mpi_comm_world");
    MUK_COMM_SELF  = MUK_DLSYM(h,"ompi_mpi_comm_self");

    MUK_GROUP_NULL  = MUK_DLSYM(h,"ompi_mpi_group_null");
    MUK_GROUP_EMPTY = MUK_DLSYM_OPT(h,"ompi_mpi_group_empty",MUK_GROUP_NULL);

    MUK_MESSAGE_NULL    = MUK_DLSYM(h,"ompi_mpi_message_null");
    MUK_MESSAGE_NO_PROC = MUK_DLSYM_OPT(h,"ompi_mpi_message_no_proc",MUK_MESSAGE_NULL);

    MUK_OP_NULL = MUK_DLSYM(h,"ompi_mpi_op_null");
    MUK_MAX     = MUK_DLSYM_OPT(h,"ompi_mpi_max",MUK_OP_NULL);
    MUK_MIN     = MUK_DLSYM_OPT(h,"ompi_mpi_min",MUK_OP_NULL);
    MUK_SUM     = MUK_DLSYM_OPT(h,"ompi_mpi_sum",MUK_OP_NULL);
    MUK_PROD    = MUK_DLSYM_OPT(h,"ompi_mpi_prod",MUK_OP_NULL);
    MUK_LAND    = MUK_DLSYM_OPT(h,"ompi_mpi_land",MUK_OP_NULL);
    MUK_BAND    = MUK_DLSYM_OPT(h,"ompi_mpi_band",MUK_OP_NULL);
    MUK_LOR     = MUK_DLSYM_OPT(h,"ompi_mpi_lor",MUK_OP_NULL);
    MUK_BOR     = MUK_DLSYM_OPT(h,"ompi_mpi_bor",MUK_OP_NULL);
    MUK_LXOR    = MUK_DLSYM_OPT(h,"ompi_mpi_lxor",MUK_OP_NULL);
    MUK_BXOR    = MUK_DLSYM_OPT(h,"ompi_mpi_bxor",MUK_OP_NULL);
    MUK_MAXLOC  = MUK_DLSYM_OPT(h,"ompi_mpi_maxloc",MUK_OP_NULL);
    MUK_MINLOC  = MUK_DLSYM_OPT(h,"ompi_mpi_minloc",MUK_OP_NULL);
    MUK_REPLACE = MUK_DLSYM_OPT(h,"ompi_mpi_replace",MUK_OP_NULL);
    MUK_NO_OP   = MUK_DLSYM_OPT(h,"ompi_mpi_no_op",MUK_OP_NULL);

    MUK_DATATYPE_NULL      = MUK_DLSYM(h,"ompi_mpi_datatype_null");
    MUK_BYTE               = MUK_DLSYM_OPT(h,"ompi_mpi_byte",MUK_DATATYPE_NULL);
    MUK_PACKED             = MUK_DLSYM_OPT(h,"ompi_mpi_packed",MUK_DATATYPE_NULL);
    MUK_CHAR               = MUK_DLSYM_OPT(h,"ompi_mpi_char",MUK_DATATYPE_NULL);
    MUK_SHORT              = MUK_DLSYM_OPT(h,"ompi_mpi_short",MUK_DATATYPE_NULL);
    MUK_INT                = MUK_DLSYM_OPT(h,"ompi_mpi_int",MUK_DATATYPE_NULL);
    MUK_LONG               = MUK_DLSYM_OPT(h,"ompi_mpi_long",MUK_DATATYPE_NULL);
    MUK_FLOAT              = MUK_DLSYM_OPT(h,"ompi_mpi_float",MUK_DATATYPE_NULL);
    MUK_DOUBLE             = MUK_DLSYM_OPT(h,"ompi_mpi_double",MUK_DATATYPE_NULL);
    MUK_LONG_DOUBLE        = MUK_DLSYM_OPT(h,"ompi_mpi_long_double",MUK_DATATYPE_NULL);
    MUK_UNSIGNED_CHAR      = MUK_DLSYM_OPT(h,"ompi_mpi_unsigned_char",MUK_DATATYPE_NULL);
    MUK_SIGNED_CHAR        = MUK_DLSYM_OPT(h,"ompi_mpi_signed_char",MUK_DATATYPE_NULL);
    MUK_UNSIGNED_SHORT     = MUK_DLSYM_OPT(h,"ompi_mpi_unsigned_short",MUK_DATATYPE_NULL);
    MUK_UNSIGNED_LONG      = MUK_DLSYM_OPT(h,"ompi_mpi_unsigned_long",MUK_DATATYPE_NULL);
    MUK_UNSIGNED           = MUK_DLSYM_OPT(h,"ompi_mpi_unsigned",MUK_DATATYPE_NULL);
    MUK_FLOAT_INT          = MUK_DLSYM_OPT(h,"ompi_mpi_float_int",MUK_DATATYPE_NULL);
    MUK_DOUBLE_INT         = MUK_DLSYM_OPT(h,"ompi_mpi_double_int",MUK_DATATYPE_NULL);
    MUK_LONG_DOUBLE_INT    = MUK_DLSYM_OPT(h,"ompi_mpi_long_double_int",MUK_DATATYPE_NULL);
    MUK_LONG_INT           = MUK_DLSYM_OPT(h,"ompi_mpi_long_int",MUK_DATATYPE_NULL);
    MUK_SHORT_INT          = MUK_DLSYM_OPT(h,"ompi_mpi_short_int",MUK_DATATYPE_NULL);
    MUK_2INT               = MUK_DLSYM_OPT(h,"ompi_mpi_2int",MUK_DATATYPE_NULL);
    MUK_WCHAR              = MUK_DLSYM_OPT(h,"ompi_mpi_wchar",MUK_DATATYPE_NULL);
    MUK_LONG_LONG_INT      = MUK_DLSYM_OPT(h,"ompi_mpi_long_long_int",MUK_DATATYPE_NULL);
    MUK_LONG_LONG          = MUK_DLSYM_OPT(h,"ompi_mpi_long_long",MUK_DATATYPE_NULL);
    MUK_UNSIGNED_LONG_LONG = MUK_DLSYM_OPT(h,"ompi_mpi_unsigned_long_long",MUK_DATATYPE_NULL);
    MUK_2COMPLEX           = MUK_DLSYM_OPT(h,"ompi_mpi_2complex",MUK_DATATYPE_NULL);
    MUK_2DOUBLE_COMPLEX    = MUK_DLSYM_OPT(h,"ompi_mpi_2double_complex",MUK_DATATYPE_NULL);
#endif
    return 0;
}
