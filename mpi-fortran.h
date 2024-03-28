// SPDX-License-Identifier: MIT

#ifndef MUK_MPI_FORTRAN_H
#define MUK_MPI_FORTRAN_H

#include <stdio.h>
#include <stdlib.h>

int MPI_Status_c2f(const MPI_Status * c_status, MPI_F08_Status * f_status) {
    printf("MPI_Status_c2f is unimplemented\n");
    abort();
    return -1;
    (void)c_status;
    (void)f_status;
}

int MPI_Status_f2c(const MPI_F08_Status * f_status, MPI_Status * c_status) {
    printf("MPI_Status_f2c is unimplemented\n");
    abort();
    return -1;
    (void)c_status;
    (void)f_status;
}

int MPI_Comm_c2f(MPI_Comm arg) {
    printf("MPI_Comm_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Comm MPI_Comm_f2c(int arg) {
    printf("MPI_Comm_f2c is unimplemented\n");
    abort();
    return MPI_COMM_NULL;
    (void)arg;
}

int MPI_Errhandler_c2f(MPI_Errhandler arg) {
    printf("MPI_Errhandler_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Errhandler MPI_Errhandler_f2c(int arg) {
    printf("MPI_Errhandler_f2c is unimplemented\n");
    abort();
    return MPI_ERRHANDLER_NULL;
    (void)arg;
}

int MPI_Type_c2f(MPI_Datatype arg) {
    printf("MPI_Type_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Datatype MPI_Type_f2c(int arg) {
    printf("MPI_Type_f2c is unimplemented\n");
    abort();
    return MPI_DATATYPE_NULL;
    (void)arg;
}

int MPI_File_c2f(MPI_File arg) {
    printf("MPI_File_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_File MPI_File_f2c(int arg) {
    printf("MPI_File_f2c is unimplemented\n");
    abort();
    return MPI_FILE_NULL;
    (void)arg;
}

int MPI_Group_c2f(MPI_Group arg) {
    printf("MPI_Group_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Group MPI_Group_f2c(int arg) {
    printf("MPI_Group_f2c is unimplemented\n");
    abort();
    return MPI_GROUP_NULL;
    (void)arg;
}

int MPI_Info_c2f(MPI_Info arg) {
    printf("MPI_Info_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Info MPI_Info_f2c(int arg) {
    printf("MPI_Info_f2c is unimplemented\n");
    abort();
    return MPI_INFO_NULL;
    (void)arg;
}

int MPI_Message_c2f(MPI_Message arg) {
    printf("MPI_Message_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Message MPI_Message_f2c(int arg) {
    printf("MPI_Message_f2c is unimplemented\n");
    abort();
    return MPI_MESSAGE_NULL;
    (void)arg;
}

int MPI_Op_c2f(MPI_Op arg) {
    printf("MPI_Op_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Op MPI_Op_f2c(int arg) {
    printf("MPI_Op_f2c is unimplemented\n");
    abort();
    return MPI_OP_NULL;
    (void)arg;
}

int MPI_Request_c2f(MPI_Request arg) {
    printf("MPI_Request_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Request MPI_Request_f2c(int arg) {
    printf("MPI_Request_f2c is unimplemented\n");
    abort();
    return MPI_REQUEST_NULL;
    (void)arg;
}

int MPI_Session_c2f(MPI_Session arg) {
    printf("MPI_Session_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Session MPI_Session_f2c(int arg) {
    printf("MPI_Session_f2c is unimplemented\n");
    abort();
    return MPI_SESSION_NULL;
    (void)arg;
}

int MPI_Win_c2f(MPI_Win arg) {
    printf("MPI_Win_c2f is unimplemented\n");
    abort();
    return -1;
    (void)arg;
}

MPI_Win MPI_Win_f2c(int arg) {
    printf("MPI_Win_f2c is unimplemented\n");
    abort();
    return MPI_WIN_NULL;
    (void)arg;
}

#endif
