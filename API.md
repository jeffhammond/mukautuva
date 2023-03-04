These are all of the functions that do not depend on MPI types.

### Library control and query
```c
MPI_Init(int *argc, char ***argv);
MPI_Init_thread(int *argc, char ***argv, int required, int *provided);
MPI_Finalize();
MPI_Finalized(int *flag);
MPI_Initialized(int *flag);
MPI_Is_thread_main(int *flag);
MPI_Query_thread(int *provided);
MPI_Get_library_version(char *version, int *resultlen);
MPI_Get_processor_name(char *name, int *resultlen);
MPI_Get_version(int *version, int *subversion);
```

### Errors
```c
MPI_Add_error_class(int *errorclass);
MPI_Add_error_code(int errorclass, int *errorcode);
MPI_Add_error_string(int errorcode, const char *string);
MPI_Error_class(int errorcode, int *errorclass);
MPI_Error_string(int errorcode, char *string, int *resultlen);
```

### Random
```c
MPI_Pcontrol(const int level, ...);
MPI_Close_port(const char *port_name);
MPI_Dims_create(int nnodes, int ndims, int dims[]);
```

### Keyvals
```c
MPI_Comm_free_keyval(int *comm_keyval);
MPI_Keyval_free(int *keyval);
MPI_Type_free_keyval(int *type_keyval);
MPI_Win_free_keyval(int *win_keyval);
```

### Memory

Because `MPI_Alloc_mem` isn't on this list, we cannot do anything interesting here.
```c
MPI_Buffer_attach(void *buffer, int size);
MPI_Buffer_detach(void *buffer_addr, int *size);
MPI_Free_mem(void *base);
```
