# libglaswegian

Use GHC's Memory Allocator from C/C++. Yes, I'm serious. You can do this:

```c++
#include <iostream>
#include <vector>

#include <glaswegian++.h>

#define LEN 4096

int main()
{
    ghc_init();
    std::vector<double, GlaswegianAllocator<double>> xs;
    for(int i = 0; i < LEN; i++)
    {
        xs.emplace_back(i * i);
    }
    double s = 0;
    for(double i : xs)
    {
        s += i;
    }
    std::cout << s << std::endl;
    return 0;
}
```

This works by allocating pinned `MutableByteArray#`s, then sticking a
`StablePtr` into a radix tree with the `MutableByteArray#`'s address as the key.
This keeps the array alive on the heap until the caller frees the memory (which
just deletes the `StablePtr` from the tree and does `freeStablePtr`).

A further optimization might be to call the RTS' C functions for doing
allocations directly, but this library is *shockingly* competitive with other
memory allocators. I'll add benchmarks soon.

This library is a fun toy I made for some silly benchmarks I wanted to run. It
is probably only useful for getting your colleagues to shut up about how
"garbage collectors are slow."
