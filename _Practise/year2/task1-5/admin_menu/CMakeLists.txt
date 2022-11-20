cmake_minimum_required(VERSION 3.23)
project(admin_menu)

set(CMAKE_CXX_STANDARD 23)
set(/O2)

add_executable(admin_menu main.cpp ../states.hpp)

target_link_libraries(admin_menu shipping_logic)