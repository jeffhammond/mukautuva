typedef struct __MPI_Comm__     * MPI_Comm;
typedef struct __MPI_Datatype__ * MPI_Datatype;
typedef struct __MPI_File__     * MPI_File;
typedef struct __MPI_Group__    * MPI_Group;
typedef struct __MPI_Info__     * MPI_Info;
typedef struct __MPI_Message__  * MPI_Message;
typedef struct __MPI_Op__       * MPI_Op;
typedef struct __MPI_Request__  * MPI_Request;
typedef struct __MPI_Win__      * MPI_Win;

typedef struct __MPI_Status__
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
MPI_Status;

int MPI_Init(int*,char***);
int MPI_Finalize(void);
int MPI_Abort(MPI_Comm,int);

int MPI_Test(MPI_Request*,int*,MPI_Status*);
int MPI_Testall(int,MPI_Request[],int*,MPI_Status[]);
int MPI_Testany(int,MPI_Request[],int*,int*,MPI_Status*);
int MPI_Testsome(int,MPI_Request[],int*,int[],MPI_Status[]);
int MPI_Wait(MPI_Request*,MPI_Status*);
int MPI_Waitall(int,MPI_Request[],MPI_Status[]);
int MPI_Waitany(int,MPI_Request[],int*,MPI_Status*);
int MPI_Waitsome(int,MPI_Request[],int*,int[],MPI_Status[]);

int MPI_Test_cancelled(const MPI_Status*,int*);
