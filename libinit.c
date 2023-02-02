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

typedef struct __MPI_Comm__ * MUK_Comm;
typedef struct __MPI_Datatype__ * MUK_Datatype;
typedef struct __MPI_Errhandler__ * MUK_Errhandler;
typedef struct __MPI_File__ * MUK_File;
typedef struct __MPI_Group__ * MUK_Group;
typedef struct __MPI_Info__ * MUK_Info;
typedef struct __MPI_Message__ * MUK_Message;
typedef struct __MPI_Op__ * MUK_Op;
typedef struct __MPI_Request__ * MUK_Request;
typedef struct __MPI_Session__ * MUK_Session;
typedef struct __MPI_Win__ * MUK_Win;

typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
MUK_Status;

typedef ptrdiff_t MUK_Aint;
typedef ptrdiff_t MUK_Count;
typedef ptrdiff_t MUK_Offset;

int (*MUK_Init)(int *argc, char ***argv);
int (*MUK_Init_thread)(int *argc, char ***argv, int required, int *provided);
int (*MUK_Initialized)(int *flag);

int (*MUK_Get_library_version)(char *version, int *resultlen);
int (*MUK_Get_processor_name)(char *name, int *resultlen);
int (*MUK_Get_version)(int *version, int *subversion);

int (*MUK_Finalize)(void);
int (*MUK_Finalized)(int *flag);

int (*MUK_Init_thread)(int *argc, char ***argv, int required, int *provided);
int (*MUK_Is_thread_main)(int *flag);
int (*MUK_Query_thread)(int *provided);

int (*MUK_Comm_rank)(MUK_Comm comm, int *rank);
int (*MUK_Comm_size)(MUK_Comm comm, int *size);
int (*MUK_Abort)(MUK_Comm comm, int errorcode);

extern MUK_Comm MPI_COMM_WORLD;

int (*WRAP_Load_functions)(void * restrict h, int major, int minor);

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

    char * wrapname;
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

    int major, minor;
    MUK_Get_version = MUK_DLSYM(h,"MPI_Get_version");
    rc = MUK_Get_version(&major, &minor);

    void * wrap_so_handle = dlopen(wrapname, RTLD_LAZY);
    if (wrap_so_handle == NULL) {
        printf("dlopen of %s failed: %s\n", wrapname, dlerror() );
        abort();
    }
    MPI_COMM_WORLD = MUK_DLSYM(wrap_so_handle,"IMPL_COMM_WORLD");

    // now we are hacking
    MUK_Abort = MUK_DLSYM(wrap_so_handle,"WRAP_Abort");
    MUK_Comm_rank = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_rank");
    MUK_Comm_size = MUK_DLSYM(wrap_so_handle,"WRAP_Comm_size");

    WRAP_Load_functions = MUK_DLSYM(wrap_so_handle,"WRAP_Load_functions");
    rc = WRAP_Load_functions(h,major,minor);

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

int MPI_Abort(MUK_Comm comm, int errorcode)
{
    return MUK_Abort(comm, errorcode);
}

int MPI_Comm_rank(MUK_Comm comm, int * rank)
{
    return MUK_Comm_rank(comm, rank);
}

int MPI_Comm_size(MUK_Comm comm, int * size)
{
    return MUK_Comm_size(comm, size);
}
