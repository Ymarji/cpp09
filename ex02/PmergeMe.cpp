#include "PmergeMe.hpp"
#include <cmath>

PmergeMe::PmergeMe() {
    std::cout << "nothing to sort!" << std::endl;
    return;
}

PmergeMe::PmergeMe(const PmergeMe& rhs) {
    this->vBuffer = rhs.vBuffer;
    this->qBuffer = rhs.qBuffer;
}

template <class container>
void PmergeMe::printList(const container list) {
    size_t i = 0;
    while (i < list.size())
    {
        std::cout << list[i] << " ";
        i++;
    }
    if (list.size() > 10)
        std::cout << "[...]";
    std::cout << std::endl;
}

PmergeMe::PmergeMe(std::vector<int> list): isOdd(list.size() % 2 != 0) {
    clock_t cStart;
    clock_t cEnd;


    std::cout << "before    :";
    this->printList(list);
    
    if (isOdd) {
        this->imposter = *(list.end() - 1);
        list.pop_back();
    }

    cStart = clock();
    if (list.size() == 0){
      this->qBuffer.push_back(this->imposter);
    } else {
        std::deque<int> dec(list.begin(), list.end());
        this->sortDeque(dec);
    }
    cEnd = clock();

    std::cout << "after     :";
    this->printList(this->qBuffer);

    std::cout << "Time to process a range of " << this->qBuffer.size() << " elements with std::deque  : " <<
        std::fixed << std::setprecision(4) << (double)(cEnd - cStart) / CLOCKS_PER_SEC * 1000<< " ms " << std::endl;

    cStart = clock();
    if (list.size() == 0){
        this->vBuffer.push_back(this->imposter);
    } else {
        std::vector<int> vec(list);
        this->sortVector(vec);
    }
    cEnd = clock();

    std::cout << "Time to process a range of " << this->vBuffer.size() << " elements with std::vector : " <<
        std::fixed << std::setprecision(4) << (double)(cEnd - cStart) / CLOCKS_PER_SEC * 1000 << " ms " << std::endl;
    return ;
}

void PmergeMe::mergeVector(std::vector<std::pair<int, int> > & highs,int start,int end, std::vector<std::pair<int, int> > arr) {
    int i = start;
    int mid = (end + start) / 2;
    int j = mid;
    int k = start;

    while (k < end)
    {
        if (i < mid && ((j < end && arr[i].first < arr[j].first) || j >= end) ) {
            highs[k] = arr[i];
            i++;
        } else {
            highs[k] = arr[j];
            j++;
        }
        k++;
    }
}

void PmergeMe::vectorMergeSort(std::vector<std::pair<int, int> > &highs, int start, int end, std::vector<std::pair<int, int> > arr) {
    int mid = (end + start) / 2;

    if (end - start <= 1)
        return ;
    this->vectorMergeSort(arr, start, mid, highs);
    this->vectorMergeSort(arr, mid, end, highs);
    
    this->mergeVector(highs, start, end, arr);
}

size_t PmergeMe::nextIndex(int currentIndex) {
    int index = (std::pow(2, currentIndex + 1) + std::pow(-1, currentIndex)) / 3;
    return index;
}

void PmergeMe::sortVector(std::vector<int> list) {

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

    this->vectorMergeSort(p, 0, p.size(), p);
    {
        std::vector<int> pend;
        if (p.size() > 0)
            this->vBuffer.push_back(p[0].second);
        for (size_t i = 0; i < p.size(); i++)
        {
            this->vBuffer.push_back(p[i].first);
            pend.push_back(p[i].second);
        }
        if (this->isOdd) {
            pend.push_back(this->imposter);
        }

        int i = 2;
        size_t jacI = this->nextIndex(i);
        it = this->vBuffer.begin() + 1;
        std::vector<int>::iterator pe = pend.begin();
       
        while (jacI < pend.size())
        {
            int arraySize = std::pow(2, i) - 1;
            std::vector<int>::iterator pe_it = pend.begin() + (jacI - 1);
            while (pe_it != pe)
            {
                std::vector<int>::iterator insertionPoint = std::upper_bound(this->vBuffer.begin(), this->vBuffer.begin() + arraySize, *pe_it);
                this->vBuffer.insert(insertionPoint, *pe_it);
                pe_it--;
            }
            pe = pend.begin() + jacI - 1;
            i++;
            jacI = this->nextIndex(i);
        }
        ++pe;
        while (pe != pend.end())
        {
            std::vector<int>::iterator insertionPoint = std::upper_bound(this->vBuffer.begin(), this->vBuffer.end(), *pe);
            this->vBuffer.insert(insertionPoint, *pe);
            pe++;
        }
    }
};

void PmergeMe::mergeDeque(std::deque<std::pair<int, int> > & highs,int start,int end, std::deque<std::pair<int, int> > arr) {
    int i = start;
    int mid = (end + start) / 2;
    int j = mid;
    int k = start;

    while (k < end)
    {
        if (i < mid && ((j < end && arr[i].first < arr[j].first)|| j >= end) ) {
            highs[k] = arr[i];
            i++;
        } else {
            highs[k] = arr[j];
            j++;
        }
        k++;
    }
}

void PmergeMe::dequeMergeSort(std::deque<std::pair<int, int> > &highs, int start, int end, std::deque<std::pair<int, int> > arr) {
    int mid = (end + start) / 2;

    if (end - start <= 1)
        return ;
    this->dequeMergeSort(arr, start, mid, highs);
    this->dequeMergeSort(arr, mid, end, highs);
    
    this->mergeDeque(highs, start, end, arr);
}

void PmergeMe:: sortDeque(std::deque<int> list) {
    std::deque<std::pair<int, int> > p;
    std::deque<int>::iterator it = list.begin();

    while (it != list.end())
    {   
        if ((*(it + 1) > *(it))) {
            p.push_back(std::make_pair(*(it + 1), *(it)));
        } else {
            p.push_back(std::make_pair(*(it), *(it + 1)));
        }
        it += 2;
    }
    this->dequeMergeSort(p, 0, p.size(), p);
    {
        std::deque<int> pend;
        if (p.size() > 0)
            this->qBuffer.push_back(p[0].second);
        for (size_t i = 0; i < p.size(); i++)
        {
            this->qBuffer.push_back(p[i].first);
            pend.push_back(p[i].second);
        }
        if (this->isOdd) {
            pend.push_back(this->imposter);
        }

        int i = 2;
        size_t jacI = this->nextIndex(i);
        it = this->qBuffer.begin() + 1;
        std::deque<int>::iterator pe = pend.begin();
       
        while (jacI < pend.size())
        {
            int arraySize = std::pow(2, i) - 1;
            std::deque<int>::iterator pe_it = pend.begin() + (jacI - 1);
            while (pe_it != pe)
            {
                std::deque<int>::iterator insertionPoint = std::upper_bound(this->qBuffer.begin(), this->qBuffer.begin() + arraySize, *pe_it);
                this->qBuffer.insert(insertionPoint, *pe_it);
                pe_it--;
            }
            pe = pend.begin() + jacI - 1;
            i++;
            jacI = this->nextIndex(i);
        }
        ++pe;
        while (pe != pend.end())
        {
            std::deque<int>::iterator insertionPoint = std::upper_bound(this->qBuffer.begin(), this->qBuffer.end(), *pe);
            this->qBuffer.insert(insertionPoint, *pe);
            pe++;
        }
    }
};


PmergeMe PmergeMe::operator=(const PmergeMe& rhs) {
    if (this != &rhs){
        this->vBuffer = rhs.vBuffer;
        this->qBuffer = rhs.qBuffer;
    }
    return (*this);
}

const std::vector<int> PmergeMe::getvBuffer() {
    return this->vBuffer;
}

const std::deque<int> PmergeMe::getqBuffer() {
    return this->qBuffer;
}

PmergeMe::~PmergeMe() {
    this->vBuffer.clear();
    this->qBuffer.clear();
}