#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <fstream>
#include <string>

class BitcoinExchange
{
  public:
    BitcoinExchange(std::string);
    BitcoinExchange(std::istream);
    BitcoinExchange(const BitcoinExchange &) = default;
    BitcoinExchange &operator=(const BitcoinExchange &) = default;

    ~BitcoinExchange();

  private:
    std::ifstream file;
};
#endif // !BITCOINEXCHANGE_HPP
