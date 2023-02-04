#undef NIMI_SUB
#undef NIMI_DSUB

#if defined(USE_MPI_NAMESPACE)
    #define NIMI_SUB(text)  MPI ## _ ## text
    #define NIMI_DSUB(text) MPI ## _ ## text
#elif defined(USE_MUK_NAMESPACE)
    #if defined(MAKE_EXTERN)
        #define NIMI_SUB(text)  MUK ## _ ## text
        #define NIMI_DSUB(text) extern MUK ## _ ## text
    #else
        #define NIMI_SUB(text)  MUK ## _ ## text
        #define NIMI_DSUB(text) MUK ## _ ## text
    #endif
#else
    #error Namespace substitution problem
#endif

NIMI_DSUB(Request) NIMI_SUB(REQUEST_NULL);

NIMI_DSUB(Errhandler) NIMI_SUB(ERRHANDLER_NULL);

NIMI_DSUB(Info) NIMI_SUB(INFO_NULL);

NIMI_DSUB(Win) NIMI_SUB(WIN_NULL);

NIMI_DSUB(File) NIMI_SUB(FILE_NULL);

NIMI_DSUB(Comm) NIMI_SUB(COMM_NULL);
NIMI_DSUB(Comm) NIMI_SUB(COMM_WORLD);
NIMI_DSUB(Comm) NIMI_SUB(COMM_SELF);

NIMI_DSUB(Group) NIMI_SUB(GROUP_NULL);
NIMI_DSUB(Group) NIMI_SUB(GROUP_EMPTY);

NIMI_DSUB(Message) NIMI_SUB(MESSAGE_NULL);
NIMI_DSUB(Message) NIMI_SUB(MESSAGE_NO_PROC);

NIMI_DSUB(Op) NIMI_SUB(OP_NULL);
NIMI_DSUB(Op) NIMI_SUB(MAX);
NIMI_DSUB(Op) NIMI_SUB(MIN);
NIMI_DSUB(Op) NIMI_SUB(SUM);
NIMI_DSUB(Op) NIMI_SUB(PROD);
NIMI_DSUB(Op) NIMI_SUB(LAND);
NIMI_DSUB(Op) NIMI_SUB(BAND);
NIMI_DSUB(Op) NIMI_SUB(LOR);
NIMI_DSUB(Op) NIMI_SUB(BOR);
NIMI_DSUB(Op) NIMI_SUB(LXOR);
NIMI_DSUB(Op) NIMI_SUB(BXOR);
NIMI_DSUB(Op) NIMI_SUB(MAXLOC);
NIMI_DSUB(Op) NIMI_SUB(MINLOC);
NIMI_DSUB(Op) NIMI_SUB(REPLACE);
NIMI_DSUB(Op) NIMI_SUB(NO_OP);

NIMI_DSUB(Datatype) NIMI_SUB(DATATYPE_NULL);
NIMI_DSUB(Datatype) NIMI_SUB(BYTE);
NIMI_DSUB(Datatype) NIMI_SUB(PACKED);
NIMI_DSUB(Datatype) NIMI_SUB(CHAR);
NIMI_DSUB(Datatype) NIMI_SUB(SHORT);
NIMI_DSUB(Datatype) NIMI_SUB(INT);
NIMI_DSUB(Datatype) NIMI_SUB(LONG);
NIMI_DSUB(Datatype) NIMI_SUB(FLOAT);
NIMI_DSUB(Datatype) NIMI_SUB(DOUBLE);
NIMI_DSUB(Datatype) NIMI_SUB(LONG_DOUBLE);
NIMI_DSUB(Datatype) NIMI_SUB(UNSIGNED_CHAR);
NIMI_DSUB(Datatype) NIMI_SUB(SIGNED_CHAR);
NIMI_DSUB(Datatype) NIMI_SUB(UNSIGNED_SHORT);
NIMI_DSUB(Datatype) NIMI_SUB(UNSIGNED_LONG);
NIMI_DSUB(Datatype) NIMI_SUB(UNSIGNED);
NIMI_DSUB(Datatype) NIMI_SUB(FLOAT_INT);
NIMI_DSUB(Datatype) NIMI_SUB(DOUBLE_INT);
NIMI_DSUB(Datatype) NIMI_SUB(LONG_DOUBLE_INT);
NIMI_DSUB(Datatype) NIMI_SUB(LONG_INT);
NIMI_DSUB(Datatype) NIMI_SUB(SHORT_INT);
NIMI_DSUB(Datatype) NIMI_SUB(2INT);
NIMI_DSUB(Datatype) NIMI_SUB(WCHAR);
NIMI_DSUB(Datatype) NIMI_SUB(LONG_LONG_INT);
NIMI_DSUB(Datatype) NIMI_SUB(LONG_LONG);
NIMI_DSUB(Datatype) NIMI_SUB(UNSIGNED_LONG_LONG);
NIMI_DSUB(Datatype) NIMI_SUB(2COMPLEX);
NIMI_DSUB(Datatype) NIMI_SUB(2DOUBLE_COMPLEX);