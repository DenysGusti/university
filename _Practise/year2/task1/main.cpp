#include <memory>

#include "menu.h"
#include "shipping_list.h"

int main() {
    const auto data = make_shared<ShippingList>(
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1\shippings.txt)",
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1\output.txt)");

    Menu menu(data);
    return 0;
}