// SPDX-License-Identifier: MIT

#ifndef MUK_MPI_FORTRAN_H
#define MUK_MPI_FORTRAN_H

#define MPI_Status_c2f(c_status, f_status) 0
#define MPI_Status_f2c(f_status, c_status) 0

#define MPI_Comm_c2f(arg) 0
#define MPI_Comm_f2c(arg) NULL
#define MPI_Errhandler_c2f(arg) 0
#define MPI_Errhandler_f2c(arg) NULL
#define MPI_Type_c2f(arg) 0
#define MPI_Type_f2c(arg) NULL
#define MPI_File_c2f(arg) 0
#define MPI_File_f2c(arg) NULL
#define MPI_Group_c2f(arg) 0
#define MPI_Group_f2c(arg) NULL
#define MPI_Info_c2f(arg) 0
#define MPI_Info_f2c(arg) NULL
#define MPI_Message_c2f(arg) 0
#define MPI_Message_f2c(arg) NULL
#define MPI_Op_c2f(arg) 0
#define MPI_Op_f2c(arg) NULL
#define MPI_Request_c2f(arg) 0
#define MPI_Request_f2c(arg) NULL
#define MPI_Session_c2f(arg) 0
#define MPI_Session_f2c(arg) NULL
#define MPI_Win_c2f(arg) 0
#define MPI_Win_f2c(arg) NULL

#endif
