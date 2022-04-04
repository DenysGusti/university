#include "task_8_5.h"

void BattleshipMatrix::recursiveDFS(vector<vector<bool>> &visited, int c, int r, array<array<int, 2>, 2> &directions) {
    visited[c][r] = true;
    for (const auto &[columns, rows] = size; auto &[i, j]: directions) {
        int n_c = c + i, n_r = r + j;
        if (n_c < columns && n_r < rows)
            if (!visited[n_c][n_r] && matrix[n_c][n_r])
                recursiveDFS(visited, n_c, n_r, directions);
    }
}

unsigned BattleshipMatrix::countShips() {
    unsigned count = 0;
    const auto &[columns, rows] = size;
    array<array<int, 2>, 2> directions = {{{1, 0}, {0, 1}}};
    vector<vector<bool>> visited(columns, vector<bool>(rows, false));
    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < rows; ++j)
            if (matrix[i][j] && !visited[i][j]) {
                recursiveDFS(visited, i, j, directions);
                ++count;
            }
    return count;
}

BattleshipMatrix::BattleshipMatrix(const vector<vector<int>> &m) : matrix(m) {
    size = {matrix.size(), matrix.at(0).size()};
    ships = countShips();
}

void BattleshipMatrix::print_matrix() {
    cout << '\n';
    for (const auto &row: matrix)
        for (const auto &el: row)
            cout << el << (&el == &row.back() ? '\n' : ' ');
}

unsigned BattleshipMatrix::getShips() const noexcept {
    return ships;
}

unique_ptr<vector<vector<int>>> enter_matrix() {
    int c{}, r{};
    cout << "Enter m and n: ";
    cin >> c >> r;
    cout << "Enter matrix:\n";
    auto pArr = make_unique<vector<vector<int>>>(c, vector<int>(r));
    for (auto &row: *pArr)
        for (auto &el: row)
            cin >> el;
    return pArr;
}

unique_ptr<vector<unique_ptr<BattleshipMatrix>>> read_matrices() {
    int k{};
    cout << "Enter k: ";
    cin >> k;
    auto pBMarr = make_unique<vector<unique_ptr<BattleshipMatrix>>>(k);
    for (char i = 'A'; auto &matrix: *pBMarr) {
        cout << "\nEnter matrix " << i++ << "[m*n]:\n";
        matrix = make_unique<BattleshipMatrix>(*enter_matrix());
        matrix->print_matrix();
    }
    return pBMarr;
}

void print_matrices_with_maximal_number_of_objects(const vector<unique_ptr<BattleshipMatrix>> &arr) {
    unsigned n = 0;
    for (const auto &obj: arr)
        n = max(n, obj->getShips());
    cout << "\nMaximal number of objects: " << n << '\n';
    for (const auto &obj: arr)
        if (obj->getShips() == n)
            obj->print_matrix();
}