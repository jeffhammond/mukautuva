# mukautuva
Adapting to multiple MPI ABIs

# Current status

The overwhelming majority of features are working, including all the common ones.

## Successes

The following are known to work:
- The [ARMCI-MPI](https://github.com/pmodels/armci-mpi) test suite, which exercises passive target RMA and some interesting group and communicator features.
- The OSU MPI Benchmarks ([OMB](https://mvapich.cse.ohio-state.edu/benchmarks/)), which test MPI performance.
- The Intel MPI Benchmarks ([IMB](https://github.com/intel/mpi-benchmarks)), which test MPI performance, including I/O.
- Most of the MPICH test suite, with exceptions noted below.

Specifically, the following MPICH test groups are passing:
- Attributes: see below.
- Basic: all OK.
- Collectives: all except `p_scan` (see below).
- Comm: all OK.
- Datatypes: all OK.
- Group: all OK.
- Initialization: see below.
- IO: all OK.
- P2P: 61/66 passing. Failures related to `MPI_Fint`, `PMPI_Message_f2c`, generalized requests - all of which are known issues - and https://github.com/jeffhammond/mukautuva/issues/19, which needs to be debugged.
- RMA: all except keyval- and errhandler-related.
- Topology: all OK.

## Known Issues

- Attributes and errhandler stuff with custom callbacks as well as grequests are not yet implemented.  The only user-defined callbacks that are implemented right now are user-defined reductions, which are the most important ones.
- Mukautuva leaks state in in persistent reductions (e.g. `MPI_Scan_init`) with user-defined ops.  This is fixable but low priority.
- Spawn is not supported.  Simple cases would work, but the shared-library lookup situation is more complicated with Spawn on multiple nodes.
- Most of the things that are supposed to work before MPI_Init don’t, because i need to reorganize all the dlsym init stuff to make that work.
- Sessions are not supported because they are a more complicated version of the "before init" problem.
- Fortran interoperability features (handle conversion) are ignore.  These will be implemented in conjunction with [VAPAA](https://github.com/jeffhammond/vapaa) at some point.

There are things that do not work because the underlying implementation does not support them yet.  For example, MPICH has a bug with `MPI_BOTTOM` throwing an error when it shouldn't, and Open-MPI does not support much of MPI-4 right now.

# Design

TODO

# Acknowledgements
