#include <iostream>
#include <cstdlib>
#include <dirent.h>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


// @brief: check if the command is in the system path 
// @ret: return the full path of the command executable bin
std::string check_command_in_path(std::string command){
    // Check in PATH directories
    const char* path_env = getenv("PATH");
    std::string full_path="";
    if (path_env != nullptr) {
        std::string path_str(path_env);
        std::stringstream path_ss(path_str);
        std::string dir;
        while (std::getline(path_ss, dir, ':')) {
            full_path = dir + "/" + command;
            struct stat stat_buf;
            if (stat(full_path.c_str(), &stat_buf) == 0) {
                // File exists, check if it's executable
                if (access(full_path.c_str(), X_OK) == 0) {
                    break;
                }
            }
        }
    } 
    return full_path;
}




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
                std::string full_path = check_command_in_path(split_commands[1]);
                if (!full_path.empty()){
                    std::cout << command << " is " << full_path << std::endl;
                }else{ 
                    std::cout << command << ": not found" << std::endl;
                }
            }
        }else {
            //TODO: execute exeternal command with multiple params 
            auto command_path = check_command_in_path(split_commands[0]);
            std::vector<char*> params;
            for(int i=1;i<split_commands.size();i++){
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