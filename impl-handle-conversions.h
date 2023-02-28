#ifndef MUK_IMPL_HANDLE_CONVERSIONS_H
#define MUK_IMPL_HANDLE_CONVERSIONS_H

//#include "impl-scalar-types.h"
#include "wrap-handle-typedefs.h"

/*
typedef union
{
    void *      p;  // OMPI
    int         i;  // MPICH
    intptr_t    ip;
}
MUK_Handle;
*/

// COMM

static inline MPI_Comm CONVERT_MPI_Comm(WRAP_Comm comm)
{
    if (comm.ip == (intptr_t)MUK_COMM_WORLD) {
        return MPI_COMM_WORLD;
    }
    else if (comm.ip == (intptr_t)MUK_COMM_SELF) {
        return MPI_COMM_SELF;
    }
    else if (comm.ip == (intptr_t)MUK_COMM_NULL) {
        return MPI_COMM_NULL;
    }
    else {
#ifdef MPICH
        return comm.i;
#elif OPEN_MPI
        return comm.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Comm OUTPUT_MPI_Comm(MPI_Comm comm)
{
    WRAP_Comm wrap = {0};
    if (comm == MPI_COMM_NULL) {
        wrap.ip = (intptr_t)MUK_COMM_NULL;
    }
    else if (comm == MPI_COMM_WORLD) {
        wrap.ip = (intptr_t)MUK_COMM_WORLD;
    }
    else if (comm == MPI_COMM_SELF) {
        wrap.ip = (intptr_t)MUK_COMM_SELF;
    }
    else {
#ifdef MPICH
        wrap.i = comm;
#elif OPEN_MPI
        wrap.p = comm;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// DATATYPE

static inline MPI_Datatype CONVERT_MPI_Datatype(WRAP_Datatype datatype)
{
    if (datatype.ip == (intptr_t)MUK_DATATYPE_NULL) {
        return MPI_DATATYPE_NULL;
    }
#ifdef MPI_CHAR
    else if (datatype.ip == (intptr_t)MUK_CHAR) {
        return MPI_CHAR;
    }
#endif
#ifdef MPI_SHORT
    else if (datatype.ip == (intptr_t)MUK_SHORT) {
        return MPI_SHORT;
    }
#endif
#ifdef MPI_INT
    else if (datatype.ip == (intptr_t)MUK_INT) {
        return MPI_INT;
    }
#endif
#ifdef MPI_LONG
    else if (datatype.ip == (intptr_t)MUK_LONG) {
        return MPI_LONG;
    }
#endif
#ifdef MPI_LONG_LONG_INT
    else if (datatype.ip == (intptr_t)MUK_LONG_LONG_INT) {
        return MPI_LONG_LONG_INT;
    }
#endif
#ifdef MPI_LONG_LONG
    else if (datatype.ip == (intptr_t)MUK_LONG_LONG) {
        return MPI_LONG_LONG;
    }
#endif
#ifdef MPI_SIGNED_CHAR
    else if (datatype.ip == (intptr_t)MUK_SIGNED_CHAR) {
        return MPI_SIGNED_CHAR;
    }
#endif
#ifdef MPI_UNSIGNED_CHAR
    else if (datatype.ip == (intptr_t)MUK_UNSIGNED_CHAR) {
        return MPI_UNSIGNED_CHAR;
    }
#endif
#ifdef MPI_UNSIGNED_SHORT
    else if (datatype.ip == (intptr_t)MUK_UNSIGNED_SHORT) {
        return MPI_UNSIGNED_SHORT;
    }
#endif
#ifdef MPI_UNSIGNED
    else if (datatype.ip == (intptr_t)MUK_UNSIGNED) {
        return MPI_UNSIGNED;
    }
#endif
#ifdef MPI_UNSIGNED_LONG
    else if (datatype.ip == (intptr_t)MUK_UNSIGNED_LONG) {
        return MPI_UNSIGNED_LONG;
    }
#endif
#ifdef MPI_UNSIGNED_LONG_LONG
    else if (datatype.ip == (intptr_t)MUK_UNSIGNED_LONG_LONG) {
        return MPI_UNSIGNED_LONG_LONG;
    }
#endif
#ifdef MPI_FLOAT
    else if (datatype.ip == (intptr_t)MUK_FLOAT) {
        return MPI_FLOAT;
    }
#endif
#ifdef MPI_DOUBLE
    else if (datatype.ip == (intptr_t)MUK_DOUBLE) {
        return MPI_DOUBLE;
    }
#endif
#ifdef MPI_LONG_DOUBLE
    else if (datatype.ip == (intptr_t)MUK_LONG_DOUBLE) {
        return MPI_LONG_DOUBLE;
    }
#endif
#ifdef MPI_WCHAR
    else if (datatype.ip == (intptr_t)MUK_WCHAR) {
        return MPI_WCHAR;
    }
#endif
#ifdef MPI_C_BOOL
    else if (datatype.ip == (intptr_t)MUK_C_BOOL) {
        return MPI_C_BOOL;
    }
#endif
#ifdef MPI_INT8_T
    else if (datatype.ip == (intptr_t)MUK_INT8_T) {
        return MPI_INT8_T;
    }
#endif
#ifdef MPI_INT16_T
    else if (datatype.ip == (intptr_t)MUK_INT16_T) {
        return MPI_INT16_T;
    }
#endif
#ifdef MPI_INT32_T
    else if (datatype.ip == (intptr_t)MUK_INT32_T) {
        return MPI_INT32_T;
    }
#endif
#ifdef MPI_INT64_T
    else if (datatype.ip == (intptr_t)MUK_INT64_T) {
        return MPI_INT64_T;
    }
#endif
#ifdef MPI_UINT8_T
    else if (datatype.ip == (intptr_t)MUK_UINT8_T) {
        return MPI_UINT8_T;
    }
#endif
#ifdef MPI_UINT16_T
    else if (datatype.ip == (intptr_t)MUK_UINT16_T) {
        return MPI_UINT16_T;
    }
#endif
#ifdef MPI_UINT32_T
    else if (datatype.ip == (intptr_t)MUK_UINT32_T) {
        return MPI_UINT32_T;
    }
#endif
#ifdef MPI_UINT64_T
    else if (datatype.ip == (intptr_t)MUK_UINT64_T) {
        return MPI_UINT64_T;
    }
#endif
#ifdef MPI_AINT
    else if (datatype.ip == (intptr_t)MUK_AINT) {
        return MPI_AINT;
    }
#endif
#ifdef MPI_COUNT
    else if (datatype.ip == (intptr_t)MUK_COUNT) {
        return MPI_COUNT;
    }
#endif
#ifdef MPI_OFFSET
    else if (datatype.ip == (intptr_t)MUK_OFFSET) {
        return MPI_OFFSET;
    }
#endif
#ifdef MPI_C_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_C_COMPLEX) {
        return MPI_C_COMPLEX;
    }
#endif
#ifdef MPI_C_FLOAT_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_C_FLOAT_COMPLEX) {
        return MPI_C_FLOAT_COMPLEX;
    }
#endif
#ifdef MPI_C_DOUBLE_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_C_DOUBLE_COMPLEX) {
        return MPI_C_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_C_LONG_DOUBLE_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_C_LONG_DOUBLE_COMPLEX) {
        return MPI_C_LONG_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_BYTE
    else if (datatype.ip == (intptr_t)MUK_BYTE) {
        return MPI_BYTE;
    }
#endif
#ifdef MPI_PACKED
    else if (datatype.ip == (intptr_t)MUK_PACKED) {
        return MPI_PACKED;
    }
#endif
#ifdef MPI_CXX_BOOL
    else if (datatype.ip == (intptr_t)MUK_CXX_BOOL) {
        return MPI_CXX_BOOL;
    }
#endif
#ifdef MPI_CXX_FLOAT_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_CXX_FLOAT_COMPLEX) {
        return MPI_CXX_FLOAT_COMPLEX;
    }
#endif
#ifdef MPI_CXX_DOUBLE_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_CXX_DOUBLE_COMPLEX) {
        return MPI_CXX_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_CXX_LONG_DOUBLE_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_CXX_LONG_DOUBLE_COMPLEX) {
        return MPI_CXX_LONG_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_INTEGER
    else if (datatype.ip == (intptr_t)MUK_INTEGER) {
        return MPI_INTEGER;
    }
#endif
#ifdef MPI_REAL
    else if (datatype.ip == (intptr_t)MUK_REAL) {
        return MPI_REAL;
    }
#endif
#ifdef MPI_DOUBLE_PRECISION
    else if (datatype.ip == (intptr_t)MUK_DOUBLE_PRECISION) {
        return MPI_DOUBLE_PRECISION;
    }
#endif
#ifdef MPI_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_COMPLEX) {
        return MPI_COMPLEX;
    }
#endif
#ifdef MPI_LOGICAL
    else if (datatype.ip == (intptr_t)MUK_LOGICAL) {
        return MPI_LOGICAL;
    }
#endif
#ifdef MPI_CHARACTER
    else if (datatype.ip == (intptr_t)MUK_CHARACTER) {
        return MPI_CHARACTER;
    }
#endif
#ifdef MPI_DOUBLE_COMPLEX
    else if (datatype.ip == (intptr_t)MUK_DOUBLE_COMPLEX) {
        return MPI_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_INTEGER1
    else if (datatype.ip == (intptr_t)MUK_INTEGER1) {
        return MPI_INTEGER1;
    }
#endif
#ifdef MPI_INTEGER2
    else if (datatype.ip == (intptr_t)MUK_INTEGER2) {
        return MPI_INTEGER2;
    }
#endif
#ifdef MPI_INTEGER4
    else if (datatype.ip == (intptr_t)MUK_INTEGER4) {
        return MPI_INTEGER4;
    }
#endif
#ifdef MPI_INTEGER8
    else if (datatype.ip == (intptr_t)MUK_INTEGER8) {
        return MPI_INTEGER8;
    }
#endif
#ifdef MPI_INTEGER16
    else if (datatype.ip == (intptr_t)MUK_INTEGER16) {
        return MPI_INTEGER16;
    }
#endif
#ifdef MPI_REAL2
    else if (datatype.ip == (intptr_t)MUK_REAL2) {
        return MPI_REAL2;
    }
#endif
#ifdef MPI_REAL4
    else if (datatype.ip == (intptr_t)MUK_REAL4) {
        return MPI_REAL4;
    }
#endif
#ifdef MPI_REAL8
    else if (datatype.ip == (intptr_t)MUK_REAL8) {
        return MPI_REAL8;
    }
#endif
#ifdef MPI_REAL16
    else if (datatype.ip == (intptr_t)MUK_REAL16) {
        return MPI_REAL16;
    }
#endif
#ifdef MPI_COMPLEX4
    else if (datatype.ip == (intptr_t)MUK_COMPLEX4) {
        return MPI_COMPLEX4;
    }
#endif
#ifdef MPI_COMPLEX8
    else if (datatype.ip == (intptr_t)MUK_COMPLEX8) {
        return MPI_COMPLEX8;
    }
#endif
#ifdef MPI_COMPLEX16
    else if (datatype.ip == (intptr_t)MUK_COMPLEX16) {
        return MPI_COMPLEX16;
    }
#endif
#ifdef MPI_COMPLEX32
    else if (datatype.ip == (intptr_t)MUK_COMPLEX32) {
        return MPI_COMPLEX32;
    }
#endif
#ifdef MPI_FLOAT_INT
    else if (datatype.ip == (intptr_t)MUK_FLOAT_INT) {
        return MPI_FLOAT_INT;
    }
#endif
#ifdef MPI_DOUBLE_INT
    else if (datatype.ip == (intptr_t)MUK_DOUBLE_INT) {
        return MPI_DOUBLE_INT;
    }
#endif
#ifdef MPI_LONG_INT
    else if (datatype.ip == (intptr_t)MUK_LONG_INT) {
        return MPI_LONG_INT;
    }
#endif
#ifdef MPI_2INT
    else if (datatype.ip == (intptr_t)MUK_2INT) {
        return MPI_2INT;
    }
#endif
#ifdef MPI_SHORT_INT
    else if (datatype.ip == (intptr_t)MUK_SHORT_INT) {
        return MPI_SHORT_INT;
    }
#endif
#ifdef MPI_LONG_DOUBLE_INT
    else if (datatype.ip == (intptr_t)MUK_LONG_DOUBLE_INT) {
        return MPI_LONG_DOUBLE_INT;
    }
#endif
#ifdef MPI_2REAL
    else if (datatype.ip == (intptr_t)MUK_2REAL) {
        return MPI_2REAL;
    }
#endif
#ifdef MPI_2DOUBLE_PRECISION
    else if (datatype.ip == (intptr_t)MUK_2DOUBLE_PRECISION) {
        return MPI_2DOUBLE_PRECISION;
    }
#endif
#ifdef MPI_2INTEGER
    else if (datatype.ip == (intptr_t)MUK_2INTEGER) {
        return MPI_2INTEGER;
    }
#endif
// Open-MPI defines these such that they do not work
#if defined(MPI_LB) && !defined(OPEN_MPI)
    else if (datatype.ip == (intptr_t)MUK_LB) {
        return MPI_LB;
    }
#endif
#if defined(MPI_UB) && !defined(OPEN_MPI)
    else if (datatype.ip == (intptr_t)MUK_UB) {
        return MPI_UB;
    }
#endif
    else {
#ifdef MPICH
        return datatype.i;
#elif OPEN_MPI
        return datatype.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Datatype OUTPUT_MPI_Datatype(MPI_Datatype datatype)
{
    WRAP_Datatype wrap = {0};
    if (datatype == MPI_DATATYPE_NULL) {
        wrap.ip = (intptr_t)MUK_DATATYPE_NULL;
    }
#ifdef MPI_CHAR
    else if (datatype == MPI_CHAR) {
        wrap.ip = (intptr_t)MUK_CHAR;
    }
#endif
#ifdef MPI_SHORT
    else if (datatype == MPI_SHORT) {
        wrap.ip = (intptr_t)MUK_SHORT;
    }
#endif
#ifdef MPI_INT
    else if (datatype == MPI_INT) {
        wrap.ip = (intptr_t)MUK_INT;
    }
#endif
#ifdef MPI_LONG
    else if (datatype == MPI_LONG) {
        wrap.ip = (intptr_t)MUK_LONG;
    }
#endif
#ifdef MPI_LONG_LONG_INT
    else if (datatype == MPI_LONG_LONG_INT) {
        wrap.ip = (intptr_t)MUK_LONG_LONG_INT;
    }
#endif
#ifdef MPI_LONG_LONG
    else if (datatype == MPI_LONG_LONG) {
        wrap.ip = (intptr_t)MUK_LONG_LONG;
    }
#endif
#ifdef MPI_SIGNED_CHAR
    else if (datatype == MPI_SIGNED_CHAR) {
        wrap.ip = (intptr_t)MUK_SIGNED_CHAR;
    }
#endif
#ifdef MPI_UNSIGNED_CHAR
    else if (datatype == MPI_UNSIGNED_CHAR) {
        wrap.ip = (intptr_t)MUK_UNSIGNED_CHAR;
    }
#endif
#ifdef MPI_UNSIGNED_SHORT
    else if (datatype == MPI_UNSIGNED_SHORT) {
        wrap.ip = (intptr_t)MUK_UNSIGNED_SHORT;
    }
#endif
#ifdef MPI_UNSIGNED
    else if (datatype == MPI_UNSIGNED) {
        wrap.ip = (intptr_t)MUK_UNSIGNED;
    }
#endif
#ifdef MPI_UNSIGNED_LONG
    else if (datatype == MPI_UNSIGNED_LONG) {
        wrap.ip = (intptr_t)MUK_UNSIGNED_LONG;
    }
#endif
#ifdef MPI_UNSIGNED_LONG_LONG
    else if (datatype == MPI_UNSIGNED_LONG_LONG) {
        wrap.ip = (intptr_t)MUK_UNSIGNED_LONG_LONG;
    }
#endif
#ifdef MPI_FLOAT
    else if (datatype == MPI_FLOAT) {
        wrap.ip = (intptr_t)MUK_FLOAT;
    }
#endif
#ifdef MPI_DOUBLE
    else if (datatype == MPI_DOUBLE) {
        wrap.ip = (intptr_t)MUK_DOUBLE;
    }
#endif
#ifdef MPI_LONG_DOUBLE
    else if (datatype == MPI_LONG_DOUBLE) {
        wrap.ip = (intptr_t)MUK_LONG_DOUBLE;
    }
#endif
#ifdef MPI_WCHAR
    else if (datatype == MPI_WCHAR) {
        wrap.ip = (intptr_t)MUK_WCHAR;
    }
#endif
#ifdef MPI_C_BOOL
    else if (datatype == MPI_C_BOOL) {
        wrap.ip = (intptr_t)MUK_C_BOOL;
    }
#endif
#ifdef MPI_INT8_T
    else if (datatype == MPI_INT8_T) {
        wrap.ip = (intptr_t)MUK_INT8_T;
    }
#endif
#ifdef MPI_INT16_T
    else if (datatype == MPI_INT16_T) {
        wrap.ip = (intptr_t)MUK_INT16_T;
    }
#endif
#ifdef MPI_INT32_T
    else if (datatype == MPI_INT32_T) {
        wrap.ip = (intptr_t)MUK_INT32_T;
    }
#endif
#ifdef MPI_INT64_T
    else if (datatype == MPI_INT64_T) {
        wrap.ip = (intptr_t)MUK_INT64_T;
    }
#endif
#ifdef MPI_UINT8_T
    else if (datatype == MPI_UINT8_T) {
        wrap.ip = (intptr_t)MUK_UINT8_T;
    }
#endif
#ifdef MPI_UINT16_T
    else if (datatype == MPI_UINT16_T) {
        wrap.ip = (intptr_t)MUK_UINT16_T;
    }
#endif
#ifdef MPI_UINT32_T
    else if (datatype == MPI_UINT32_T) {
        wrap.ip = (intptr_t)MUK_UINT32_T;
    }
#endif
#ifdef MPI_UINT64_T
    else if (datatype == MPI_UINT64_T) {
        wrap.ip = (intptr_t)MUK_UINT64_T;
    }
#endif
#ifdef MPI_AINT
    else if (datatype == MPI_AINT) {
        wrap.ip = (intptr_t)MUK_AINT;
    }
#endif
#ifdef MPI_COUNT
    else if (datatype == MPI_COUNT) {
        wrap.ip = (intptr_t)MUK_COUNT;
    }
#endif
#ifdef MPI_OFFSET
    else if (datatype == MPI_OFFSET) {
        wrap.ip = (intptr_t)MUK_OFFSET;
    }
#endif
#ifdef MPI_C_COMPLEX
    else if (datatype == MPI_C_COMPLEX) {
        wrap.ip = (intptr_t)MUK_C_COMPLEX;
    }
#endif
#ifdef MPI_C_FLOAT_COMPLEX
    else if (datatype == MPI_C_FLOAT_COMPLEX) {
        wrap.ip = (intptr_t)MUK_C_FLOAT_COMPLEX;
    }
#endif
#ifdef MPI_C_DOUBLE_COMPLEX
    else if (datatype == MPI_C_DOUBLE_COMPLEX) {
        wrap.ip = (intptr_t)MUK_C_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_C_LONG_DOUBLE_COMPLEX
    else if (datatype == MPI_C_LONG_DOUBLE_COMPLEX) {
        wrap.ip = (intptr_t)MUK_C_LONG_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_BYTE
    else if (datatype == MPI_BYTE) {
        wrap.ip = (intptr_t)MUK_BYTE;
    }
#endif
#ifdef MPI_PACKED
    else if (datatype == MPI_PACKED) {
        wrap.ip = (intptr_t)MUK_PACKED;
    }
#endif
#ifdef MPI_CXX_BOOL
    else if (datatype == MPI_CXX_BOOL) {
        wrap.ip = (intptr_t)MUK_CXX_BOOL;
    }
#endif
#ifdef MPI_CXX_FLOAT_COMPLEX
    else if (datatype == MPI_CXX_FLOAT_COMPLEX) {
        wrap.ip = (intptr_t)MUK_CXX_FLOAT_COMPLEX;
    }
#endif
#ifdef MPI_CXX_DOUBLE_COMPLEX
    else if (datatype == MPI_CXX_DOUBLE_COMPLEX) {
        wrap.ip = (intptr_t)MUK_CXX_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_CXX_LONG_DOUBLE_COMPLEX
    else if (datatype == MPI_CXX_LONG_DOUBLE_COMPLEX) {
        wrap.ip = (intptr_t)MUK_CXX_LONG_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_INTEGER
    else if (datatype == MPI_INTEGER) {
        wrap.ip = (intptr_t)MUK_INTEGER;
    }
#endif
#ifdef MPI_REAL
    else if (datatype == MPI_REAL) {
        wrap.ip = (intptr_t)MUK_REAL;
    }
#endif
#ifdef MPI_DOUBLE_PRECISION
    else if (datatype == MPI_DOUBLE_PRECISION) {
        wrap.ip = (intptr_t)MUK_DOUBLE_PRECISION;
    }
#endif
#ifdef MPI_COMPLEX
    else if (datatype == MPI_COMPLEX) {
        wrap.ip = (intptr_t)MUK_COMPLEX;
    }
#endif
#ifdef MPI_LOGICAL
    else if (datatype == MPI_LOGICAL) {
        wrap.ip = (intptr_t)MUK_LOGICAL;
    }
#endif
#ifdef MPI_CHARACTER
    else if (datatype == MPI_CHARACTER) {
        wrap.ip = (intptr_t)MUK_CHARACTER;
    }
#endif
#ifdef MPI_DOUBLE_COMPLEX
    else if (datatype == MPI_DOUBLE_COMPLEX) {
        wrap.ip = (intptr_t)MUK_DOUBLE_COMPLEX;
    }
#endif
#ifdef MPI_INTEGER1
    else if (datatype == MPI_INTEGER1) {
        wrap.ip = (intptr_t)MUK_INTEGER1;
    }
#endif
#ifdef MPI_INTEGER2
    else if (datatype == MPI_INTEGER2) {
        wrap.ip = (intptr_t)MUK_INTEGER2;
    }
#endif
#ifdef MPI_INTEGER4
    else if (datatype == MPI_INTEGER4) {
        wrap.ip = (intptr_t)MUK_INTEGER4;
    }
#endif
#ifdef MPI_INTEGER8
    else if (datatype == MPI_INTEGER8) {
        wrap.ip = (intptr_t)MUK_INTEGER8;
    }
#endif
#ifdef MPI_INTEGER16
    else if (datatype == MPI_INTEGER16) {
        wrap.ip = (intptr_t)MUK_INTEGER16;
    }
#endif
#ifdef MPI_REAL2
    else if (datatype == MPI_REAL2) {
        wrap.ip = (intptr_t)MUK_REAL2;
    }
#endif
#ifdef MPI_REAL4
    else if (datatype == MPI_REAL4) {
        wrap.ip = (intptr_t)MUK_REAL4;
    }
#endif
#ifdef MPI_REAL8
    else if (datatype == MPI_REAL8) {
        wrap.ip = (intptr_t)MUK_REAL8;
    }
#endif
#ifdef MPI_REAL16
    else if (datatype == MPI_REAL16) {
        wrap.ip = (intptr_t)MUK_REAL16;
    }
#endif
#ifdef MPI_COMPLEX4
    else if (datatype == MPI_COMPLEX4) {
        wrap.ip = (intptr_t)MUK_COMPLEX4;
    }
#endif
#ifdef MPI_COMPLEX8
    else if (datatype == MPI_COMPLEX8) {
        wrap.ip = (intptr_t)MUK_COMPLEX8;
    }
#endif
#ifdef MPI_COMPLEX16
    else if (datatype == MPI_COMPLEX16) {
        wrap.ip = (intptr_t)MUK_COMPLEX16;
    }
#endif
#ifdef MPI_COMPLEX32
    else if (datatype == MPI_COMPLEX32) {
        wrap.ip = (intptr_t)MUK_COMPLEX32;
    }
#endif
#ifdef MPI_FLOAT_INT
    else if (datatype == MPI_FLOAT_INT) {
        wrap.ip = (intptr_t)MUK_FLOAT_INT;
    }
#endif
#ifdef MPI_DOUBLE_INT
    else if (datatype == MPI_DOUBLE_INT) {
        wrap.ip = (intptr_t)MUK_DOUBLE_INT;
    }
#endif
#ifdef MPI_LONG_INT
    else if (datatype == MPI_LONG_INT) {
        wrap.ip = (intptr_t)MUK_LONG_INT;
    }
#endif
#ifdef MPI_2INT
    else if (datatype == MPI_2INT) {
        wrap.ip = (intptr_t)MUK_2INT;
    }
#endif
#ifdef MPI_SHORT_INT
    else if (datatype == MPI_SHORT_INT) {
        wrap.ip = (intptr_t)MUK_SHORT_INT;
    }
#endif
#ifdef MPI_LONG_DOUBLE_INT
    else if (datatype == MPI_LONG_DOUBLE_INT) {
        wrap.ip = (intptr_t)MUK_LONG_DOUBLE_INT;
    }
#endif
#ifdef MPI_2REAL
    else if (datatype == MPI_2REAL) {
        wrap.ip = (intptr_t)MUK_2REAL;
    }
#endif
#ifdef MPI_2DOUBLE_PRECISION
    else if (datatype == MPI_2DOUBLE_PRECISION) {
        wrap.ip = (intptr_t)MUK_2DOUBLE_PRECISION;
    }
#endif
#ifdef MPI_2INTEGER
    else if (datatype == MPI_2INTEGER) {
        wrap.ip = (intptr_t)MUK_2INTEGER;
    }
#endif
#if defined(MPI_LB) && !defined(OPEN_MPI)
    else if (datatype == MPI_LB) {
        wrap.ip = (intptr_t)MUK_LB;
    }
#endif
#if defined(MPI_UB) && !defined(OPEN_MPI)
    else if (datatype == MPI_UB) {
        wrap.ip = (intptr_t)MUK_UB;
    }
#endif
    else {
#ifdef MPICH
        wrap.i = datatype;
#elif OPEN_MPI
        wrap.p = datatype;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// ERRHANDLER

static inline MPI_Errhandler CONVERT_MPI_Errhandler(WRAP_Errhandler errhandler)
{
    if (errhandler.ip == (intptr_t)MUK_ERRHANDLER_NULL) {
        return MPI_ERRHANDLER_NULL;
    }
    else if (errhandler.ip == (intptr_t)MUK_ERRORS_ARE_FATAL) {
        return MPI_ERRORS_ARE_FATAL;
    }
    else if (errhandler.ip == (intptr_t)MUK_ERRORS_RETURN) {
        return MPI_ERRORS_RETURN;
    }
#if MPI_VERSION >= 4
    else if (errhandler.ip == (intptr_t)MUK_ERRORS_ABORT) {
        return MPI_ERRORS_ABORT;
    }
#endif
    else {
#ifdef MPICH
        return errhandler.i;
#elif OPEN_MPI
        return errhandler.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Errhandler OUTPUT_MPI_Errhandler(MPI_Errhandler errhandler)
{
    WRAP_Errhandler wrap = {0};
    if (errhandler == MPI_ERRHANDLER_NULL) {
        wrap.ip = (intptr_t)MUK_ERRHANDLER_NULL;
    }
    else if (errhandler == MPI_ERRORS_ARE_FATAL) {
        wrap.ip = (intptr_t)MUK_ERRORS_ARE_FATAL;
    }
    else if (errhandler == MPI_ERRORS_RETURN) {
        wrap.ip = (intptr_t)MUK_ERRORS_RETURN;
    }
#if MPI_VERSION >= 4
    else if (errhandler == MPI_ERRORS_ABORT) {
        wrap.ip = (intptr_t)MUK_ERRORS_ABORT;
    }
#endif
    else {
#ifdef MPICH
        wrap.i = errhandler;
#elif OPEN_MPI
        wrap.p = errhandler;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// FILE

static inline MPI_File CONVERT_MPI_File(WRAP_File file)
{
    if (file.ip == (intptr_t)MUK_FILE_NULL) {
        return MPI_FILE_NULL;
    }
    else {
#ifdef MPICH
        // ADIOS is an exception to MPICH handle design
        return file.p;
#elif OPEN_MPI
        return file.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_File OUTPUT_MPI_File(MPI_File file)
{
    WRAP_File wrap = {0};
    if (file == MPI_FILE_NULL) {
        wrap.ip = (intptr_t)MUK_FILE_NULL;
    }
    else {
#ifdef MPICH
        // ADIOS is an exception to MPICH handle design
        wrap.p = file;
#elif OPEN_MPI
        wrap.p = file;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// GROUP

static inline MPI_Group CONVERT_MPI_Group(WRAP_Group group)
{
    if (group.ip == (intptr_t)MUK_GROUP_NULL) {
        return MPI_GROUP_NULL;
    }
    else if (group.ip == (intptr_t)MUK_GROUP_EMPTY) {
        return MPI_GROUP_EMPTY;
    }
    else {
#ifdef MPICH
        return group.i;
#elif OPEN_MPI
        return group.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Group OUTPUT_MPI_Group(MPI_Group group)
{
    WRAP_Group wrap = {0};
    if (group == MPI_GROUP_NULL) {
        wrap.ip = (intptr_t)MUK_GROUP_NULL;
    }
    else if (group == MPI_GROUP_EMPTY) {
        wrap.ip = (intptr_t)MUK_GROUP_EMPTY;
    }
    else {
#ifdef MPICH
        wrap.i = group;
#elif OPEN_MPI
        wrap.p = group;
#else
#error NO ABI
#endif
    }
    return wrap;
}

//

static inline MPI_Info CONVERT_MPI_Info(WRAP_Info info)
{
    if (info.ip == (intptr_t)MUK_INFO_NULL) {
        return MPI_INFO_NULL;
    }
    else if (info.ip == (intptr_t)MUK_INFO_ENV) {
        return MPI_INFO_ENV;
    }
    else {
#ifdef MPICH
        return info.i;
#elif OPEN_MPI
        return info.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Info OUTPUT_MPI_Info(MPI_Info info)
{
    WRAP_Info wrap = {0};
    if (info == MPI_INFO_NULL) {
        wrap.ip = (intptr_t)MUK_INFO_NULL;
    }
    else if (info == MPI_INFO_ENV) {
        wrap.ip = (intptr_t)MUK_INFO_ENV;
    }
    else {
#ifdef MPICH
        wrap.i = info;
#elif OPEN_MPI
        wrap.p = info;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// MESSAGE

static inline MPI_Message CONVERT_MPI_Message(WRAP_Message message)
{
    if (message.ip == (intptr_t)MUK_MESSAGE_NULL) {
        return MPI_MESSAGE_NULL;
    }
    else if (message.ip == (intptr_t)MUK_MESSAGE_NO_PROC) {
        return MPI_MESSAGE_NO_PROC;
    }
    else {
#ifdef MPICH
        return message.i;
#elif OPEN_MPI
        return message.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Message OUTPUT_MPI_Message(MPI_Message message)
{
    WRAP_Message wrap = {0};
    if (message == MPI_MESSAGE_NULL) {
        wrap.ip = (intptr_t)MUK_MESSAGE_NULL;
    }
    else if (message == MPI_MESSAGE_NO_PROC) {
        wrap.ip = (intptr_t)MUK_MESSAGE_NO_PROC;
    }
    else {
#ifdef MPICH
        wrap.i = message;
#elif OPEN_MPI
        wrap.p = message;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// OP

static inline MPI_Op CONVERT_MPI_Op(WRAP_Op op)
{
    if (op.ip == (intptr_t)MUK_SUM) {
        return MPI_SUM;
    }
    else if (op.ip == (intptr_t)MUK_NO_OP) {
        return MPI_NO_OP;
    }
    else if (op.ip == (intptr_t)MUK_REPLACE) {
        return MPI_REPLACE;
    }
    else if (op.ip == (intptr_t)MUK_MAX) {
        return MPI_MAX;
    }
    else if (op.ip == (intptr_t)MUK_MIN) {
        return MPI_MIN;
    }
    else if (op.ip == (intptr_t)MUK_LAND) {
        return MPI_LAND;
    }
    else if (op.ip == (intptr_t)MUK_BAND) {
        return MPI_BAND;
    }
    else if (op.ip == (intptr_t)MUK_LOR) {
        return MPI_LOR;
    }
    else if (op.ip == (intptr_t)MUK_BOR) {
        return MPI_BOR;
    }
    else if (op.ip == (intptr_t)MUK_LXOR) {
        return MPI_LXOR;
    }
    else if (op.ip == (intptr_t)MUK_BXOR) {
        return MPI_BXOR;
    }
    else if (op.ip == (intptr_t)MUK_MAXLOC) {
        return MPI_MAXLOC;
    }
    else if (op.ip == (intptr_t)MUK_MINLOC) {
        return MPI_MINLOC;
    }
    else if (op.ip == (intptr_t)MUK_OP_NULL) {
        return MPI_OP_NULL;
    }
    else if (op.ip == (intptr_t)MUK_PROD) {
        return MPI_PROD;
    }
    else {
#ifdef MPICH
        return op.i;
#elif OPEN_MPI
        return op.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Op OUTPUT_MPI_Op(MPI_Op op)
{
    // I do not know any scenario where backwards conversion
    // of built-ins will be required, but implement this
    // anyways just to be safe, because adding extra branches
    // in Op_create does not matter.
    WRAP_Op wrap = {0};
    if (op == MPI_SUM) {
        wrap.ip = (intptr_t)MUK_SUM;
    }
    else if (op == MPI_NO_OP) {
        wrap.ip = (intptr_t)MUK_NO_OP;
    }
    else if (op == MPI_REPLACE) {
        wrap.ip = (intptr_t)MUK_REPLACE;
    }
    else if (op == MPI_MAX) {
        wrap.ip = (intptr_t)MUK_MAX;
    }
    else if (op == MPI_MIN) {
        wrap.ip = (intptr_t)MUK_MIN;
    }
    else if (op == MPI_LAND) {
        wrap.ip = (intptr_t)MUK_LAND;
    }
    else if (op == MPI_BAND) {
        wrap.ip = (intptr_t)MUK_BAND;
    }
    else if (op == MPI_LOR) {
        wrap.ip = (intptr_t)MUK_LOR;
    }
    else if (op == MPI_BOR) {
        wrap.ip = (intptr_t)MUK_BOR;
    }
    else if (op == MPI_LXOR) {
        wrap.ip = (intptr_t)MUK_LXOR;
    }
    else if (op == MPI_BXOR) {
        wrap.ip = (intptr_t)MUK_BXOR;
    }
    else if (op == MPI_MAXLOC) {
        wrap.ip = (intptr_t)MUK_MAXLOC;
    }
    else if (op == MPI_MINLOC) {
        wrap.ip = (intptr_t)MUK_MINLOC;
    }
    else if (op == MPI_OP_NULL) {
        wrap.ip = (intptr_t)MUK_OP_NULL;
    }
    else if (op == MPI_PROD) {
        wrap.ip = (intptr_t)MUK_PROD;
    }
    else {
#ifdef MPICH
        wrap.i = op;
#elif OPEN_MPI
        wrap.p = op;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// REQUEST

static inline MPI_Request CONVERT_MPI_Request(WRAP_Request request)
{
    if (request.ip == (intptr_t)MUK_REQUEST_NULL) {
        return MPI_REQUEST_NULL;
    }
    else {
#ifdef MPICH
        return request.i;
#elif OPEN_MPI
        return request.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Request OUTPUT_MPI_Request(MPI_Request request)
{
    WRAP_Request wrap = {0};
    if (request == MPI_REQUEST_NULL) {
        wrap.ip = (intptr_t)MUK_REQUEST_NULL;
    }
    else {
#ifdef MPICH
        wrap.i = request;
#elif OPEN_MPI
        wrap.p = request;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// SESSION

#if MPI_VERSION >= 4
static inline MPI_Session CONVERT_MPI_Session(WRAP_Session session)
{
    if (session.ip == (intptr_t)MUK_SESSION_NULL) {
        return MPI_SESSION_NULL;
    }
    else {
#ifdef MPICH
        return session.i;
#elif OPEN_MPI
        return session.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Session OUTPUT_MPI_Session(MPI_Session session)
{
    WRAP_Session wrap = {0};
    if (session == MPI_SESSION_NULL) {
        wrap.ip = (intptr_t)MUK_SESSION_NULL;
    }
    else {
#ifdef MPICH
        wrap.i = session;
#elif OPEN_MPI
        wrap.p = session;
#else
#error NO ABI
#endif
    }
    return wrap;
}
#endif

// WIN

static inline MPI_Win CONVERT_MPI_Win(WRAP_Win win)
{
    if (win.ip == (intptr_t)MUK_WIN_NULL) {
        return MPI_WIN_NULL;
    }
    else {
#ifdef MPICH
        return win.i;
#elif OPEN_MPI
        return win.p;
#else
#error NO ABI
#endif
    }
}

static inline WRAP_Win OUTPUT_MPI_Win(MPI_Win win)
{
    WRAP_Win wrap = {0};
    if (win == MPI_WIN_NULL) {
        wrap.ip = (intptr_t)MUK_WIN_NULL;
    }
    else {
#ifdef MPICH
        wrap.i = win;
#elif OPEN_MPI
        wrap.p = win;
#else
#error NO ABI
#endif
    }
    return wrap;
}

// OTHER

static inline bool IS_IN_PLACE(const void* ptr)
{
    return ((intptr_t)ptr == (intptr_t)MUK_IN_PLACE);
}

#endif
