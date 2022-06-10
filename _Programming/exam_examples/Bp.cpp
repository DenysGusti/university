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
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\exam_examples\in1.txt)"};
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_Programming\exam_examples\out.txt)"};
    fout << "Input:\n";
    cout << "Input:\n";
    printStream(fin, fout);
    printStream(fin, cout);
    fout << "\nOutput:\n";
    cout << "\nOutput:\n";

    char target[] = "testing";
    for (char line[100], newLine[100], *res; fin.getline(line, 100); fout << newLine << '\n', cout << newLine << '\n') {
        size_t last = 0, len = strlen(target);
        strcpy_s(newLine, "");
        res = line;
        for (bool del = true; (res = strstr(res, target)) != nullptr; ++res)
            if (line[res - line + len] == '*' && line[res - line - 1] == '*' ||
                res - line + len == strlen(line) && line[res - line - 1] == '*' ||
                line[res - line + len] == '*' && res - line == 0) {
                strncat_s(newLine, 100, line + last, res - line - last + (del ? 0 : len + 1));
                last = res - line + len + 1;
                del = !del;
            }
        if (strlen(line) > last)
            strcat_s(newLine, line + last);
        else if (newLine[strlen(newLine) - 1] == '*')
            strncpy_s(newLine, newLine, strlen(newLine) - 1);
    }
    return 0;
}