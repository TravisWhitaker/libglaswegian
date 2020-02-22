#include <limits>

extern "C"
{
#include <glaswegian.h>
};

// Call ghc_init before constructing one of these.
template <typename a>
struct GlaswegianAllocator
{
    typedef a value_type;

    GlaswegianAllocator() = default;

    a* allocate(std::size_t n)
    {
        if(n > std::numeric_limits<std::size_t>::max() / sizeof(a))
        {
            throw std::bad_alloc();
        }
        if(auto p = static_cast<a*>(ghc_alloc(n*sizeof(a))))
        {
            return p;
        }
        throw std::bad_alloc();
    }
    void deallocate(a* p, std::size_t) noexcept
    {
        ghc_free(p);
    }
};

template <typename a, typename b>
bool operator==(const GlaswegianAllocator<a>&, const GlaswegianAllocator<b>&)
{
    return true;
}
template <typename a, typename b>
bool operator!=(const GlaswegianAllocator<a>&, const GlaswegianAllocator<b>&)
{
    return false;
}
