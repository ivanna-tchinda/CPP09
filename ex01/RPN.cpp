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
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
            tmp1 = stack2.top();
            stack2.pop();
            tmp2 = stack2.top();
            stack2.pop();
            if(get_sign(arr[i]) == 1)
                result = tmp1 * tmp2;
            else if(get_sign(arr[i]) == 2)
                result = tmp1 + tmp2;
            else if(get_sign(arr[i]) == 3)
                result = tmp1 - tmp2;
            else if(get_sign(arr[i]) == 4)
                result = tmp1 / tmp2;
            stack1.push(result);
            while(!stack2.empty())
            {
                stack1.push(stack2.top());
                stack2.pop();
            }
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
        if(get_sign(arr[i++]) != -1)
        {
            while(!isdigit(arr[i++]));
            if(get_sign(arr[i]))
            {
                std::cout << "Error: negative number" << std::endl;
                return(1);
            }
        }
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