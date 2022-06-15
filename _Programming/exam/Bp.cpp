#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void printStream(istream &in, ostream &out) {
    in.clear();
    in.seekg(0, ios::beg);
    for (char line[100]; in.getline(line, 100);)
        out << line << '\n';
    in.clear();
    in.seekg(0, ios::beg);
}

int main() {
    ifstream fin{"in1.txt"};
    ofstream fout{"out.txt"};
    fout << "Input:\n";
    cout << "Input:\n";
    printStream(fin, fout);
    printStream(fin, cout);
    fout << "\nOutput:\n";
    cout << "\nOutput:\n";

    char line[100];
    fin.getline(line, 100);

    char *res = line, buf[100];

    for (size_t len; res; res = strchr(res, '-'), res ? res += 2: nullptr) {
        len = strchr(res, '-') - res;
        strncpy_s(buf, res, len);

        if (buf[0] == 'd' && buf[1] == 'd') {
            fout << buf << ' ';
            cout << buf << ' ';
        }
    }
    return 0;
}