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
    vector<vector<int>> matrix; // матриця
    pair<int, int> size; // її розмір
    unsigned ships{}; // кількість кораблів в об'єкті

    unsigned countShips(); // рахує кораблі

public:
    explicit BattleshipMatrix(vector<vector<int>>); // конструктор

    void printMatrix() const noexcept; // друкує матрицю

    unsigned getShips() const noexcept; // ґеттер кораблів
};

vector<vector<int>> enterMatrix(); // читає матрицю

vector<BattleshipMatrix> readMatrices(); // створює масив об'єктів

void printMatricesWithMaximalNumberOfObjects(const vector<BattleshipMatrix> &); // шукає max кораблі в масиві об'єктів

#endif
