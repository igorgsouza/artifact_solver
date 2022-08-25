cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 20)

project(main LANGUAGES CXX VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(include)
add_subdirectory(source)
target_link_libraries(${PROJECT_NAME} library)
