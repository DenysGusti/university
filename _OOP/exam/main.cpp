#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

static const string path = R"(C:\Users\denys\CLionProjects\University\university\_OOP\exam\)";  // change!

// -побудувати абстрактний клас для опрацювання зазначених даних (5 балів);
// абстрактний клас повинний мати хоча б одну чисто віртуальну функцію (метод);
class IdObject {
protected:
    uint64_t id{};
public:
    IdObject() = default;

    explicit IdObject(const uint64_t id_) : id{id_} {}

    virtual ~IdObject() = default;

    uint64_t getId() const noexcept {
        return id;
    }

    void setId(const uint64_t id_) noexcept {
        id = id_;
    }

    // чисто віртуальна функція
    virtual string getInfo() const noexcept = 0;
};


// -побудувати батьківський клас на основі абстрактного (5 балів); клас повинний мати такі поля: деяку назву об’єкта
// (для кожного – своя – з файла), код об'єкта – ціле число або текстовий рядок, дані про об’єкт отримані з файла;
// хоча б одне з полів має бути вказівником;
class Car : public IdObject {
protected:
    string company, model, owner;
    float *price{};
    uint64_t capacity{};
public:
    // -батьківський і дочірній класи повинні мати свої окремі конструктори і деструктор (5 балів);
    // конструкторів має бути три для кожного класу: конструктор без параметрів, конструктор з параметрами,
    // конструктор копіювання; деструктор має друкувати повідомлення про припинення існування об’єкта з зазначенням
    // його назви;
    Car() = default;

    Car(const uint64_t id_, string_view company_, string_view model_, string_view owner_, const float price_,
        const uint64_t capacity_) :
            IdObject{id_}, company{company_}, model{model_}, owner{owner_}, price{new float{price_}},
            capacity{capacity_} {}

    Car(const Car &other) :
            IdObject{other}, company{other.company}, model{other.model}, owner{other.owner},
            price{new float{*other.price}},
            capacity{other.capacity} {}

    // -вибрати, обгрунтувати і побудувати деяку перевантажену операцію бінарну чи унарну (5 балів);
    Car &operator=(const Car &other) { // оператор присвоєння, оскільки вже перевантажений конструктор копіювання
        if (this == &other)
            return *this;

        id = other.id;
        company = other.company;
        model = other.model;
        *price = *other.price;
        capacity = other.capacity;
    }

    ~Car() override {
        delete price;
        cout << "car deleted" << endl;
    }

    string getInfo() const noexcept override {
        return "id: " + to_string(id) + "; company: " + company + "; model: " + model + "; owner: " + owner +
               "; price: " + to_string(*price) + "; capacity: " + to_string(capacity) + '\n';
    };

    string getCompany() const noexcept {
        return company;
    }

    // -побудувати методи редагування змісту об’єкта (5 балів);
    void setCompany(string_view company_) {
        company = company_;
    }

    // -побудувати методи доступу до потрібних полів об’єкта або методи обчислювальних операцій (5 балів);
    string getModel() const noexcept {
        return company;
    }

    void setModel(string_view company_) {
        company = company_;
    }

    string getOwner() const noexcept {
        return owner;
    }

    void setOwner(string_view owner_) {
        owner = owner_;
    }

    float getPrice() const {
        return *price;
    }

    void setPrice(const float price_) const {
        *price = price_;
    }

    uint64_t getCapacity() const noexcept {
        return capacity;
    }

    void setCapacity(const uint64_t capacity_) {
        capacity = capacity_;
    }
};

// -побудувати дочірній клас на основі батьківського (5 балів); дочірній клас повинний матихоча б одне нове поле,
// хоча б один новий метод відносно батьківського і хоча б один перекритий метод;
class SportCar : public Car {
private:
    uint64_t maxSpeed{};
    uint64_t horsepower{};
public:
    SportCar() = default;

    SportCar(const uint64_t id_, string_view company_, string_view model_, string_view owner_, const float price_,
             const uint64_t capacity_, const uint64_t maxSpeed_, const uint64_t horsepower_) :
            Car{id_, company_, model_, owner_, price_, capacity_}, maxSpeed{maxSpeed_}, horsepower{horsepower_} {}

    string getInfo() const noexcept override {
        return "id: " + to_string(id) + "; company: " + company + "; model: " + model + "; owner: " + owner +
               "; price: " + to_string(*price) + "; capacity: " + to_string(capacity) + "; max speed: " +
               to_string(maxSpeed) + "; horsepower: " + to_string(horsepower) + '\n';
    };

    uint64_t getMaxSpeed() const noexcept {
        return maxSpeed;
    }

    void setMaxSpeed(const uint64_t maxSpeed_) {
        maxSpeed = maxSpeed_;
    }

    uint64_t getHorsepower() const noexcept {
        return horsepower;
    }

    void setHorsepower(const uint64_t horsepower_) {
        horsepower = horsepower_;
    }
};

class FamilyCar : public Car {
private:
    uint64_t maxWeight{};
    uint64_t consumption{};
public:

    FamilyCar() = default;

    FamilyCar(const uint64_t id_, string_view company_, string_view model_, string_view owner_, const float price_,
              const uint64_t capacity_, const uint64_t maxWeight_, const uint64_t consumption_) :
            Car{id_, company_, model_, owner_, price_, capacity_}, maxWeight{maxWeight_}, consumption{consumption_} {}

    string getInfo() const noexcept override {
        return "id: " + to_string(id) + "; company: " + company + "; model: " + model + "; owner: " + owner +
               "; price: " + to_string(*price) + "; capacity: " + to_string(capacity) + "; max weight: " +
               to_string(maxWeight) + "; consumption: " + to_string(consumption) + '\n';
    };

    uint64_t getMaxWeight() const noexcept {
        return maxWeight;
    }

    void setMaxWeight(const uint64_t maxWeight_) {
        maxWeight = maxWeight_;
    }

    uint64_t getConsumption() const noexcept {
        return consumption;
    }

    void setConsumption(const uint64_t consumption_) {
        consumption = consumption_;
    }
};

class Statistics {
public:
    virtual float getTotalPrice() const noexcept = 0;

    virtual void sortById() noexcept = 0;

    virtual void sortByCompany() noexcept = 0;

    virtual void sortByModel() noexcept = 0;

    virtual void sortByOwner() noexcept = 0;

    virtual void sortByPrice() noexcept = 0;

    virtual ~Statistics() = default;
};

class InputOutputCars {
public:
    virtual void registerCarsFromFile() = 0;

    virtual void registerCarFromTerminal() = 0;

    // -побудувати методи відображення об’єкта в текстовий файл і на екран (5 балів);
    virtual void printCarsToFile() const noexcept = 0;

    virtual void printCarsToTerminal() const noexcept = 0;

    virtual ~InputOutputCars() = default;
};

class Inspection : public InputOutputCars, public Statistics {
private:
    // -використати стандартну бібліотеку шаблонів STL і один з контейнерів list, map, vector, set для зберігання
    // всіх об’єктів (10 балів); продемонструвати операції з контейнером для пошуку і редагування об’єктів;
    // показати використання функторів або предикатів.
    vector<Car *> cars;

    void printCars(ostream &os) const noexcept {
        for (const auto &car: cars)
            os << car->getInfo();
    }

    void registerCar(istream &is) {
        string company, model, owner;
        float price{};
        uint64_t id{}, capacity{};

        if (&is == &cin)
            cout << "print id:" << endl;
        is >> id;

        if (&is == &cin)
            cout << "print company:" << endl;
        is >> company;

        if (&is == &cin)
            cout << "print model:" << endl;
        is >> model;

        if (&is == &cin)
            cout << "print owner:" << endl;
        is >> owner;

        if (&is == &cin)
            cout << "print price:" << endl;
        is >> price;

        if (&is == &cin)
            cout << "print capacity:" << endl;
        is >> capacity;

        cars.push_back(new Car{id, company, model, owner, price, capacity});
    }

public:
    void printCarsToFile() const noexcept override {
        ofstream fout{path + "out.txt"};
        printCars(fout);
    }

    void printCarsToTerminal() const noexcept override {
        printCars(cout);
    }

    void registerCarsFromFile() override {
        try { // -включити технологію захисту від помилок try-throw-catch.
            ifstream fin{path + "in.txt"};

            if (!fin.is_open())
                throw exception(string{"input file not found!\ncheck your path: " + path}.c_str());

            while (!fin.eof())
                registerCar(fin);

        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }

    void registerCarFromTerminal() override {
        registerCar(cin);
    }

    // метод обчислювальних операцій
    float getTotalPrice() const noexcept override {
        float sum = 0;
        for (const auto &car: cars)
            sum += car->getPrice();
        return sum;
    }

    // сортування контейнеру vector
    void sortById() noexcept override { // функтор лямбда вираз
        sort(cars.begin(), cars.end(), [](const Car *car1, const Car *car2) { return car1->getId() < car2->getId(); });
    }

    void sortByCompany() noexcept override {
        sort(cars.begin(), cars.end(),
             [](const Car *car1, const Car *car2) { return car1->getCompany() < car2->getCompany(); });
    }

    void sortByModel() noexcept override {
        sort(cars.begin(), cars.end(),
             [](const Car *car1, const Car *car2) { return car1->getModel() < car2->getModel(); });
    }

    void sortByOwner() noexcept override {
        sort(cars.begin(), cars.end(),
             [](const Car *car1, const Car *car2) { return car1->getOwner() < car2->getOwner(); });
    }

    void sortByPrice() noexcept override {
        sort(cars.begin(), cars.end(),
             [](const Car *car1, const Car *car2) { return car1->getPrice() < car2->getPrice(); });
    }

    ~Inspection() override {
        for (auto &car: cars)
            delete car;
        cout << "inspection deleted" << endl;
    }
};


int main() {
    Inspection inspection;
    inspection.registerCarsFromFile();

    cout << "total price: " << inspection.getTotalPrice() << '\n';

    inspection.sortByPrice();

    inspection.printCarsToTerminal();
    inspection.printCarsToFile();
    return 0;
}