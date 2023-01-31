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

// alkaa = start
int MUK_Alkaa(int * argc, char *** argv, int requested, int * provided)
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
    MUK_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    if (provided == NULL) {
        rc = MUK_Init(argc,argv);
    } else {
        rc = MUK_Init_thread(argc,argv,requested,provided);
    }

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

    // these are ABI-agnostic and important, so why not load them now...
    MUK_Finalize = MUK_DLSYM(h,"MPI_Finalize");
    MUK_Finalized = MUK_DLSYM(h,"MPI_Finalized");
    MUK_Init_thread = MUK_DLSYM(h,"MPI_Init_thread");
    MUK_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    MUK_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    MUK_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    MUK_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    if (whose_mpi == MPICH) {
        rc = MPICH_Load_functions(h, major, minor);
    } else if (whose_mpi == OMPI) {
        rc = OMPI_Load_functions(h, major, minor);
        rc = OMPI_Load_predefined(h);
    }

    return rc;
}

int MPI_Init(int * argc, char *** argv)
{
    return MUK_Alkaa(argc,argv,-1,NULL);
}

int MPI_Init_thread(int * argc, char *** argv, int requested, int * provided)
{
    return MUK_Alkaa(argc,argv,requested,provided);
}
