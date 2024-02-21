#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>
#include <limits>

class BitcoinExchange
{
private:
    std::fstream input_file;
    std::fstream btc_file;
    std::map<std::string, float> btc_values;
public:
    BitcoinExchange();
    BitcoinExchange(std::string arg_file);
    void BitcoinSetValues();
    void BitcoinFindValues();
    void DisplayMap();
    std::string get_date(std::string line);
    std::string get_date_line(std::string line);
    float get_value(std::string line);
    float get_value_line(std::string line);
    int empty_line(std::string line);
    int is_value(std::string line);
    int error_line(std::string line);
    int parse_date(std::string _date);
    int parse_value(float _value);
    ~BitcoinExchange();
};


#endif