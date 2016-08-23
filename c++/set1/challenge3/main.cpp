#include <cryptopals/xor.hpp>
#include <cryptopals/encoding.hpp>
#include <iostream>

namespace pm = porkfactor::matasano;

int main(int argc, char **argv)
{
    std::string m = { "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736" };
    std::vector<uint8_t> b { pm::base16decode(m) };

    for(unsigned char c = 0; c < 128; c++)
    {
        if(std::isprint(c)) {
            std::vector<uint8_t> key = { static_cast<uint8_t>(c) };
            std::cout << "[" << c << "]" << (char const *)pm::buffer_xor(b, key).data() << std::endl;
        }
    }

    return 0;
}
