#include "RPN.hpp"


RPN::RPN() {
    throw std::runtime_error("Syntax Error: No expression used to call constractor");
}

RPN::RPN(std::string expression) {
    this->decompose(expression);
    while (this->rpn.size() != 0)
    {
        std::cout << this->rpn.top() << " ";
        this->rpn.pop();
    }
    std::cout << std::endl;
}

RPN::RPN(const RPN &rhs) {
    this->rpn = rhs.rpn;
};

RPN &RPN::operator= (const RPN &rhs) {
    if (this != &rhs) {
        this->rpn = rhs.rpn;
    }
    return *this;
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

    if (expression.size() == 0) {
        std::cout << "expression empty";
        return;
    }
    if (expression.find_last_not_of(" \t\n\r") == std::string::npos)
        throw std::runtime_error("Syntax Error: RPN expression not found");

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
            else if (token == "/"){
                if (b == 0){
                    throw std::runtime_error("Syntax Error: cannot divide by 0");
                }
                this->rpn.push(a / b);
            }
        } else {
            if (!this->isDigit(token)) {
                throw std::runtime_error("Syntax Error: RPN expression containe invalid operands. ( " + token + " )");
            }
            this->rpn.push(toInt(token));
        }
    }
    if (this->rpn.size() > 1) {
            throw std::runtime_error("Syntax Error: RPN expression lacks operator to process the remaining values.");
    }
    
}

bool RPN::isDigit(const std::string& str) {
    std::string::const_iterator it = str.begin();

    if (str.empty() || str.size() > 1){
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
}

RPN::~RPN() {
    return;
}