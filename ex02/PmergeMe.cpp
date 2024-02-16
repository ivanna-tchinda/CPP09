#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

void PmergeMe::sortAll(void)
{
    std::vector<std::pair<int,int> >::iterator it = _vec.begin();
    std::vector<std::pair<int,int> >::iterator it2 = _vec2.begin();
    while(it != _vec.end())
    {
        it2 = _vec2.begin() + (*it).second;
        while(it2 != _vec2.end())
        {
            if((*it).first < (*it2).first)
            {
                _vec2.insert(it2, *it);
                _vec.erase(it);
                it = _vec.begin();
                break;
            }
            else
                it2++;
        }
    }
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Sorted: " << std::endl;
    displayVec(_vec2);
}

void PmergeMe::restoreKey(void)
{
    std::vector<std::pair<int,int> >::iterator it = _vec2.begin();
    int i = 0;
    while (it != _vec2.end())
    {
        (*it).second = i;
        it++;
        i++;
    }
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Restore vec2" << std::endl;
    displayVec(_vec2);
}

void PmergeMe::restoreKey2(void)
{
    std::vector<std::pair<int,int> >::iterator it = _vec.begin();
    int i = 0;
    while (it != _vec.end())
    {
        (*it).second = i;
        it++;
        i++;
    }
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Restore vec" << std::endl;
    displayVec(_vec);
}


void PmergeMe::sortSmallest(void)
{
    std::pair<int, int> _smallest;
    int i = 1;
    int _times = 0;
    while(_times < (int)_vec2.size())
    {
        i = 0;
        _smallest.first = _vec.at(0).first;
        while(i < (int)_vec2.size() - _times)
        {
            if(_vec2.at(i).first < _smallest.first)
            {
                _smallest.first = _vec2.at(i).first;
                _smallest.second = i;
            }
            i++;
        }
        _vec2.push_back(_vec2.at(_smallest.second));
        _vec2.erase(_vec2.begin() + _smallest.second);
        _times++;
    }
    _vec2.push_back(_vec.at(_vec2.back().second));
    _vec.erase(_vec.begin() + _vec2.back().second);
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "vec: " << std::endl;
    displayVec(_vec);
    std::cout << "Sort smallest vec2: " << std::endl;
    displayVec(_vec2);
}

void PmergeMe::pairSort(void)
{
    std::vector<std::pair<int, int> >::iterator it = _vec.begin();
    while(*it != _vec.back())
    {
        if(*it < *(it + 1))
        {
            _vec2.push_back(*it);
            _vec.erase(it);
        }
        else
        {
            _vec2.push_back(*(it + 1));
            _vec.erase(it + 1);
        }
        it++;
    }
    std::cout << "Pair sort vec: " << std::endl;
    displayVec(_vec);
    std::cout << "Pair sort vec2: " << std::endl;
    displayVec(_vec2);

}

void PmergeMe::displayVec(std::vector<std::pair<int,int> > vec)
{
    std::vector<std::pair<int,int> >::iterator it = vec.begin();
    while(it != vec.end())
    {
        std::cout << (*it).first << ";" << (*it).second << ' ' << std::endl;
        it++;
    }
}


void PmergeMe::addList(char **av)
{
    int i = 1;
    int j = 0;
    while(av[i])
    {
        _vec.push_back(std::make_pair(atoi(av[i]), j));
        i++;
        if(i % 2 == 1)
            j++;
    }
    //displayVec(_vec);
}

int PmergeMe::parseList(char **av)
{
    int i = 1;
    int j = 0;
    while(av[i])
    {
        j = 0;
        while(av[i][j])
        {
            if(!isdigit(av[i][j]))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

PmergeMe::~PmergeMe()
{
}