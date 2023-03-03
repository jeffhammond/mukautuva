int add_comm_keyval_callbacks(int keyval,
                              WRAP_Comm_copy_attr_function   * comm_copy_attr_fn,
                              WRAP_Comm_delete_attr_function * comm_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, comm_copy_attr_fn=%p, comm_delete_attr_fn=%p)\n",
            __func__, keyval, comm_copy_attr_fn, comm_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_comm_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(comm_copy_attr_fn,
                                                                           comm_delete_attr_fn));
    return int{rc};
}

int find_comm_keyval_callbacks(int keyval,
                               WRAP_Comm_copy_attr_function   ** comm_copy_attr_fn,
                               WRAP_Comm_delete_attr_function ** comm_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_comm_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [comm_copy_attr_fn=%p, comm_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (comm_copy_attr_fn != NULL) {
            *comm_copy_attr_fn = copy_fn;
        }
        if (comm_delete_attr_fn != NULL) {
            *comm_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_comm_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_comm_attr_cb_map.erase(keyval);
}
