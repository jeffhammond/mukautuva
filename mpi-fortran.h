// SPDX-License-Identifier: MIT

#ifndef MUK_MPI_FORTRAN_H
#define MUK_MPI_FORTRAN_H

int MPI_Status_c2f(const MPI_Status * c_status, MPI_F08_Status * f_status);
int MPI_Status_f2c(const MPI_F08_Status * f_status, MPI_Status * c_status);
int MPI_Comm_c2f(MPI_Comm arg);
MPI_Comm MPI_Comm_f2c(int arg);
int MPI_Errhandler_c2f(MPI_Errhandler arg);
MPI_Errhandler MPI_Errhandler_f2c(int arg);
int MPI_Type_c2f(MPI_Datatype arg);
MPI_Datatype MPI_Type_f2c(int arg);
int MPI_File_c2f(MPI_File arg);
MPI_File MPI_File_f2c(int arg);
int MPI_Group_c2f(MPI_Group arg);
MPI_Group MPI_Group_f2c(int arg);
int MPI_Info_c2f(MPI_Info arg);
MPI_Info MPI_Info_f2c(int arg);
int MPI_Message_c2f(MPI_Message arg);
MPI_Message MPI_Message_f2c(int arg);
int MPI_Op_c2f(MPI_Op arg);
MPI_Op MPI_Op_f2c(int arg);
int MPI_Request_c2f(MPI_Request arg);
MPI_Request MPI_Request_f2c(int arg);
int MPI_Session_c2f(MPI_Session arg);
MPI_Session MPI_Session_f2c(int arg);
int MPI_Win_c2f(MPI_Win arg);
MPI_Win MPI_Win_f2c(int arg);

#endif
