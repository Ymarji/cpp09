#include "PmergeMe.hpp"


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
        std::cout << i << "|" << j << std::endl;
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

    printContainer(p);
    sort_highs(p, 0, p.size(), p);

    
    printContainer(p);
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