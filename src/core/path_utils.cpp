#include "core/path_utils.h"

/* @brief: check if the command is in the system path 
* @param command
* @ret: return the full path of the command executable bin
*/
std::string check_command_in_path(std::string command){
    // Check in PATH directories
    const char* path_env = getenv("PATH");
    bool found=0;
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
                    found = true;
                    break;
                }
            }
        }
    } 
    if (!found)
    {
        full_path.clear();   
    }
    return full_path;
}