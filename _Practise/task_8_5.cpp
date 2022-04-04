#include "task_8_5.h"

int main() {
    auto pMatrices = read_matrices();
    print_matrices_with_maximal_number_of_objects(*pMatrices);
    for (const auto &element: *pMatrices) {
        element->print_matrix();
        cout << '\n' << "ships: " << element->getShips() << '\n';
    }
// test
//    auto obj1 = BattleshipMatrix({
//                                         {1, 1, 1, 1, 1, 1},
//                                         {0, 0, 0, 0, 0, 0},
//                                         {1, 0, 0, 0, 0, 1},
//                                         {0, 0, 0, 0, 0, 0},
//                                         {1, 1, 1, 1, 1, 1},
//                                 });
//    auto obj2 = BattleshipMatrix({
//                                         {1, 1, 1, 1, 1, 1},
//                                         {1, 1, 1, 1, 1, 1},
//                                         {0, 0, 0, 0, 0, 0},
//                                         {0, 0, 0, 0, 1, 1},
//                                         {0, 0, 0, 0, 1, 1},
//                                 });
//    auto obj3 = BattleshipMatrix({
//                                         {1, 0, 1, 1, 1, 1},
//                                         {0, 0, 1, 1, 1, 1},
//                                         {0, 0, 1, 1, 1, 1},
//                                         {0, 0, 1, 1, 1, 1},
//                                         {1, 0, 0, 0, 0, 0},
//                                 });
//
//    vector<unique_ptr<BattleshipMatrix>> TestMatrices;
//    TestMatrices.push_back(make_unique<BattleshipMatrix>(obj1));
//    TestMatrices.push_back(make_unique<BattleshipMatrix>(obj2));
//    TestMatrices.push_back(make_unique<BattleshipMatrix>(obj3));
//    print_matrices_with_maximal_number_of_objects(TestMatrices);
//    cout << "\n----------\n";
//    for (const auto &element: TestMatrices) {
//        element->print_matrix();
//        cout << '\n' << "ships: " << element->getShips() << '\n';
//    }
    return 0;
}
