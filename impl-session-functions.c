#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <mpi.h>

//#include "muk-dl.h"
#include "muk-predefined.h"

//#include "impl-scalar-types.h"
//#include "impl-status.h"
//#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
//#include "impl-linked-list.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

// WRAP->IMPL functions

#if 0
#if MPI_VERSION >= 4
int WRAP_Session_call_errhandler(WRAP_Session session, int errorcode)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_call_errhandler(impl_session, errorcode);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Session_create_errhandler(WRAP_Session_errhandler_function *session_errhandler_fn, WRAP_Errhandler *errhandler)
{
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Session_create_errhandler(session_errhandler_fn, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif
#endif

int WRAP_Session_finalize(WRAP_Session *session)
{
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_finalize(&impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_errhandler(WRAP_Session session, WRAP_Errhandler *errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler;
    int rc = IMPL_Session_get_errhandler(impl_session, &impl_errhandler);
    *errhandler = OUTPUT_MPI_Errhandler(impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_info(WRAP_Session session, WRAP_Info *info_used)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info_used;
    int rc = IMPL_Session_get_info(impl_session, &impl_info_used);
    *info_used = OUTPUT_MPI_Info(impl_info_used);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_nth_pset(WRAP_Session session, WRAP_Info info, int n, int *pset_len, char *pset_name)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_nth_pset(impl_session, impl_info, n, pset_len, pset_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_num_psets(WRAP_Session session, WRAP_Info info, int *npset_names)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    int rc = IMPL_Session_get_num_psets(impl_session, impl_info, npset_names);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_get_pset_info(WRAP_Session session, const char *pset_name, WRAP_Info *info)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Info impl_info;
    int rc = IMPL_Session_get_pset_info(impl_session, pset_name, &impl_info);
    *info = OUTPUT_MPI_Info(impl_info);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_init(WRAP_Info info, WRAP_Errhandler errhandler, WRAP_Session *session)
{
    MPI_Info impl_info = CONVERT_MPI_Info(info);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    MPI_Session impl_session = CONVERT_MPI_Session(*session);
    int rc = IMPL_Session_init(impl_info, impl_errhandler, &impl_session);
    *session = OUTPUT_MPI_Session(impl_session);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Session_set_errhandler(WRAP_Session session, WRAP_Errhandler errhandler)
{
    MPI_Session impl_session = CONVERT_MPI_Session(session);
    MPI_Errhandler impl_errhandler = CONVERT_MPI_Errhandler(errhandler);
    int rc = IMPL_Session_set_errhandler(impl_session, impl_errhandler);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

