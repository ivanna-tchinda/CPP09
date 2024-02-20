#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

class RPN
{
private:
    std::stack<int> stack1;
    std::stack<int> stack2;
public:
    void calculStack(char *arr);
    int get_sign(char c);
    int parseRPN(std::string arr);
    RPN();
    ~RPN();
};



#endif