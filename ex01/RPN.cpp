#include "RPN.hpp"

RPN::RPN()
{
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

void RPN::calculStack(char *arr)
{
    (void)arr;
    int tmp1;
    int tmp2;
    int result;
    int i = -1;
    while(arr[++i])
    {
        if(arr[i] == ' ')
            continue;
        else if(get_sign(arr[i]) != -1)
        {
            if(stack1.size() < 2)
            {
                std::cout << "Error: not enough digits before operator" << std::endl;
                return;
            }
            tmp2 = stack1.top();
            stack1.pop();
            tmp1 = stack1.top();
            stack1.pop();
            if(get_sign(arr[i]) == 1)
                result = tmp1 * tmp2;
            else if(get_sign(arr[i]) == 2)
                result = tmp1 + tmp2;
            else if(get_sign(arr[i]) == 3)
                result = tmp1 - tmp2;
            else if(get_sign(arr[i]) == 4)
                result = tmp1 / tmp2;
            stack1.push(result);
        }
        else
            stack1.push(arr[i] - 48);
    }
    if(stack1.size() > 1)
        std::cout << "Error: The stack contains more than one element: ";
    while(!stack1.empty())
    {
        std::cout << stack1.top() << ' ';
        stack1.pop();
    }
    std::cout << std::endl;
}


int RPN::parseRPN(std::string arr)
{
    int i = 0;
    while(arr[i])
    {
        if(arr[i] != ' ' && !isalpha(arr[i]) && get_sign(arr[i]) == -1 && !(arr[i] > 47 && arr[i] < 56))
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