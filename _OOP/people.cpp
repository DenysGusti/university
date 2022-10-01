#include <iostream>

using namespace std;

class Person {
protected:
    const char *name = "", *surname = "";
    int age{};

public:
    Person() = default;

    Person(const char *name_, const char *surname_, const int age_) : name{name_}, surname{surname_}, age{age_} {}

    Person(const Person &other) = default;

    Person &operator=(const Person &other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            age = other.age;
        }
        return *this;
    }

    virtual ~Person() = default;

    virtual void Print_info() {
        cout << "Person: " << name << ' ' << surname << ' ' << age << endl;
    }

    int get_age() const {
        return age;
    }
};

class Employer : virtual public Person {
protected:
    const char *position = "";
    int salary{};

public:
    Employer() = default;

    Employer(const char *name_, const char *surname_, const int age_, const char *position_, const int salary_)
            : Person(name_, surname_, age_), position(position_), salary(salary_) { cout << "call e" << endl; }

    Employer(const Employer &other) = default;

    Employer &operator=(const Employer &other) {
        if (this != &other) {
            Person::operator=(other);
            position = other.position;
            salary = other.salary;
        }
        return *this;
    }

    ~Employer() override = default;

    void Print_info() override {
        cout << "Employer: " << name << ' ' << surname << ' ' << age << ' ' << position << ' ' << salary << endl;
    }
};

class Teacher : virtual public Employer {
protected:
    const char *university = "";

public:
    Teacher() = default;

    Teacher(const char *name_, const char *surname_, const int age_, const char *position_, const int salary_,
            const char *university_)
            : Person(name_, surname_, age_), Employer(name_, surname_, age_, position_, salary_),
              university(university_) {}

    Teacher(const Teacher &other) = default;

    Teacher &operator=(const Teacher &other) {
        if (this != &other) {
            Employer::operator=(other);
            university = other.university;
        }
        return *this;
    }

    ~Teacher() override = default;

    void Print_info() override {
        cout << "Teacher: " << name << ' ' << surname << ' ' << age << ' ' << position << ' ' << salary <<
             ' ' << university << endl;
    }
};

class Student : virtual public Person {
protected:
    const char *group = "";
    int course{};

public:
    Student() = default;

    Student(const char *name_, const char *surname_, const int age_, const char *group_, const int course_)
            : Person(name_, surname_, age_), group(group_), course(course_) {}

    Student(const Student &other) = default;

    Student &operator=(const Student &other) {
        if (this != &other) {
            Person::operator=(other);
            group = other.group;
            course = other.course;
        }
        return *this;
    }

    ~Student() override = default;

    void Print_info() override {
        cout << "Student: " << name << ' ' << surname << ' ' << age << ' ' << group << ' ' << course << endl;
    }
};

class Postgraduate : public Teacher, public Student {
public:
    Postgraduate() = default;

    Postgraduate(const char *name_, const char *surname_, const int age_, const char *position_, const int salary_,
                 const char *university_, const char *group_, const int course_)
            : Teacher(name_, surname_, age_, position_, salary_, university_),
              Employer(name_, surname_, age_, position_, salary_),
              Student(name_, surname_, age_, group_, course_), Person(name_, surname_, age_) {}

    Postgraduate(const Postgraduate &other) = default;

    Postgraduate &operator=(const Postgraduate &other) {
        if (this != &other) {
            Teacher::operator=(other);
            Student::operator=(other);
        }
        return *this;
    }

    ~Postgraduate() override = default;

    void Print_info() override {
        cout << "Postgraduate: " << name << ' ' << surname << ' ' << age << ' ' << position << ' ' << salary << ' '
             << university << ' ' << group << ' ' << course << endl;
    }
};

void print_all(Person **p_persons, const size_t count) {
    for (size_t i = 0; i < count; i++)
        p_persons[i]->Print_info();

}

Person *get_oldest_person(Person **p_persons, const size_t count) {
    size_t k = 0;
    auto years = p_persons[k]->get_age();
    for (size_t i = 1; i < count; i++)
        if (p_persons[i]->get_age() > years) {
            years = p_persons[i]->get_age();
            k = i;
        }
    return p_persons[k];
}

int main() {
    Person person("Person", "s", 25);
    Student student("Student", "s", 18, "PmP-32", 3);
    Employer employer("Employer", "s", 35, "plumber", 25000);
    Teacher teacher("Teacher", "s", 27, "teacher", 6000, "LNU");
    teacher.Print_info();

    auto **all = new Person *[]{&person, &student, &employer, &teacher,
                                new Teacher("Teacher_2", "s", 27, "teacher", 6000, "LNU"),
                                new Postgraduate("postgraduate", "p", 23, "assistant", 4000, "LNU", "PMP-11", 1)};

    print_all(all, 6);
    cout << "\nOldest person: ";
    get_oldest_person(all, 6)->Print_info();
    cout << endl;

    delete[] all;
    return 0;
}