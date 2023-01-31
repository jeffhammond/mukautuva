#include "mpi.h"
#include "muk.h"

#if defined(__linux__) && defined(__x86_64__)
#define LIBMPI_NAME "/usr/lib/x86_64-linux-gnu/libmpi.so"
#elif defined(__MACH__)
#define LIBMPI_NAME "/opt/homebrew/lib/libmpi.dylib"
#else
#warning No default MPI library path.
#endif

Which_MPI_e whose_mpi = UNKNOWN;

static int load_symbols(void * restrict handle);

int MPI_Init(int * argc, char *** argv)
{
    int rc;

    char * soname;
    char * env = getenv("MPI_LIB");
    if (env == NULL) {
        soname = LIBMPI_NAME;
    }

    void * h = dlopen(soname, RTLD_LAZY);
    if (h == NULL) {
        printf("dlopen failed: %s\n", dlerror() );
        abort();
    }

    MUK_Init = MUK_DLSYM(h,"MPI_Init");
    rc = MUK_Init(argc,argv);

    // figure out which library i am using
    MUK_Get_library_version = MUK_DLSYM(h,"MPI_Get_library_version");
    {
        char lib_version[16384] = {0};
        int  lib_version_length;
        rc = MUK_Get_library_version(lib_version, &lib_version_length);
        printf("MPI_Get_library_version = %s\n", lib_version);

        char * pos;
        pos = strstr(lib_version, "Open MPI");
        if (pos != NULL) {
            whose_mpi = OMPI;
        }
        pos = strstr(lib_version, "MPICH");
        if (pos != NULL) {
            whose_mpi = MPICH;
        }
    }

    // load these here because theoretically, we need to handle the case where they
    // are not symbols, which will be dependent on the library.
    MUK_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    MUK_Wtick = MUK_DLSYM(h,"MPI_Wtick");

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    if (whose_mpi == MPICH) {
        rc = MPICH_Load_symbols(h, major, minor);
    } else if (whose_mpi == OMPI) {
        rc = OMPI_Load_symbols(h, major, minor);
    }

    return rc;
}

// VIM tip
// s/int (\*MUK_\(.*\))(\(.*\));/MUK_\1 = MUK_DLSYM(h,"MPI_\1");

static int MPICH_Load_symbols(void * restrict h, int major, int minor)
{
    MPICH_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");
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

    MPICH_Info_create = MUK_DLSYM(h,"MPI_Info_create");
    MPICH_Info_dup = MUK_DLSYM(h,"MPI_Info_dup");
    MPICH_Info_free = MUK_DLSYM(h,"MPI_Info_free");
    MPICH_Info_get_nkeys = MUK_DLSYM(h,"MPI_Info_get_nkeys");
    MPICH_Info_get_nthkey = MUK_DLSYM(h,"MPI_Info_get_nthkey");
    MPICH_Info_get_string = MUK_DLSYM(h,"MPI_Info_get_string");
    MPICH_Info_set = MUK_DLSYM(h,"MPI_Info_set");

    MPICH_Comm_accept = MUK_DLSYM(h,"MPI_Comm_accept");
    MPICH_Comm_connect = MUK_DLSYM(h,"MPI_Comm_connect");
    MPICH_Comm_get_parent = MUK_DLSYM(h,"MPI_Comm_get_parent");
    MPICH_Comm_join = MUK_DLSYM(h,"MPI_Comm_join");
    MPICH_Comm_spawn = MUK_DLSYM(h,"MPI_Comm_spawn");
    MPICH_Comm_spawn_multiple = MUK_DLSYM(h,"MPI_Comm_spawn_multiple");
    MPICH_Finalize = MUK_DLSYM(h,"MPI_Finalize");
    MPICH_Finalized = MUK_DLSYM(h,"MPI_Finalized");
    MPICH_Init = MUK_DLSYM(h,"MPI_Init");
    MPICH_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    MPICH_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    MPICH_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    MPICH_Lookup_name = MUK_DLSYM(h,"MPI_Lookup_name");
    MPICH_Open_port = MUK_DLSYM(h,"MPI_Open_port");
    MPICH_Publish_name = MUK_DLSYM(h,"MPI_Publish_name");
    MPICH_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    MPICH_Unpublish_name = MUK_DLSYM(h,"MPI_Unpublish_name");

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

    return 0;
}

static int OMPI_Load_symbols(void * restrict h, int major, int minor)
{
    OMPI_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");
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

    OMPI_Info_create = MUK_DLSYM(h,"MPI_Info_create");
    OMPI_Info_dup = MUK_DLSYM(h,"MPI_Info_dup");
    OMPI_Info_free = MUK_DLSYM(h,"MPI_Info_free");
    OMPI_Info_get_nkeys = MUK_DLSYM(h,"MPI_Info_get_nkeys");
    OMPI_Info_get_nthkey = MUK_DLSYM(h,"MPI_Info_get_nthkey");
    OMPI_Info_get_string = MUK_DLSYM(h,"MPI_Info_get_string");
    OMPI_Info_set = MUK_DLSYM(h,"MPI_Info_set");

    OMPI_Comm_accept = MUK_DLSYM(h,"MPI_Comm_accept");
    OMPI_Comm_connect = MUK_DLSYM(h,"MPI_Comm_connect");
    OMPI_Comm_get_parent = MUK_DLSYM(h,"MPI_Comm_get_parent");
    OMPI_Comm_join = MUK_DLSYM(h,"MPI_Comm_join");
    OMPI_Comm_spawn = MUK_DLSYM(h,"MPI_Comm_spawn");
    OMPI_Comm_spawn_multiple = MUK_DLSYM(h,"MPI_Comm_spawn_multiple");
    OMPI_Finalize = MUK_DLSYM(h,"MPI_Finalize");
    OMPI_Finalized = MUK_DLSYM(h,"MPI_Finalized");
    OMPI_Init = MUK_DLSYM(h,"MPI_Init");
    OMPI_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    OMPI_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    OMPI_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    OMPI_Lookup_name = MUK_DLSYM(h,"MPI_Lookup_name");
    OMPI_Open_port = MUK_DLSYM(h,"MPI_Open_port");
    OMPI_Publish_name = MUK_DLSYM(h,"MPI_Publish_name");
    OMPI_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    OMPI_Unpublish_name = MUK_DLSYM(h,"MPI_Unpublish_name");

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

    return 0;
}
