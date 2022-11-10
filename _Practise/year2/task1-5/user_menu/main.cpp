#include <memory>

#include "user_menu.hpp"

int main() {
    const auto data = make_shared<ShippingList>(
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-5\shippings.txt)",
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-5\output.txt)");

    AdminMenu menu{data};
    return 0;
}