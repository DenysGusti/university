#include "task_8_5.h"

unsigned BattleshipMatrix::countShips() { // рахує кораблі
    unsigned count{};
    const auto &[columns, rows] = size; // structured binding, розархівовую для зручності
    const array<array<int, 2>, 2> directions = {{{1, 0}, {0, 1}}}; // напрямки пошуку, вправо і вниз
    vector<vector<bool>> used(columns, vector<bool>(rows)); // булева матриця відвіданих
    stack<pair<int, int>> dfs; // стек клітинок на основі дек

    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < rows; ++j)
            if (matrix[i][j] && !used[i][j]) { // пошук компонент зв'язності
                dfs.emplace(i, j);  // то саме, що push, просто з конструктором
                while (!dfs.empty()) {  // поки стек не пустий
                    const auto [c, r] = dfs.top(); // копія, не референс, бо стек міняє розмір в процесі
                    dfs.pop(); // last in first out
                    used[c][r] = true; // позначаємо клітинку відвіданою
                    for (auto &[di, dj]: directions) // сусідні клітинки справа і внизу
                        if (c + di < columns && r + dj < rows) // щоб не вилізло за межі матриці
                            if (matrix[c + di][r + dj]) // якщо сусідня = 1
                                // умову треба було розділити, щоб не вилізло не туди в пам'яті
                                dfs.emplace(c + di, r + dj); // додаємо сусідню в стек
                }
                ++count;  // + 1 компонента
            }
    return count;
}

BattleshipMatrix::BattleshipMatrix(vector<vector<int>> m) // конструктор
        : matrix{move(m)}, size{matrix.size(), matrix.at(0).size()}, ships{countShips()} {}
//      move для оптимізації, щоб вхідна матриця не копіювалася, а вказівник matrix почав вказувати на місце m

void BattleshipMatrix::printMatrix() const noexcept { // друкує матрицю, noexept для оптимізації, не викине помилку
    cout << '\n';
    for (auto &row: as_const(matrix)) // as_const робить весь масив const (+ захист від deepcopy)
        for (auto &el: row)
            cout << el << (&el == &row.back() ? '\n' : ' '); // форматування, перейти на новий рядок
}

unsigned BattleshipMatrix::getShips() const noexcept { // ґеттер кораблів
    return ships;
}

vector<vector<int>> enterMatrix() { // читає матрицю
    size_t c{}, r{}; // = unsigned int, безпечніше для розмірів
    cout << "Enter m and n: ";
    cin >> c >> r;
    cout << "Enter matrix:\n";
    vector<vector<int>> arr(c, vector<int>(r));
    for (auto &row: arr) // ввід
        for (auto &el: row)
            cin >> el;
    return arr;
}

vector<BattleshipMatrix> readMatrices() { // створює масив об'єктів
    size_t k{};
    cout << "Enter k: ";
    cin >> k;
    vector<BattleshipMatrix> BMarr;
    BMarr.reserve(k); // збільшуємо місткість до k елементів, резервуємо пам'ять наперед (оптимізація при збільшенні)
    for (int i = 0; i < k; ++i) {
        cout << "\nEnter matrix " << static_cast<char>(i + 65) << "[m*n]:\n";
        BMarr.emplace_back(enterMatrix()); // то саме що push_back, але з конструктором, оптимізація від копіювання
    }
    return BMarr;
}

void printMatricesWithMaximalNumberOfObjects(const vector<BattleshipMatrix> &arr) {
    auto n = ranges::max_element(arr, {}, &BattleshipMatrix::getShips)->getShips();
    // ranges (C++ 20) перегружає функції для зручності роботи з масивами, max_element вертає ітератор на найбільший ел.
    // приймає масив, компаратор (за замовчуванням less(), {}) і проєкцію (незмінний об'єкт, за яким порівнюють)
    cout << "\nMaximal number of objects: " << n << '\n';
    for (int i = 1; auto &obj: arr) { // може бути декілька з найбільшою кількістю, тому проходимося 2 раз
        if (obj.getShips() == n) {
            cout << "\nMatrix " << i;
            obj.printMatrix();
        }
        ++i;
    }
}