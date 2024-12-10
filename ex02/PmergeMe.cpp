#include "PmergeMe.hpp"
#include <cmath>


template <typename Container>
void printContainer(const Container& container) {
    typename Container::const_iterator it = container.begin();

    std::cout << "*********** first *************" << std::endl;
    for (; it != container.end(); ++it) {
        std::cout << (*it).first << " ";
    }
    std::cout << std::endl;
    it = container.begin();
    std::cout << "*********** sec *************" << std::endl;
    for (; it != container.end(); ++it) {
        std::cout << (*it).second << " ";
    }
    std::cout << std::endl;
}

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(std::vector<int>& list): isOdd(list.size() % 2 != 0) {
    if (isOdd) {
        this->imposter = *(list.end() - 1);
        list.pop_back();
    }
    this->vBuffer.assign(list.begin(), list.end());
    this->qBuffer.assign(list.begin(), list.end());
    this->make_pairs(this->vBuffer);
    return ;
}

PmergeMe::PmergeMe(const PmergeMe& rop) {
    this->vBuffer = rop.vBuffer;
    this->qBuffer = rop.qBuffer;
}

void merge(std::vector<std::pair<int, int> > & highs,int start,int end, std::vector<std::pair<int, int> > arr) {
    int i = start;
    int mid = (end + start) / 2;
    int j = mid;
    int k = start;

    while (k < end)
    {
        // std::cout << i << "|" << j << std::endl;
        if (i < mid && (arr[i].first < arr[j].first || j >= end) ) {
            highs[k] = arr[i];
            i++;
        } else {
            highs[k] = arr[j];
            j++;
        }
        k++;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
}

void sort_highs(std::vector<std::pair<int, int> > &highs, int start, int end, std::vector<std::pair<int, int> > arr) {
    int mid = (end + start) / 2;

    if (end - start <= 1)
        return ;
    sort_highs(arr, start, mid, highs);
    sort_highs(arr, mid, end, highs);
    
    merge(highs, start, end, arr);
}

size_t nextIndex(int currentIndex) {
    int index = (std::pow(2, currentIndex + 1) + std::pow(-1, currentIndex)) / 3;
    std::cout << currentIndex << " " << index << std::endl;
    return index;
}

void PmergeMe::make_pairs(std::vector<int> list) {
    std::vector<std::pair<int, int> > p;
    std::vector<int>::iterator it = list.begin();

    while (it != list.end())
    {   
        if ((*(it + 1) > *(it))) {
            p.push_back(std::make_pair(*(it + 1), *(it)));
        } else {
            p.push_back(std::make_pair(*(it), *(it + 1)));
        }
        it += 2;
    }

    // printContainer(p);
    sort_highs(p, 0, p.size(), p);
    {
        std::vector<int> pend;
        this->vBuffer.clear();
        this->vBuffer.push_back(p[0].second);
        for (size_t i = 0; i < p.size(); i++)
        {
            this->vBuffer.push_back(p[i].first);
            if (i != 0)
                pend.push_back(p[i].second);
        }
        if (this->isOdd) {
            pend.push_back(this->imposter);
        }
        // this->vBuffer.assign(p.begin(), p.end());

        int i = 2;
        // std::vector<int>::iterator it = this->vBuffer.begin();
        std::vector<int>::iterator pe = pend.begin();
       
        while (size_t jacI = nextIndex(i) < pend.size())
        {
            std::vector<int>::iterator pe_it = pend.begin() + jacI;
            while (pe_it != pe)
            {
                std::cout << *(pe_it) << std::endl;
                pe_it--;
            }
            pe = pend.begin() + jacI;
            i++;
        }
        
    }
    
    // printContainer(p);
};



PmergeMe PmergeMe::operator=(const PmergeMe& rop) {
    this->vBuffer = rop.vBuffer;
    this->qBuffer = rop.qBuffer;
    return (*this);
}

const std::vector<int> PmergeMe::getvBuffer() {
    return this->vBuffer;
}

const std::deque<int> PmergeMe::getqBuffer() {
    return this->qBuffer;
}

void sortList() {
    
}

PmergeMe::~PmergeMe() {
    this->vBuffer.clear();
    this->qBuffer.clear();
}