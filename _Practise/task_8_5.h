#ifndef TASK_8_5_H
#define TASK_8_5_H

#include <iostream>
#include <vector>
#include <array>
#include <memory>

using namespace std;

class BattleshipMatrix {
private:
    pair<int, int> size;
    unsigned ships{};
    const vector<vector<int>> matrix;

    void recursiveDFS(vector<vector<bool>> &visited, int c, int r, array<array<int, 2>, 2> &directions);

    unsigned countShips();

public:
    explicit BattleshipMatrix(const vector<vector<int>> &m);

    void print_matrix();

    unsigned getShips() const noexcept;
};

unique_ptr<vector<vector<int>>> enter_matrix();

unique_ptr<vector<unique_ptr<BattleshipMatrix>>> read_matrices();

void print_matrices_with_maximal_number_of_objects(const vector<unique_ptr<BattleshipMatrix>> &arr);

#endif
