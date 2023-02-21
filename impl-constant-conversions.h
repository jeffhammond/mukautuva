#ifndef MUK_IMPL_CONSTANT_CONVERSIONS_H
#define MUK_IMPL_CONSTANT_CONVERSIONS_H

// declaration for impl-functions.c symbol
extern int (*IMPL_Error_class)(int errorcode, int *errorclass);

static int ERROR_CODE_IMPL_TO_MUK(int error_c)
{
    if (error_c == 0) return 0;

    int error;
    // "To make it possible for an application to interpret an error code,
    //  the routine MPI_ERROR_CLASS converts any error code into one of a
    //  small set of standard error codes, called error classes."
    // MPI_Error_class is one of the functions that can be called after MPI_Finalize.
    IMPL_Error_class(error_c, &error);

    // If, for some reason, you need to known the actual error returned from
    // the MPI library, and not just the class, enable the following code.
#if 0
    int len;
    char name[MPI_MAX_ERROR_STRING] = {0};
    MPI_Error_string(error_c, name, &len);
    printf("Real error code returned from the C library: %d=%x, name=%s\n",
            error_c, error_c, name);
#endif

         if (error == MPI_SUCCESS                   ) { return MUK_SUCCESS; }
    else if (error == MPI_ERR_BUFFER                ) { return MUK_ERR_BUFFER; }
    else if (error == MPI_ERR_COUNT                 ) { return MUK_ERR_COUNT; }
    else if (error == MPI_ERR_TYPE                  ) { return MUK_ERR_TYPE; }
    else if (error == MPI_ERR_TAG                   ) { return MUK_ERR_TAG; }
    else if (error == MPI_ERR_COMM                  ) { return MUK_ERR_COMM; }
    else if (error == MPI_ERR_RANK                  ) { return MUK_ERR_RANK; }
    else if (error == MPI_ERR_REQUEST               ) { return MUK_ERR_REQUEST; }
    else if (error == MPI_ERR_ROOT                  ) { return MUK_ERR_ROOT; }
    else if (error == MPI_ERR_GROUP                 ) { return MUK_ERR_GROUP; }
    else if (error == MPI_ERR_OP                    ) { return MUK_ERR_OP; }
    else if (error == MPI_ERR_TOPOLOGY              ) { return MUK_ERR_TOPOLOGY; }
    else if (error == MPI_ERR_DIMS                  ) { return MUK_ERR_DIMS; }
    else if (error == MPI_ERR_ARG                   ) { return MUK_ERR_ARG; }
    else if (error == MPI_ERR_UNKNOWN               ) { return MUK_ERR_UNKNOWN; }
    else if (error == MPI_ERR_TRUNCATE              ) { return MUK_ERR_TRUNCATE; }
    else if (error == MPI_ERR_OTHER                 ) { return MUK_ERR_OTHER; }
    else if (error == MPI_ERR_INTERN                ) { return MUK_ERR_INTERN; }
    else if (error == MPI_ERR_PENDING               ) { return MUK_ERR_PENDING; }
    else if (error == MPI_ERR_IN_STATUS             ) { return MUK_ERR_IN_STATUS; }
    else if (error == MPI_ERR_ACCESS                ) { return MUK_ERR_ACCESS; }
    else if (error == MPI_ERR_AMODE                 ) { return MUK_ERR_AMODE; }
    else if (error == MPI_ERR_ASSERT                ) { return MUK_ERR_ASSERT; }
    else if (error == MPI_ERR_BAD_FILE              ) { return MUK_ERR_BAD_FILE; }
    else if (error == MPI_ERR_BASE                  ) { return MUK_ERR_BASE; }
    else if (error == MPI_ERR_CONVERSION            ) { return MUK_ERR_CONVERSION; }
    else if (error == MPI_ERR_DISP                  ) { return MUK_ERR_DISP; }
    else if (error == MPI_ERR_DUP_DATAREP           ) { return MUK_ERR_DUP_DATAREP; }
    else if (error == MPI_ERR_FILE_EXISTS           ) { return MUK_ERR_FILE_EXISTS; }
    else if (error == MPI_ERR_FILE_IN_USE           ) { return MUK_ERR_FILE_IN_USE; }
    else if (error == MPI_ERR_FILE                  ) { return MUK_ERR_FILE; }
    else if (error == MPI_ERR_INFO_KEY              ) { return MUK_ERR_INFO_KEY; }
    else if (error == MPI_ERR_INFO_NOKEY            ) { return MUK_ERR_INFO_NOKEY; }
    else if (error == MPI_ERR_INFO_VALUE            ) { return MUK_ERR_INFO_VALUE; }
    else if (error == MPI_ERR_INFO                  ) { return MUK_ERR_INFO; }
    else if (error == MPI_ERR_IO                    ) { return MUK_ERR_IO; }
    else if (error == MPI_ERR_KEYVAL                ) { return MUK_ERR_KEYVAL; }
    else if (error == MPI_ERR_LOCKTYPE              ) { return MUK_ERR_LOCKTYPE; }
    else if (error == MPI_ERR_NAME                  ) { return MUK_ERR_NAME; }
    else if (error == MPI_ERR_NO_MEM                ) { return MUK_ERR_NO_MEM; }
    else if (error == MPI_ERR_NOT_SAME              ) { return MUK_ERR_NOT_SAME; }
    else if (error == MPI_ERR_NO_SPACE              ) { return MUK_ERR_NO_SPACE; }
    else if (error == MPI_ERR_NO_SUCH_FILE          ) { return MUK_ERR_NO_SUCH_FILE; }
    else if (error == MPI_ERR_PORT                  ) { return MUK_ERR_PORT; }
#if (MPI_VERSION >= 4)
    else if (error == MPI_ERR_PROC_ABORTED          ) { return MUK_ERR_PROC_ABORTED; }
#endif
    else if (error == MPI_ERR_QUOTA                 ) { return MUK_ERR_QUOTA; }
    else if (error == MPI_ERR_READ_ONLY             ) { return MUK_ERR_READ_ONLY; }
    else if (error == MPI_ERR_RMA_ATTACH            ) { return MUK_ERR_RMA_ATTACH; }
    else if (error == MPI_ERR_RMA_CONFLICT          ) { return MUK_ERR_RMA_CONFLICT; }
    else if (error == MPI_ERR_RMA_RANGE             ) { return MUK_ERR_RMA_RANGE; }
    else if (error == MPI_ERR_RMA_SHARED            ) { return MUK_ERR_RMA_SHARED; }
    else if (error == MPI_ERR_RMA_SYNC              ) { return MUK_ERR_RMA_SYNC; }
    else if (error == MPI_ERR_RMA_FLAVOR            ) { return MUK_ERR_RMA_FLAVOR; }
    else if (error == MPI_ERR_SERVICE               ) { return MUK_ERR_SERVICE; }
#if (MPI_VERSION >= 4)
    else if (error == MPI_ERR_SESSION               ) { return MUK_ERR_SESSION; }
#endif
    else if (error == MPI_ERR_SIZE                  ) { return MUK_ERR_SIZE; }
    else if (error == MPI_ERR_SPAWN                 ) { return MUK_ERR_SPAWN; }
    else if (error == MPI_ERR_UNSUPPORTED_DATAREP   ) { return MUK_ERR_UNSUPPORTED_DATAREP; }
    else if (error == MPI_ERR_UNSUPPORTED_OPERATION ) { return MUK_ERR_UNSUPPORTED_OPERATION; }
#if (MPI_VERSION >= 4)
    else if (error == MPI_ERR_VALUE_TOO_LARGE       ) { return MUK_ERR_VALUE_TOO_LARGE; }
#endif
    else if (error == MPI_ERR_WIN                   ) { return MUK_ERR_WIN; }
    else if (error == MPI_T_ERR_CANNOT_INIT         ) { return MUK_T_ERR_CANNOT_INIT; }
    //else if (error == MPI_T_ERR_NOT_ACCESSIBLE      ) { return MUK_T_ERR_NOT_ACCESSIBLE; }
    else if (error == MPI_T_ERR_NOT_INITIALIZED     ) { return MUK_T_ERR_NOT_INITIALIZED; }
#if (MPI_VERSION >= 4)
    else if (error == MPI_T_ERR_NOT_SUPPORTED       ) { return MUK_T_ERR_NOT_SUPPORTED; }
#endif
    else if (error == MPI_T_ERR_MEMORY              ) { return MUK_T_ERR_MEMORY; }
    else if (error == MPI_T_ERR_INVALID             ) { return MUK_T_ERR_INVALID; }
    else if (error == MPI_T_ERR_INVALID_INDEX       ) { return MUK_T_ERR_INVALID_INDEX; }
    else if (error == MPI_T_ERR_INVALID_ITEM        ) { return MUK_T_ERR_INVALID_ITEM; }
    else if (error == MPI_T_ERR_INVALID_SESSION     ) { return MUK_T_ERR_INVALID_SESSION; }
    else if (error == MPI_T_ERR_INVALID_HANDLE      ) { return MUK_T_ERR_INVALID_HANDLE; }
    else if (error == MPI_T_ERR_INVALID_NAME        ) { return MUK_T_ERR_INVALID_NAME; }
    else if (error == MPI_T_ERR_OUT_OF_HANDLES      ) { return MUK_T_ERR_OUT_OF_HANDLES; }
    else if (error == MPI_T_ERR_OUT_OF_SESSIONS     ) { return MUK_T_ERR_OUT_OF_SESSIONS; }
    else if (error == MPI_T_ERR_CVAR_SET_NOT_NOW    ) { return MUK_T_ERR_CVAR_SET_NOT_NOW; }
    else if (error == MPI_T_ERR_CVAR_SET_NEVER      ) { return MUK_T_ERR_CVAR_SET_NEVER; }
    else if (error == MPI_T_ERR_PVAR_NO_WRITE       ) { return MUK_T_ERR_PVAR_NO_WRITE; }
    else if (error == MPI_T_ERR_PVAR_NO_STARTSTOP   ) { return MUK_T_ERR_PVAR_NO_STARTSTOP; }
    else if (error == MPI_T_ERR_PVAR_NO_ATOMIC      ) { return MUK_T_ERR_PVAR_NO_ATOMIC; }
    else if (error == MPI_ERR_LASTCODE              ) { return MUK_ERR_LASTCODE; }
    else {
#if 0
        int len;
        char name[MPI_MAX_ERROR_STRING] = {0};
        rc = MPI_Error_string(error, name, &len);
        printf("Unknown error class returned from the C library: code=%d=%x, class=%d=%x, name=%s\n",
                     error_c, error_c, error, error, name);
#endif
        return MUK_ERR_UNKNOWN;
    }
}

static int ERROR_CODE_MUK_TO_IMPL(int error_muk)
{
         if (error_muk == MUK_SUCCESS                    ) { return MPI_SUCCESS;                   }
    else if (error_muk == MUK_ERR_BUFFER                 ) { return MPI_ERR_BUFFER;                }
    else if (error_muk == MUK_ERR_COUNT                  ) { return MPI_ERR_COUNT;                 }
    else if (error_muk == MUK_ERR_TYPE                   ) { return MPI_ERR_TYPE;                  }
    else if (error_muk == MUK_ERR_TAG                    ) { return MPI_ERR_TAG;                   }
    else if (error_muk == MUK_ERR_COMM                   ) { return MPI_ERR_COMM;                  }
    else if (error_muk == MUK_ERR_RANK                   ) { return MPI_ERR_RANK;                  }
    else if (error_muk == MUK_ERR_REQUEST                ) { return MPI_ERR_REQUEST;               }
    else if (error_muk == MUK_ERR_ROOT                   ) { return MPI_ERR_ROOT;                  }
    else if (error_muk == MUK_ERR_GROUP                  ) { return MPI_ERR_GROUP;                 }
    else if (error_muk == MUK_ERR_OP                     ) { return MPI_ERR_OP;                    }
    else if (error_muk == MUK_ERR_TOPOLOGY               ) { return MPI_ERR_TOPOLOGY;              }
    else if (error_muk == MUK_ERR_DIMS                   ) { return MPI_ERR_DIMS;                  }
    else if (error_muk == MUK_ERR_ARG                    ) { return MPI_ERR_ARG;                   }
    else if (error_muk == MUK_ERR_UNKNOWN                ) { return MPI_ERR_UNKNOWN;               }
    else if (error_muk == MUK_ERR_TRUNCATE               ) { return MPI_ERR_TRUNCATE;              }
    else if (error_muk == MUK_ERR_OTHER                  ) { return MPI_ERR_OTHER;                 }
    else if (error_muk == MUK_ERR_INTERN                 ) { return MPI_ERR_INTERN;                }
    else if (error_muk == MUK_ERR_PENDING                ) { return MPI_ERR_PENDING;               }
    else if (error_muk == MUK_ERR_IN_STATUS              ) { return MPI_ERR_IN_STATUS;             }
    else if (error_muk == MUK_ERR_ACCESS                 ) { return MPI_ERR_ACCESS;                }
    else if (error_muk == MUK_ERR_AMODE                  ) { return MPI_ERR_AMODE;                 }
    else if (error_muk == MUK_ERR_ASSERT                 ) { return MPI_ERR_ASSERT;                }
    else if (error_muk == MUK_ERR_BAD_FILE               ) { return MPI_ERR_BAD_FILE;              }
    else if (error_muk == MUK_ERR_BASE                   ) { return MPI_ERR_BASE;                  }
    else if (error_muk == MUK_ERR_CONVERSION             ) { return MPI_ERR_CONVERSION;            }
    else if (error_muk == MUK_ERR_DISP                   ) { return MPI_ERR_DISP;                  }
    else if (error_muk == MUK_ERR_DUP_DATAREP            ) { return MPI_ERR_DUP_DATAREP;           }
    else if (error_muk == MUK_ERR_FILE_EXISTS            ) { return MPI_ERR_FILE_EXISTS;           }
    else if (error_muk == MUK_ERR_FILE_IN_USE            ) { return MPI_ERR_FILE_IN_USE;           }
    else if (error_muk == MUK_ERR_FILE                   ) { return MPI_ERR_FILE;                  }
    else if (error_muk == MUK_ERR_INFO_KEY               ) { return MPI_ERR_INFO_KEY;              }
    else if (error_muk == MUK_ERR_INFO_NOKEY             ) { return MPI_ERR_INFO_NOKEY;            }
    else if (error_muk == MUK_ERR_INFO_VALUE             ) { return MPI_ERR_INFO_VALUE;            }
    else if (error_muk == MUK_ERR_INFO                   ) { return MPI_ERR_INFO;                  }
    else if (error_muk == MUK_ERR_IO                     ) { return MPI_ERR_IO;                    }
    else if (error_muk == MUK_ERR_KEYVAL                 ) { return MPI_ERR_KEYVAL;                }
    else if (error_muk == MUK_ERR_LOCKTYPE               ) { return MPI_ERR_LOCKTYPE;              }
    else if (error_muk == MUK_ERR_NAME                   ) { return MPI_ERR_NAME;                  }
    else if (error_muk == MUK_ERR_NO_MEM                 ) { return MPI_ERR_NO_MEM;                }
    else if (error_muk == MUK_ERR_NOT_SAME               ) { return MPI_ERR_NOT_SAME;              }
    else if (error_muk == MUK_ERR_NO_SPACE               ) { return MPI_ERR_NO_SPACE;              }
    else if (error_muk == MUK_ERR_NO_SUCH_FILE           ) { return MPI_ERR_NO_SUCH_FILE;          }
    else if (error_muk == MUK_ERR_PORT                   ) { return MPI_ERR_PORT;                  }
#if (MPI_VERSION >= 4)
    else if (error_muk == MUK_ERR_PROC_ABORTED           ) { return MPI_ERR_PROC_ABORTED;          }
#endif
    else if (error_muk == MUK_ERR_QUOTA                  ) { return MPI_ERR_QUOTA;                 }
    else if (error_muk == MUK_ERR_READ_ONLY              ) { return MPI_ERR_READ_ONLY;             }
    else if (error_muk == MUK_ERR_RMA_ATTACH             ) { return MPI_ERR_RMA_ATTACH;            }
    else if (error_muk == MUK_ERR_RMA_CONFLICT           ) { return MPI_ERR_RMA_CONFLICT;          }
    else if (error_muk == MUK_ERR_RMA_RANGE              ) { return MPI_ERR_RMA_RANGE;             }
    else if (error_muk == MUK_ERR_RMA_SHARED             ) { return MPI_ERR_RMA_SHARED;            }
    else if (error_muk == MUK_ERR_RMA_SYNC               ) { return MPI_ERR_RMA_SYNC;              }
    else if (error_muk == MUK_ERR_RMA_FLAVOR             ) { return MPI_ERR_RMA_FLAVOR;            }
    else if (error_muk == MUK_ERR_SERVICE                ) { return MPI_ERR_SERVICE;               }
#if (MPI_VERSION >= 4)
    else if (error_muk == MUK_ERR_SESSION                ) { return MPI_ERR_SESSION;               }
#endif
    else if (error_muk == MUK_ERR_SIZE                   ) { return MPI_ERR_SIZE;                  }
    else if (error_muk == MUK_ERR_SPAWN                  ) { return MPI_ERR_SPAWN;                 }
    else if (error_muk == MUK_ERR_UNSUPPORTED_DATAREP    ) { return MPI_ERR_UNSUPPORTED_DATAREP;   }
    else if (error_muk == MUK_ERR_UNSUPPORTED_OPERATION  ) { return MPI_ERR_UNSUPPORTED_OPERATION; }
#if (MPI_VERSION >= 4)
    else if (error_muk == MUK_ERR_VALUE_TOO_LARGE        ) { return MPI_ERR_VALUE_TOO_LARGE;       }
#endif
    else if (error_muk == MUK_ERR_WIN                    ) { return MPI_ERR_WIN;                   }
    else if (error_muk == MUK_T_ERR_CANNOT_INIT          ) { return MPI_T_ERR_CANNOT_INIT;         }
    //else if (error_muk == MUK_T_ERR_NOT_ACCESSIBLE       ) { return MPI_T_ERR_NOT_ACCESSIBLE;      }
    else if (error_muk == MUK_T_ERR_NOT_INITIALIZED      ) { return MPI_T_ERR_NOT_INITIALIZED;     }
#if (MPI_VERSION >= 4)
    else if (error_muk == MUK_T_ERR_NOT_SUPPORTED        ) { return MPI_T_ERR_NOT_SUPPORTED;       }
#endif
    else if (error_muk == MUK_T_ERR_MEMORY               ) { return MPI_T_ERR_MEMORY;              }
    else if (error_muk == MUK_T_ERR_INVALID              ) { return MPI_T_ERR_INVALID;             }
    else if (error_muk == MUK_T_ERR_INVALID_INDEX        ) { return MPI_T_ERR_INVALID_INDEX;       }
    else if (error_muk == MUK_T_ERR_INVALID_ITEM         ) { return MPI_T_ERR_INVALID_ITEM;        }
    else if (error_muk == MUK_T_ERR_INVALID_SESSION      ) { return MPI_T_ERR_INVALID_SESSION;     }
    else if (error_muk == MUK_T_ERR_INVALID_HANDLE       ) { return MPI_T_ERR_INVALID_HANDLE;      }
    else if (error_muk == MUK_T_ERR_INVALID_NAME         ) { return MPI_T_ERR_INVALID_NAME;        }
    else if (error_muk == MUK_T_ERR_OUT_OF_HANDLES       ) { return MPI_T_ERR_OUT_OF_HANDLES;      }
    else if (error_muk == MUK_T_ERR_OUT_OF_SESSIONS      ) { return MPI_T_ERR_OUT_OF_SESSIONS;     }
    else if (error_muk == MUK_T_ERR_CVAR_SET_NOT_NOW     ) { return MPI_T_ERR_CVAR_SET_NOT_NOW;    }
    else if (error_muk == MUK_T_ERR_CVAR_SET_NEVER       ) { return MPI_T_ERR_CVAR_SET_NEVER;      }
    else if (error_muk == MUK_T_ERR_PVAR_NO_WRITE        ) { return MPI_T_ERR_PVAR_NO_WRITE;       }
    else if (error_muk == MUK_T_ERR_PVAR_NO_STARTSTOP    ) { return MPI_T_ERR_PVAR_NO_STARTSTOP;   }
    else if (error_muk == MUK_T_ERR_PVAR_NO_ATOMIC       ) { return MPI_T_ERR_PVAR_NO_ATOMIC;      }
    else if (error_muk == MUK_ERR_LASTCODE               ) { return MPI_ERR_LASTCODE;              }
    else {
        //fprintf(stderr, "Unknown error code returned from the F library: %d\n", error_muk);
        return MPI_ERR_UNKNOWN;
    }
}

static int COMBINER_CODE_IMPL_TO_MUK(int in)
{
         if (in == MPI_COMBINER_CONTIGUOUS)     { return MUK_COMBINER_CONTIGUOUS; }
    else if (in == MPI_COMBINER_DARRAY)         { return MUK_COMBINER_DARRAY; }
    else if (in == MPI_COMBINER_DUP)            { return MUK_COMBINER_DUP; }
    else if (in == MPI_COMBINER_F90_COMPLEX)    { return MUK_COMBINER_F90_COMPLEX; }
    else if (in == MPI_COMBINER_F90_INTEGER)    { return MUK_COMBINER_F90_INTEGER; }
    else if (in == MPI_COMBINER_F90_REAL)       { return MUK_COMBINER_F90_REAL; }
    else if (in == MPI_COMBINER_HINDEXED)       { return MUK_COMBINER_HINDEXED; }
    else if (in == MPI_COMBINER_HVECTOR)        { return MUK_COMBINER_HVECTOR; }
    else if (in == MPI_COMBINER_INDEXED_BLOCK)  { return MUK_COMBINER_INDEXED_BLOCK; }
    else if (in == MPI_COMBINER_HINDEXED_BLOCK) { return MUK_COMBINER_HINDEXED_BLOCK; }
    else if (in == MPI_COMBINER_INDEXED)        { return MUK_COMBINER_INDEXED; }
    else if (in == MPI_COMBINER_NAMED)          { return MUK_COMBINER_NAMED; }
    else if (in == MPI_COMBINER_RESIZED)        { return MUK_COMBINER_RESIZED; }
    else if (in == MPI_COMBINER_STRUCT)         { return MUK_COMBINER_STRUCT; }
    else if (in == MPI_COMBINER_SUBARRAY)       { return MUK_COMBINER_SUBARRAY; }
    else if (in == MPI_COMBINER_VECTOR)         { return MUK_COMBINER_VECTOR; }
    else                                        { return MUK_UNDEFINED; }
}

//static inline int TAG_MUK_TO_IMPL(int tag_muk)
#define TAG_MUK_TO_IMPL(tag) (tag)

static inline int RANK_MUK_TO_IMPL(int rank_muk)
{
    // predefined constants are always negative
    if (rank_muk >= 0) {
        return rank_muk;
    }
    else if (rank_muk == MUK_ANY_SOURCE) {
        return MPI_ANY_SOURCE;
    }
    else if (rank_muk == MUK_PROC_NULL) {
        return MPI_PROC_NULL;
    }
    // this one only applies to intercomms
    else if (rank_muk == MUK_ROOT) {
        return MPI_ROOT;
    }
    else {
#if 1
        printf("RANK_MUK_TO_IMPL rank=%d\n", rank_muk);
#endif
        return rank_muk;
    }
}

// mode constant conversion - this needs to handle multiple modes OR-ed together
static int IO_MODE_MUK_TO_IMPL(int mode_muk)
{
    int mode_impl = 0;
    if (mode_muk & MUK_MODE_APPEND)          { mode_impl |= MPI_MODE_APPEND; }
    if (mode_muk & MUK_MODE_CREATE)          { mode_impl |= MPI_MODE_CREATE; }
    if (mode_muk & MUK_MODE_DELETE_ON_CLOSE) { mode_impl |= MPI_MODE_DELETE_ON_CLOSE; }
    if (mode_muk & MUK_MODE_EXCL)            { mode_impl |= MPI_MODE_EXCL; }
    if (mode_muk & MUK_MODE_RDONLY)          { mode_impl |= MPI_MODE_RDONLY; }
    if (mode_muk & MUK_MODE_RDWR)            { mode_impl |= MPI_MODE_RDWR; }
    if (mode_muk & MUK_MODE_SEQUENTIAL)      { mode_impl |= MPI_MODE_SEQUENTIAL; }
    if (mode_muk & MUK_MODE_UNIQUE_OPEN)     { mode_impl |= MPI_MODE_UNIQUE_OPEN; }
    if (mode_muk & MUK_MODE_WRONLY)          { mode_impl |= MPI_MODE_WRONLY; }
    return mode_impl;
}

static int IO_MODE_IMPL_TO_MUK(int mode_impl)
{
    int mode_muk = 0;
    if (mode_impl & MUK_MODE_APPEND)          { mode_muk |= MPI_MODE_APPEND; }
    if (mode_impl & MUK_MODE_CREATE)          { mode_muk |= MPI_MODE_CREATE; }
    if (mode_impl & MUK_MODE_DELETE_ON_CLOSE) { mode_muk |= MPI_MODE_DELETE_ON_CLOSE; }
    if (mode_impl & MUK_MODE_EXCL)            { mode_muk |= MPI_MODE_EXCL; }
    if (mode_impl & MUK_MODE_RDONLY)          { mode_muk |= MPI_MODE_RDONLY; }
    if (mode_impl & MUK_MODE_RDWR)            { mode_muk |= MPI_MODE_RDWR; }
    if (mode_impl & MUK_MODE_SEQUENTIAL)      { mode_muk |= MPI_MODE_SEQUENTIAL; }
    if (mode_impl & MUK_MODE_UNIQUE_OPEN)     { mode_muk |= MPI_MODE_UNIQUE_OPEN; }
    if (mode_impl & MUK_MODE_WRONLY)          { mode_muk |= MPI_MODE_WRONLY; }
    return mode_muk;
}

// mode constant conversion - this needs to handle multiple modes OR-ed together
static int RMA_MODE_MUK_TO_IMPL(int mode_muk)
{
    int mode_impl = 0;
    if (mode_muk & MUK_MODE_NOCHECK)         { mode_impl |= MPI_MODE_NOCHECK; }
    if (mode_muk & MUK_MODE_NOPRECEDE)       { mode_impl |= MPI_MODE_NOPRECEDE; }
    if (mode_muk & MUK_MODE_NOPUT)           { mode_impl |= MPI_MODE_NOPUT; }
    if (mode_muk & MUK_MODE_NOSTORE)         { mode_impl |= MPI_MODE_NOSTORE; }
    if (mode_muk & MUK_MODE_NOSUCCEED)       { mode_impl |= MPI_MODE_NOSUCCEED; }
    return mode_impl;
}

// predefined attribute conversion
static int KEY_MUK_TO_IMPL(int key_muk)
{
         if (key_muk == MUK_TAG_UB)            { return MPI_TAG_UB; }
    else if (key_muk == MUK_IO)                { return MPI_IO; }
    else if (key_muk == MUK_HOST)              { return MPI_HOST; }
    else if (key_muk == MUK_WTIME_IS_GLOBAL)   { return MPI_WTIME_IS_GLOBAL; }
    else if (key_muk == MUK_APPNUM)            { return MPI_APPNUM; }
    else if (key_muk == MUK_LASTUSEDCODE)      { return MPI_LASTUSEDCODE; }
    else if (key_muk == MUK_UNIVERSE_SIZE)     { return MPI_UNIVERSE_SIZE; }
    else if (key_muk == MUK_WIN_BASE)          { return MPI_WIN_BASE; }
    else if (key_muk == MUK_WIN_DISP_UNIT)     { return MPI_WIN_DISP_UNIT; }
    else if (key_muk == MUK_WIN_SIZE)          { return MPI_WIN_SIZE; }
    else if (key_muk == MUK_WIN_CREATE_FLAVOR) { return MPI_WIN_CREATE_FLAVOR; }
    else if (key_muk == MUK_WIN_MODEL)         { return MPI_WIN_MODEL; }
    else                                       { return key_muk; }
}
#endif
