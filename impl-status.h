#ifndef IMPL_STATUS_H
#define IMPL_STATUS_H

#include <string.h>

#include "impl-constant-conversions.h"

// status typedef
typedef struct
{
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int __kielletty__[5];
}
WRAP_Status;

// SUPPORT_F08 enables F08 stuff I am ignoring for now

#ifdef SUPPORT_F08
// status typedef
typedef struct
{
    MPI_Fint MPI_SOURCE;
    MPI_Fint MPI_TAG;
    MPI_Fint MPI_ERROR;
    MPI_Fint __kielletty__[5];
}
WRAP_F08_status;
#endif

static inline bool IS_STATUS_IGNORE(const WRAP_Status * status)
{
    return ((intptr_t)status == (intptr_t)MUK_STATUS_IGNORE);
}

static inline bool IS_STATUSES_IGNORE(const WRAP_Status * status)
{
    return ((intptr_t)status == (intptr_t)MUK_STATUSES_IGNORE);
}

static inline void WRAP_Status_empty(const bool ignore, WRAP_Status * w)
{
    if (ignore) return;

    // An empty status is a status which is set to return
    // tag = MPI_ANY_TAG
    // source = MPI_ANY_SOURCE
    // error = MPI_SUCCESS
    // and is also internally configured so that calls to
    // MPI_GET_COUNT, MPI_GET_ELEMENTS, and MPI_GET_ELEMENTS_X
    // return count = 0 and MPI_TEST_CANCELLED returns false.

    w->MPI_SOURCE = MUK_ANY_SOURCE;
    w->MPI_TAG    = MUK_ANY_TAG;
    w->MPI_ERROR  = MUK_SUCCESS;

#if defined(MPICH)
    memset(w->__kielletty__, 0, 2*sizeof(int));
#elif defined(OPEN_MPI)
    memset(w->__kielletty__, 0, 3*sizeof(int));
#else
#error Need MPI_Status ABI support
#endif
}

static inline void WRAP_Status_to_MPI_Status(const WRAP_Status * w, MPI_Status * m)
{
    if (IS_STATUSES_IGNORE(w)) {
        printf("WRAP_Status_to_MPI_Status passed STATUS_IGNORE\n");
        return;
    }
    if (w == NULL || m == NULL) {
        printf("WRAP_Status_to_MPI_Status passed NULL (w=%p m=%p)\n",w,m);
        return;
    }

    memset(m,0,sizeof(MPI_Status));

    //printf("WRAP_Status = { .SOURCE=%d .TAG=%d .ERROR=%d } \n", w->MPI_SOURCE, w->MPI_TAG, w->MPI_ERROR);

    m->MPI_SOURCE = RANK_MUK_TO_IMPL(w->MPI_SOURCE);
    m->MPI_TAG    = TAG_MUK_TO_IMPL(w->MPI_TAG);
    m->MPI_ERROR  = (w->MPI_ERROR) ? ERROR_CODE_MUK_TO_IMPL(w->MPI_ERROR) : 0;

#if defined(MPICH)
    memcpy(&(m->count_lo), w->__kielletty__, 2*sizeof(int));
#elif defined(OPEN_MPI)
    memcpy(&(m->_cancelled), w->__kielletty__, 3*sizeof(int));
#else
#error Need MPI_Status ABI support
#endif
}

static inline void MPI_Status_to_WRAP_Status(const MPI_Status * m, WRAP_Status * w)
{
    if (IS_STATUSES_IGNORE(w)) {
        printf("MPI_Status_to_WRAP_Status passed STATUS_IGNORE\n");
        return;
    }
    if (w == NULL || m == NULL) {
        printf("MPI_Status_to_WRAP_Status passed NULL (m=%p w=%p)\n",m,w);
        return;
    }

    memset(w,0,sizeof(WRAP_Status));

    w->MPI_SOURCE = RANK_IMPL_TO_MUK(m->MPI_SOURCE);
    w->MPI_TAG    = TAG_IMPL_TO_MUK(m->MPI_TAG);
    w->MPI_ERROR  = (m->MPI_ERROR) ? ERROR_CODE_IMPL_TO_MUK(m->MPI_ERROR) : 0;

#if defined(MPICH)
    memcpy(w->__kielletty__, &(m->count_lo), 2*sizeof(int));
#elif defined(OPEN_MPI)
    memcpy(w->__kielletty__, &(m->_cancelled), 3*sizeof(int));
#else
#error Need MPI_Status ABI support
#endif
}

#endif
