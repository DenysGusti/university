// Реалізувати структуру Автомобіль з полями: Марка (стрічка), Модель (стрічка), рік випуску (ціле число), об’єм двигуна
// (дійсне число). Зчитати список автомобілів, заданий у вхідному файлі. Посортувати по Марці та Моделі, вивести у
// вихідний файл. Вивести на екран інформацію про найстаріший автомобіль.

#include <fstream>
#include "cw3_task_1_6.h"

using namespace std;

int main() {
    fstream fs{"cw3_1.txt"};

    if (fs.is_open()) {
        try {
            size_t n;
            fs >> n;
            auto arr = new Car *[n];

            for (size_t i = 0; i < n; ++i) {
                char b[20], m[20];
                int y;
                double v;
                fs >> b >> m >> y >> v;
                cout << b << ' ' << m << ' ' << y << ' ' << v << '\n';
                arr[i] = new Car(b, m, y, v);
                cout << arr[i]->brand << ' ' << arr[i]->model << ' ' << arr[i]->year << ' ' << arr[i]->volume << '\n';
            }

            printArray(cout, "Масив:", arr, n);
            fs.seekg(0, ios::end);

            mergeSort(arr, n, 0);
            printArray(cout, "Посортовані по марці:", arr, n);
            printArray(fs, "Посортовані по марці:", arr, n);

            mergeSort(arr, n, 1);
            printArray(cout, "Посортовані по моделі:", arr, n);
            printArray(fs, "Посортовані по моделі:", arr, n);

            findTheOldest(arr, n);

            delete[] arr;
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    } else
        cerr << "Файл не відкрився" << endl;
    return 0;
}