#include <iostream>
using namespace std;

class Person {
    int x;
public:
    Person(int x) {
        cout << "Parameterized Person" << endl;
    }

    Person(){
        cout << "Default Person" << endl;
    }

    void setX(int i) {
        x = i;
    }

    void print() {
        cout << x;
    }
};

class Faculty : virtual public Person {
public:
    Faculty() {
        setX(10);
    }

    Faculty(int x) : Person(x) {
        cout << "Faculty Parameterized" << endl;
    }
};

class Student : virtual public Person {
public:
    Student() {
        setX(20);
    }

    Student(int x) : Person(x) {
        cout << "Student Parameterized" << endl;
    }
};

class TA : public Faculty, public Student {
public:
    TA() {
        // default constructor
    }

    TA(int x) : Person(x), Faculty(x), Student(x) {
        cout << "TA Parameterized" << endl;
    }
};

int main() {
    TA ta1(30), ta2;
    ta1.print();
    ta2.print();
    return 0;
}
