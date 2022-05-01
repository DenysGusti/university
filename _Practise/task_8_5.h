#ifndef TASK_8_5_H
#define TASK_8_5_H

#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <ranges>

using namespace std;

class BattleshipMatrix {
private:
    vector<vector<int>> matrix;
    pair<int, int> size;
    unsigned ships{};

    unsigned countShips();

public:
    explicit BattleshipMatrix(vector<vector<int>>);

    void printMatrix() const noexcept;

    unsigned getShips() const noexcept;
};

vector<vector<int>> enterMatrix();

vector<BattleshipMatrix> readMatrices();

void printMatricesWithMaximalNumberOfObjects(const vector<BattleshipMatrix> &);

#endif
