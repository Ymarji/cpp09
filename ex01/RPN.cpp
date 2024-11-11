#include "RPN.hpp"


RPN::RPN(std::string expression) {
    try
    {
        this->decompose(expression);
        while (this->rpn.size() != 0)
        {
            std::cout << this->rpn.top() << " ";
            this->rpn.pop();
        }
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int toInt(std::string str) {
    std::stringstream ss(str);
    int myInt;

    ss >> myInt;

    return myInt;
}

void RPN::decompose(std::string expression) {
    std::stringstream ss(expression);
    std::string token;

    while (std::getline(ss, token, static_cast<char>(32)))
    {
        if (token.size() == 0)
            continue;
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (this->rpn.size() < 2){
                throw std::runtime_error("Syntax Error: RPN operator (" + token + ") need at least 2 operands");
            }
            int b = this->rpn.top();
                this->rpn.pop();
            int a = this->rpn.top();
                this->rpn.pop();
            if (token == "+")
                this->rpn.push(a + b);
            else if (token == "-")
                this->rpn.push(a - b);
            else if (token == "*")
                this->rpn.push(a * b);
            else if (token == "/")
                this->rpn.push(a / b);
        } else {
            if (!this->isDigit(token)) {
                throw std::runtime_error("Syntax Error: RPN expretion containe non degit operands.");
            }
            this->rpn.push(toInt(token));
        }
    }
    if (this->rpn.size() > 1) {
            throw std::runtime_error("Syntax Error: RPN expretion lacks operator to process the remaining values.");
    }
    
}

bool RPN::isDigit(const std::string& str) {
    std::string::const_iterator it = str.begin();

    if (str.empty()){
        return false;
    }
    while (it != str.end())
    {
        if (!isdigit(*it)){
            return false;
        }
        it++;
    }
    return true;
    // return !str.empty() && std::all_of(str.begin(), str.end(), isdigit);
}

RPN::~RPN() {
    return;
}