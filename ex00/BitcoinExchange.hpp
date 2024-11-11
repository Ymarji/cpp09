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

    std::pair<int, double> dataSplit(std::string, char);
    void validateYear(std::string);
    void inputData(const char *);
    
    ~BitcoinExchange();

  private:
    std::map<long int, double, std::greater<long int> > db;
};
#endif // !BITCOINEXCHANGE_HPP
