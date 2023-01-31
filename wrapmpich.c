#include "muk-mpi-typedefs.h"
#include "muk-functions.h"

int MUK_Load_functions(void * restrict h, int major, int minor)
{
    (void)minor;

    MUK_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    MUK_Wtick = MUK_DLSYM(h,"MPI_Wtick");
    MUK_Abort = MUK_DLSYM(h,"MPI_Abort");

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
