#ifndef __cplusplus
#error Sorry, but you have to use a C++ compiler.
#endif
#if defined(__cplusplus) && (__cplusplus < 201703L)
#error Sorry, but you have to use a C++17 compiler.
#endif

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <string>
#include <utility>
#include <map>

extern "C" {

// we do not want anything MPI C++ related here.
// this header is only used to determine the MPI ABI we are compiling against,
// and then only the scalar types (impl-scalar-types.h) it seems.
#define OMPI_SKIP_MPICXX
#define MPICH_SKIP_MPICXX
#include <mpi.h>

#include "muk-predefined.h"
#include "wrap-handle-typedefs.h"

}

// we will not try to purge the callback mappings when handle keys are no longer used
// because that will require reference counting.  instead, we will just keep
// them around forever, which has the potential to waste a trivial amount of memory -
// it is key and two pointers worth of storage (20 or 24 bytes) per entry.
//
// the lookup cost of a std::map is logarithmic in the size of the container, which
// is a price worth paying to avoid dealing with the use-after-free situation.
//
// TODO:
// to please memory tools like valgrind, we will purge everything using clear()
// during finalization.

// for attributes
std::map<int, std::pair<WRAP_Comm_copy_attr_function*,WRAP_Comm_delete_attr_function*>> keyval_comm_attr_cb_map{};
std::map<int, std::pair<WRAP_Type_copy_attr_function*,WRAP_Type_delete_attr_function*>> keyval_type_attr_cb_map{};
std::map<int, std::pair<WRAP_Win_copy_attr_function* ,WRAP_Win_delete_attr_function*>>  keyval_win_attr_cb_map{};

// for user-defined reductions - implemented but unused
std::map<MPI_Op, std::pair<WRAP_User_function*, WRAP_User_function_c*>> op_user_function_map{};

// for errhandlers - TODO
std::map<MPI_Errhandler, WRAP_Comm_errhandler_function*> errhandler_comm_cb_map{};
std::map<MPI_Errhandler, WRAP_File_errhandler_function*> errhandler_file_cb_map{};
std::map<MPI_Errhandler, WRAP_Win_errhandler_function*>  errhandler_win_cb_map{};

// for nonblocking alltoallw - TODO
//
// persistent ialltoallw must be concluded with MPI_Request_free so we should have a dedicated
// list for these, to ensure that we only pay the lookup cost in MPI_Request_free.
//
// for neighborhood ialltoallw, we can associate the allocations with the communicator
// and clean up when it is freed, although more than one outstanding ialltoallw per communicator
// is permitted, so we need to use a std::multimap here.
//
// for ialltoallw, we should just assume the user will not free the associated communicator
// in a timely fashion (it will probably be a predefined one) and we have to use the request
// as the key, which means putting the lookup on the critical path of request completion.
//
std::map<MPI_Request, std::pair<MPI_Datatype*, MPI_Datatype*>> request_persistent_ialltoallw_map{};
std::map<MPI_Request, std::pair<MPI_Datatype*, MPI_Datatype*>> comm_neighborhood_ialltoallw_multimap{};
std::map<MPI_Request, std::pair<MPI_Datatype*, MPI_Datatype*>> request_ialltoallw_map{};

extern "C" {

// we use int as the boolean return code to avoid theoretical incompatibilities
// between C and C++ bool

#include "impl-keyval-map-commattr.h" // keyval_comm_attr_cb_map
#include "impl-keyval-map-typeattr.h" // keyval_type_attr_cb_map
#include "impl-keyval-map-winattr.h"  // keyval_win_attr_cb_map
#include "impl-keyval-map-opuserfn.h" // op_user_function_map
#include "impl-keyval-map-commerrh.h" // errhandler_comm_cb_map
#include "impl-keyval-map-fileerrh.h" // errhandler_file_cb_map
#include "impl-keyval-map-winerrh.h"  // errhandler_win_cb_map
#include "impl-keyval-map-preqa2aw.h" // request_persistent_ialltoallw_map

void WRAP_Clear_maps(void)
{
    keyval_comm_attr_cb_map.clear();
    keyval_type_attr_cb_map.clear();
    keyval_win_attr_cb_map.clear();
    op_user_function_map.clear();
    errhandler_comm_cb_map.clear();
    errhandler_file_cb_map.clear();
    errhandler_win_cb_map.clear();
    request_persistent_ialltoallw_map.clear();
    comm_neighborhood_ialltoallw_multimap.clear();
    request_ialltoallw_map.clear();
}

} // extern "C"
