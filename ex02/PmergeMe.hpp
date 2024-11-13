#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

class PmergeMe {
    private:
        std::vector<int> vBuffer;
        std::deque<int> qBuffer;
    public:
        PmergeMe();
        PmergeMe(std::vector<int>&);
        PmergeMe(const PmergeMe&);
        PmergeMe operator= (const PmergeMe&);

        const std::vector<int> getvBuffer();
        const std::deque<int> getqBuffer();

        ~PmergeMe();
};