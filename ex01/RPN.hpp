#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>

class RPN
{
private:
    std::deque<char> rpn_deque_int;
    std::deque<char> rpn_deque_op;
public:
    void addDeque(std::string arr);
    void displayDeque(std::deque<char> rpn_deque);
    void calculDeque();
    int get_sign(char c);
    RPN();
    ~RPN();
};



#endif