#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc,&argv);

    const int nr = (argc > 1) ? atoi(argv[1]) : 1000;
    const int nm = (argc > 2) ? atoi(argv[2]) : 1000;

    printf("iterations = %d, mallocs = %d\n", nr, nm);

    void ** pp = calloc(nm,sizeof(void*));

    double t0,t1,t2,t3,tt01=0,tt12=0,tt23=0;

    for (int r=0; r<=nr; r++) {

        t0 = MPI_Wtime();        

        for (int m=0; m<nm; m++) {
            pp[m] = malloc(sizeof(void*));
        }

        t1 = MPI_Wtime();        

        for (int m=0; m<nm; m++) {
            pp[m] = NULL;
        }

        t2 = MPI_Wtime();        

        for (int m=0; m<nm; m++) {
            free(pp[m]);
        }

        t3 = MPI_Wtime();        

        if (r==0 || r==1 || r==10 || r==100 || r==nr) {
            printf("iteration %d\n", r);
            printf("malloc = %lf ns\n", 1e9*(t1-t0)/nm);
            printf("assign = %lf ns\n", 1e9*(t2-t1)/nm);
            printf("free   = %lf ns\n", 1e9*(t3-t2)/nm);
        }

        tt01 += t1-t0;
        tt12 += t2-t1;
        tt23 += t3-t2;
    }

    printf("malloc = %lf ns\n", 1e9*tt01/(nm*nr));
    printf("assign = %lf ns\n", 1e9*tt12/(nm*nr));
    printf("free   = %lf ns\n", 1e9*tt23/(nm*nr));

    free(pp);

    return MPI_Finalize();
}
