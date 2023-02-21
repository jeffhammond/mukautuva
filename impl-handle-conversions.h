#ifndef MUK_IMPL_HANDLE_CONVERSIONS_H
#define MUK_IMPL_HANDLE_CONVERSIONS_H

// NULLIFY functions

static inline void WRAP_COMM_NULLIFY(MPI_Comm * comm)
{
}

static inline void WRAP_DATATYPE_NULLIFY(MPI_Datatype * datatype)
{
}

static inline void WRAP_ERRHANDLER_NULLIFY(MPI_Errhandler * errhandler)
{
}

static inline void WRAP_FILE_NULLIFY(MPI_File * file)
{
}

static inline void WRAP_GROUP_NULLIFY(MPI_Group * group)
{
}

static inline void WRAP_INFO_NULLIFY(MPI_Info * info)
{
}

static inline void WRAP_MESSAGE_NULLIFY(MPI_Message * message)
{
}

static inline void WRAP_OP_NULLIFY(MPI_Op * op)
{
}

static inline void WRAP_REQUEST_NULLIFY(MPI_Request * request)
{
    //remove_cookie_pair_from_list(*request);
}

#if MPI_VERSION >= 4
static inline void WRAP_SESSION_NULLIFY(MPI_Session * session)
{
}
#endif

static inline void WRAP_WIN_NULLIFY(MPI_Win * win)
{
}

static inline void WRAP_DATATYPE_IMPL_TO_MUK(MPI_Datatype impl_datatype, MPI_Datatype ** muk_datatype)
{
    if (1) {
    }
    else {
        // The datatypes returned in array_of_datatypes are handles to datatype objects
        // that are equivalent to the datatypes used in the original construction call.
        // If these were derived datatypes, then the returned datatypes are new datatype objects,
        // and the user is responsible for freeing these datatypes with MPI_TYPE_FREE.
        // If these were predefined datatypes, then the returned datatype is equal to that
        // (constant) predefined datatype and cannot be freed.
    }
}

MPI_Comm CONVERT_MPI_Comm(WRAP_Comm comm);
MPI_Datatype CONVERT_MPI_Datatype(WRAP_Datatype datatype);
MPI_Errhandler CONVERT_MPI_Errhandler(WRAP_Errhandler errhandler);
MPI_File CONVERT_MPI_File(WRAP_File fh);
MPI_Group CONVERT_MPI_Group(WRAP_Group group);
MPI_Info CONVERT_MPI_Info(WRAP_Info info);
MPI_Message CONVERT_MPI_Message(WRAP_Message op);
MPI_Op CONVERT_MPI_Op(WRAP_Op op);
MPI_Request CONVERT_MPI_Request(WRAP_Request request);
#if MPI_VERSION >= 4
MPI_Session CONVERT_MPI_Session(WRAP_Session session);
#endif
MPI_Win CONVERT_MPI_Win(WRAP_Win win);

WRAP_Comm OUTPUT_MPI_Comm(MPI_Comm comm);
WRAP_Datatype OUTPUT_MPI_Datatype(MPI_Datatype datatype);
WRAP_Errhandler OUTPUT_MPI_Errhandler(MPI_Errhandler errhandler);
WRAP_File OUTPUT_MPI_File(MPI_File fh);
WRAP_Group OUTPUT_MPI_Group(MPI_Group group);
WRAP_Info OUTPUT_MPI_Info(MPI_Info info);
WRAP_Message OUTPUT_MPI_Message(MPI_Message op);
WRAP_Op OUTPUT_MPI_Op(MPI_Op op);
WRAP_Request OUTPUT_MPI_Request(MPI_Request request);
#if MPI_VERSION >= 4
WRAP_Session OUTPUT_MPI_Session(MPI_Session session);
#endif
WRAP_Win OUTPUT_MPI_Win(MPI_Win win);

bool IS_IN_PLACE(const void* ptr);
bool IS_STATUS_IGNORE(const WRAP_Status * status);

#endif
