#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <sys/time.h>
#include <iomanip>

class PmergeMe
{
private:
    std::vector<std::pair<int, int> > _vec;
    std::vector<std::pair<int, int> > _vec2;
    std::list<std::pair<int, int> > _list;
    std::list<std::pair<int, int> > _list2;
    timeval startTime;
    timeval endTime;
    timeval startTime2;
    timeval endTime2;
public:
    PmergeMe();
    int parseList(char **av);
    int parseVec();
    void addList(char **av);
    void addList2(char **av);
    void displayVec(std::vector<std::pair<int, int> > vec);
    void displayList(std::list<std::pair<int, int> > vec);
    void pairSort();
    void pairSort2();
    void sortSmallest();
    void sortSmallest2();
    void sortAll();
    void sortAllList();
    double elapsedTimeMicroseconds();
    double elapsedTimeMicroseconds2();
    ~PmergeMe();
};



#endif