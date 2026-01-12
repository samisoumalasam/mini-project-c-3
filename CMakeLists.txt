cmake_minimum_required(VERSION 4.0)
project(mini_project_c_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(mini_project_c_3 main.c
        utils.c
        utils.h)
target_link_libraries(mini_project_c_3 m)
