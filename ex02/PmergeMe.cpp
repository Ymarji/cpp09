#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(std::vector<int>& list): vBuffer(list.begin(), list.end()), qBuffer(list.begin(), list.end()) {
    return ;
}

PmergeMe::PmergeMe(const PmergeMe& rop) {
    this->vBuffer = rop.vBuffer;
    this->qBuffer = rop.qBuffer;
}

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

PmergeMe::~PmergeMe() {
    this->vBuffer.clear();
    this->qBuffer.clear();
}