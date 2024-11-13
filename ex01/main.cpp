#include <iostream>
#include "RPN.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    try {
        RPN rpn(argv[1]);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
