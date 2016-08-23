#include <cryptopals/encoding.hpp>
#include <iostream>

namespace pm = porkfactor::matasano;

int main(int argc, char **argv)
{
    std::string s { "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d" };

    std::cout << pm::base64encode(pm::base16decode(s)) << std::endl;
}

