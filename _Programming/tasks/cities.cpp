#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\tasks\cities.txt)"};
    vector<vector<string>> cities;
    string target, tmp;

    for (size_t i = 0; getline(fin, tmp);)
        if (!tmp.empty()) {
            cities.emplace_back(vector<string>());
            istringstream line{tmp};
            for (string temp; line >> temp; cities[i].emplace_back(temp))
                if (temp.back() == ',')
                    temp.pop_back();
            ++i;
        }

    target = cities.back()[0];
    cities.pop_back();

    unordered_map<string, size_t> idx;
    unordered_map<size_t, string> re_idx;
    for (size_t i = -1; const auto &line: cities)
        for (const auto &city: line)
            if (idx.find(city) == idx.end() && city != "Н") {
                idx[city] = ++i;
                re_idx[i] = city;
            }

    vector<vector<bool>> matrix(idx.size(), vector<bool>(idx.size()));
    for (const auto &line: cities)
        for (const auto &city: line)
            if (&city != &line.front() && city != "Н")
                matrix[idx[line.front()]][idx[city]] = true;

    for (size_t k = 0; k < idx.size(); ++k)
        for (size_t i = 0; i < idx.size(); ++i)
            for (size_t j = 0; j < idx.size(); ++j)
                if (matrix[i][k] && matrix[k][j])
                    matrix[i][j] = true;

    cout << target << ": ";
    for (size_t i = 0; i < idx.size(); ++i)
        if (matrix[idx[target]][i])
            cout << re_idx[i] << (i < idx.size() - 1 ? ", " : "\n");
    return 0;
}