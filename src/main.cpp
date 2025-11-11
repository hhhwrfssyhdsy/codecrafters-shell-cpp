#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Flush after every std::cout / std:cerr
    std::string command;
    std::set<std::string> builtin_commands={"echo","type","exit"};
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
        }else if(split_commands[0] == "type"){
            // Check if it's a builtin command
            if(builtin_commands.count(split_commands[1]) == 1){
                std::cout << split_commands[1] << " is a shell builtin" << std::endl;
            } else {
                // Check in PATH directories
                const char* path_env = getenv("PATH");
                if (path_env != nullptr) {
                    std::string path_str(path_env);
                    std::stringstream path_ss(path_str);
                    std::string dir;
                    bool found = false;
                    
                    while (std::getline(path_ss, dir, ':')) {
                        std::string full_path = dir + "/" + split_commands[1];
                        struct stat stat_buf;
                        
                        if (stat(full_path.c_str(), &stat_buf) == 0) {
                            // File exists, check if it's executable
                            if (access(full_path.c_str(), X_OK) == 0) {
                                std::cout << split_commands[1] << " is " << full_path << std::endl;
                                found = true;
                                break;
                            }
                        }
                    }
                    
                    if (!found) {
                        std::cout << split_commands[1] << ": not found" << std::endl;
                    }
                } else {
                    std::cout << split_commands[1] << ": not found" << std::endl;
                }
            }
        }else {
            std::cout << command << ": command not found" << std::endl;
        }
    }
    
    return 0;
}