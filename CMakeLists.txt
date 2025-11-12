cmake_minimum_required(VERSION 3.13)
project(shell-starter-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(shell ${SOURCE_FILES})


find_library(READLINE_LIB readline)
if(READLINE_LIB)
    message(STATUS "Found readline: ${READLINE_LIB}")
    target_link_libraries(shell PRIVATE ${READLINE_LIB})
else()
    message(WARNING "libreadline not found, skipping link")
endif()
