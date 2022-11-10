cmake_minimum_required(VERSION 3.23)
project(shipping_logic)

set(CMAKE_CXX_STANDARD 23)
set(/O2)

add_library(shipping_logic STATIC
        exceptions/goods_exception.hpp
        exceptions/menu_exception.hpp
        exceptions/option_exception.hpp

        logistics/factory/shipping_factory.hpp
        logistics/factory/transport_interface.hpp

        logistics/list_interfaces/dynamic_list.hpp
        logistics/list_interfaces/my_list.hpp
        logistics/list_interfaces/printable_list.hpp

        logistics/shipping_members/driver.hpp
        logistics/shipping_members/goods.hpp
        logistics/shipping_members/shipping_member.hpp
        logistics/shipping_members/warehouse.hpp

        logistics/transport_types/plane.hpp
        logistics/transport_types/ship.hpp
        logistics/transport_types/train.hpp
        logistics/transport_types/truck.hpp

        logistics/shipping_list.hpp
        logistics/shipping.hpp

        logistics/named_object.hpp

        main.cpp)

set_target_properties(shipping_logic PROPERTIES LINKER_LANGUAGE CXX)