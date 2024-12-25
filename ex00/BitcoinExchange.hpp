#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <limits.h>

#define DB_FILENAME "data.csv"
class BitcoinExchange
{
  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &);
    BitcoinExchange &operator=(const BitcoinExchange &);

    bool isdigit(std::string, size_t);
    void trimSpaces(std::string &);
    std::pair<int, double> dataSplit(std::string, char);
    void validateYear(std::string);
    void inputData(const char *);
    bool isValidDate(int, int, int);
    
    ~BitcoinExchange();

  private:
    std::map<long int, double, std::greater<long int> > db;
};
#endif // !BITCOINEXCHANGE_HPP
