#include "BitcoinExchange.hpp"
#include <exception>

BitcoinExchange::BitcoinExchange(std::string fileName)
{
	std::ifstream file(DB_FILENAME, std::ios::in);
	std::string   str;
	
	if (!file.good()) // to exeption 
		exit(1);
	std::getline(file, str);	
	while (std::getline(file, str))
		this->db.insert(this->dataSplit(str, ','));
	return;
}

BitcoinExchange::BitcoinExchange(std::istream file)
{
	std::string   str;

	std::getline(file, str);	
	while (std::getline(file, str))
		this->db.insert(this->dataSplit(str, ','));
	return;
}

bool isdigit(std::string str, size_t size){
	return str.find_first_not_of("0123456789") == std::string::npos && str.size() == size;
}

void BitcoinExchange::validateYear(std::string str) {
	std::string year;
	std::string month;
	std::string day;
	int pos = 0;

	str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
	pos = str.find('-');
	year = str.substr(0, pos);
	pos = str.find_last_of('-');
	month = str.substr(year.size() + 1, pos - year.size() - 1);
	day = str.substr(pos + 1);

	// std::cout << year << "|" << month << "|" << day << std::endl;
	if (!isdigit(year, 4) || !isdigit(month, 2) || !isdigit(day, 2)
	|| (std::atof(month.c_str()) > 12 || std::atof(day.c_str()) > 31))
	{	
		str = "error: bad input " + str;
		throw std::runtime_error(str);
	}
}

std::pair<int, double> BitcoinExchange::dataSplit(std::string str, char sign)
{
	int day;
	int month;
	int year;

	size_t pos = str.find(sign);
	std::string datePart = str.substr(0, pos);
	std::string exchangeRate = str.substr(pos + 1);
	std::sscanf(datePart.c_str(), "%d-%d-%d", &year, &month, &day);
	this->validateYear(datePart);

	return std::make_pair<long int, double>(10000 * year + 100.00 * month + day, std::atof(exchangeRate.c_str()));
}

void BitcoinExchange::inputData(std::string filename) {
	std::ifstream file(filename, std::ios::in);
	std::string str;
	std::pair<double, double> temp;

	std::getline(file, str);
	while (std::getline(file, str)) {
		try
		{
			temp = this->dataSplit(str, '|');
			std::cout.unsetf(std::ios::scientific);
			std::cout << db.lower_bound(temp.first)->first << "\n";

		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}
	}	
}

BitcoinExchange::~BitcoinExchange()
{
	this->db.clear();
}
