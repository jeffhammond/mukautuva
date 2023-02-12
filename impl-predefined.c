#include <stdio.h>
#include <mpi.h>
#include "muk-predefined.h"

// This file captures all of the predefined handles
// so that they can be referenced by dlsym, since
// this is not necessarily possible.
//
// MPICH, for example, defines predefined handles in
// the preprocessor, which means there are no symbols
// in the MPICH shared library.

// error codes
int IMPL_SUCCESS = MPI_SUCCESS;
int IMPL_ERR_BUFFER = MPI_ERR_BUFFER;
int IMPL_ERR_COUNT = MPI_ERR_COUNT;
int IMPL_ERR_TYPE = MPI_ERR_TYPE;
int IMPL_ERR_TAG = MPI_ERR_TAG;
int IMPL_ERR_COMM = MPI_ERR_COMM;
int IMPL_ERR_RANK = MPI_ERR_RANK;
int IMPL_ERR_REQUEST = MPI_ERR_REQUEST;
int IMPL_ERR_ROOT = MPI_ERR_ROOT;
int IMPL_ERR_GROUP = MPI_ERR_GROUP;
int IMPL_ERR_OP = MPI_ERR_OP;
int IMPL_ERR_TOPOLOGY = MPI_ERR_TOPOLOGY;
int IMPL_ERR_DIMS = MPI_ERR_DIMS;
int IMPL_ERR_ARG = MPI_ERR_ARG;
int IMPL_ERR_UNKNOWN = MPI_ERR_UNKNOWN;
int IMPL_ERR_TRUNCATE = MPI_ERR_TRUNCATE;
int IMPL_ERR_OTHER = MPI_ERR_OTHER;
int IMPL_ERR_INTERN = MPI_ERR_INTERN;
int IMPL_ERR_PENDING = MPI_ERR_PENDING;
int IMPL_ERR_IN_STATUS = MPI_ERR_IN_STATUS;
int IMPL_ERR_ACCESS = MPI_ERR_ACCESS;
int IMPL_ERR_AMODE = MPI_ERR_AMODE;
int IMPL_ERR_ASSERT = MPI_ERR_ASSERT;
int IMPL_ERR_BAD_FILE = MPI_ERR_BAD_FILE;
int IMPL_ERR_BASE = MPI_ERR_BASE;
int IMPL_ERR_CONVERSION = MPI_ERR_CONVERSION;
int IMPL_ERR_DISP = MPI_ERR_DISP;
int IMPL_ERR_DUP_DATAREP = MPI_ERR_DUP_DATAREP;
int IMPL_ERR_FILE_EXISTS = MPI_ERR_FILE_EXISTS;
int IMPL_ERR_FILE_IN_USE = MPI_ERR_FILE_IN_USE;
int IMPL_ERR_FILE = MPI_ERR_FILE;
int IMPL_ERR_INFO_KEY = MPI_ERR_INFO_KEY;
int IMPL_ERR_INFO_NOKEY = MPI_ERR_INFO_NOKEY;
int IMPL_ERR_INFO_VALUE = MPI_ERR_INFO_VALUE;
int IMPL_ERR_INFO = MPI_ERR_INFO;
int IMPL_ERR_IO = MPI_ERR_IO;
int IMPL_ERR_KEYVAL = MPI_ERR_KEYVAL;
int IMPL_ERR_LOCKTYPE = MPI_ERR_LOCKTYPE;
int IMPL_ERR_NAME = MPI_ERR_NAME;
int IMPL_ERR_NO_MEM = MPI_ERR_NO_MEM;
int IMPL_ERR_NOT_SAME = MPI_ERR_NOT_SAME;
int IMPL_ERR_NO_SPACE = MPI_ERR_NO_SPACE;
int IMPL_ERR_NO_SUCH_FILE = MPI_ERR_NO_SUCH_FILE;
int IMPL_ERR_PORT = MPI_ERR_PORT;
#if MPI_VERSION >= 4
int IMPL_ERR_PROC_ABORTED = MPI_ERR_PROC_ABORTED;
#endif
int IMPL_ERR_QUOTA = MPI_ERR_QUOTA;
int IMPL_ERR_READ_ONLY = MPI_ERR_READ_ONLY;
int IMPL_ERR_RMA_ATTACH = MPI_ERR_RMA_ATTACH;
int IMPL_ERR_RMA_CONFLICT = MPI_ERR_RMA_CONFLICT;
int IMPL_ERR_RMA_RANGE = MPI_ERR_RMA_RANGE;
int IMPL_ERR_RMA_SHARED = MPI_ERR_RMA_SHARED;
int IMPL_ERR_RMA_SYNC = MPI_ERR_RMA_SYNC;
int IMPL_ERR_RMA_FLAVOR = MPI_ERR_RMA_FLAVOR;
int IMPL_ERR_SERVICE = MPI_ERR_SERVICE;
#if MPI_VERSION >= 4
int IMPL_ERR_SESSION = MPI_ERR_SESSION;
#endif
int IMPL_ERR_SIZE = MPI_ERR_SIZE;
int IMPL_ERR_SPAWN = MPI_ERR_SPAWN;
int IMPL_ERR_UNSUPPORTED_DATAREP = MPI_ERR_UNSUPPORTED_DATAREP;
int IMPL_ERR_UNSUPPORTED_OPERATION = MPI_ERR_UNSUPPORTED_OPERATION;
#if MPI_VERSION >= 4
int IMPL_ERR_VALUE_TOO_LARGE = MPI_ERR_VALUE_TOO_LARGE;
#endif
int IMPL_ERR_WIN = MPI_ERR_WIN;
int IMPL_T_ERR_CANNOT_INIT = MPI_T_ERR_CANNOT_INIT;
#if 0
int IMPL_T_ERR_NOT_ACCESSIBLE = MPI_T_ERR_NOT_ACCESSIBLE;
#endif
int IMPL_T_ERR_NOT_INITIALIZED = MPI_T_ERR_NOT_INITIALIZED;
#if MPI_VERSION >= 4
int IMPL_T_ERR_NOT_SUPPORTED = MPI_T_ERR_NOT_SUPPORTED;
#endif
int IMPL_T_ERR_MEMORY = MPI_T_ERR_MEMORY;
int IMPL_T_ERR_INVALID = MPI_T_ERR_INVALID;
int IMPL_T_ERR_INVALID_INDEX = MPI_T_ERR_INVALID_INDEX;
int IMPL_T_ERR_INVALID_ITEM = MPI_T_ERR_INVALID_ITEM;
int IMPL_T_ERR_INVALID_SESSION = MPI_T_ERR_INVALID_SESSION;
int IMPL_T_ERR_INVALID_HANDLE = MPI_T_ERR_INVALID_HANDLE;
int IMPL_T_ERR_INVALID_NAME = MPI_T_ERR_INVALID_NAME;
int IMPL_T_ERR_OUT_OF_HANDLES = MPI_T_ERR_OUT_OF_HANDLES;
int IMPL_T_ERR_OUT_OF_SESSIONS = MPI_T_ERR_OUT_OF_SESSIONS;
int IMPL_T_ERR_CVAR_SET_NOT_NOW = MPI_T_ERR_CVAR_SET_NOT_NOW;
int IMPL_T_ERR_CVAR_SET_NEVER = MPI_T_ERR_CVAR_SET_NEVER;
int IMPL_T_ERR_PVAR_NO_WRITE = MPI_T_ERR_PVAR_NO_WRITE;
int IMPL_T_ERR_PVAR_NO_STARTSTOP = MPI_T_ERR_PVAR_NO_STARTSTOP;
int IMPL_T_ERR_PVAR_NO_ATOMIC = MPI_T_ERR_PVAR_NO_ATOMIC;
int IMPL_ERR_LASTCODE = MPI_ERR_LASTCODE;

// declaration for impl-functions.c symbol
extern int (*IMPL_Finalized)(int * finalized);
extern int (*IMPL_Error_class)(int errorcode, int *errorclass);

int ERROR_CODE_IMPL_TO_MUK(int error_c)
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
        MUK_Warning("Unknown error class returned from the C library: code=%d=%x, class=%d=%x, name=%s\n",
                     error_c, error_c, error, error, name);
#endif
        return MUK_ERR_UNKNOWN;
    }
}

int ERROR_CODE_MUK_TO_IMPL(int error_muk)
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

// Buffer Address Constants
void * IMPL_BOTTOM = MPI_BOTTOM;
void * IMPL_IN_PLACE = MPI_IN_PLACE;

// Assorted Constants
int IMPL_PROC_NULL = MPI_PROC_NULL;
int IMPL_ANY_SOURCE = MPI_ANY_SOURCE;
int IMPL_ROOT = MPI_ROOT;
int IMPL_ANY_TAG = MPI_ANY_TAG;
int IMPL_UNDEFINED = MPI_UNDEFINED;
int IMPL_BSEND_OVERHEAD = MPI_BSEND_OVERHEAD;
int IMPL_KEYVAL_INVALID = MPI_KEYVAL_INVALID;
int IMPL_LOCK_EXCLUSIVE = MPI_LOCK_EXCLUSIVE;
int IMPL_LOCK_SHARED = MPI_LOCK_SHARED;

// No Process Message Handle
MPI_Message IMPL_MESSAGE_NO_PROC = MPI_MESSAGE_NO_PROC;

#if 0
//Fortran status array size and reserved index values (C only)
int IMPL_F_STATUS_SIZE = MPI_F_STATUS_SIZE;
int IMPL_F_SOURCE      = MPI_F_SOURCE;
int IMPL_F_TAG         = MPI_F_TAG;
int IMPL_F_ERROR       = MPI_F_ERROR;
int IMPL_ADDRESS_KIND = MPI_ADDRESS_KIND;
int IMPL_COUNT_KIND = MPI_COUNT_KIND;
int IMPL_INTEGER_KIND = MPI_INTEGER_KIND;
int IMPL_OFFSET_KIND = MPI_OFFSET_KIND;
#endif

// Error-handling specifiers
MPI_Errhandler IMPL_ERRORS_ARE_FATAL = MPI_ERRORS_ARE_FATAL;
#if MPI_VERSION >= 4
MPI_Errhandler IMPL_ERRORS_ABORT     = MPI_ERRORS_ABORT;
#endif
MPI_Errhandler IMPL_ERRORS_RETURN    = MPI_ERRORS_RETURN;

// Named Predefined Datatypes
MPI_Datatype IMPL_CHAR = MPI_CHAR;
MPI_Datatype IMPL_SHORT = MPI_SHORT;
MPI_Datatype IMPL_INT = MPI_INT;
MPI_Datatype IMPL_LONG = MPI_LONG;
MPI_Datatype IMPL_LONG_LONG_INT = MPI_LONG_LONG_INT;
MPI_Datatype IMPL_LONG_LONG = MPI_LONG_LONG;
MPI_Datatype IMPL_SIGNED_CHAR = MPI_SIGNED_CHAR;
MPI_Datatype IMPL_UNSIGNED_CHAR = MPI_UNSIGNED_CHAR;
MPI_Datatype IMPL_UNSIGNED_SHORT = MPI_UNSIGNED_SHORT;
MPI_Datatype IMPL_UNSIGNED = MPI_UNSIGNED;
MPI_Datatype IMPL_UNSIGNED_LONG = MPI_UNSIGNED_LONG;
MPI_Datatype IMPL_UNSIGNED_LONG_LONG = MPI_UNSIGNED_LONG_LONG;
MPI_Datatype IMPL_FLOAT = MPI_FLOAT;
MPI_Datatype IMPL_DOUBLE = MPI_DOUBLE;
MPI_Datatype IMPL_LONG_DOUBLE = MPI_LONG_DOUBLE;
MPI_Datatype IMPL_WCHAR = MPI_WCHAR;
MPI_Datatype IMPL_C_BOOL = MPI_C_BOOL;

MPI_Datatype IMPL_INT8_T = MPI_INT8_T;
MPI_Datatype IMPL_INT16_T = MPI_INT16_T;
MPI_Datatype IMPL_INT32_T = MPI_INT32_T;
MPI_Datatype IMPL_INT64_T = MPI_INT64_T;
MPI_Datatype IMPL_UINT8_T = MPI_UINT8_T;
MPI_Datatype IMPL_UINT16_T = MPI_UINT16_T;
MPI_Datatype IMPL_UINT32_T = MPI_UINT32_T;
MPI_Datatype IMPL_UINT64_T = MPI_UINT64_T;
MPI_Datatype IMPL_AINT = MPI_AINT;
MPI_Datatype IMPL_COUNT = MPI_COUNT;
MPI_Datatype IMPL_OFFSET = MPI_OFFSET;
MPI_Datatype IMPL_C_COMPLEX = MPI_C_COMPLEX;
MPI_Datatype IMPL_C_FLOAT_COMPLEX = MPI_C_FLOAT_COMPLEX;
MPI_Datatype IMPL_C_DOUBLE_COMPLEX = MPI_C_DOUBLE_COMPLEX;
MPI_Datatype IMPL_C_LONG_DOUBLE_COMPLEX = MPI_C_LONG_DOUBLE_COMPLEX;

MPI_Datatype IMPL_BYTE = MPI_BYTE;
MPI_Datatype IMPL_PACKED = MPI_PACKED;

MPI_Datatype IMPL_INTEGER = MPI_INTEGER;
MPI_Datatype IMPL_REAL = MPI_REAL;
MPI_Datatype IMPL_DOUBLE_PRECISION = MPI_DOUBLE_PRECISION;
MPI_Datatype IMPL_COMPLEX = MPI_COMPLEX;
MPI_Datatype IMPL_LOGICAL = MPI_LOGICAL;
MPI_Datatype IMPL_CHARACTER = MPI_CHARACTER;

MPI_Datatype IMPL_CXX_BOOL = MPI_CXX_BOOL;
MPI_Datatype IMPL_CXX_FLOAT_COMPLEX = MPI_CXX_FLOAT_COMPLEX;
MPI_Datatype IMPL_CXX_DOUBLE_COMPLEX = MPI_CXX_DOUBLE_COMPLEX;
MPI_Datatype IMPL_CXX_LONG_DOUBLE_COMPLEX = MPI_CXX_LONG_DOUBLE_COMPLEX;

#if 0
MPI_Datatype IMPL_DOUBLE_COMPLEX = MPI_DOUBLE_COMPLEX;
MPI_Datatype IMPL_INTEGER1 = MPI_INTEGER1;
MPI_Datatype IMPL_INTEGER2 = MPI_INTEGER2;
MPI_Datatype IMPL_INTEGER4 = MPI_INTEGER4;
MPI_Datatype IMPL_INTEGER8 = MPI_INTEGER8;
MPI_Datatype IMPL_INTEGER16 = MPI_INTEGER16;
MPI_Datatype IMPL_REAL2 = MPI_REAL2;
MPI_Datatype IMPL_REAL4 = MPI_REAL4;
MPI_Datatype IMPL_REAL8 = MPI_REAL8;
MPI_Datatype IMPL_REAL16 = MPI_REAL16;
MPI_Datatype IMPL_COMPLEX4 = MPI_COMPLEX4;
MPI_Datatype IMPL_COMPLEX8 = MPI_COMPLEX8;
MPI_Datatype IMPL_COMPLEX16 = MPI_COMPLEX16;
MPI_Datatype IMPL_COMPLEX32 = MPI_COMPLEX32;
#endif

MPI_Datatype IMPL_FLOAT_INT = MPI_FLOAT_INT;
MPI_Datatype IMPL_DOUBLE_INT = MPI_DOUBLE_INT;
MPI_Datatype IMPL_LONG_INT = MPI_LONG_INT;
MPI_Datatype IMPL_2INT = MPI_2INT;
MPI_Datatype IMPL_SHORT_INT = MPI_SHORT_INT;
MPI_Datatype IMPL_LONG_DOUBLE_INT = MPI_LONG_DOUBLE_INT;

MPI_Datatype IMPL_2REAL = MPI_2REAL;
MPI_Datatype IMPL_2DOUBLE_PRECISION = MPI_2DOUBLE_PRECISION;
MPI_Datatype IMPL_2INTEGER = MPI_2INTEGER;

// Reserved communicators
MPI_Comm IMPL_COMM_WORLD = MPI_COMM_WORLD;
MPI_Comm IMPL_COMM_SELF  = MPI_COMM_SELF;

// Communicator split type constants
int IMPL_COMM_TYPE_SHARED = MPI_COMM_TYPE_SHARED;
#if MPI_VERSION >= 4
int IMPL_COMM_TYPE_HW_UNGUIDED = MPI_COMM_TYPE_HW_UNGUIDED;
int IMPL_COMM_TYPE_HW_GUIDED = MPI_COMM_TYPE_HW_GUIDED;
#endif

// Results of communicator and group comparisons
int IMPL_IDENT = MPI_IDENT;
int IMPL_CONGRUENT = MPI_CONGRUENT;
int IMPL_SIMILAR = MPI_SIMILAR;
int IMPL_UNEQUAL = MPI_UNEQUAL;

// Environmental inquiry info key
MPI_Info IMPL_INFO_ENV = MPI_INFO_ENV;

// Environmental inquiry keys
int IMPL_TAG_UB = MPI_TAG_UB;
int IMPL_IO = MPI_IO;
int IMPL_HOST = MPI_HOST;
int IMPL_WTIME_IS_GLOBAL = MPI_WTIME_IS_GLOBAL;

// Collective Operations
MPI_Op IMPL_MAX = MPI_MAX;
MPI_Op IMPL_MIN = MPI_MIN;
MPI_Op IMPL_SUM = MPI_SUM;
MPI_Op IMPL_PROD = MPI_PROD;
MPI_Op IMPL_LAND = MPI_LAND;
MPI_Op IMPL_BAND = MPI_BAND;
MPI_Op IMPL_LOR = MPI_LOR;
MPI_Op IMPL_BOR = MPI_BOR;
MPI_Op IMPL_LXOR = MPI_LXOR;
MPI_Op IMPL_BXOR = MPI_BXOR;
MPI_Op IMPL_MAXLOC = MPI_MAXLOC;
MPI_Op IMPL_MINLOC = MPI_MINLOC;
MPI_Op IMPL_REPLACE = MPI_REPLACE;
MPI_Op IMPL_NO_OP = MPI_NO_OP;

// Null Handles
MPI_Group IMPL_GROUP_NULL  = MPI_GROUP_NULL;
MPI_Comm IMPL_COMM_NULL  = MPI_COMM_NULL;
MPI_Datatype IMPL_DATATYPE_NULL = MPI_DATATYPE_NULL;
MPI_Request IMPL_REQUEST_NULL = MPI_REQUEST_NULL;
MPI_Op IMPL_OP_NULL = MPI_OP_NULL;
MPI_Errhandler IMPL_ERRHANDLER_NULL = MPI_ERRHANDLER_NULL;
MPI_File IMPL_FILE_NULL = MPI_FILE_NULL;
MPI_Info IMPL_INFO_NULL = MPI_INFO_NULL;
#if MPI_VERSION >= 4
MPI_Session IMPL_SESSION_NULL = MPI_SESSION_NULL;
#endif
MPI_Win IMPL_WIN_NULL =  MPI_WIN_NULL;
MPI_Message IMPL_MESSAGE_NULL = MPI_MESSAGE_NULL;

// Empty group
MPI_Group IMPL_GROUP_EMPTY = MPI_GROUP_EMPTY;

// Topologies
int IMPL_GRAPH = MPI_GRAPH;
int IMPL_CART = MPI_CART;
int IMPL_DIST_GRAPH = MPI_DIST_GRAPH;

// Predefined functions
// TODO
// Deprecated predefined functions
// TODO

// Predefined Attribute Keys
int IMPL_APPNUM = MPI_APPNUM;
int IMPL_LASTUSEDCODE = MPI_LASTUSEDCODE;
int IMPL_UNIVERSE_SIZE = MPI_UNIVERSE_SIZE;
int IMPL_WIN_BASE = MPI_WIN_BASE;
int IMPL_WIN_DISP_UNIT = MPI_WIN_DISP_UNIT;
int IMPL_WIN_SIZE = MPI_WIN_SIZE;
int IMPL_WIN_CREATE_FLAVOR = MPI_WIN_CREATE_FLAVOR;
int IMPL_WIN_MODEL = MPI_WIN_MODEL;

// MPI Window Create Flavors
int IMPL_WIN_FLAVOR_CREATE = MPI_WIN_FLAVOR_CREATE;
int IMPL_WIN_FLAVOR_ALLOCATE = MPI_WIN_FLAVOR_ALLOCATE;
int IMPL_WIN_FLAVOR_DYNAMIC = MPI_WIN_FLAVOR_DYNAMIC;
int IMPL_WIN_FLAVOR_SHARED = MPI_WIN_FLAVOR_SHARED;

// MPI Window Models
int IMPL_WIN_SEPARATE = MPI_WIN_SEPARATE;
int IMPL_WIN_UNIFIED = MPI_WIN_UNIFIED;
            
// Mode Constants
int IMPL_MODE_APPEND = MPI_MODE_APPEND;
int IMPL_MODE_CREATE = MPI_MODE_CREATE;
int IMPL_MODE_DELETE_ON_CLOSE = MPI_MODE_DELETE_ON_CLOSE;
int IMPL_MODE_EXCL = MPI_MODE_EXCL;
int IMPL_MODE_NOCHECK = MPI_MODE_NOCHECK;
int IMPL_MODE_NOPRECEDE = MPI_MODE_NOPRECEDE;
int IMPL_MODE_NOPUT = MPI_MODE_NOPUT;
int IMPL_MODE_NOSTORE = MPI_MODE_NOSTORE;
int IMPL_MODE_NOSUCCEED = MPI_MODE_NOSUCCEED;
int IMPL_MODE_RDONLY = MPI_MODE_RDONLY;
int IMPL_MODE_RDWR = MPI_MODE_RDWR;
int IMPL_MODE_SEQUENTIAL = MPI_MODE_SEQUENTIAL;
int IMPL_MODE_UNIQUE_OPEN = MPI_MODE_UNIQUE_OPEN;
int IMPL_MODE_WRONLY = MPI_MODE_WRONLY;

// Datatype Decoding Constants
int IMPL_COMBINER_CONTIGUOUS = MPI_COMBINER_CONTIGUOUS;
int IMPL_COMBINER_DARRAY = MPI_COMBINER_DARRAY;
int IMPL_COMBINER_DUP = MPI_COMBINER_DUP;
int IMPL_COMBINER_F90_COMPLEX = MPI_COMBINER_F90_COMPLEX;
int IMPL_COMBINER_F90_INTEGER = MPI_COMBINER_F90_INTEGER;
int IMPL_COMBINER_F90_REAL = MPI_COMBINER_F90_REAL;
int IMPL_COMBINER_HINDEXED = MPI_COMBINER_HINDEXED;
int IMPL_COMBINER_HVECTOR = MPI_COMBINER_HVECTOR;
int IMPL_COMBINER_INDEXED_BLOCK = MPI_COMBINER_INDEXED_BLOCK;
int IMPL_COMBINER_HINDEXED_BLOCK = MPI_COMBINER_HINDEXED_BLOCK;
int IMPL_COMBINER_INDEXED = MPI_COMBINER_INDEXED;
int IMPL_COMBINER_NAMED = MPI_COMBINER_NAMED;
int IMPL_COMBINER_RESIZED = MPI_COMBINER_RESIZED;
int IMPL_COMBINER_STRUCT = MPI_COMBINER_STRUCT;
int IMPL_COMBINER_SUBARRAY = MPI_COMBINER_SUBARRAY;
int IMPL_COMBINER_VECTOR = MPI_COMBINER_VECTOR;

int COMBINER_CODE_IMPL_TO_MUK(int in)
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

// Threads Constants
int IMPL_THREAD_FUNNELED = MPI_THREAD_FUNNELED;
int IMPL_THREAD_MULTIPLE = MPI_THREAD_MULTIPLE;
int IMPL_THREAD_SERIALIZED = MPI_THREAD_SERIALIZED;
int IMPL_THREAD_SINGLE = MPI_THREAD_SINGLE;

// File Operation Constants, Part 1
int IMPL_DISPLACEMENT_CURRENT = MPI_DISPLACEMENT_CURRENT;

// File Operation Constants, Part 2
int IMPL_DISTRIBUTE_BLOCK = MPI_DISTRIBUTE_BLOCK;
int IMPL_DISTRIBUTE_CYCLIC = MPI_DISTRIBUTE_CYCLIC;
int IMPL_DISTRIBUTE_DFLT_DARG = MPI_DISTRIBUTE_DFLT_DARG;
int IMPL_DISTRIBUTE_NONE = MPI_DISTRIBUTE_NONE;
int IMPL_ORDER_C = MPI_ORDER_C;
int IMPL_ORDER_FORTRAN = MPI_ORDER_FORTRAN;
int IMPL_SEEK_CUR = MPI_SEEK_CUR;
int IMPL_SEEK_END = MPI_SEEK_END;
int IMPL_SEEK_SET = MPI_SEEK_SET;

// F90 Datatype Matching Constants
int IMPL_TYPECLASS_COMPLEX = MPI_TYPECLASS_COMPLEX;
int IMPL_TYPECLASS_INTEGER = MPI_TYPECLASS_INTEGER;
int IMPL_TYPECLASS_REAL = MPI_TYPECLASS_REAL;

// Constants Specifying Empty or Ignored Input
char *** IMPL_ARGVS_NULL = MPI_ARGVS_NULL;
char ** IMPL_ARGV_NULL = MPI_ARGV_NULL;
int * IMPL_ERRCODES_IGNORE = MPI_ERRCODES_IGNORE;
MPI_Status * IMPL_STATUSES_IGNORE = MPI_STATUSES_IGNORE;
MPI_Status * IMPL_STATUS_IGNORE = MPI_STATUS_IGNORE;
#ifndef MPICH
int * IMPL_UNWEIGHTED = MPI_UNWEIGHTED;
int * IMPL_WEIGHTS_EMPTY = MPI_WEIGHTS_EMPTY;
#endif

