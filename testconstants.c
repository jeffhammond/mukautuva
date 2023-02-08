#ifdef NOWRAP
#include <mpi.h>
#else
#include "mpi.h"
#endif

static int s = MPI_ANY_TAG;
const int c = MPI_ANY_TAG;

int main(void)
{
  int m = MPI_ANY_TAG;
  (void)m;
  (void)s;
  (void)c;
  return MPI_ANY_TAG;
}
