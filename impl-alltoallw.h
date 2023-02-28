#ifndef IMPL_ALLTOALLW_H
#define IMPL_ALLTOALLW_H

static int ALLTOALLW_SETUP(bool in_place, const MPI_Comm comm, const WRAP_Datatype sendtypes[], const WRAP_Datatype recvtypes[],
                           MPI_Datatype ** impl_sendtypes, MPI_Datatype ** impl_recvtypes)
{
    int rc;
    int sendnum, recvnum;

    // ignore this for now - we can always allocate too much memory for types in neigherbor_alltoallw
#if 0
    int topo;
    rc = MPI_Topo_test(comm, &topo);
    if (rc != MPI_SUCCESS) {
        return rc;
    }
#endif

    int is_intercomm;
    rc = IMPL_Comm_test_inter(comm, &is_intercomm);
    if (rc != MPI_SUCCESS) {
        return rc;
    }

    if (is_intercomm) {
        int remote_size;
        rc = IMPL_Comm_remote_size(comm,&remote_size);
        if (rc != MPI_SUCCESS) {
            return rc;
        }
        sendnum = remote_size;
        recvnum = remote_size;
    }
#if 0
    else if (topo == MPI_GRAPH || topo == MPI_CART || topo == MPI_DIST_GRAPH) {
    }
#endif
    else {
        int size;
        rc = IMPL_Comm_size(comm,&size);
        if (rc != MPI_SUCCESS) {
            return rc;
        }
        sendnum = size;
        recvnum = size;
    }
    //printf("sendnum=%d recvnum=%d\n", sendnum, recvnum); fflush(0);

    if (!in_place) {
        *impl_sendtypes = calloc(sendnum,sizeof(MPI_Datatype));
        if (*impl_sendtypes == NULL) return MPI_ERR_OTHER;
        for (int i=0; i<sendnum; i++) {
            (*impl_sendtypes)[i] = CONVERT_MPI_Datatype(sendtypes[i]);
#if 0
            char name[MPI_MAX_OBJECT_NAME] = {0};
            int namelen;
            IMPL_Type_get_name((*impl_sendtypes)[i],name,&namelen);
            printf("%d: send type=%lx impl=%lx name=%s\n",
                    i, sendtypes[i].ip, (intptr_t)(*impl_sendtypes)[i], name);
#endif
        }
    }
    *impl_recvtypes = calloc(recvnum,sizeof(MPI_Datatype));
    if (*impl_recvtypes == NULL) return MPI_ERR_OTHER;
    for (int i=0; i<recvnum; i++) {
        (*impl_recvtypes)[i] = CONVERT_MPI_Datatype(recvtypes[i]);
#if 0
        char name[MPI_MAX_OBJECT_NAME] = {0};
        int namelen;
        IMPL_Type_get_name((*impl_recvtypes)[i],name,&namelen);
        printf("%d: recv type=%lx impl=%lx name=%s\n",
                i, recvtypes[i].ip, (intptr_t)(*impl_recvtypes)[i], name);
#endif
    }
    return MPI_SUCCESS;
}

#endif
