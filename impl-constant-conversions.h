#ifndef MUK_IMPL_CONSTANT_CONVERSIONS_H
#define MUK_IMPL_CONSTANT_CONVERSIONS_H

#define MAYBE_UNUSED __attribute__((unused))

// success is the common case, so static inline it.
// jump to the error conversion only when necessary.
// the ERROR_CODE functions need to be symbols because
// they are used in the outer layer for the functions
// that are used directly (because they do not have
// handle arguments).
int ERROR_CODE_IMPL_TO_MUK(int error_c);
static inline int RETURN_CODE_IMPL_TO_MUK(int error_c)
{
    if (error_c == 0) return 0;
    return  ERROR_CODE_IMPL_TO_MUK(error_c);
}

int ERROR_CODE_MUK_TO_IMPL(int error_muk);
static inline int RETURN_CODE_MUK_TO_IMPL(int error_muk)
{
    if (error_muk == 0) return 0;
    return ERROR_CODE_MUK_TO_IMPL(error_muk);
}

MAYBE_UNUSED
static int COMBINER_CODE_IMPL_TO_MUK(int in)
{
         if (in == MPI_COMBINER_CONTIGUOUS)     { return MUK_COMBINER_CONTIGUOUS; }
    else if (in == MPI_COMBINER_DARRAY)         { return MUK_COMBINER_DARRAY; }
    else if (in == MPI_COMBINER_DUP)            { return MUK_COMBINER_DUP; }
    else if (in == MPI_COMBINER_F90_COMPLEX)    { return MUK_COMBINER_F90_COMPLEX; }
    else if (in == MPI_COMBINER_F90_INTEGER)    { return MUK_COMBINER_F90_INTEGER; }
    else if (in == MPI_COMBINER_F90_REAL)       { return MUK_COMBINER_F90_REAL; }
    else if (in == MPI_COMBINER_HINDEXED)       { return MUK_COMBINER_HINDEXED; }
    else if (in == MPI_COMBINER_HVECTOR)        { return MUK_COMBINER_HVECTOR; }
    else if (in == MPI_COMBINER_INDEXED_BLOCK)  { return MUK_COMBINER_INDEXED_BLOCK; }
    else if (in == MPI_COMBINER_HINDEXED_BLOCK) { return MUK_COMBINER_HINDEXED_BLOCK; }
    else if (in == MPI_COMBINER_INDEXED)        { return MUK_COMBINER_INDEXED; }
    else if (in == MPI_COMBINER_NAMED)          { return MUK_COMBINER_NAMED; }
    else if (in == MPI_COMBINER_RESIZED)        { return MUK_COMBINER_RESIZED; }
    else if (in == MPI_COMBINER_STRUCT)         { return MUK_COMBINER_STRUCT; }
    else if (in == MPI_COMBINER_SUBARRAY)       { return MUK_COMBINER_SUBARRAY; }
    else if (in == MPI_COMBINER_VECTOR)         { return MUK_COMBINER_VECTOR; }
    else                                        { return MUK_UNDEFINED; }
}

// MUK, MPICH and OMPI agree that ANY_TAG = -1 so no conversion is required.
#define TAG_MUK_TO_IMPL(tag) (tag)
#define TAG_IMPL_TO_MUK(tag) (tag)

MAYBE_UNUSED
static inline int RANK_MUK_TO_IMPL(int rank_muk)
{
    // predefined constants are always negative
    if (rank_muk >= 0) {
        return rank_muk;
    }
    else if (rank_muk == MUK_ANY_SOURCE) {
        return MPI_ANY_SOURCE;
    }
    else if (rank_muk == MUK_PROC_NULL) {
        return MPI_PROC_NULL;
    }
    // This gets used by MPICH at least, as an initialization value.
    else if (rank_muk == MUK_UNDEFINED) {
        return MPI_UNDEFINED;
    }
#ifdef MPICH
    // https://github.com/pmodels/mpich/issues/6421
    else if (rank_muk == -269488145) {
        return MPI_UNDEFINED;
    }
#endif
    // this one only applies to intercomms
    else if (rank_muk == MUK_ROOT) {
        return MPI_ROOT;
    }
    else {
        // This will generate false-positive warnings with MPICH
        // of the following form, so we handle this case above.
        // RANK_MUK_TO_IMPL rank=-269488145=efefefef
#if 1
        printf("RANK_MUK_TO_IMPL rank=%d=%x\n", rank_muk, rank_muk);
#endif
        return rank_muk;
    }
}

MAYBE_UNUSED
static inline int RANK_IMPL_TO_MUK(int rank_impl)
{
    // predefined constants are always negative
    if (rank_impl >= 0) {
        return rank_impl;
    }
    else if (rank_impl == MPI_ANY_SOURCE) {
        return MUK_ANY_SOURCE;
    }
    else if (rank_impl == MPI_PROC_NULL) {
        return MUK_PROC_NULL;
    }
    // This gets used by MPICH at least, as an initialization value.
    else if (rank_impl == MPI_UNDEFINED) {
        return MUK_UNDEFINED;
    }
#ifdef MPICH
    // https://github.com/pmodels/mpich/issues/6421
    else if (rank_impl == -269488145) {
        return MPI_UNDEFINED;
    }
#endif
#if 0
    // this one only applies to intercomms
    else if (rank_impl == MPI_ROOT) {
        return MUK_ROOT;
    }
#endif
    else {
#if DEBUG
        printf("RANK_IMPL_TO_MUK rank=%d=%x\n", rank_impl, rank_impl);
#endif
        return rank_impl;
    }
}

// mode constant conversion - this needs to handle multiple modes OR-ed together
MAYBE_UNUSED
static int IO_MODE_MUK_TO_IMPL(int mode_muk)
{
    int mode_impl = 0;
    if (mode_muk & MUK_MODE_APPEND) {
        mode_impl |= MPI_MODE_APPEND;
        //printf("mode_impl |= MPI_MODE_APPEND\n");
    }
    if (mode_muk & MUK_MODE_CREATE) {
        mode_impl |= MPI_MODE_CREATE;
        //printf("mode_impl |= MPI_MODE_CREATE\n");
    }
    if (mode_muk & MUK_MODE_DELETE_ON_CLOSE) {
        mode_impl |= MPI_MODE_DELETE_ON_CLOSE;
        //printf("mode_impl |= MPI_MODE_DELETE_ON_CLOSE\n");
    }
    if (mode_muk & MUK_MODE_EXCL) {
        mode_impl |= MPI_MODE_EXCL;
        //printf("mode_impl |= MPI_MODE_EXCL\n");
    }
    if (mode_muk & MUK_MODE_RDONLY) {
        mode_impl |= MPI_MODE_RDONLY;
        //printf("mode_impl |= MPI_MODE_RDONLY\n");
    }
    if (mode_muk & MUK_MODE_RDWR) {
        mode_impl |= MPI_MODE_RDWR;
        //printf("mode_impl |= MPI_MODE_RDWR\n");
    }
    if (mode_muk & MUK_MODE_SEQUENTIAL) {
        mode_impl |= MPI_MODE_SEQUENTIAL;
        //printf("mode_impl |= MPI_MODE_SEQUENTIAL\n");
    }
    if (mode_muk & MUK_MODE_UNIQUE_OPEN) {
        mode_impl |= MPI_MODE_UNIQUE_OPEN;
        //printf("mode_impl |= MPI_MODE_UNIQUE_OPEN\n");
    }
    if (mode_muk & MUK_MODE_WRONLY) {
        mode_impl |= MPI_MODE_WRONLY;
        //printf("mode_impl |= MPI_MODE_WRONLY\n");
    }
    return mode_impl;
}

MAYBE_UNUSED
static int IO_MODE_IMPL_TO_MUK(int mode_impl)
{
    int mode_muk = 0;
    if (mode_impl & MUK_MODE_APPEND)          { mode_muk |= MPI_MODE_APPEND; }
    if (mode_impl & MUK_MODE_CREATE)          { mode_muk |= MPI_MODE_CREATE; }
    if (mode_impl & MUK_MODE_DELETE_ON_CLOSE) { mode_muk |= MPI_MODE_DELETE_ON_CLOSE; }
    if (mode_impl & MUK_MODE_EXCL)            { mode_muk |= MPI_MODE_EXCL; }
    if (mode_impl & MUK_MODE_RDONLY)          { mode_muk |= MPI_MODE_RDONLY; }
    if (mode_impl & MUK_MODE_RDWR)            { mode_muk |= MPI_MODE_RDWR; }
    if (mode_impl & MUK_MODE_SEQUENTIAL)      { mode_muk |= MPI_MODE_SEQUENTIAL; }
    if (mode_impl & MUK_MODE_UNIQUE_OPEN)     { mode_muk |= MPI_MODE_UNIQUE_OPEN; }
    if (mode_impl & MUK_MODE_WRONLY)          { mode_muk |= MPI_MODE_WRONLY; }
    return mode_muk;
}

// mode constant conversion - this needs to handle multiple modes OR-ed together
MAYBE_UNUSED
static int RMA_MODE_MUK_TO_IMPL(int mode_muk)
{
    int mode_impl = 0;
    if (mode_muk & MUK_MODE_NOCHECK)         { mode_impl |= MPI_MODE_NOCHECK; }
    if (mode_muk & MUK_MODE_NOPRECEDE)       { mode_impl |= MPI_MODE_NOPRECEDE; }
    if (mode_muk & MUK_MODE_NOPUT)           { mode_impl |= MPI_MODE_NOPUT; }
    if (mode_muk & MUK_MODE_NOSTORE)         { mode_impl |= MPI_MODE_NOSTORE; }
    if (mode_muk & MUK_MODE_NOSUCCEED)       { mode_impl |= MPI_MODE_NOSUCCEED; }
    return mode_impl;
}

// predefined attribute conversion
MAYBE_UNUSED
static int KEY_MUK_TO_IMPL(int key_muk)
{
         if (key_muk == MUK_TAG_UB)            { return MPI_TAG_UB; }
    else if (key_muk == MUK_IO)                { return MPI_IO; }
    else if (key_muk == MUK_HOST)              { return MPI_HOST; }
    else if (key_muk == MUK_WTIME_IS_GLOBAL)   { return MPI_WTIME_IS_GLOBAL; }
    else if (key_muk == MUK_APPNUM)            { return MPI_APPNUM; }
    else if (key_muk == MUK_LASTUSEDCODE)      { return MPI_LASTUSEDCODE; }
    else if (key_muk == MUK_UNIVERSE_SIZE)     { return MPI_UNIVERSE_SIZE; }
    else if (key_muk == MUK_WIN_BASE)          { return MPI_WIN_BASE; }
    else if (key_muk == MUK_WIN_DISP_UNIT)     { return MPI_WIN_DISP_UNIT; }
    else if (key_muk == MUK_WIN_SIZE)          { return MPI_WIN_SIZE; }
    else if (key_muk == MUK_WIN_CREATE_FLAVOR) { return MPI_WIN_CREATE_FLAVOR; }
    else if (key_muk == MUK_WIN_MODEL)         { return MPI_WIN_MODEL; }
    else                                       { return key_muk; }
}

MAYBE_UNUSED
static const int * WEIGHTS_MUK_TO_IMPL(const int * weights_muk, const int * mpich_unweighted, const int * mpich_weights_empty)
{
    if ((intptr_t)weights_muk == (intptr_t)MUK_UNWEIGHTED) {
#if OPEN_MPI
        return MPI_UNWEIGHTED;
        (void)mpich_unweighted;
#else
        return mpich_unweighted;
#endif
    }
    else if ((intptr_t)weights_muk == (intptr_t)MUK_WEIGHTS_EMPTY) {
#if OPEN_MPI
        return MPI_WEIGHTS_EMPTY;
        (void)mpich_weights_empty;
#else
        return mpich_weights_empty;
#endif
    }
    else {
        return weights_muk;
    }
}

MAYBE_UNUSED
static const int * WEIGHTS_IMPL_TO_MUK(const int * weights_impl)
{
    if ((intptr_t)weights_impl == (intptr_t)MPI_UNWEIGHTED)    {
        return MUK_UNWEIGHTED;
    }
    else if ((intptr_t)weights_impl == (intptr_t)MPI_WEIGHTS_EMPTY) {
        return MUK_WEIGHTS_EMPTY;
    }
    else {
        return weights_impl;
    }
}
#endif
