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
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\bilet_1\in1.txt)"};
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_Programming\bilet_1\out.txt)"};
    fout << "Input:\n";
    cout << "Input:\n";
    printStream(fin, fout);
    printStream(fin, cout);
    fout << "\nOutput:\n";
    cout << "\nOutput:\n";

    for (char line[100], newLine[100]; fin.getline(line, 100); fout << newLine << '\n', cout << newLine << '\n') {
        bool flag = true;
        for (size_t i = 0; i < strlen(line) - 1; ++i)
            if (line[i] == ' ' && line[i + 1] == ' ') {
                flag = false;
                break;
            }

        char comment[100];
        if (flag)
            strcpy_s(comment, 100, " // one space");
        else
            strcpy_s(comment, 100, " // more than one space");

        strcpy_s(newLine, 100, line);
        strcat_s(newLine, comment);
    }
    return 0;
}