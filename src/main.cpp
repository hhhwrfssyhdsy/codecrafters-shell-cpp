#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::string command;
  std::cout << "$ "; 
  std::getline(std::cin,command);
  std::cerr << std::unitbuf;
  std::cout << command << ": command not found" << std::endl;
}
