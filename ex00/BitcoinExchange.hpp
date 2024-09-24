#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <ctime>

#define DB_FILENAME "data.csv"
class BitcoinExchange
{
  public:
    BitcoinExchange(std::string);
    BitcoinExchange(std::istream);
    BitcoinExchange(const BitcoinExchange &) = default;
    BitcoinExchange &operator=(const BitcoinExchange &) = default;

    std::pair<int, double> dataSplit(std::string, char);
    void validateYear(std::string);
    void inputData(std::string);
    void inputData(std::ifstream);
    
    ~BitcoinExchange();

  private:
    std::map<long int, double, std::greater<long int> > db;
};
#endif // !BITCOINEXCHANGE_HPP
