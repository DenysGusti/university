#include <iostream>

#include "admin_states.hpp"
#include "../functions.hpp"

using namespace std;

int main() {
    functionWrapper(inputHandle, Menu{make_unique<StateBaseMenuAdmin>(), make_unique<ShippingList>(
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-5\shippings.txt)",
            R"(C:\Users\denys\CLionProjects\University\university\_Practise\year2\task1-5\output.txt)"
    )});
    return 0;
}