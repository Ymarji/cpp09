#include <fstream>
#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) { 
  BitcoinExchange btc("test"); 
  btc.inputData("input.txt");
  return 0;
}
