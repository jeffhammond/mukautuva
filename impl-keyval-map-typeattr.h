int add_type_keyval_callbacks(int keyval,
                              WRAP_Type_copy_attr_function   * type_copy_attr_fn,
                              WRAP_Type_delete_attr_function * type_delete_attr_fn)
{
#if DEBUG
    printf("%s: insert_or_assign(keyval=%d, type_copy_attr_fn=%p, type_delete_attr_fn=%p)\n",
            __func__, keyval, type_copy_attr_fn, type_delete_attr_fn);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = keyval_type_attr_cb_map.insert_or_assign(keyval,
                                                            std::make_pair(type_copy_attr_fn,
                                                                           type_delete_attr_fn));
    return int{rc};
}

int find_type_keyval_callbacks(int keyval,
                               WRAP_Type_copy_attr_function   ** type_copy_attr_fn,
                               WRAP_Type_delete_attr_function ** type_delete_attr_fn)
{
    try {
        auto [copy_fn,delete_fn] = keyval_type_attr_cb_map.at(keyval);
#if DEBUG
        printf("%s: lookup(keyval=%d) -> [type_copy_attr_fn=%p, type_delete_attr_fn=%p]\n",
                __func__, keyval, copy_fn, delete_fn);
#endif
        if (type_copy_attr_fn != NULL) {
            *type_copy_attr_fn = copy_fn;
        }
        if (type_delete_attr_fn != NULL) {
            *type_delete_attr_fn = delete_fn;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(keyval=%d) failed\n", __func__, keyval);
        return 0;
    }
}

int remove_type_keyval_callbacks(int keyval)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return keyval_type_attr_cb_map.erase(keyval);
}
