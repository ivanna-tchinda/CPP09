#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if(ac < 2)
        return(1);
    PmergeMe pmg;

    if(pmg.parseList(av))
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::cout << "Before: ";
    pmg.addList(av);
    pmg.addList2(av);
    if(pmg.parseVec())
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    pmg.pairSort();
    pmg.sortSmallest();
    //pmg.restoreVec();
    std::cout << "After: ";
    pmg.sortAll();

    pmg.pairSort2();
    pmg.sortSmallest2();
    pmg.sortAllList();
    return(0);
}
