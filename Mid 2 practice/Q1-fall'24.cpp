#include <iostream>
#include <string>
using namespace std;

class Employee {
    string empID;
    float salary;
    int hours;

    public:
        Employee() : empID(""), salary(0.0), hours(0) {}

        Employee(string e, float s, int h) {
            empID = e;
            salary = s;
            hours = h;
        }
};

class Office {
    Employee* emps;
    float revenue;
    string code, address, phone;

    public:
        Office() : emps(nullptr), revenue(0.0), code(""), address(""), phone("") {}

        Office(string c, string a, string p, int n) {
            revenue = 0;
            code = c;
            address = a;
            phone = p;
            emps = new Employee[n];
            string e;
            float s;
            int h;
            for (int i = 0; i < n; i++) {
                cin >> e >> s >> h;
                emps[i] = Employee(e, s, h);
            }
        }

        ~Office() {
            delete[] emps;
        }
};

class Business {
    protected:
        Office* offices;

    public:
        Business() {
            offices = new Office;
        }

        Business(int n) {
            string c, a, p;
            offices = new Office[n];
            for (int i = 0; i < n; i++) {
                cin >> c >> a >> p;
                offices[i] = Office(c, a, p, 0); // Assuming 0 employees initially
            }
        }

        virtual ~Business() {
            delete[] offices;
        }
};

class Leasing : public Business {
    public:
        Leasing(int n_offices) : Business(n_offices) {}
};

class Brokerage : public Business {
    public:
        Brokerage(int n_offices) : Business(n_offices) {}
};

class Marketing : public Business {
    public:
        Marketing(int n_offices) : Business(n_offices) {}
};





