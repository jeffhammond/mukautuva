#include "muk.h"
#include "muk-dl.h"

#define USE_MUK_NAMESPACE
#include "muk-mpi-typedefs.h"
#define MAKE_FUNCTION_POINTERS
#include "muk-mpi-functions.h"

double (*MUK_Wtime)(void);
double (*MUK_Wtick)(void);

#if defined(__linux__) && defined(__x86_64__)
#define LIBMPI_NAME "/usr/lib/x86_64-linux-gnu/libmpi.so"
#elif defined(__MACH__)
#define LIBMPI_NAME "/opt/homebrew/lib/libmpi.dylib"
#else
#warning No default MPI library path.
#endif

Which_MPI_e whose_mpi = UNKNOWN;

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

    void * h = dlopen(soname, RTLD_LAZY);
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
    MUK_Initialized = MUK_DLSYM(h,"MPI_Initialized");
    MUK_Is_thread_main = MUK_DLSYM(h,"MPI_Is_thread_main");
    MUK_Query_thread = MUK_DLSYM(h,"MPI_Query_thread");
    MUK_Get_processor_name = MUK_DLSYM(h,"MPI_Get_processor_name");
    MUK_Wtime = MUK_DLSYM(h,"MPI_Wtime");
    MUK_Wtick = MUK_DLSYM(h,"MPI_Wtick");

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    char * wrapname;
    if (whose_mpi == OMPI) {
        wrapname = "libmukompi.so";
    } else if (whose_mpi == MPICH) {
        wrapname = "libmukmpich.so";
    }

    // now we load the wrapper for the implementation we have
    void * w = dlopen(wrapname, RTLD_LAZY);
    if (w == NULL) {
        printf("dlopen of %s failed: %s\n", wrapname, dlerror() );
        abort();
    } else {
        MUK_Load_functions = MUK_DLSYM(w,"MUK_Load_functions");
        rc = MUK_Load_functions(h, major, minor);
        MUK_Load_predefined = MUK_DLSYM(w,"MUK_Load_predefined");
        rc = MUK_Load_predefined(h);
    }

    return rc;
}

#define USE_MPI_NAMESPACE
#include "muk-mpi-typedefs.h"
#include "muk-mpi-functions.h"

int MPI_Init(int * argc, char *** argv)
{
    return MUK_Alkaa(argc,argv,-1,NULL);
}

int MPI_Init_thread(int * argc, char *** argv, int requested, int * provided)
{
    return MUK_Alkaa(argc,argv,requested,provided);
}

int MPI_Get_library_version(char *version, int *resultlen)
{
    return MUK_Get_library_version(version, resultlen);
}

int MPI_Finalize(void)
{
    return MUK_Finalize();
}

int MPI_Finalized(int * flag)
{
    return MUK_Finalized(flag);
}

int MPI_Initialized(int * flag)
{
    return MUK_Initialized(flag);
}

int MPI_Is_thread_main(int * flag)
{
    return MUK_Is_thread_main(flag);
}

int MPI_Query_thread(int * provided)
{
    return MUK_Query_thread(provided);
}

int MPI_Get_processor_name(char *name, int *resultlen)
{
    return MUK_Get_processor_name(name, resultlen);
}

int MPI_Get_version(int * major, int * minor)
{
    return MUK_Get_version(major, minor);
}

double MPI_Wtime(void) { return MUK_Wtime(); }
double MPI_Wtick(void) { return MUK_Wtick(); }
