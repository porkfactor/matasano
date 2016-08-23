#ifndef INCLUDE_CRYPTOPALS_ENCODING_HPP_
#define INCLUDE_CRYPTOPALS_ENCODING_HPP_


#include <string>
#include <vector>
#include <cstdint>

namespace porkfactor
{
    namespace matasano
    {
        std::string base64encode(std::vector<uint8_t> const &v);
        std::string base64encode(void const *data, size_t szData);
        std::vector<uint8_t> base64decode(std::string const &s);
        std::string base16encode(std::vector<uint8_t> const &v);
        std::string base16encode(void const *data, size_t szData);
        std::vector<uint8_t> base16decode(std::string const &s);
    }
}

#endif
