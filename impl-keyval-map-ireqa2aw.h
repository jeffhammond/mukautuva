int add_nonblocking_request_alltoallw_buffers(MPI_Request request, MPI_Datatype * sendtypes, MPI_Datatype * recvtypes)
{
#if DEBUG
    printf("%s: insert_or_assign(request=%lx, sendtypes=%p, recvtypes=%p)\n",
            __func__, (intptr_t)request, sendtypes, recvtypes);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = request_nonblocking_alltoallw_map.insert_or_assign(request, std::make_pair(sendtypes, recvtypes));
#if DEBUG
    printf("%s: insert_or_assign(request=%lx, sendtypes=%p, recvtypes=%p) returned %d\n",
            __func__, (intptr_t)request, sendtypes, recvtypes, rc);
#endif
    return 1; // SUCCESS int{rc};
    (void)it;
    (void)rc;
}

int find_nonblocking_request_alltoallw_buffers(MPI_Request request, MPI_Datatype ** sendtypes, MPI_Datatype ** recvtypes)
{
    if (request_nonblocking_alltoallw_map.empty()) return 0;;

    try {
        auto [stypes,rtypes] = request_nonblocking_alltoallw_map.at(request);
#if DEBUG
        printf("%s: lookup(request=%lx) -> [sendtypes=%p, sendtypes=%p]\n",
                __func__, (intptr_t)request, sendtypes, recvtypes);
#endif
        if (stypes != NULL) {
            *sendtypes = stypes;
        }
        else if (rtypes != NULL) {
            *recvtypes = rtypes;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(request=%lx) failed\n", __func__, (intptr_t)request);
        return 0;
    }
}

int remove_nonblocking_request_alltoallw_buffers(MPI_Request request)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return request_nonblocking_alltoallw_map.erase(request);
}
