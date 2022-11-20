cmake_minimum_required(VERSION 3.23)
project(user_menu)

set(CMAKE_CXX_STANDARD 23)
set(/O2)

add_executable(user_menu main.cpp ../states.hpp)

target_link_libraries(user_menu shipping_logic)