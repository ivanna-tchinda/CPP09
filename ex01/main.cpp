#include "RPN.hpp"

int main(int ac, char **av)
{
    RPN revpn;
    std::string array;

    if(ac != 2)
        return (1);
    array = av[1];
    if(revpn.parseRPN(array))
        return 1;
    revpn.addDeque(array);
    revpn.calculDeque();
    return 0;
}