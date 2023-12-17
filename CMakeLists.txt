cmake_minimum_required(VERSION 3.26)
project(Server)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/connection/mongo.cpp
    src/entity/user.cpp
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
    target_link_directories(${PROJECT_NAME}
        PRIVATE
        /opt/homebrew/lib
    )
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
    message("Architecture is x86_64")
    target_include_directories(${PROJECT_NAME}
        PUBLIC
        include/
        /usr/local/include/mongocxx/v_noabi/ 
        /usr/local/include/bsoncxx/v_noabi/
        /usr/local/include
    )
    target_link_directories(${PROJECT_NAME}
        PRIVATE
        /usr/local/lib
    )
endif()
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    mongocxx
    bsoncxx
)
