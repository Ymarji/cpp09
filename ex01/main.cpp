#include <iostream>
#include "RPN.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        if (argc > 2)
            std::cout << "Error: too much args: ";
        std::cout << "example ./RPN \"5 2 +\"" << std::endl;
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
