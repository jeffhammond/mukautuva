int add_win_keyval_callbacks(int keyval,
                              WRAP_Win_copy_attr_function   * win_copy_attr_fn,
                              WRAP_Win_delete_attr_function * win_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, win_copy_attr_fn=%p, win_delete_attr_fn=%p)\n",
            __func__, keyval, win_copy_attr_fn, win_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_win_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(win_copy_attr_fn,
                                                                           win_delete_attr_fn));
    return 1; // SUCCESS int{rc};
    (void)it;
    (void)rc;
}

int find_win_keyval_callbacks(int keyval,
                               WRAP_Win_copy_attr_function   ** win_copy_attr_fn,
                               WRAP_Win_delete_attr_function ** win_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_win_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [win_copy_attr_fn=%p, win_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (win_copy_attr_fn != NULL) {
            *win_copy_attr_fn = copy_fn;
        }
        if (win_delete_attr_fn != NULL) {
            *win_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_win_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_win_attr_cb_map.erase(keyval);
}
