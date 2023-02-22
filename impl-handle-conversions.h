#ifndef MUK_IMPL_HANDLE_CONVERSIONS_H
#define MUK_IMPL_HANDLE_CONVERSIONS_H

/*
typedef union
{
    void *      p;  // OMPI
    int         i;  // MPICH
    intptr_t    ip;
}
MUK_Handle;
*/

static inline MPI_Comm CONVERT_MPI_Comm(WRAP_Comm comm)
{
#ifdef MPICH
    return comm.i;
#elif OPEN_MPI
    return comm.p;
#else
#error NO ABI
#endif
}

static inline MPI_Datatype CONVERT_MPI_Datatype(WRAP_Datatype datatype)
{
#ifdef MPICH
    return datatype.i;
#elif OPEN_MPI
    return datatype.p;
#else
#error NO ABI
#endif
}

static inline MPI_Errhandler CONVERT_MPI_Errhandler(WRAP_Errhandler errhandler)
{
#ifdef MPICH
    return errhandler.i;
#elif OPEN_MPI
    return errhandler.p;
#else
#error NO ABI
#endif
}

static inline MPI_File CONVERT_MPI_File(WRAP_File fh)
{
#ifdef MPICH
    // ADIOS is an exception to MPICH handle design
    return fh.p;
#elif OPEN_MPI
    return fh.p;
#else
#error NO ABI
#endif
}

static inline MPI_Group CONVERT_MPI_Group(WRAP_Group group)
{
#ifdef MPICH
    return group.i;
#elif OPEN_MPI
    return group.p;
#else
#error NO ABI
#endif
}

static inline MPI_Info CONVERT_MPI_Info(WRAP_Info info)
{
#ifdef MPICH
    return info.i;
#elif OPEN_MPI
    return info.p;
#else
#error NO ABI
#endif
}

static inline MPI_Message CONVERT_MPI_Message(WRAP_Message op)
{
#ifdef MPICH
    return op.i;
#elif OPEN_MPI
    return op.p;
#else
#error NO ABI
#endif
}

static inline MPI_Op CONVERT_MPI_Op(WRAP_Op op)
{
#ifdef MPICH
    return op.i;
#elif OPEN_MPI
    return op.p;
#else
#error NO ABI
#endif
}

static inline MPI_Request CONVERT_MPI_Request(WRAP_Request request)
{
#ifdef MPICH
    return request.i;
#elif OPEN_MPI
    return request.p;
#else
#error NO ABI
#endif
}

#if MPI_VERSION >= 4
static inline MPI_Session CONVERT_MPI_Session(WRAP_Session session)
{
#ifdef MPICH
    return session.i;
#elif OPEN_MPI
    return session.p;
#else
#error NO ABI
#endif
}
#endif

static inline MPI_Win CONVERT_MPI_Win(WRAP_Win win)
{
#ifdef MPICH
    return win.i;
#elif OPEN_MPI
    return win.p;
#else
#error NO ABI
#endif
}

static inline WRAP_Comm OUTPUT_MPI_Comm(MPI_Comm comm)
{
    WRAP_Comm wrap;
#ifdef MPICH
    wrap.i = comm;
#elif OPEN_MPI
    wrap.p = comm;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Datatype OUTPUT_MPI_Datatype(MPI_Datatype datatype)
{
    WRAP_Datatype wrap;
#ifdef MPICH
    wrap.i = datatype;
#elif OPEN_MPI
    wrap.p = datatype;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Errhandler OUTPUT_MPI_Errhandler(MPI_Errhandler errhandler)
{
    WRAP_Errhandler wrap;
#ifdef MPICH
    wrap.i = errhandler;
#elif OPEN_MPI
    wrap.p = errhandler;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_File OUTPUT_MPI_File(MPI_File fh)
{
    WRAP_File wrap;
#ifdef MPICH
    // ADIOS is an exception to MPICH handle design
    wrap.p = fh;
#elif OPEN_MPI
    wrap.p = fh;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Group OUTPUT_MPI_Group(MPI_Group group)
{
    WRAP_Group wrap;
#ifdef MPICH
    wrap.i = group;
#elif OPEN_MPI
    wrap.p = group;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Info OUTPUT_MPI_Info(MPI_Info info)
{
    WRAP_Info wrap;
#ifdef MPICH
    wrap.i = info;
#elif OPEN_MPI
    wrap.p = info;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Message OUTPUT_MPI_Message(MPI_Message op)
{
    WRAP_Message wrap;
#ifdef MPICH
    wrap.i = op;
#elif OPEN_MPI
    wrap.p = op;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Op OUTPUT_MPI_Op(MPI_Op op)
{
    WRAP_Op wrap;
#ifdef MPICH
    wrap.i = op;
#elif OPEN_MPI
    wrap.p = op;
#else
#error NO ABI
#endif
     return wrap;
}

static inline WRAP_Request OUTPUT_MPI_Request(MPI_Request request)
{
    WRAP_Request wrap;
#ifdef MPICH
    wrap.i = request;
#elif OPEN_MPI
    wrap.p = request;
#else
#error NO ABI
#endif
     return wrap;
}

#if MPI_VERSION >= 4
static inline WRAP_Session OUTPUT_MPI_Session(MPI_Session session)
{
    WRAP_Session wrap;
#ifdef MPICH
    wrap.i = session;
#elif OPEN_MPI
    wrap.p = session;
#else
#error NO ABI
#endif
     return wrap;
}
#endif

static inline WRAP_Win OUTPUT_MPI_Win(MPI_Win win)
{
    WRAP_Win wrap;
#ifdef MPICH
    wrap.i = win;
#elif OPEN_MPI
    wrap.p = win;
#else
#error NO ABI
#endif
     return wrap;
}

static inline bool IS_IN_PLACE(const void* ptr)
{
    return ((intptr_t)ptr == (intptr_t)MUK_IN_PLACE);
}

static inline bool IS_STATUS_IGNORE(const WRAP_Status * status)
{
    return ((intptr_t)status == (intptr_t)MUK_STATUS_IGNORE);
}

#endif
