#include "PmergeMe.hpp"
#include <cctype>

bool isNumeric(const std::string& str) {
    if (str.empty()) return false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (!std::isdigit(str[i]) && str[i] != ' ') {
            return false;
        }
    }
    return true;
}

int toInt(std::string str) {
    std::stringstream ss(str);
    int myInt;

    ss >> myInt;

    return myInt;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    std::vector<int> list;
    std::stringstream ss;
    std::string str;

    if (argc < 2) {
        std::cerr << "missing argument" << std::endl;
        return 1;
    }

    while (argv[++i]) {
         if (!isNumeric(argv[i])) {
            std::cerr << "error numeric" << std::endl;
            return 1;
        }
        ss << argv[i] << " ";
    }

    while (std::getline(ss, str, ' '))
    {
        list.push_back(toInt(str));
    }
    
    // for (size_t i = 0; i < list.size(); i++)
    // {
    //     std::cout << list[i] << std::endl;
    // }

    PmergeMe sortedList(list);
    // std::cout << sortedList.getvBuffer().size() << std::endl;
    // std::cout << sortedList.getqBuffer().size() << std::endl;
    return 0;
}
