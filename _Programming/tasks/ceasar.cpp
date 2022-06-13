#include <iostream>
#include <cstring>

using namespace std;

int main() {
    const size_t max_size = 100;
    int k{};
    char p[max_size], c[max_size], d[max_size];
    cin.getline(p, max_size);
    strcpy_s(c, max_size, p);
    strcpy_s(d, max_size, p);
    cout << "k: ";
    cin >> k;
    cout << p << '\n';

    cout << "ciphering...\n";
    for (size_t i = 0; i < strnlen_s(p, max_size); ++i)
        if ('A' <= p[i] && p[i] <= 'Z')
            c[i] = static_cast<char>('A' + ((p[i] - 'A' + k) % 26 + 26) % 26);
        else if ('a' <= p[i] && p[i] <= 'z')
            c[i] = static_cast<char>('a' + ((p[i] - 'a' + k) % 26 + 26) % 26);
        else
            c[i] = p[i];
    cout << c << '\n';

    cout << "deciphering...\n";
    for (size_t i = 0; i < strnlen_s(p, max_size); ++i)
        if ('A' <= p[i] && p[i] <= 'Z')
            d[i] = static_cast<char>('A' + ((p[i] - 'A' - k) % 26 + 26) % 26);
        else if ('a' <= p[i] && p[i] <= 'z')
            d[i] = static_cast<char>('a' + ((p[i] - 'a' - k) % 26 + 26) % 26);
        else
            d[i] = p[i];
    cout << d << endl;
    return 0;
}

// Be sure to drink your Ovaltine!
// Or fher gb qevax lbhe Binygvar!
// Ps gifs hc rfwby mcif Cjozhwbs!
// Lo cebo dy nbsxu iyeb Yfkvdsxo!