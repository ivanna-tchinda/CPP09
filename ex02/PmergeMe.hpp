#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <utility>

class PmergeMe
{
private:
    std::vector<std::pair<int,int> > _vec;
    std::vector<std::pair<int,int> > _vec2;
public:
    PmergeMe();
    int parseList(char **av);
    void addList(char **av);
    void displayVec(std::vector<std::pair<int,int> > vec);
    void pairSort();
    void sortSmallest();
    void restoreKey();
    void restoreKey2();
    void sortAll();
    ~PmergeMe();
};



#endif