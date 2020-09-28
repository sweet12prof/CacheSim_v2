cmake_minimum_required(VERSION 3.3.2)
project(Project VERSION 0.0.1)

add_subdirectory(HeaderFiles)
add_subdirectory(SourceFiles)

add_executable(output main.cpp)

target_link_libraries(output PRIVATE Sources Headers)



