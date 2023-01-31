#include "muk.h"
#include "mpi.h"
#include "ompi.h"

int OMPI_Load_functions(void * restrict h, int major, int minor)
{
    (void)minor;

    OMPI_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    OMPI_Wtick = MUK_DLSYM(h,"MPI_Wtick");
    OMPI_Abort = MUK_DLSYM(h,"MPI_Abort");

    OMPI_Alloc_mem = MUK_DLSYM(h,"MPI_Alloc_mem");
    OMPI_Free_mem = MUK_DLSYM(h,"MPI_Free_mem");

    OMPI_Add_error_class = MUK_DLSYM(h,"MPI_Add_error_class");
    OMPI_Add_error_code = MUK_DLSYM(h,"MPI_Add_error_code");
    OMPI_Add_error_string = MUK_DLSYM(h,"MPI_Add_error_string");

    OMPI_Comm_call_errhandler = MUK_DLSYM(h,"MPI_Comm_call_errhandler");
    OMPI_Comm_create_errhandler = MUK_DLSYM(h,"MPI_Comm_create_errhandler");
    OMPI_Comm_get_errhandler = MUK_DLSYM(h,"MPI_Comm_get_errhandler");
    OMPI_Comm_set_errhandler = MUK_DLSYM(h,"MPI_Comm_set_errhandler");

    OMPI_Errhandler_free = MUK_DLSYM(h,"MPI_Errhandler_free");
    OMPI_Error_class = MUK_DLSYM(h,"MPI_Error_class");
    OMPI_Error_string = MUK_DLSYM(h,"MPI_Error_string");

    OMPI_File_call_errhandler = MUK_DLSYM(h,"MPI_File_call_errhandler");
    OMPI_File_create_errhandler = MUK_DLSYM(h,"MPI_File_create_errhandler");
    OMPI_File_get_errhandler = MUK_DLSYM(h,"MPI_File_get_errhandler");
    OMPI_File_set_errhandler = MUK_DLSYM(h,"MPI_File_set_errhandler");

    OMPI_Win_call_errhandler = MUK_DLSYM(h,"MPI_Win_call_errhandler");
    OMPI_Win_create_errhandler = MUK_DLSYM(h,"MPI_Win_create_errhandler");
    OMPI_Win_get_errhandler = MUK_DLSYM(h,"MPI_Win_get_errhandler");
    OMPI_Win_set_errhandler = MUK_DLSYM(h,"MPI_Win_set_errhandler");

    OMPI_Close_port = MUK_DLSYM(h,"MPI_Close_port");
    OMPI_Comm_disconnect = MUK_DLSYM(h,"MPI_Comm_disconnect");
    OMPI_Lookup_name = MUK_DLSYM(h,"MPI_Lookup_name");
    OMPI_Open_port = MUK_DLSYM(h,"MPI_Open_port");
    OMPI_Publish_name = MUK_DLSYM(h,"MPI_Publish_name");
    OMPI_Unpublish_name = MUK_DLSYM(h,"MPI_Unpublish_name");

    OMPI_Info_create = MUK_DLSYM(h,"MPI_Info_create");
    OMPI_Info_dup = MUK_DLSYM(h,"MPI_Info_dup");
    OMPI_Info_free = MUK_DLSYM(h,"MPI_Info_free");
    OMPI_Info_get_nkeys = MUK_DLSYM(h,"MPI_Info_get_nkeys");
    OMPI_Info_get_nthkey = MUK_DLSYM(h,"MPI_Info_get_nthkey");
    OMPI_Info_set = MUK_DLSYM(h,"MPI_Info_set");
    if (major >= 4) {
        OMPI_Info_get_string = MUK_DLSYM(h,"MPI_Info_get_string");
    }

    OMPI_Comm_accept = MUK_DLSYM(h,"MPI_Comm_accept");
    OMPI_Comm_connect = MUK_DLSYM(h,"MPI_Comm_connect");
    OMPI_Comm_get_parent = MUK_DLSYM(h,"MPI_Comm_get_parent");
    OMPI_Comm_join = MUK_DLSYM(h,"MPI_Comm_join");
    OMPI_Comm_spawn = MUK_DLSYM(h,"MPI_Comm_spawn");
    OMPI_Comm_spawn_multiple = MUK_DLSYM(h,"MPI_Comm_spawn_multiple");

    if (major >= 4) {
        OMPI_Session_finalize = MUK_DLSYM(h,"MPI_Session_finalize");
        OMPI_Session_get_nth_pset = MUK_DLSYM(h,"MPI_Session_get_nth_pset");
        OMPI_Session_get_info = MUK_DLSYM(h,"MPI_Session_get_info");
        OMPI_Session_get_num_psets = MUK_DLSYM(h,"MPI_Session_get_num_psets");
        OMPI_Session_get_pset_info = MUK_DLSYM(h,"MPI_Session_get_pset_info");
        OMPI_Session_init = MUK_DLSYM(h,"MPI_Session_init");
        OMPI_Session_call_errhandler = MUK_DLSYM(h,"MPI_Session_call_errhandler");
        OMPI_Session_create_errhandler = MUK_DLSYM(h,"MPI_Session_create_errhandler");
        OMPI_Session_get_errhandler = MUK_DLSYM(h,"MPI_Session_get_errhandler");
        OMPI_Session_set_errhandler = MUK_DLSYM(h,"MPI_Session_set_errhandler");
    }

    return 0;
}

int OMPI_Load_predefined(void * restrict h)
{
    OMPI_REQUEST_NULL    = MUK_DLSYM(h,"MPI_REQUEST_NULL");
    OMPI_ERRHANDLER_NULL = MUK_DLSYM(h,"MPI_ERRHANDLER_NULL");
    OMPI_INFO_NULL       = MUK_DLSYM(h,"MPI_INFO_NULL");
    OMPI_WIN_NULL        = MUK_DLSYM(h,"MPI_WIN_NULL");
    OMPI_FILE_NULL       = MUK_DLSYM(h,"MPI_FILE_NULL");

    OMPI_COMM_NULL  = MUK_DLSYM(h,"MPI_COMM_NULL");
    OMPI_COMM_WORLD = MUK_DLSYM(h,"MPI_COMM_WORLD");
    OMPI_COMM_SELF  = MUK_DLSYM(h,"MPI_COMM_SELF");

    OMPI_GROUP_NULL  = MUK_DLSYM(h,"MPI_GROUP_NULL");
    OMPI_GROUP_EMPTY = MUK_DLSYM_OPT(h,"MPI_GROUP_EMPTY",OMPI_GROUP_NULL);

    OMPI_MESSAGE_NULL    = MUK_DLSYM(h,"MPI_MESSAGE_NULL");
    OMPI_MESSAGE_NO_PROC = MUK_DLSYM_OPT(h,"MPI_MESSAGE_NO_PROC",OMPI_MESSAGE_NULL);

    OMPI_OP_NULL = MUK_DLSYM(h,"MPI_OP_NULL");
    OMPI_MAX     = MUK_DLSYM_OPT(h,"MPI_MAX",OMPI_OP_NULL);
    OMPI_MIN     = MUK_DLSYM_OPT(h,"MPI_MIN",OMPI_OP_NULL);
    OMPI_SUM     = MUK_DLSYM_OPT(h,"MPI_SUM",OMPI_OP_NULL);
    OMPI_PROD    = MUK_DLSYM_OPT(h,"MPI_PROD",OMPI_OP_NULL);
    OMPI_LAND    = MUK_DLSYM_OPT(h,"MPI_LAND",OMPI_OP_NULL);
    OMPI_BAND    = MUK_DLSYM_OPT(h,"MPI_BAND",OMPI_OP_NULL);
    OMPI_LOR     = MUK_DLSYM_OPT(h,"MPI_LOR",OMPI_OP_NULL);
    OMPI_BOR     = MUK_DLSYM_OPT(h,"MPI_BOR",OMPI_OP_NULL);
    OMPI_LXOR    = MUK_DLSYM_OPT(h,"MPI_LXOR",OMPI_OP_NULL);
    OMPI_BXOR    = MUK_DLSYM_OPT(h,"MPI_BXOR",OMPI_OP_NULL);
    OMPI_MAXLOC  = MUK_DLSYM_OPT(h,"MPI_MAXLOC",OMPI_OP_NULL);
    OMPI_MINLOC  = MUK_DLSYM_OPT(h,"MPI_MINLOC",OMPI_OP_NULL);
    OMPI_REPLACE = MUK_DLSYM_OPT(h,"MPI_REPLACE",OMPI_OP_NULL);
    OMPI_NO_OP   = MUK_DLSYM_OPT(h,"MPI_NO_OP",OMPI_OP_NULL);

    OMPI_DATATYPE_NULL      = MUK_DLSYM(h,"MPI_DATATYPE_NULL");
    OMPI_BYTE               = MUK_DLSYM_OPT(h,"MPI_BYTE",OMPI_DATATYPE_NULL);
    OMPI_PACKED             = MUK_DLSYM_OPT(h,"MPI_PACKED",OMPI_DATATYPE_NULL);
    OMPI_CHAR               = MUK_DLSYM_OPT(h,"MPI_CHAR",OMPI_DATATYPE_NULL);
    OMPI_SHORT              = MUK_DLSYM_OPT(h,"MPI_SHORT",OMPI_DATATYPE_NULL);
    OMPI_INT                = MUK_DLSYM_OPT(h,"MPI_INT",OMPI_DATATYPE_NULL);
    OMPI_LONG               = MUK_DLSYM_OPT(h,"MPI_LONG",OMPI_DATATYPE_NULL);
    OMPI_FLOAT              = MUK_DLSYM_OPT(h,"MPI_FLOAT",OMPI_DATATYPE_NULL);
    OMPI_DOUBLE             = MUK_DLSYM_OPT(h,"MPI_DOUBLE",OMPI_DATATYPE_NULL);
    OMPI_LONG_DOUBLE        = MUK_DLSYM_OPT(h,"MPI_LONG_DOUBLE",OMPI_DATATYPE_NULL);
    OMPI_UNSIGNED_CHAR      = MUK_DLSYM_OPT(h,"MPI_UNSIGNED_CHAR",OMPI_DATATYPE_NULL);
    OMPI_SIGNED_CHAR        = MUK_DLSYM_OPT(h,"MPI_SIGNED_CHAR",OMPI_DATATYPE_NULL);
    OMPI_UNSIGNED_SHORT     = MUK_DLSYM_OPT(h,"MPI_UNSIGNED_SHORT",OMPI_DATATYPE_NULL);
    OMPI_UNSIGNED_LONG      = MUK_DLSYM_OPT(h,"MPI_UNSIGNED_LONG",OMPI_DATATYPE_NULL);
    OMPI_UNSIGNED           = MUK_DLSYM_OPT(h,"MPI_UNSIGNED",OMPI_DATATYPE_NULL);
    OMPI_FLOAT_INT          = MUK_DLSYM_OPT(h,"MPI_FLOAT_INT",OMPI_DATATYPE_NULL);
    OMPI_DOUBLE_INT         = MUK_DLSYM_OPT(h,"MPI_DOUBLE_INT",OMPI_DATATYPE_NULL);
    OMPI_LONG_DOUBLE_INT    = MUK_DLSYM_OPT(h,"MPI_LONG_DOUBLE_INT",OMPI_DATATYPE_NULL);
    OMPI_LONG_INT           = MUK_DLSYM_OPT(h,"MPI_LONG_INT",OMPI_DATATYPE_NULL);
    OMPI_SHORT_INT          = MUK_DLSYM_OPT(h,"MPI_SHORT_INT",OMPI_DATATYPE_NULL);
    OMPI_2INT               = MUK_DLSYM_OPT(h,"MPI_2INT",OMPI_DATATYPE_NULL);
    OMPI_WCHAR              = MUK_DLSYM_OPT(h,"MPI_WCHAR",OMPI_DATATYPE_NULL);
    OMPI_LONG_LONG_INT      = MUK_DLSYM_OPT(h,"MPI_LONG_LONG_INT",OMPI_DATATYPE_NULL);
    OMPI_LONG_LONG          = MUK_DLSYM_OPT(h,"MPI_LONG_LONG",OMPI_DATATYPE_NULL);
    OMPI_UNSIGNED_LONG_LONG = MUK_DLSYM_OPT(h,"MPI_UNSIGNED_LONG_LONG",OMPI_DATATYPE_NULL);
    OMPI_2COMPLEX           = MUK_DLSYM_OPT(h,"MPI_2COMPLEX",OMPI_DATATYPE_NULL);
    OMPI_2DOUBLE_COMPLEX    = MUK_DLSYM_OPT(h,"MPI_2DOUBLE_COMPLEX",OMPI_DATATYPE_NULL);

    return 0;
}

