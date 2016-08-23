#ifndef INCLUDE_CRYPTOPALS_XOR_HPP_
#define INCLUDE_CRYPTOPALS_XOR_HPP_

#include <vector>

namespace porkfactor
{
    namespace matasano
    {
        template<typename T>
        std::vector<T> buffer_xor(std::vector<T> const &m, std::vector<T> const &key)
        {
            typename std::vector<T>::size_type sz = m.size();
            std::vector<T> rv(sz);

            for(typename std::vector<T>::size_type i = 0; i < sz; i++)
            {
                rv[i] = m[i] ^ key[i % key.size()];
            }

            return rv;
        }
    }
}

#endif
