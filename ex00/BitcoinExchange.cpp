#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string fileName)
{
	std::ifstream file(DB_FILENAME, std::ios::in);
	std::string   str;

	while (std::getline(file, str))
	{
		// std::cout << this->dataSplit(str).first << "|" << this->dataSplit(str).second << std::endl;
		this->dataSplit(str);
	}
	return;
}

BitcoinExchange::BitcoinExchange(std::istream file)
{
	return;
}

std::pair<double, double> BitcoinExchange::dataSplit(std::string str)
{
	int day;
	int month;
	int year;

	size_t pos = str.find(',');
	std::string datePart = str.substr(0, pos);
	std::string exchangeRate = str.substr(pos);
	std::sscanf(datePart.c_str(), "%d-%d-%d", &year, &month, &day);

	std::cout << year << "|" << month << "|" << day <<  "|" <<  std::endl;

	return std::make_pair(10000 * year + 100 * month + day, std::atoi(exchangeRate.c_str()));
}

BitcoinExchange::~BitcoinExchange()
{
}
