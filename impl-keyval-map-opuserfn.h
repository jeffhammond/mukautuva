int add_comm_op_callback(MPI_Op op,
                         WRAP_User_function   * user_fn,
                         WRAP_User_function_c * user_fn_c)
{
#if DEBUG
    printf("%s: insert_or_assign(op=%lx, user_fn=%p, user_fn_c=%p)\n",
            __func__, (intptr_t)op, user_fn, user_fn_c);
#endif
    // insert_or_assign (C++17) inserts an element or assigns to the current element if the key already exists
    auto [it,rc] = op_user_function_map.insert_or_assign(op, std::make_pair(user_fn, user_fn_c));
    return int{rc};
}

int find_comm_op_callback(MPI_Op op,
                          WRAP_User_function   ** user_fn,
                          WRAP_User_function_c ** user_fn_c)
{
    try {
        auto [fn,fn_c] = op_user_function_map.at(op);
#if DEBUG
        printf("%s: lookup(op=%lx) -> [user_fn=%p, user_fn=%p]\n",
                __func__, (intptr_t)op, user_fn, user_fn_c);
#endif
        if (fn != NULL) {
            *user_fn = fn;
        }
        else if (fn_c != NULL) {
            *user_fn_c = fn_c;
        }
        return 1;
    }
    catch (...) {
        printf("%s: lookup(op=%lx) failed\n", __func__, (intptr_t)op);
        return 0;
    }
}

int remove_comm_op_callback(MPI_Op op)
{
    // returns the number of elements removed, so 0=failure and 1=success
    return op_user_function_map.erase(op);
}
