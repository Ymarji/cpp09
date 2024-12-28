#include "BitcoinExchange.hpp"
#include <exception>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream file(DB_FILENAME, std::ios::in);
	std::string   str;	
	
	if (!file.good()){
		throw std::runtime_error("Error: could not open data.csv file.");
		return;
	}
	if (file.peek() == std::ifstream::traits_type::eof()) {
			throw std::runtime_error("Error: data.csv file is empty.");
		return;
	}

	std::getline(file, str);
	while (std::getline(file, str))
		this->db.insert(this->dataSplit(str, ','));
	return;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs) {
	if (!rhs.db.empty())
		this->db = rhs.db;
	else {
		throw std::runtime_error("Error: copy constructor db is empty (check data.csv)");
		return;
	}
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	if (this != &rhs) {
		if (!rhs.db.empty())
			this->db = rhs.db;
		else {
			throw std::runtime_error("Error: assigned db is empty (check data.csv)");
		}
	}
	return *this;
}


bool BitcoinExchange::isdigit(std::string str, size_t size){
	return str.find_first_not_of("0123456789") == std::string::npos && str.size() == size;
}

void BitcoinExchange::trimSpaces(std::string &str) {
	str.erase(str.find_last_not_of(" \t\n\r") + 1);
	str.erase(0, str.find_first_not_of(" \n\r\t"));
}

bool BitcoinExchange::isValidDate(int day, int month, int year) {
	if (month < 1 || month > 12)
		return false;

	int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
		monthDays[1] = 29;
	}

	return day > 0 && day <= monthDays[month - 1];
}

void BitcoinExchange::validateYear(std::string str) {
	std::string year;
	std::string month;
	std::string day;
	int pos = 0;

	this->trimSpaces(str);
	if (str.size() < 10) {
		if (str.empty()) {
			str = "Error: bad input => date is empty";
		} else
			str = "Error: bad input => " + str;
		throw std::runtime_error(str);
	}
	pos = str.find_first_of('-');
	year = str.substr(0, pos);
	pos = str.find_last_of('-');
	month = str.substr(year.size() + 1, pos - year.size() - 1);
	day = str.substr(pos + 1);

	if (!this->isdigit(year, 4) || !this->isdigit(month, 2) || !this->isdigit(day, 2)
	|| isValidDate(std::atoi(day.c_str()), std::atoi(month.c_str()), std::atoi(year.c_str())) == false)
	{
		str = "Error: bad input => " + str;
		throw std::runtime_error(str);
	}
}

std::pair<int, double> BitcoinExchange::dataSplit(std::string str, char sign)
{
	int day;
	int month;
	int year;
	double exchRate;

	size_t pos = str.find(sign);
	if (pos == std::string::npos){
		throw std::runtime_error("Error: |" + str + "| wrong syntax.");
	}
	std::string datePart = str.substr(0, pos);
	std::string exchangeRate = str.substr(pos + 1);

	this->trimSpaces(exchangeRate);
	this->validateYear(datePart);
	std::sscanf(datePart.c_str(), "%d-%d-%d", &year, &month, &day);
	if (exchangeRate.size() == 0 || exchangeRate.find_first_not_of("0123456789.") != std::string::npos ||
		exchangeRate.find_first_of('.') != exchangeRate.find_last_of('.')) {
		if (exchangeRate.find_last_of('-') != 0)
			throw std::runtime_error("Error: |" + str + "| wrong syntax.");
	}
	if (exchangeRate[0] == '-') {
		throw std::runtime_error("Error: not a positive number.");
	}
	exchRate = std::atof(exchangeRate.c_str());
	if (exchRate > INT_MAX) {
		throw std::runtime_error("Error: too large a number.");
	}

	return std::make_pair<long int, double>(10000 * year + 100 * month + day, exchRate);
}

std::string formatString(long int date) {
 	int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;
	std::ostringstream oss;

	oss << year << "-" << std::setfill('0') << std::setw(2) << month << "-"
    << std::setfill('0') << std::setw(2) << day ;

	return oss.str();
}

void BitcoinExchange::inputData(const char * filename) {
	std::ifstream file(filename, std::ios::in);
	std::string str;
	std::pair<double, double> temp;

	if (!file.good()){
		str.append(filename);
		throw std::runtime_error("Error: could not open " + str + " file.");
		return;
	}
	if (file.peek() == std::ifstream::traits_type::eof()) {
		str.append(filename);
		throw std::runtime_error("Error: "+ str +" file is empty.");
		return;
	}

	std::getline(file, str);
	if (str != "date | value") {
		throw std::runtime_error("Error: invalid first line <<date | value>>.");
		return;
	}
	if (file.eof() || file.peek() == std::ifstream::traits_type::eof()) {
		std::string err = filename;
		throw std::runtime_error("Error: "+ err +" file is empty.");
		return;
	}
	while (std::getline(file, str)) {
		try {
			if (str.size() == 0) {
				std::cout << "Error: Empty line" << std::endl;
				continue;
			}
			temp = this->dataSplit(str, '|');
			if (temp.second > 1000) {
				throw std::runtime_error("Error: too large a number, max value 1000.");
			}
			std::map<long, double>::iterator lowerIt=  db.lower_bound(temp.first);
			if (lowerIt == db.end())
				std::cout << formatString(temp.first) << " => No record" <<  std::endl;
			else 
				std::cout << formatString(temp.first) << " => " << std::fixed << std::setprecision(2) << temp.second << " = " << db.lower_bound(temp.first)->second * temp.second  << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}

BitcoinExchange::~BitcoinExchange()
{
	this->db.clear();
}
