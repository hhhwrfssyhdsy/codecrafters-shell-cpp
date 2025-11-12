#pragma once
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <cstdlib>

std::string check_command_in_path(std::string command);