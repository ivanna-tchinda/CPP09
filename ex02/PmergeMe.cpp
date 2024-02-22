#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

double PmergeMe::elapsedTimeMicroseconds2() 
{
    double startMicroseconds = startTime2.tv_sec * 1000000 + startTime2.tv_usec;
    double endMicroseconds = endTime2.tv_sec * 1000000 + endTime2.tv_usec;
    return endMicroseconds - startMicroseconds;
}

double PmergeMe::elapsedTimeMicroseconds() 
{
    double startMicroseconds = startTime.tv_sec * 1000000 + startTime.tv_usec;
    double endMicroseconds = endTime.tv_sec * 1000000 + endTime.tv_usec;
    return endMicroseconds - startMicroseconds;
}

void PmergeMe::sortAllList(void)
{
    std::list<std::pair<int,int> >::iterator it = _list.begin();
    std::list<std::pair<int,int> >::iterator it2 = _list2.begin();
    std::list<std::pair<int,int> >::iterator it2_bis = _list2.begin();
    while(it != _list.end())
    {
        /*while((*it2).second != (*it).second && *it2 != _list2.back())
            ++it2;*/
        while(it2 != _list2.end())
        {
            it2_bis = it2;
            ++it2_bis;
            if(it2_bis == _list2.end() && ((*it).first > (*it2).first))
            {
                _list2.insert(it2_bis, *it);
                _list.erase(it);
                if((*it).first)
                    it = _list.begin();
                break;
            }
            else if((*it).first < (*it2).first)
            {
                _list2.insert(it2, *it);
                _list.erase(it);
                if((*it).first)
                    it = _list.begin();
                break;
            }
            else
                it2++;
        }
    }
    gettimeofday(&endTime2, NULL);
    std::cout << "Time to process a range of " << (int)_list2.size() << " elements with std::list: " <<  elapsedTimeMicroseconds2() << "µs" << std::endl;
}

void PmergeMe::sortAll(void)
{
    std::vector<std::pair<int,int> >::iterator it = _vec.begin();
    std::vector<std::pair<int,int> >::iterator it2 = _vec2.begin();
    while(it != _vec.end())
    {
        it2 = _vec2.begin()/* + (*it).second*/;
        while(it2 != _vec2.end())
        {
            if(it2 + 1 == _vec2.end() && ((*it).first > (*it2).first))
            {
                _vec2.insert(it2 + 1, *it);
                _vec.erase(it);
                if((*it).first)
                    it = _vec.begin();
                break;
            }
            else if((*it).first < (*it2).first)
            {
                _vec2.insert(it2, *it);
                _vec.erase(it);
                if((*it).first)
                    it = _vec.begin();
                break;
            }
            else
                it2++;
        }
    }
    gettimeofday(&endTime, NULL);
    displayVec(_vec2);
    std::cout << "Time to process a range of " << (int)_vec2.size() << " elements with std::vector: " << elapsedTimeMicroseconds() << "µs" << std::endl;

}

void PmergeMe::sortSmallest2(void)
{
    std::pair<int, int> _smallest;
    std::list<std::pair<int, int> >::iterator it = _list2.begin();
    std::list<std::pair<int, int> >::iterator tmp = _list2.begin();
    int i = 1;
    int _times = 0;
    if(_list.size() == 1)
        return;
    while(_times < (int)_list2.size())
    {
        i = 0;
        it = _list2.begin();
        _smallest = (*it);
        tmp = it;
        while(i < (int)_list2.size() - _times)
        {
            if((*it).first < _smallest.first)
            {
                _smallest = *it;
                tmp = it;
            }
            it++;
            i++;
        }
        _list2.splice(_list2.end(), _list2, tmp);
        _times++;
    }
    std::list<std::pair<int, int> >::iterator it2 = _list.begin();
    while((*it2).second != _list2.back().second && it2 != _list.end())
        it2++;
    if((int)_list.size() > (_list2.back()).second)
        _list2.splice(_list2.end(), _list, it2);
}

/*void PmergeMe::restoreVec(void)
{
    std::vector<std::pair<int, int> >::iterator it = _vec.begin();
    std::vector<std::pair<int, int> >::iterator it2 = _vec2.begin();
    std::cout << "vec: " << std::endl;
    displayVec(_vec);
    std::cout << "vec2: " << std::endl;
    displayVec(_vec2);
    int i = 0;
    while(it2 != _vec2.end())
    {
        it2 = _vec2.begin() + i;
        while(it != _vec.end() && (*it).second != (*it2).second)
            it++;
        std::cout << (*it).first << ";" << (*it).second << " and " << (*it2).first << ";" << (*it2).second  << " becomes " << i << std::endl;
        (*it).second = i;
        (*it2).second = i;
        i++;
    }
    std::cout << "new vec " << std::endl;
    displayVec(_vec);
    std::cout << "new vec2 " << std::endl;
    displayVec(_vec);
}*/

void PmergeMe::sortSmallest(void)
{
    std::pair<int, int> _smallest;
    int i = 1;
    int _times = 0;
    int j = 0;
    if(_vec.size() == 1)
        return;
    while(_times < (int)_vec2.size())
    {
        i = 0;
        _smallest = _vec2.at(0);
        j = 0;
        while(i < (int)_vec2.size() - _times)
        {
            if(_vec2.at(i).first < _smallest.first)
            {
                _smallest = _vec2.at(i);
                j = i;
            }
            i++;
        }
        _vec2.push_back(_vec2.at(j));
        _vec2.erase(_vec2.begin() + j);
        _times++;
    }
    if((int)_vec.size() > _vec2.back().second)
    {
        _vec2.push_back(_vec.at(_vec2.back().second));
        _vec.erase(_vec.begin() + _vec2.back().second);
    }

}

void PmergeMe::pairSort2(void)
{
    int even_odd = 0;
    gettimeofday(&startTime2, NULL);
    std::list<std::pair<int, int> >::iterator list_it = _list.begin();
    std::list<std::pair<int, int> >::iterator list_it_next = _list.begin();
    ++list_it_next;
    if(_list.size() % 2 == 1)
        even_odd = 1;
    while(list_it != _list.end())
    {
        if(*list_it == _list.back())
        {
            if(even_odd)
            {
                _list2.push_back(*list_it);
                _list.erase(list_it);
            }
            break;
        }
        if(*list_it < *list_it_next)
        {
            _list2.push_back(*list_it);
            _list.erase(list_it);
            list_it = list_it_next;
        }
        else
        {
            _list2.push_back(*list_it_next);
            _list.erase(list_it_next);
            list_it_next = list_it;
        }
        ++list_it_next;
        ++list_it_next;
        list_it++;
    }
}


void PmergeMe::pairSort(void)
{
    int even_odd = 0;
    gettimeofday(&startTime, NULL);
    std::vector<std::pair<int, int> >::iterator it = _vec.begin();
    if(_vec.size() % 2 == 1)
        even_odd = 1;
    while(it != _vec.end())
    {
        if(*it == _vec.back())
        {
            if(even_odd)
            {
                _vec2.push_back(*it);
                _vec.erase(it);
            }
            break;
        }
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
}

void PmergeMe::displayList(std::list<std::pair<int, int> > vec)
{
    std::list<std::pair<int,int> >::iterator it = vec.begin();
    while(it != vec.end())
    {
        std::cout << (*it).first << ' '/* << (*it).second << std::endl*/;
        it++;
    }
    std::cout << std::endl;
}

void PmergeMe::displayVec(std::vector<std::pair<int,int> > vec)
{
    std::vector<std::pair<int,int> >::iterator it = vec.begin();
    while(it != vec.end())
    {
        std::cout << (*it).first << " "/* << (*it).second << std::endl*/;
        it++;
    }
    std::cout << std::endl;
}


void PmergeMe::addList2(char **av)
{
    int i = 1;
    int j = 0;
    while(av[i])
    {
        _list.push_back(std::make_pair(atoi(av[i]), j));
        i++;
        if(i % 2 == 1)
            j++;
    }
    displayList(_list);

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

}

int PmergeMe::parseVec()
{
    std::vector<std::pair<int, int> >::iterator it = _vec.begin();
    std::vector<std::pair<int, int> >::iterator it2 = _vec.begin();
    if(_vec.size() == 1)
        return 1;
    while(it != _vec.end())
    {
        it2 = _vec.begin();
        while(it2 != _vec.end())
        {
            if(it != it2 && (*it).first == (*it2).first)
                return 1;
            it2++;
        }
        it++;
    }
    return 0;
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