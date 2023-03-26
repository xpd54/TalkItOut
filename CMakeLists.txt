cmake_minimum_required(VERSION 3.26)
project(Server)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} 
    src/main.cpp
)
target_include_directories(${PROJECT_NAME} 
        PUBLIC 
        include/
        /usr/local/include
    )
