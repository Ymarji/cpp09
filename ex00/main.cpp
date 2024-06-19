#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string str;
  std::ifstream myFile(argv[1], std::ios::in);
  std::getline(myFile, str);
  std::cout << str << std::endl;
  myFile.close();
  
  return 0;
}
