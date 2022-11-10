cmake_minimum_required(VERSION 3.23)
project(task1_5)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(shipping_logic)
add_subdirectory(user_menu)
add_subdirectory(admin_menu)

target_link_libraries(user_menu shipping_logic)
target_link_libraries(admin_menu shipping_logic)