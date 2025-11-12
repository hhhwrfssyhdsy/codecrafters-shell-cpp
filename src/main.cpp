#include <iostream>
#include <dirent.h>
#include <vector>
#include <sys/wait.h>
#include "core/path_utils.h"
#include "core/builtin.h"
#include "navigation/pwd.h"

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
        //TODO:改为switch case结构
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
                std::string full_path = check_command_in_path(split_commands[1]);
                if (!full_path.empty()){
                    std::cout << split_commands[1] << " is " << full_path << std::endl;
                }else{ 
                    std::cout << split_commands[1] << ": not found" << std::endl;
                }
            }
        }else if(split_commands[0] == "pwd"){
            path_locate();
        }else { 
            auto command_path = check_command_in_path(split_commands[0]);
            std::vector<char*> params;
            for(int i=0;i<split_commands.size();i++){
                params.push_back(const_cast<char*>(split_commands[i].c_str()));
            }
            params.push_back(nullptr);
            if(!command_path.empty()){
                pid_t pid = fork();
                if (pid==0)
                {
                    execv(command_path.c_str(),params.data());
                }else if (pid>0)
                {
                    int status;
                    waitpid(pid, &status,0);
                }
            }else{
            std::cout << command << ": command not found" << std::endl;
            }
        }
    }
    
    return 0;
}