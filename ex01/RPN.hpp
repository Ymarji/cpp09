#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>


class RPN {
    private:
        std::stack<int> rpn;
    public:
        RPN(std::string);
        RPN(const RPN &);
        RPN &operator= (const RPN &);
        void decompose(std::string);
        bool isDigit(const std::string&);

        void expCalc();

        ~RPN();
};