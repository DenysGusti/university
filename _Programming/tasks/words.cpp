#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\tasks\words.txt)"};

    map<pair<uint8_t, uint8_t>, int8_t> dict_ua_en;
    string ua_alpha = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя", en_alpha = "abvhgdeEZzyiIjklmnoprstufxcTSqwUA";
    for (size_t i = 0; i < ua_alpha.length(); i += 2)
        dict_ua_en[{ua_alpha[i], ua_alpha[i + 1]}] = en_alpha[i / 2];

    size_t m, n;
    fin >> m >> n;
    fin.ignore();
    vector<string> table(m), new_table(m);
    string target = "задача", new_target;

    for (auto &el: table)
        getline(fin, el);

    for (size_t i = 0; i < target.length(); i += 2)
        new_target += dict_ua_en[{target[i], target[i + 1]}];

    for (size_t i = 0; i < table.size(); ++i)
        for (size_t j = 0; j < table[i].length(); ++j)
            if (-48 <= table[i][j] && table[i][j] <= -46)
                new_table[i] += dict_ua_en[{table[i][j], table[i][++j]}];
            else
                new_table[i] += table[i][j];

    for (const auto &el: table)
        cout << el << '\n';
    cout << '\n' << target << "\n\n";

    uint16_t counter{};
    for (size_t i = 0; i < new_table.size(); ++i)
        for (size_t j = 0; j < new_table[i].length(); ++j) {
            if (j < new_table[i].length() - new_target.length() + 1)
                if (new_table[i].substr(j, new_target.length()) == new_target)
                    ++counter;
            if (i < new_table.size() - new_target.length() + 1) {
                string tmp;
                for (size_t k = 0; k < new_target.length(); ++k)
                    tmp += new_table[i + k][j];
                if (tmp == new_target)
                    ++counter;
            }
            if (i < new_table.size() - new_target.length() + 1 && j < new_table[i].length() - new_target.length() + 1) {
                string tmp;
                for (size_t k = 0; k < new_target.length(); ++k)
                    tmp += new_table[i + k][j + k];
                if (tmp == new_target)
                    ++counter;
            }
            if (i > new_target.length() - 2 && j < new_table[i].length() - new_target.length() + 1) {
                string tmp;
                for (size_t k = 0; k < new_target.length(); ++k)
                    tmp += new_table[i - k][j + k];
                if (tmp == new_target)
                    ++counter;
            }
        }

    cout << counter << endl;
    return 0;
}