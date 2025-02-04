cmake_minimum_required(VERSION 3.26)
project(Server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_compile_options("-O3;-march=native;-fomit-frame-pointer;")

file(GLOB talk_out_src
    "src/**/*.cpp"
    "src/*.cpp"
)
add_executable(${PROJECT_NAME} 
    ${talk_out_src}
)

message("Architecture is ${CMAKE_SYSTEM_PROCESSOR}")
target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/asio/include/
    include/
    /usr/local/include/mongocxx/v_noabi/ 
    /usr/local/include/bsoncxx/v_noabi/
    #/opt/homebrew/include/ # particular to access header on Mac Silicon 
)
target_link_directories(${PROJECT_NAME}
    PRIVATE
    /usr/local/lib
    #/opt/homebrew/lib # particular to access lib on Mac Silicon 
)
# endif()
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    mongocxx
    bsoncxx
)
