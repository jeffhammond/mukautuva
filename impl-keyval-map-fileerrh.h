// SPDX-License-Identifier: MIT

int add_file_errhandler_callback(MPI_Errhandler errhandler, WRAP_File_errhandler_function * user_fn)
{
    const std::lock_guard<std::mutex> lock(errhandler_file_cb_mutex);
#if DEBUG
    printf("%s: insert_or_assign(errhandler=%lx, user_fn=%p)\n",
            __func__, (intptr_t)errhandler, user_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = errhandler_file_cb_map.insert_or_assign(errhandler, user_fn);
    return 1; // SUCCESS int{rc};
    (void)it;
    (void)rc;
}

int find_file_errhandler_callback(MPI_Errhandler errhandler, WRAP_File_errhandler_function ** user_fn)
{
    const std::lock_guard<std::mutex> lock(errhandler_file_cb_mutex);
    try {
        auto fn = errhandler_file_cb_map.at(errhandler);
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

int remove_file_errhandler_callback(MPI_Errhandler errhandler)
{
    const std::lock_guard<std::mutex> lock(errhandler_file_cb_mutex);
    // returns the number of elements removed, so 0=failure and 1=success
    return errhandler_file_cb_map.erase(errhandler);
}
