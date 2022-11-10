#include <memory>

#include "ui/menu.hpp"
#include "logistics/shipping_list.hpp"

int main() {
    const auto data = make_shared<ShippingList>(
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-3\shippings.txt)",
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-3\output.txt)");

    Menu menu{data};
    return 0;
}