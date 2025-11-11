#include <iostream>
#include <string>
#include <vector>

int main() {
  // Flush after every std::cout / std:cerr
  std::string command,tmp;
  std::vector<std::string> split_commands;
  while(1){
    std::cout << "$ "; 
    std::getline(std::cin,command);
    std::cerr << std::unitbuf;
    std::cout << command << ": command not found" << std::endl;
    for(char c:command){
      if(c!=' ')
        tmp.push_back(c);
      else{
        split_commands.push_back(tmp);
        tmp = "";
      }      
    }
    if (split_commands[0]=="exit")
    {
      std::string param = split_commands[1];
      if(param=="0")
      {
        break;
      }
    }
    
  }
}
