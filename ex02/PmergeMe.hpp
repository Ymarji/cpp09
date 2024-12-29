#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <ctime>
#include <iomanip>

class PmergeMe {
    private:
        std::vector<int> vBuffer;
        std::deque<int> qBuffer;
        int imposter;
        bool isOdd;
    public:
        PmergeMe();
        PmergeMe(std::vector<int>);
        PmergeMe(const PmergeMe&);
        PmergeMe operator= (const PmergeMe&);

        size_t nextIndex(int);
        template <class container>
        void printList(const container);

        void mergeVector(std::vector<std::pair<int, int> > & ,int ,int , std::vector<std::pair<int, int> > );
        void vectorMergeSort(std::vector<std::pair<int, int> > &, int , int , std::vector<std::pair<int, int> > );

        void mergeDeque(std::deque<std::pair<int, int> > & ,int ,int , std::deque<std::pair<int, int> > );
        void dequeMergeSort(std::deque<std::pair<int, int> > &, int , int , std::deque<std::pair<int, int> > );

        const std::vector<int> getvBuffer();
        const std::deque<int> getqBuffer();

        void sortVector(std::vector<int>);
        void sortDeque(std::deque<int>);
        ~PmergeMe();
};