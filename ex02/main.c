#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    (void)av;
    if(ac < 2)
        return(1);
    PmergeMe pmg;

    if(pmg.parseList(av))
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    //std::cout << "Before: ";
    pmg.addList(av);
    pmg.pairSort();
    pmg.sortSmallest();
    pmg.restoreKey();
    pmg.restoreKey2();
    pmg.sortAll();
    return(0);
}

/*int main() {
    std::multimap<int, int> myMultiMap;

    // Insérer chaque paire clé-valeur individuellement
    myMultiMap.insert(std::make_pair(57, 1));
    myMultiMap.insert(std::make_pair(29, 2));
    myMultiMap.insert(std::make_pair(86, 3));
    myMultiMap.insert(std::make_pair(42, 4));
    myMultiMap.insert(std::make_pair(18, 5));
    myMultiMap.insert(std::make_pair(91, 1));
    myMultiMap.insert(std::make_pair(5, 7));
    myMultiMap.insert(std::make_pair(74, 8));
    myMultiMap.insert(std::make_pair(38, 9));
    myMultiMap.insert(std::make_pair(63, 10));

    // Affichage des éléments de la multimap
    std::multimap<int, int>::iterator it;
    for (it = myMultiMap.begin(); it != myMultiMap.end(); ++it) {
        std::cout << "Clé: " << it->first << ", Valeur: " << it->second << std::endl;
    }

    return 0;
}*/
