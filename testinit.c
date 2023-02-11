#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

int main(int argc, char* argv[])
{
    int rc, flag;
    rc = MPI_Initialized(&flag);
    printf("is init? %d\n", flag);

    int major, minor;
    rc = MPI_Get_version(&major,&minor);
    printf("BEFORE major=%d, minor=%d\n", major, minor);

    int len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    rc = MPI_Get_library_version(version,&len);
    printf("BEFORE version=%s\n", version);

    rc = MPI_Init(&argc,&argv);

    rc = MPI_Get_version(&major,&minor);
    printf("AFTER major=%d, minor=%d\n", major, minor);

    rc = MPI_Get_library_version(version,&len);
    printf("AFTER version=%s\n", version);

    double t0 = MPI_Wtime();

    rc = MPI_Initialized(&flag);
    printf("is init? %d\n", flag);
    rc = MPI_Finalized(&flag);
    printf("is final? %d\n", flag);
    rc = MPI_Is_thread_main(&flag);
    printf("is thread main? %d\n", flag);

    double t1 = MPI_Wtime();

    printf("dt=%lf\n",t1-t0);

    rc = MPI_Finalize();

    rc = MPI_Finalized(&flag);
    printf("is final? %d\n", flag);

    printf("all done\n");

    return rc;
}
