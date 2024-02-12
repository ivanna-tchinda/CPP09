#include "RPN.hpp"

int main(int ac, char **av)
{
    (void)ac;
    RPN revpn;
    std::string array;

    array = av[1];
    //parsing
    //creer le tableau
    revpn.addDeque(array);
    //fct qui fait les calculs
    revpn.calculDeque();
    return 0;
}