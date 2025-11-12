#include "navigation/pwd.h"

void path_locate(){
    char *buffer = getcwd(NULL,PATH_MAX);
    std::cout<<buffer<<std::endl;
}

