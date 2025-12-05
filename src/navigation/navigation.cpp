#include "navigation/navigation.h"

void pwd(){
    char *buffer = getcwd(NULL,PATH_MAX);
    std::cout<<buffer<<std::endl;
}

void change_directory(const char* path){
    if(access(path,R_OK)==0)
    {
        chdir(path);
    }
    else
    {
        std::cout<<"cd: "<<path<<": No such file or directory"<<std::endl;
    }
    
}