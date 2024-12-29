#include "PmergeMe.hpp"
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>

bool isNumeric(const std::string& str) {
    if (str.empty()) return false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (!std::isdigit(str[i]) && str[i] != 32) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    std::vector<int> list;
    std::stringstream ss;
    std::string str;

    if (argc < 2) {
        std::cout << "missing argument" << std::endl;
        return 1;
    }

    while (argv[++i]) {
         if (!isNumeric(argv[i])) {
            std::cout << "argument syntax error, contains non digit" << std::endl;
            return 1;
        }
        ss << argv[i] << " ";
    }

    while (std::getline(ss, str, ' '))
    {
        double value = 0;
        if (isNumeric(str)){
            value = strtol(str.c_str(), NULL, 10);
        }
        if (errno == ERANGE || value > INT_MAX)  {
            std::cout << "argument " << str << " out of range" << std::endl;
            return 1;
        }
        list.push_back(value);
    }

    PmergeMe sortedList(list);
    return 0;
}
