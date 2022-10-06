#include <iostream>

#include "flotilla_manager.h"

using namespace std;

/*
Варіант 2
Додайте клас Plane для зберігання інформації про літак (назва, марка, кількість місць, об'єм двигуна, наявність
автопілоту). Реалізуйте клас Flotilla для зберігання масиву літаків певної компанії. В даному класі перевизначити
оператор для друку всіх літаків у текстовий файл і оператор “+” для додавання літака у масив. В головній програмі
користувач має мати змогу ввести назву компанії, інформацію про всі літаки, додати літак у флотилію, і надрукувати
інформацію про всі літаки флотилії, у якої найбільше літаків з автопілотом(використовуючи відповідні оператори).
Для стрічок використати тип char*.
*/

int main() {
    Flotilla flotilla1{"companyA"}, flotilla2{"companyB"}, flotilla3{"companyC"};

    flotilla1 += Plane{"a", "b", 1, 2, true};
    flotilla1 += Plane{"c", "d", 3, 4, false};
    flotilla1 += Plane{"e", "f", 5, 6, false};

    flotilla2 += Plane{"g", "h", 7, 8, true};
    flotilla2 += Plane{"c", "d", 9, 10, true};

    flotilla3 += Plane{"a", "b", 11, 12, false};
    flotilla3 += Plane{"c", "d", 13, 14, false};
    flotilla3 += Plane{"e", "f", 15, 16, false};

    FlotillasManager flots;
    flots += flotilla1;
    flots += flotilla2;
    flots += flotilla3;

//    flots.addNewFlotilla();
//    flots[0].addNewPlane();

    size_t maxAutopilotIdx = flots.findFlotillaWithMaxAutopilot();
    flots[maxAutopilotIdx].printToFile(); // change file path!
    cout << flots[maxAutopilotIdx] << endl;
    return 0;
}