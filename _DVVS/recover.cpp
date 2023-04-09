#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <format>

using namespace std;
namespace fs = filesystem;

const static int buf_size = 512;

void recover(istream &fin) {
    fs::path directory = "images";
    if (!exists(directory)) create_directory(directory);

    string jpg_block{0xff - 256, 0xd8 - 256, 0xff - 256};
    string buf(buf_size, {});

    for (; buf.substr(0, 3) != jpg_block; fin.read(buf.data(), buf_size));
    fin.seekg(-buf_size, ios::cur);

    for (ofstream fout; fin.read(buf.data(), buf_size); fout << buf) {
        if (buf.substr(0, 3) == jpg_block) {
            static uint64_t image_number = 0;
            fout.close();
            fout.open(directory / format("0{:0>2}.jpg", image_number++), ios::binary); // C++20
        }
    }
}

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./recover image" << endl;
        return 1;
    }

    fs::path infile{ argv[1] };
    ifstream fin{argv[1], ios::binary};
    if (!fin) {
        cout << "Could not open " << infile << endl;
        return 2;
    }

    recover(fin);
    return 0;
}