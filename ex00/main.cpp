#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)ac;

    if (ac != 2)
    {
        std::cout << "Error: the program can be executed with one argument only" << std::endl;
        return 1;
    }
    std::string file_name = av[1];
    BitcoinExchange btc(file_name);

    btc.BitcoinSetValues();
    btc.BitcoinFindValues();
    
    return(0);
}