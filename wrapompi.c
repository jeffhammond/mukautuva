#include "muk.h"
#include "mpi.h"
#include "ompi.h"

int OMPI_Load_symbols(void * restrict h, int major, int minor)
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
