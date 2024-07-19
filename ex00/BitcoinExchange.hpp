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

    std::pair<double, double> dataSplit(std::string);
    ~BitcoinExchange();

  private:
    std::map<double, double> db;
};
#endif // !BITCOINEXCHANGE_HPP
