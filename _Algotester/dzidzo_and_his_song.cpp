#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    string s;
    getline(cin, s);

    int result = s.size();

    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            --result;
        }
    }

    cout << result << endl;
}

