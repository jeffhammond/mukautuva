int add_win_errhandler_callback(MPI_Errhandler errhandler, WRAP_Win_errhandler_function * user_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(errhandler=%lx, user_fn=%p)\n",
            __func__, (intptr_t)errhandler, user_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = errhandler_win_cb_map.insert_or_assign(errhandler, user_fn);
    return int{rc};
}

int find_win_errhandler_callback(MPI_Errhandler errhandler, WRAP_Win_errhandler_function ** user_fn)
{
    try {
        auto fn = errhandler_win_cb_map.at(errhandler);
#if DEBUG
        printf("%s: lookup(errhandler=%lx) -> user_fn=%p\n",
                __func__, (intptr_t)errhandler, user_fn);
#endif
        if (fn != NULL) {
            *user_fn = fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(errhandler=%lx) failed\n", __func__, (intptr_t)errhandler);
        return 0;
    }
}

int remove_win_errhandler_callback(MPI_Errhandler errhandler)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return errhandler_win_cb_map.erase(errhandler);
}
