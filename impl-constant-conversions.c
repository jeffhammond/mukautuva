#include <mpi.h>
#include "muk-predefined.h"

// declaration for impl-functions.c symbol
extern int (*IMPL_Error_class)(int errorcode, int *errorclass);

int ERROR_CODE_IMPL_TO_MUK(int error_c)
{
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
