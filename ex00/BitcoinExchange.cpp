#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}


BitcoinExchange::BitcoinExchange(std::string arg_file)
{
    input_file.open("data.csv");
    if(input_file.bad())
        return;
    btc_file.open(arg_file.c_str());

    if(btc_file.is_open() == false)
    {
        std::cout << "Error: cannot open " << arg_file << std::endl;
        return;
    }
    if(btc_file.bad())
        return;
}

void BitcoinExchange::DisplayMap()
{
    std::map<std::string, float>::iterator it = btc_values.begin();
    while(it != btc_values.end())
    {
        std::cout << (*it).first << " " << (*it).second << std::endl;
        ++it;
    }
}

std::string BitcoinExchange::get_date(std::string line)
{
    int i = 0;
    std::string _date;
    while(line[i] && line[i] != ',')
        i++;
    _date = line.substr(0, i);
    return _date;
}

std::string BitcoinExchange::get_date_line(std::string line)
{
    int i = 0;
    int deb = 0;
    int num = 4;
    std::string _date = "";

    while (line[i] && (line[i] > 0 && line[i] < 33))
        i++;
    deb = i;
    if(!isdigit(line[i]))
        return _date;
    while (line[i] && isdigit(line[i]) && num--)
        i++;
    if(line[i++] != '-')
        return _date;
    num = 3;
    while (line[i] && isdigit(line[i]) && --num)
        i++;
    if(line[i++] != '-')
        return _date;
    num = 3;
    while (line[i] && isdigit(line[i]) && --num)
        i++;
    if(deb == i || i < deb || i < 10)
        return _date;
    _date = line.substr(deb, 10);
    return _date;
}


float BitcoinExchange::get_value(std::string line)
{
    int begin = 0;
    int end = 0;
    float _value;

    while(line[begin] && line[begin] != ',')
        begin++;
    end = begin++;
    while(line[end])
        end++;
    
    line = line.substr(begin, end);
    _value = atof(line.c_str());
    return _value;
}

float BitcoinExchange::get_value_line(std::string line)
{
    int begin = 0;
    int end = 0;
    float _value;

    while(line[++begin] && line[begin] != '|');
    while(line[begin] && line[++begin] == ' ');
    end = begin;
    while(line[end] && end++);
    line = line.substr(begin, line.size() - begin);
    _value = atof(line.c_str());
    return _value;
}

int BitcoinExchange::is_value(std::string line)
{
    int begin = 0;
    int end = 0;

    while(line[++begin] && line[begin] != '|');
    while(line[begin] && line[++begin] == ' ');
    end = begin;
    while(line[end] && end++);
    if(begin == end)
        return 1;
    return 0;
}


void BitcoinExchange::BitcoinSetValues()
{
    std::string line;
    std::string _date;
    float _value;
    if(input_file.is_open() == false)
    {
        std::cout << "Error: cannot open data.csv" << std::endl;
        return;
    }
    while(input_file.good())
    {
        input_file >> line;
        _date = get_date(line);
        _value = get_value(line);
        btc_values.insert(std::make_pair(_date, _value));
    }
}

int BitcoinExchange::empty_line(std::string line)
{
    int i = 0;
    if(line.size() == 0)
        return 1;
    while(line[i++])
    {
        if(line[i] > 32)
            return 0;
    }
    return(1);
}

int BitcoinExchange::error_line(std::string line)
{
    int i = 0;
    while(line[i++])
    {
        if(isalpha(line[i]))
            return(1);
    }
    return 0;
}

int BitcoinExchange::parse_date(std::string _date)
{
    if(_date.size() == 0)
        return 1;
    if(error_line(_date) || _date.size() != 10)
        return 1;
    std::string year = _date.substr(0, 4);
    std::string month = _date.substr(5, 2);
    std::string day = _date.substr(8, 2);
    //jour avant le premier jour de data csv
    if(year.compare("2008") == -1)
        return 1;
    if(month.compare("00") < 1 || month.compare("13") > -1)
        return 1;
    if(day.compare("00") < 1 || day.compare("32") > -1)
        return 1;
    return 0;
}

int BitcoinExchange::parse_value(float _value)
{
    if(_value < 0)
        return 1;
    if(_value > 1000)
        return 1;
    return 0;
}

void BitcoinExchange::BitcoinFindValues()
{
    std::string _line;
    std::string _date;
    float _value;
    std::string _lowest_bound;
    if(btc_file.is_open())
    {
        while(std::getline(btc_file, _line))
        {
            if(empty_line(_line))
                continue;
            _date = get_date_line(_line);
            if(parse_date(_date))
            {
                std::cout << "Error: bad input => " << _line << std::endl;
                continue;
            }
            if(is_value(_line))
            {
                std::cout << "Error: bad input => " << _line << std::endl;
                continue;
            }
            _value = get_value_line(_line);
            if(parse_value(_value))
            {
                std::cout << "Error: bad input => " << _line << std::endl;
                continue;
            }
            std::map<std::string, float>::iterator it = btc_values.begin();
            while(it != btc_values.end())
            {
                if(_date.compare(it->first) == 0)
                    break;
                if(_date.compare(it->first) == -1)
                {
                    --it;
                    break;
                }
                ++it;
            }
            std::cout << _date << " => " << _value << " = " << it->second * _value << std::endl;
            _date.clear();
            //_date.clear();
        }
    }
    return;
}

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, int>& p)
{
    os << "date: " << p.first << " value: " << p.second << std::endl;
    return os;
}

BitcoinExchange::~BitcoinExchange()
{
    btc_file.close();
    input_file.close();
}