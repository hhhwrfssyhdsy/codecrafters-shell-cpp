#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    // Flush after every std::cout / std:cerr
    std::string command;
    
    while(1){
        std::cout << "$ "; 
        std::getline(std::cin, command);
        std::cerr << std::unitbuf;
        
        // 使用stringstream来分割命令
        std::stringstream ss(command);
        std::string token;
        std::vector<std::string> split_commands;
        
        while(ss >> token) {
            split_commands.push_back(token);
        }
        
        // 检查是否有命令输入
        if(split_commands.empty()) {
            continue; // 空命令，重新输入
        }
        
        if (split_commands[0] == "exit") {
            if(split_commands.size() > 1 && split_commands[1] == "0") {
                break;
            }
        }else if(split_commands[0] == "echo"){
            for(int i=1;i<split_commands.size();i++){
              std::cout<<split_commands[i]<<' ';
            }
            std::cout<<std::endl;
        } else {
            std::cout << command << ": command not found" << std::endl;
        }
    }
    
    return 0;
}