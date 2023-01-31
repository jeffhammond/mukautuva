#include "muk.h"
#include "mpi.h"
#include "mpich.h"

// VIM tip
// s/int (\*MUK_\(.*\))(\(.*\));/MUK_\1 = MUK_DLSYM(h,"MPI_\1");

int MPICH_Load_symbols(void * restrict h, int major, int minor)
{
    (void)minor;

    MPICH_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    MPICH_Wtick = MUK_DLSYM(h,"MPI_Wtick");
    MPICH_Abort = MUK_DLSYM(h,"MPI_Abort");

    MPICH_Alloc_mem = MUK_DLSYM(h,"MPI_Alloc_mem");
    MPICH_Free_mem = MUK_DLSYM(h,"MPI_Free_mem");

    MPICH_Add_error_class = MUK_DLSYM(h,"MPI_Add_error_class");
    MPICH_Add_error_code = MUK_DLSYM(h,"MPI_Add_error_code");
    MPICH_Add_error_string = MUK_DLSYM(h,"MPI_Add_error_string");

    MPICH_Comm_call_errhandler = MUK_DLSYM(h,"MPI_Comm_call_errhandler");
    MPICH_Comm_create_errhandler = MUK_DLSYM(h,"MPI_Comm_create_errhandler");
    MPICH_Comm_get_errhandler = MUK_DLSYM(h,"MPI_Comm_get_errhandler");
    MPICH_Comm_set_errhandler = MUK_DLSYM(h,"MPI_Comm_set_errhandler");

    MPICH_Errhandler_free = MUK_DLSYM(h,"MPI_Errhandler_free");
    MPICH_Error_class = MUK_DLSYM(h,"MPI_Error_class");
    MPICH_Error_string = MUK_DLSYM(h,"MPI_Error_string");

    MPICH_File_call_errhandler = MUK_DLSYM(h,"MPI_File_call_errhandler");
    MPICH_File_create_errhandler = MUK_DLSYM(h,"MPI_File_create_errhandler");
    MPICH_File_get_errhandler = MUK_DLSYM(h,"MPI_File_get_errhandler");
    MPICH_File_set_errhandler = MUK_DLSYM(h,"MPI_File_set_errhandler");

    MPICH_Win_call_errhandler = MUK_DLSYM(h,"MPI_Win_call_errhandler");
    MPICH_Win_create_errhandler = MUK_DLSYM(h,"MPI_Win_create_errhandler");
    MPICH_Win_get_errhandler = MUK_DLSYM(h,"MPI_Win_get_errhandler");
    MPICH_Win_set_errhandler = MUK_DLSYM(h,"MPI_Win_set_errhandler");

    MPICH_Close_port = MUK_DLSYM(h,"MPI_Close_port");
    MPICH_Comm_disconnect = MUK_DLSYM(h,"MPI_Comm_disconnect");
    MPICH_Lookup_name = MUK_DLSYM(h,"MPI_Lookup_name");
    MPICH_Open_port = MUK_DLSYM(h,"MPI_Open_port");
    MPICH_Publish_name = MUK_DLSYM(h,"MPI_Publish_name");
    MPICH_Unpublish_name = MUK_DLSYM(h,"MPI_Unpublish_name");

    MPICH_Info_create = MUK_DLSYM(h,"MPI_Info_create");
    MPICH_Info_dup = MUK_DLSYM(h,"MPI_Info_dup");
    MPICH_Info_free = MUK_DLSYM(h,"MPI_Info_free");
    MPICH_Info_get_nkeys = MUK_DLSYM(h,"MPI_Info_get_nkeys");
    MPICH_Info_get_nthkey = MUK_DLSYM(h,"MPI_Info_get_nthkey");
    MPICH_Info_set = MUK_DLSYM(h,"MPI_Info_set");
    if (major >= 4) {
        MPICH_Info_get_string = MUK_DLSYM(h,"MPI_Info_get_string");
    }

    MPICH_Comm_accept = MUK_DLSYM(h,"MPI_Comm_accept");
    MPICH_Comm_connect = MUK_DLSYM(h,"MPI_Comm_connect");
    MPICH_Comm_get_parent = MUK_DLSYM(h,"MPI_Comm_get_parent");
    MPICH_Comm_join = MUK_DLSYM(h,"MPI_Comm_join");
    MPICH_Comm_spawn = MUK_DLSYM(h,"MPI_Comm_spawn");
    MPICH_Comm_spawn_multiple = MUK_DLSYM(h,"MPI_Comm_spawn_multiple");

    if (major >= 4) {
        MPICH_Session_finalize = MUK_DLSYM(h,"MPI_Session_finalize");
        MPICH_Session_get_nth_pset = MUK_DLSYM(h,"MPI_Session_get_nth_pset");
        MPICH_Session_get_info = MUK_DLSYM(h,"MPI_Session_get_info");
        MPICH_Session_get_num_psets = MUK_DLSYM(h,"MPI_Session_get_num_psets");
        MPICH_Session_get_pset_info = MUK_DLSYM(h,"MPI_Session_get_pset_info");
        MPICH_Session_init = MUK_DLSYM(h,"MPI_Session_init");
        MPICH_Session_call_errhandler = MUK_DLSYM(h,"MPI_Session_call_errhandler");
        MPICH_Session_create_errhandler = MUK_DLSYM(h,"MPI_Session_create_errhandler");
        MPICH_Session_get_errhandler = MUK_DLSYM(h,"MPI_Session_get_errhandler");
        MPICH_Session_set_errhandler = MUK_DLSYM(h,"MPI_Session_set_errhandler");
    }

    return 0;
}
