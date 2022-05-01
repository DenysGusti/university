#include "task_8_5.h"

int main() {
    const auto matrices = readMatrices();
    for (auto &el: matrices) {
        el.printMatrix();
        cout << "ships: " << el.getShips() << '\n';
    }
    printMatricesWithMaximalNumberOfObjects(matrices);
    return 0;
}
/*
3
5 6
1 1 1 1 1 1
0 0 0 0 0 0
1 1 0 1 1 1
0 0 0 0 0 0
1 1 1 1 1 1
5 6
1 1 1 1 1 1
1 1 1 1 1 1
0 0 0 0 0 0
0 0 0 0 1 1
1 1 1 0 1 1
5 6
1 0 1 1 1 1
0 0 1 1 1 1
1 0 1 1 1 1
0 0 1 1 1 1
1 0 1 1 1 1
*/