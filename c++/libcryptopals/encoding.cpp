#include <cryptopals/encoding.hpp>

namespace porkfactor
{
    namespace matasano
    {
        std::string base64encode(std::vector<uint8_t> const &v)
        {
            std::string rv;
            static char const b64[64] = {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', /* 0x00 - 0x07 */
                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', /* 0x08 - 0x0f */
                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', /* 0x10 - 0x17 */
                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', /* 0x18 - 0x1f */
                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', /* 0x20 - 0x27 */
                'o', 'p', 'q', 'r', 's', 't', 'u', 'v', /* 0x28 - 0x2f */
                'w', 'x', 'y', 'z', '0', '1', '2', '3', /* 0x30 - 0x37 */
                '4', '5', '6', '7', '8', '9', '+', '/', /* 0x38 - 0x3f */
            };

            uint16_t buffer = 0;
            uint16_t bits = 0;

            for(auto i : v)
            {
                buffer |= i << (((sizeof(buffer) - sizeof(i)) * 8) - bits);
                bits += 8;

                while(bits >= 6)
                {
                    rv.push_back(b64[(buffer & 0xfc00) >> 10]);
                    buffer <<= 6;
                    bits -= 6;
                }
            }

            return rv;
        }

        std::string base64encode(void const *data, size_t szData)
        {
            return base64encode(std::vector<uint8_t>(static_cast<uint8_t const *>(data), static_cast<uint8_t const *>(data) + szData));
        }

        std::vector<uint8_t> base64decode(std::string const &s)
        {
            std::vector<uint8_t> rv;
            static uint8_t const b64[128] = {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 - 0x07 */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08 - 0x0f */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10 - 0x17 */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x18 - 0x1f */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 - 0x27 */
                0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f, /* 0x28 - 0x2f */
                0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, /* 0x30 - 0x37 */
                0x3c, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38 - 0x3f */
                0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* 0x40 - 0x47 */
                0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, /* 0x48 - 0x4f */
                0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, /* 0x50 - 0x57 */
                0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58 - 0x5f */
                0x00, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, /* 0x60 - 0x67 */
                0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, /* 0x68 - 0x6f */
                0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, /* 0x70 - 0x77 */
                0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x78 - 0x7f */
            };

            uint16_t buffer = 0;
            uint16_t bits = 0;

            for(auto c : s)
            {
                buffer |= b64[c & 0x7f] << ((sizeof(buffer) * 8) - (6 + bits));

                while(bits >= 8)
                {
                    rv.push_back((buffer & 0xff00) >> 8);
                    bits -= 8;
                    buffer <<= 8;
                }
            }

            return rv;
        }

        std::string base16encode(std::vector<uint8_t> const &v)
        {
            std::string rv;

            for(auto i : v)
            {
                std::string::value_type s[3];

                rv.append(s, std::snprintf(s, sizeof(s), "%02x", i));
            }

            return rv;
        }

        std::string base16encode(void const *data, size_t szData)
        {
            return base16encode(std::vector<uint8_t>(static_cast<uint8_t const *>(data), static_cast<uint8_t const *>(data) + szData));
        }

        std::vector<uint8_t> base16decode(std::string const &s)
        {
            std::vector<uint8_t> rv;

            for(auto i = s.cbegin(); i != s.cend(); i += 2)
            {
                rv.push_back(static_cast<uint8_t>(std::stoul(std::string(i, i + 2), 0, 16)));
            }

            return rv;
        }
    }
}

