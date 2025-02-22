#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int id;
    bool isRegistered;
    bool hasPaid;

public:
    Student(string name, int id) : name(name), id(id), isRegistered(false), hasPaid(false) {}

    void registerForTransport() {
        isRegistered = true;
        cout << "Student " << name << " registered for transport." << endl;
    }

    void payFees() {
        if (isRegistered) {
            hasPaid = true;
            cout << "Student " << name << " has paid the semester fees." << endl;
        } else {
            cout << "Student " << name << " is not registered for transport." << endl;
        }
    }

    bool isActive() {
        return isRegistered && hasPaid;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }
};

class Route {
private:
    string routeName;
    string pickUpStop;
    string dropOffStop;

public:
    Route(string routeName, string pickUpStop, string dropOffStop)
        : routeName(routeName), pickUpStop(pickUpStop), dropOffStop(dropOffStop) {}

    string getRouteName() {
        return routeName;
    }

    string getPickUpStop() {
        return pickUpStop;
    }

    string getDropOffStop() {
        return dropOffStop;
    }
};

class Attendance {
public:
    void recordAttendance(Student& student) {
        if (student.isActive()) {
            cout << "Attendance recorded for student " << student.getName() << "." << endl;
        } else {
            cout << "Student " << student.getName() << " is not active." << endl;
        }
    }
};

int main() {
    Student student1("John Doe", 1);
    student1.registerForTransport();
    student1.payFees();

    Route route1("Route 1", "Stop A", "Stop B");

    Attendance attendance;
    attendance.recordAttendance(student1);

    return 0;
}









