int add_file_errhandler_callback_2(MPI_File file, WRAP_File_errhandler_function * user_fn)
{
    const std::lock_guard<std::mutex> lock(file_errhandler_cb_mutex);
#if DEBUG
    printf("%s: insert_or_assign(file=%lx, user_fn=%p)\n",
            __func__, (intptr_t)file, user_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = file_errhandler_cb_map.insert_or_assign(file, user_fn);
    return 1; // SUCCESS int{rc};
    (void)it;
    (void)rc;
}

int find_file_errhandler_callback_2(MPI_File file, WRAP_File_errhandler_function ** user_fn)
{
    const std::lock_guard<std::mutex> lock(file_errhandler_cb_mutex);
    try {
        auto fn = file_errhandler_cb_map.at(file);
#if DEBUG
        printf("%s: lookup(file=%lx) -> user_fn=%p\n",
                __func__, (intptr_t)file, user_fn);
#endif
        if (fn != NULL) {
            *user_fn = fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(file=%lx) failed\n", __func__, (intptr_t)file);
        return 0;
    }
}

int remove_file_errhandler_callback_2(MPI_File file)
{
    const std::lock_guard<std::mutex> lock(file_errhandler_cb_mutex);
    // returns the number of elements removed, so 0=failure and 1=success
    return file_errhandler_cb_map.erase(file);
}
