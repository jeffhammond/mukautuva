# Mukautuva lookup requirements

Goal:

A container C that satisfies the following:

```c++
// input = K and V
// return (0/1) = whether the K was new and added or existing and the value overwritten
C.add_or_replace(Keytype K, Valuetype V);
```

```c++
// input = remove, which indicates whether or not the KV should be removed or not.
// input = K
// output = V
// return = found (boolean), which indicates whether or not the value was found.
found = C.fetch_value(remove, Keytype K, Valuetype & V);
```

```c++
// input = K
C.remove(Keytype K);
```

where

- Keytype is either an `int` or a `intptr_t`.  Keys are unique.
- Valuetype is either a pointer or a pair of pointers; memory blocks of 8 or 16 bytes are sufficient.

`C.add_or_replace` can be as expensive as necessary.
`C.fetch_value` must be as fast as possible when `K` is _not_ in `C`; the speed on hits matters less.

The size of C is likely to be small (less than 20 members) but is permitted to be arbitrarily large in pathological cases.

`C.fetch_value` may be called hundreds or thousands of times in a loop where most or all of the `K` are not in `C`.
It would be ideal to optimize for this scenario, with an interface that takes a vector of `Keytype` if necessary.

The following a C-compatible API prototype for such a function:
```c++
// input = remove, which indicates whether or not the KVs should be removed or not.
// input = key_count, the size of K[]
// input = K[], a vector of keys
// input = value_count, the length of V[], i.e. the maximum number of keys that should be found before the method returns
// output = V[], a vector of values the length of K[]
// return = found_count, indicates how many values were found and can be read from V[]
found_count = C.fetch_value_many(remove, key_count, Keytype K[], value_count, Valuetype & V[]);
```
