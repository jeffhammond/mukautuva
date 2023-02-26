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

#include "impl-scalar-types.h"
#include "wrap-handle-typedefs.h"

#define MUK_EXTERN extern
#include "impl-fpointers.h"
#include "impl-status.h"
#include "impl-constant-conversions.h"
#include "impl-handle-conversions.h"

int WRAP_Type_create_keyval(WRAP_Type_copy_attr_function *type_copy_attr_fn, WRAP_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state)
{
    MPI_Type_copy_attr_function * impl_type_copy_attr_fn = (MPI_Type_copy_attr_function*)type_copy_attr_fn;
    if ((intptr_t)type_copy_attr_fn == (intptr_t)MUK_TYPE_NULL_COPY_FN) {
        impl_type_copy_attr_fn = MPI_TYPE_NULL_COPY_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    MPI_Type_delete_attr_function * impl_type_delete_attr_fn = (MPI_Type_delete_attr_function*)type_delete_attr_fn;
    if ((intptr_t)type_delete_attr_fn == (intptr_t)MUK_TYPE_NULL_DELETE_FN) {
        impl_type_delete_attr_fn = MPI_TYPE_NULL_DELETE_FN;
    } else {
        printf("%s : %d FIXME\n",__func__,__LINE__);
    }
    int rc = IMPL_Type_create_keyval(impl_type_copy_attr_fn, impl_type_delete_attr_fn, type_keyval, extra_state);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free_keyval(int *type_keyval)
{
    int rc = IMPL_Type_free_keyval(type_keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_commit(WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(*datatype);
    int rc = IMPL_Type_commit(&impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_contiguous(int count, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_contiguous(count, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_contiguous_c(WRAP_Count count, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_contiguous_c(count, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_darray(int size, int rank, int ndims, const int array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_darray(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_darray_c(int size, int rank, int ndims, const WRAP_Count array_of_gsizes[], const int array_of_distribs[], const int array_of_dargs[], const int array_of_psizes[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_darray_c(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_complex(int p, int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_complex(p, r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_integer(int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_integer(r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_f90_real(int p, int r, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_f90_real(p, r, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed(int count, const int array_of_blocklengths[], const WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_hindexed_block(int count, int blocklength, const WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_block(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_hindexed_block_c(WRAP_Count count, WRAP_Count blocklength, const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_block_c(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

#if MPI_VERSION >= 4
int WRAP_Type_create_hindexed_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hindexed_c(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_hvector(int count, int blocklength, WRAP_Aint stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hvector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_hvector_c(WRAP_Count count, WRAP_Count blocklength, WRAP_Count stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_hvector_c(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_indexed_block(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_indexed_block_c(WRAP_Count count, WRAP_Count blocklength, const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_indexed_block_c(count, blocklength, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_resized(WRAP_Datatype oldtype, WRAP_Aint lb, WRAP_Aint extent, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_resized(impl_oldtype, lb, extent, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_resized_c(WRAP_Datatype oldtype, WRAP_Count lb, WRAP_Count extent, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_resized_c(impl_oldtype, lb, extent, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_struct(int count, const int array_of_blocklengths[], const WRAP_Aint array_of_displacements[], const WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (int i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_struct(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_create_struct_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], const WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (MPI_Count i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_struct_c(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_create_subarray(int ndims, const int array_of_sizes[], const int array_of_subsizes[], const int array_of_starts[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_create_subarray_c(int ndims, const WRAP_Count array_of_sizes[], const WRAP_Count array_of_subsizes[], const WRAP_Count array_of_starts[], int order, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    int impl_order = MPI_UNDEFINED;
    if (order == MUK_ORDER_C) {
        impl_order = MPI_ORDER_C;
    }
    else if (order == MUK_ORDER_FORTRAN) {
        impl_order = MPI_ORDER_FORTRAN;
    }
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_create_subarray_c(ndims, array_of_sizes, array_of_subsizes, array_of_starts, impl_order, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_delete_attr(WRAP_Datatype datatype, int type_keyval)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_delete_attr(impl_datatype, type_keyval);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_dup(WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_dup(impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_extent(WRAP_Datatype datatype, WRAP_Aint *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_extent(impl_datatype, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_free(WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(*datatype);
    int rc = IMPL_Type_free(&impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_attr(WRAP_Datatype datatype, int type_keyval, void *attribute_val, int *flag)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_attr(impl_datatype, KEY_MUK_TO_IMPL(type_keyval), attribute_val, flag);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_contents(WRAP_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], WRAP_Aint array_of_addresses[], WRAP_Datatype array_of_datatypes[])
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Datatype * impl_array_of_datatypes = malloc(max_datatypes * sizeof(MPI_Datatype));
    int rc = IMPL_Type_get_contents(impl_datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, impl_array_of_datatypes);
    for (int i=0; i<max_datatypes; i++) {
        array_of_datatypes[i] = OUTPUT_MPI_Datatype(impl_array_of_datatypes[i]);
    }
    free(impl_array_of_datatypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_contents_c(WRAP_Datatype datatype, WRAP_Count max_integers, WRAP_Count max_addresses, WRAP_Count max_large_counts, WRAP_Count max_datatypes, int array_of_integers[], WRAP_Aint array_of_addresses[], WRAP_Count array_of_large_counts[], WRAP_Datatype array_of_datatypes[])
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    MPI_Datatype * impl_array_of_datatypes = malloc(max_datatypes * sizeof(MPI_Datatype));
    int rc = IMPL_Type_get_contents_c(impl_datatype, max_integers, max_addresses, max_large_counts, max_datatypes, array_of_integers, array_of_addresses, array_of_large_counts, impl_array_of_datatypes);
    for (int i=0; i<max_datatypes; i++) {
        array_of_datatypes[i] = OUTPUT_MPI_Datatype(impl_array_of_datatypes[i]);
    }
    free(impl_array_of_datatypes);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_envelope(WRAP_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_envelope(impl_datatype, num_integers, num_addresses, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_envelope_c(WRAP_Datatype datatype, WRAP_Count *num_integers, WRAP_Count *num_addresses, WRAP_Count *num_large_counts, WRAP_Count *num_datatypes, int *combiner)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_envelope_c(impl_datatype, num_integers, num_addresses, num_large_counts, num_datatypes, combiner);
    *combiner = COMBINER_CODE_IMPL_TO_MUK(*combiner);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_extent(WRAP_Datatype datatype, WRAP_Aint *lb, WRAP_Aint *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent(impl_datatype, lb, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_extent_c(WRAP_Datatype datatype, WRAP_Count *lb, WRAP_Count *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent_c(impl_datatype, lb, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_extent_x(WRAP_Datatype datatype, WRAP_Count *lb, WRAP_Count *extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_extent_x(impl_datatype, lb, extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_name(WRAP_Datatype datatype, char *type_name, int *resultlen)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    // MUK defines all the possible datatypes, without knowing if the implementation
    // supports them, so we prevent crashes by doing this.
    if (impl_datatype == MPI_DATATYPE_NULL) {
        strcpy(type_name,"MPI_DATATYPE_NULL");
        *resultlen = strlen("MPI_DATATYPE_NULL");
        return MPI_ERR_TYPE;
    }
    int rc = IMPL_Type_get_name(impl_datatype, type_name, resultlen);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_get_true_extent(WRAP_Datatype datatype, WRAP_Aint *true_lb, WRAP_Aint *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent(impl_datatype, true_lb, true_extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_get_true_extent_c(WRAP_Datatype datatype, WRAP_Count *true_lb, WRAP_Count *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent_c(impl_datatype, true_lb, true_extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_get_true_extent_x(WRAP_Datatype datatype, WRAP_Count *true_lb, WRAP_Count *true_extent)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_get_true_extent_x(impl_datatype, true_lb, true_extent);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hindexed(int count, int array_of_blocklengths[], WRAP_Aint array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_hindexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_hvector(int count, int blocklength, WRAP_Aint stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_hvector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_indexed(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_indexed_c(WRAP_Count count, const WRAP_Count array_of_blocklengths[], const WRAP_Count array_of_displacements[], WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_indexed_c(count, array_of_blocklengths, array_of_displacements, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_lb(WRAP_Datatype datatype, WRAP_Aint *displacement)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_lb(impl_datatype, displacement);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_match_size(int typeclass, int size, WRAP_Datatype *datatype)
{
    MPI_Datatype impl_datatype;
    int impl_typeclass;
    if (typeclass == MUK_TYPECLASS_INTEGER) {
        impl_typeclass = MPI_TYPECLASS_INTEGER;
    }
    else if (typeclass == MUK_TYPECLASS_REAL) {
        impl_typeclass = MPI_TYPECLASS_REAL;
    }
    else if (typeclass == MUK_TYPECLASS_COMPLEX) {
        impl_typeclass = MPI_TYPECLASS_COMPLEX;
    }
    else {
        printf("Unknown typeclass: %d\n", typeclass);
        impl_typeclass = MPI_UNDEFINED;
    }
    int rc = IMPL_Type_match_size(impl_typeclass, size, &impl_datatype);
    *datatype = OUTPUT_MPI_Datatype(impl_datatype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_attr(WRAP_Datatype datatype, int type_keyval, void *attribute_val)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_set_attr(impl_datatype, type_keyval, attribute_val);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_set_name(WRAP_Datatype datatype, const char *type_name)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_set_name(impl_datatype, type_name);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_size(WRAP_Datatype datatype, int *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size(impl_datatype, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_size_c(WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size_c(impl_datatype, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif

int WRAP_Type_size_x(WRAP_Datatype datatype, WRAP_Count *size)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_size_x(impl_datatype, size);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_struct(int count, int array_of_blocklengths[], WRAP_Aint array_of_displacements[], WRAP_Datatype array_of_types[], WRAP_Datatype *newtype)
{
    MPI_Datatype * impl_array_of_types = malloc(count * sizeof(MPI_Datatype));
    for (int i=0; i<count; i++) {
        impl_array_of_types[i] = CONVERT_MPI_Datatype(array_of_types[i]);
    }
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_struct(count, array_of_blocklengths, array_of_displacements, impl_array_of_types, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    free(impl_array_of_types);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_ub(WRAP_Datatype datatype, WRAP_Aint *displacement)
{
    MPI_Datatype impl_datatype = CONVERT_MPI_Datatype(datatype);
    int rc = IMPL_Type_ub(impl_datatype, displacement);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

int WRAP_Type_vector(int count, int blocklength, int stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_vector(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}

#if MPI_VERSION >= 4
int WRAP_Type_vector_c(WRAP_Count count, WRAP_Count blocklength, WRAP_Count stride, WRAP_Datatype oldtype, WRAP_Datatype *newtype)
{
    MPI_Datatype impl_oldtype = CONVERT_MPI_Datatype(oldtype);
    MPI_Datatype impl_newtype;
    int rc = IMPL_Type_vector_c(count, blocklength, stride, impl_oldtype, &impl_newtype);
    *newtype = OUTPUT_MPI_Datatype(impl_newtype);
    return RETURN_CODE_IMPL_TO_MUK(rc);
}
#endif
