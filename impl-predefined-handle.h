// SPDX-License-Identifier: MIT

#ifndef IMPL_PREDEFINED_OP_H
#define IMPL_PREDEFINED_OP_H

#define MAYBE_UNUSED __attribute__((unused))

MAYBE_UNUSED
static bool IS_PREDEFINED_OP(MPI_Op op)
{
    // it is ideal to optimize the branching order here by ordering the tests
    // in order of the frequency that the predefine ops are used in real code.
    return (op == MPI_SUM ||
            op == MPI_MAX ||
            op == MPI_MIN ||
            op == MPI_LAND ||
            op == MPI_LOR ||
            op == MPI_BAND ||
            op == MPI_BOR ||
            op == MPI_LXOR ||
            op == MPI_BXOR ||
            op == MPI_MAXLOC ||
            op == MPI_MINLOC ||
            // no one uses this, so it is last among the valid ones.
            op == MPI_PROD ||
            // these two are invalid for reductions but they are predefined
            // so we will include them and let the implementation throw an
            // error in the reduction.
            op == MPI_REPLACE ||
            op == MPI_NO_OP);
}

MAYBE_UNUSED
static bool IS_PREDEFINED_ERRHANDLER(MPI_Errhandler errhandler)
{
    return ( (errhandler == MPI_ERRORS_ARE_FATAL) ||
             (errhandler == MPI_ERRORS_RETURN) ||
    #if MPI_VERSION >= 4
             (errhandler == MPI_ERRORS_ABORT) ||
    #endif
             (errhandler == MPI_ERRHANDLER_NULL)
           );
}

MAYBE_UNUSED
static bool IS_DERIVED_DATATYPE(MPI_Datatype type)
{
    int ni, na, nd, combiner;
    int rc = IMPL_Type_get_envelope(type, &ni, &na, &nd, &combiner);
    return ((combiner != MPI_COMBINER_NAMED)    && (combiner != MPI_COMBINER_F90_INTEGER) &&
            (combiner != MPI_COMBINER_F90_REAL) && (combiner != MPI_COMBINER_F90_COMPLEX));
    (void)rc;
}

#endif
