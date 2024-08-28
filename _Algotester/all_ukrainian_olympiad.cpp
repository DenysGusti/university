#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    //4+((7-4)+(4+4))*(7-4)
    string s;
    getline(cin, s);

    vector<int> l = {};
    vector<int> r = {};

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            l.push_back(i + 1);
        }
    }

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ')') {
            r.push_back(i + 1);
        }
    }

//    for(auto& c : l){
//        cout << c << ' ';;
//    }
//
//    cout << endl;
//
//    for(auto& c : r){
//        cout << c << ' ';
//    }

    cout << l.size() << '\n';

    int i = 0, j = 0;
    vector<int> st;

    while (j < r.size()) {
        if (l[i] < r[j] && i < l.size()) {
            st.push_back(l[i]);
            i++;
        } else {
            cout << st.back() << ' ' << r[j] << '\n';
            st.pop_back();
            j++;
        }
    }

}

