#ifndef BIT_TRICKS_HPP_
#define BIT_TRICKS_HPP_

#include <limits>

// Should return the number of bits in a integer type.
template <typename T>
inline size_t num_bits = sizeof(T) * (CHAR_BIT);

// This function should return the member of T, where the first
// 'num_one' bits are set to one.
template <typename T = unsigned>
inline T ones(unsigned num_ones)
{
    assert (num_ones <= num_bits<T>);

    // The implementation here is cautions!
    T res = 0;
    for (unsigned i = 0; i < num_ones; i++) {
        res = (res << 1) | 1;
    }
    return res;

    // Could maybe also just use the following:
    /*
    return std::numeric_limits<T>::max() >> (num_bits<T> - num_ones);
    */
    // But this relies on the fact that max() is indeed the value of T
    // where all bits are set to one. This seems too risky.
}

template <typename T = unsigned>
inline bool subset(T a, T b)
{
    return (a & (~b)) == 0;
}

#endif // BIT_TRICKS_HPP_


