#ifndef IMPL_SCALAR_TYPES_H
#define IMPL_SCALAR_TYPES_H

// This is terrible but compiles complain even though they are the same size
#if defined(OPEN_MPI)
typedef long int WRAP_Aint;
typedef long long int WRAP_Count;
typedef long long int WRAP_Offset;
#elif defined(MPICH)
typedef long int WRAP_Aint;
// Linux?
//typedef long int WRAP_Count;
//typedef long int WRAP_Offset;
// Mac
typedef long long int WRAP_Count;
typedef long long int WRAP_Offset;
#else
#error NO ABI
#endif

#endif
