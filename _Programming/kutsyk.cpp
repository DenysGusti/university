#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main() {
    vector<string> s, temp;
    for (string tmp; cin.peek() != '\n' && cin >> tmp;)
        s.emplace_back(tmp);
    while (s.size() > 1) {
        for (size_t i = 0; i < s.size(); ++i)
            if (i < s.size() - 2) {
                if ((isdigit(s[i][0]) || isdigit(s[i][1])) && (isdigit(s[i + 1][0]) || isdigit(s[i + 1][1])) &&
                    !(isdigit(s[i + 2][0]) || isdigit(s[i + 2][1]))) {
                    switch (s[i + 2][0]) {
                        case '+':
                            temp.emplace_back(to_string(stoi(s[i]) + stoi(s[i + 1])));
                            break;
                        case '-':
                            temp.emplace_back(to_string(stoi(s[i]) - stoi(s[i + 1])));
                            break;
                        case '*':
                            temp.emplace_back(to_string(stoi(s[i]) * stoi(s[i + 1])));
                            break;
                        case '/':
                            temp.emplace_back(to_string(stoi(s[i]) / stoi(s[i + 1])));
                            break;
                        case '^':
                            temp.emplace_back(to_string(static_cast<int>(pow(stod(s[i]), stod(s[i + 1])))));
                            break;
                    }
                    i += 2;
                } else
                    temp.emplace_back(s[i]);
            } else
                temp.emplace_back(s[i]);
        s = temp;
        temp.clear();
    }
    cout << s[0] << endl;
    return 0;
}

// 1 5 3 - + 4 *