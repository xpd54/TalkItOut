cmake_minimum_required(VERSION 3.26)
project(Server)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} 
    src/main.cpp
)
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64")
    message("Architecture is arm64")
    target_include_directories(${PROJECT_NAME} 
        PUBLIC 
        include/
        /opt/homebrew/include/mongocxx/v_noabi/ 
        /opt/homebrew/include/bsoncxx/v_noabi/
        /opt/homebrew/include/
    )
else()
    message("Architecture not x86_64")
    target_include_directories(${PROJECT_NAME} 
        /usr/local/include/mongocxx/v_noabi/ 
        /usr/local/include/bsoncxx/v_noabi/
        /usr/local/include
    )
endif()

target_link_directories(${PROJECT_NAME}
    PRIVATE
    /opt/homebrew/lib
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    mongocxx
    bsoncxx
)
