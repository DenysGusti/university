#include "task_8_5.h"

unsigned BattleshipMatrix::countShips() {
    unsigned count{};
    const auto &[columns, rows] = size;
    const array<array<int, 2>, 2> directions = {{{1, 0}, {0, 1}}};
    vector<vector<bool>> used(columns, vector<bool>(rows));
    stack<pair<int, int>> dfs;

    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < rows; ++j)
            if (matrix[i][j] && !used[i][j]) {
                dfs.emplace(i, j);
                while (!dfs.empty()) {
                    const auto [c, r] = dfs.top();
                    dfs.pop();
                    used[c][r] = true;
                    for (auto &[di, dj]: directions)
                        if (c + di < columns && r + dj < rows)
                            if (matrix[c + di][r + dj])
                                dfs.emplace(c + di, r + dj);
                }
                ++count;
            }
    return count;
}

BattleshipMatrix::BattleshipMatrix(vector<vector<int>> m)
        : matrix{move(m)}, size{matrix.size(), matrix.at(0).size()}, ships{countShips()} {}

void BattleshipMatrix::printMatrix() const noexcept {
    cout << '\n';
    for (auto &row: as_const(matrix))
        for (auto &el: row)
            cout << el << (&el == &row.back() ? '\n' : ' ');
}

unsigned BattleshipMatrix::getShips() const noexcept {
    return ships;
}

vector<vector<int>> enterMatrix() {
    size_t c{}, r{};
    cout << "Enter m and n: ";
    cin >> c >> r;
    cout << "Enter matrix:\n";
    vector<vector<int>> arr(c, vector<int>(r));
    for (auto &row: arr)
        for (auto &el: row)
            cin >> el;
    return arr;
}

vector<BattleshipMatrix> readMatrices() {
    size_t k{};
    cout << "Enter k: ";
    cin >> k;
    vector<BattleshipMatrix> BMarr;
    BMarr.reserve(k);
    for (int i = 0; i < k; ++i) {
        cout << "\nEnter matrix " << static_cast<char>(i + 65) << "[m*n]:\n";
        BMarr.emplace_back(enterMatrix());
    }
    return BMarr;
}

void printMatricesWithMaximalNumberOfObjects(const vector<BattleshipMatrix> &arr) {
    auto n = ranges::max_element(arr, [](auto &el1, auto &el2) { return el1.getShips() < el2.getShips(); })->getShips();

    cout << "\nMaximal number of objects: " << n << '\n';
    for (int i = 1; auto &obj: arr) {
        if (obj.getShips() == n) {
            cout << "Matrix " << i;
            obj.printMatrix();
        }
        ++i;
    }
}