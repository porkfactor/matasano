#include <cryptopals/xor.hpp>
#include <cryptopals/encoding.hpp>
#include <iostream>

namespace pm = porkfactor::matasano;

int main(int argc, char **argv)
{
    std::string s1 { "1c0111001f010100061a024b53535009181c" };
    std::string s2 { "686974207468652062756c6c277320657965" };

    std::cout << pm::base16encode(pm::buffer_xor(pm::base16decode(s1), pm::base16decode(s2)));
    std::cout << std::endl;

    return 0;
}
