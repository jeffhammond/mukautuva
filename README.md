# Mukautuva

Mukautuva means "adaptable" in Finnish.  The purpose of Mukautuva (MUK for short) is to allow one to compile 
an MPI application once against the MUK ABI, which is a prototype of the MPI-5 ABI we are developing,
and run using any MPI implementation.

Currently, we support Open-MPI, MPICH and Intel MPI.  The latter two are already ABI-compatible, while
MPICH and Open-MPI are quite different.  Internally, MUK supports MPICH and Open-MPI, so if you use an
MPI ABI that is not based on either of these, some work may be required.  However, as long as an MPI
implementation handle is compatible with an `int`, a `void*`, or an `intptr_t`, then the only work to
support it is detection.

To use MUK, you compile using the implementation-agnostic parts with the system C compiler.
You must tell the build system which `mpicc` to use for MPICH and Open-MPI.
At runtime, you must use the appropriate `mpirun` for your implementation, which is specified
by `MPI_LIB=<path to libmpi.so>`.  MUK knows the defaults for some systems so you can use
`mpirun` and not set `MPI_LIB` and it will probably work.

You configure the build system by editing the top of `Makefile`.
More complex build systems are a pointless distraction and will not be supported.

# Current status

The overwhelming majority of features are working, including all the common ones.

## Successes

The following are known to work:
- The [ARMCI-MPI](https://github.com/pmodels/armci-mpi) test suite, which exercises passive target RMA and some interesting group and communicator features.
- The OSU MPI Benchmarks ([OMB](https://mvapich.cse.ohio-state.edu/benchmarks/)), which test MPI performance.
- The Intel MPI Benchmarks ([IMB](https://github.com/intel/mpi-benchmarks)), which test MPI performance, including I/O.
- Most of the MPICH test suite, with exceptions noted below.

Specifically, the following MPICH test groups are passing:
- Attributes: all OK.
- Basic: all OK.
- Collectives: all OK.
- Comm: all OK.
- Datatypes: all OK.
- Group: all OK.
- Initialization: see below.
- IO: all OK.
- P2P: 61/66 passing. Failures related to Fortran handles and generalized requests.
- RMA: all OK.
- Topology: all OK.

## Known Issues

- Generakized requests need to be implemented. See the issue for details.
- Spawn is not supported.  Simple cases would work, but the shared-library lookup situation is more complicated with Spawn on multiple nodes.
- Most of the things that are supposed to work before MPI_Init don’t, because I need to reorganize all the `dlsym` stuff to make that work.
- Sessions are not supported because they are a more complicated version of the "before init" problem.
- Fortran interoperability features (handle conversion) are ignored.  These will be implemented in conjunction with [VAPAA](https://github.com/jeffhammond/vapaa) at some point.

There are things that do not work because the underlying implementation does not support them yet.  For example, MPICH has a bug with `MPI_BOTTOM` throwing an error when it shouldn't, and Open-MPI does not support much of MPI-4 right now.

# Design

Most things are straightforward.  Some times are not.

## Layering

We need to create an abstraction layer between the MPI namespace that Mukautuva exposes to MPI applications
and the MPI implementation namespace.  This is done using `dlopen`.  There are two shared libraries.
The first is `libmuk.so`, which implements the MPI API in terms of an internal namespace, MUK.
The MUK API is almost identical to the MPI.  There is one pair of exceptions that are not interesting.
When possible, we implement deprecated or deleted APIs in terms of their replacements.

The second shared library is implementation dependent, so it is named `ompi-wrap.so` or `mpich-wrap.so`.
It implements the MUK API in the WRAP namespace.  The MPI implementation is loaded with symbols that
have the IMPL namespace prefix.

The `libmuk.so` library is implemented in `libinit.c`.  Almost all of it is boilerplate to `dlsym`
MUK functions to the WRAP ones in the back-end.  However, it first has to figure out which implementation
is used.  It does this by looking at `libmpi.so` (or whatever the user provides via the `MPI_LIB`
environment variable).  Because the necessary features for this are ABI-agnostic (i.e. they use
only built-in C types), we can load these functions directly from the implementation shared object (SO).
We call `MPI_Get_library_version` to see if we are using Open-MPI or an MPICH-derivative
(only Intel MPI is recognized right now, but MVAPICH2 is trivial to add).
Once we know if we are working with the Open-MPI or MPICH ABI, we `dlopen` the appropriate `<impl>-wrap.so`
and `dlsym` all of the WRAP symbols.

Because all of the `dlsym` mappings are setup during MPI initialization, most of the MPI functionality
that is required to work before initialization does not work correctly.
We implement the ABI-agnostic operations to some extent, since they are easy.
For similar reasons, we do not implement MPI sessions, which are not widely available in implementations
right now anyways.

We are definitely not using `dlopen` optimally right now.  This project is the first time
I've used it and I am only doing what is absolutely necessary to make Mukautuva work on Linux
and MacOS.  Some things are brittle due to lack of careful namespacing, which we triggered
during development by using `MPI_Comm_rank` in the wrong place, which caused the MPI
implementation symbols to be used instead of Mukautuva MPI symbols, which causes
some really nasty, hard-to-debug crashes.
Erik Schnetter appears to be doing sensible things in
[MPItrampoline](https://github.com/eschnett/MPItrampoline), so we will try
to learn from that at some point.

## Translation of predefined constants and handles

All of the WRAP functions map the MUK ABI to the IMPL ABI.
For example, we have special integer constants like `MPI_ANY_SOURCE` and `MPI_PROC_NULL` that
are not standardized values, so we have a function to convert all rank-like arguments.
Similar recognition and translation occurs for buffer sentinels like `MPI_STATUS_IGNORE`.
Wherever possible, i.e. when MPICH and Open-MPI agree on values, e.g. `MPI_BOTTOM=NULL`,
we just use the same value to avoid translation overhead.
MPICH made an unfortunate design choice with `MPI_UNWEIGHTED`, we must handle this one
in a special way, which is the one exception to the 1:1 mapping between MPI and MUK APIs.

MUK handles are exposed to the user as incomplete `struct` pointers for type-safety.
Internally, they are a `union` of `{ int, void*, intptr_t }`.
We use the appropriate field for the MPICH and Open-MPI ABI, respectively,
and `intptr_t` to `printf` handles in diagnostic messages (one must ignore
the `0xFFFF..` junk bits to recognize MPICH handles).

## Translation of callbacks

Callbacks are the most difficult part of Mukautuva.
Recall that the application will be compiled against the MUK ABI.
Callbacks are invoked by the MPI implementation with the IMPL ABI.
Furthermore, even when handles are passed by pointer, they are checked
for validity, so we can't just pass a `MUK_Datatype*` when a `IMPL_Datatype*`
is expected, because this will cause an error.

The way we support callbacks is to replace the callback argument with a
trampoline function that matches the function pointer signature of the
IMPL ABI.  The trampoline must look up the WRAP ABI function pointer
and call it with the appropriate translated handles, as well as do
back-translation of error codes, where appropriate.

MPI is far from consistent in the callback signatures, so we have to use
different strategies.

## Reduction callbacks

In `MPI_Op_create`, we create a map (a C++ `std::map`) between the
`MPI_User_function(_c)` and the `MPI_Op` handle.
When the `MPI_Op` is used inside of e.g. `MPI_Allreduce`,
we lookup the function pointer via the `MPI_Op` and attach
it to a duplicate of the `MPI_Datatype` argument to that function.
Why the `MPI_Datatype` and why a duplicate?
We use the `MPI_Datatype` because that is the only thing we
can uniquely identify inside of the trampoline.
It is a duplicate because we can't be sure that the user won't
call two different reductions with the same datatype before
the callback is done.
Inside of the callback, we get the datatype attribute
that contains the function pointer of the original callback,
and we invoke it with the translated datatype, then free
it if it was the copy of derived datatype.

The biggest problem here is that MPI implementations are expected
to ref-count everything, so it is legal to call `Op_create`,
`Iallreduce` and `Op_free` before calling `Wait`, which means
that the op-callback mapping will be destroyed while the reduction
is in-flight.
Our first few designs were bad.  We used a heap object for the attribute,
which is freed during `Op_free`.  We can fix this and just
attach the function pointer directly to the datatype
so no heap allocation is necessary.  However, we store the mapping
between the `MPI_Op` and `MPI_User_function(_c)` forever, which
has trivial space and time overheads in all but the most pathological
use cases. (If you call `MPI_Op_create` millions of times in your program,
I don't know what to tell you.)

## Errhandler callbacks

It is legal - and practiced by the MPICH test suite - to free
an errhandler and still use it.
We solved this by using the function pointer as the attribute directly.
Obviously, the function pointer itself cannot go out of scope,
so this eliminates the use-after-free issue above.

Unfortunately, `MPI_File` objects don't support attributes, so
we need a second mapping between those handles and the errhandler
callbacks, but the overheads of anything related to file errhandlers
is irrelevant compared to actual file I/O.

## Attribute callbacks

Both of the above use a C linked-list implementation taken from
[ARMCI-MPI](https://github.com/pmodels/armci-mpi/).
However, writing yet another linked-list for attribute callbacks
was going to be tedious, so we decided instead to use the C++
`std::map` container, which provides exactly what we need, at the
small cost of requiring awareness of C++ in the project.
The C++ code itself is encapsulated in a single file, which
implements a C API that can be used in the rest of the library
without requiring any C++.
The build system links the shared libraries using a C++ compiler
to ensure that the C++ runtime library is linked automatically.

Ironically, using C++ defeats the purpose of having a clean ABI
abstraction layer, because we are now dependent on the C++ ABI,
but this is not expected to be a major issue, since almost everyone
will use the system default C++ library.  However, since
we are only using C++ in the IMPL back-end, we can, in theory,
`dlopen` the correct C++ library there without interfering with
the user's use of a different C++ library, or aversion to C++
altogether, but we are not going to implement this without
significant incentives.

## Nonblocking alltoallw

All of the nonblocking variants of nonblocking alltoallw
require us to track the state of the temporary arrays of
converted datatypes, which cannot be freed until the operation
finishes.  We implement this using a mapping between the
nonblocking request and array pointers.  This means that
all request completion functions need to look to see
if there are any completed requests associated with
alltoallw state.  This introduces some overhead if we do
something silly like initiate a nonblocking alltoall,
then run an MPI message rate benchmark that calls
`MPI_Waitall` with lots of requests.  However, if there
are no outstanding nonblocking alltoalw operations, the
overhead is a single branch (per request, although we could
theoretically optimize it to one branch per request-completion
call).

## Persistent collectives

Persistent reductions are working correctly.

## Generalized requests

Because generalized requests use `extra_state`, we can stick everything to support
the trampoline in there.

# Acknowledgements

Hui Zhou and Ken Raffineti of the MPICH team were extremely helpful when debugging a number of issues with Mukautuva.

My team at NVIDIA allowed me to focus on this project for the month or so it took to create.
