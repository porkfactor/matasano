#include <cstdlib>
#include <cstdint>
#include <string>
#include <iostream>

namespace porkfactor
{
    namespace matasano
    {
        template<typename T>
        T bit_distance(T const &l, T const &r)
        {
            T rv = static_cast<T>(0);

            for(auto i = 0U; i < (sizeof(l) * 8U); i++)
            {
                rv += (((l >> i) & 0x1) != ((r >> i) & 0x1)) ? 1 : 0;
            }

            return rv;
        }

        std::size_t hamming_distance(std::string const &l, std::string const &r)
        {
            std::size_t distance { 0UL };
            auto i = l.begin();
            auto j = r.begin();

            for(; i != l.end() && j != r.end(); ++i, ++j)
            {
                distance += bit_distance(*i, *j);
            }

            return distance;
        }
    }
}

namespace pm = porkfactor::matasano;

int main(int argc, char **argv)
{
    std::string a("this is a test");
    std::string b("wokka wokka!!!");

    std::cout << "distance = " << pm::hamming_distance(a, b) << std::endl;
}

