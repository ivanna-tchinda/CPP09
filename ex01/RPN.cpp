#include "RPN.hpp"

RPN::RPN()
{
}

void RPN::addDeque(std::string arr)
{
    (void)arr;
    int i = -1;
    while(arr[++i])
    {
        if(arr[i] == ' ')
            continue;
        if(isalnum(arr[i]))
        {
            rpn_deque_int.push_back(arr[i]);
            rpn_deque_op.push_back(' ');
        }
        else
        {
            rpn_deque_op.push_back(arr[i]);
            rpn_deque_int.push_back(' ');
        }
    }
    //displayDeque(rpn_deque_int);
    //displayDeque(rpn_deque_op);
}

void RPN::displayDeque(std::deque<char> rpn_deque)
{
    int i = 0;
    int size = rpn_deque.size();

    while (i < size)
    {
        std::cout << rpn_deque[i];
        i++;
    }
    std::cout << std::endl;
    
}

int RPN::get_sign(char c)
{
    if(c == '*')
        return 1;
    else if(c == '+')
        return 2;
    else if(c == '-')
        return 3;
    else if(c == '/')
        return 4;
    return -1;
}


void RPN::calculDeque(void)
{
    int i = 0;
    int _sign = 0;
    float result = 0;
    int size_op = rpn_deque_op.size();

    float tmp_1;
    float tmp_2;
    std::deque<char>::iterator it = rpn_deque_int.begin();
    while(i < size_op)
    {
        if(rpn_deque_op[i] != ' ')
        {
            while(*it != ' ' || *it != *rpn_deque_int.rbegin())
                it++;
            tmp_1 = *(it - 2) - 48;
            tmp_2 = *(it - 1) - 48;
            //std::cout << "tmp1:" << tmp_1 << " tmp2:" << tmp_2 << std::endl;
            _sign = get_sign(rpn_deque_op[i]);
            if(_sign == 1)
                result = tmp_1 * tmp_2;
            else if(_sign == 2)
                result = tmp_1 + tmp_2;
            else if(_sign == 3)
                result = tmp_1 - tmp_2;
            else if(_sign == 4)
                result = tmp_1 / tmp_2;
            *it = result + 48;
            rpn_deque_int.erase(it - 2);
            rpn_deque_int.erase(it - 1);
        }
        i++;
    }
    std::cout << result << std::endl;
}

int RPN::parseRPN(std::string arr)
{
    int i = 0;
    while(arr[i])
    {
        if(arr[i] == '(' || arr[i] == ')')
        {
            std::cout << "Error" << std::endl;
            return(1);
        }
        i++;
    }
    return(0);
}


RPN::~RPN()
{
}