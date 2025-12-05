#include "navigation/navigation.h"

void pwd(){
    char *buffer = getcwd(NULL,PATH_MAX);
    std::cout<<buffer<<std::endl;
}

void change_directory(const char* path){
    try
    {
        chdir(path);
    }
    catch(const std::exception& e)
    {
        std::cout<<"cd: "<<path<<": No such file or directory"<<std::endl;
    }
    
}