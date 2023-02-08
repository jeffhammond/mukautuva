#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

#if 0
extern void * MUK_MPI_ANY_TAG;
#define MPI_ANY_TAG (*(int*)MUK_MPI_ANY_TAG);

static int s = MPI_ANY_TAG;
const int c = MPI_ANY_TAG;

(void)s;
(void)c;

int rc = MPI_ERR_UNKNOWN;
#endif

int main(void)
{
  int m = MPI_ANY_TAG;
  (void)m;
  return MPI_SUCCESS;
}
