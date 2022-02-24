#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    int x, y;
    cin >> s;
    cin >> x >> y;
    int r = count(s.begin(), s.end(), 'R');
    int u = s.length() - r;
    if (x <= r && y <= u){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}