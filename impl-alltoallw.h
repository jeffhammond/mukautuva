#ifndef IMPL_ALLTOALLW_H
#define IMPL_ALLTOALLW_H

static int ALLTOALLW_SETUP(bool in_place, const MPI_Comm comm, const WRAP_Datatype sendtypes[], const WRAP_Datatype recvtypes[],
                           MPI_Datatype ** impl_sendtypes, MPI_Datatype ** impl_recvtypes)
{
    int rc;
    int sendnum, recvnum;

    // FIXME neighborhood collectives - need to set sendnum and recvnum based on indegree and outdegree...
    // int MPI_Topo_test(MPI_Comm comm, int *status)
    // status = { MPI_GRAPH MPI_CART MPI_DIST_GRAPH MPI_UNDEFINED }

    int is_intercomm;
    rc = IMPL_Comm_test_inter(comm, &is_intercomm);
    if (is_intercomm) {
        int remote_size;
        rc = IMPL_Comm_remote_size(comm,&remote_size);
        if (rc != MPI_SUCCESS) {
            return MPI_ERR_INTERN;
        }
        sendnum = remote_size;
        recvnum = remote_size;
    }
    else {
        int size;
        rc = IMPL_Comm_size(comm,&size);
        if (rc != MPI_SUCCESS) {
            return MPI_ERR_INTERN;
        }
        sendnum = size;
        recvnum = size;
    }
    //printf("sendnum=%d recvnum=%d\n", sendnum, recvnum); fflush(0);

    if (!in_place) {
        *impl_sendtypes = calloc(sendnum,sizeof(MPI_Datatype));
        if (*impl_sendtypes == NULL) return MPI_ERR_INTERN;
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
    if (*impl_recvtypes == NULL) return MPI_ERR_INTERN;
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
