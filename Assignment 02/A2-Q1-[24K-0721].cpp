#include <iostream>
using namespace std;

class User {
protected:
    string name;
    int id;
    bool isRegistered;
    bool hasPaid;

public:
    User(string name, int id) : name(name), id(id), isRegistered(false), hasPaid(false) {}

    virtual void registerForTransport() {
        isRegistered = true;
        cout << "User " << name << " registered for transport." << endl;
    }

    virtual void payFees() = 0;

    bool isActive() {
        return isRegistered && hasPaid;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    // Overload the equality operator to compare users by ID
    bool operator==(const User& other) {
        return id == other.id;
    }

    // Overload the stream insertion operator to output user details
    friend ostream& operator<<(ostream& os, const User& user) {
        os << "User(Name: " << user.name << ", ID: " << user.id << ")";
        return os;
    }
};

class Student : public User {
public:
    Student(string name, int id) : User(name, id) {}

    void payFees() {
        if (isRegistered) {
            hasPaid = true;
            cout << "Student " << name << " has paid the semester fees." << endl;
        } else {
            cout << "Student " << name << " is not registered for transport." << endl;
        }
    }
};

class Teacher : public User {
public:
    Teacher(string name, int id) : User(name, id) {}

    void payFees() {
        if (isRegistered) {
            hasPaid = true;
            cout << "Teacher " << name << " has paid the monthly fees." << endl;
        } else {
            cout << "Teacher " << name << " is not registered for transport." << endl;
        }
    }
};

class StaffMember : public User {
public:
    StaffMember(string name, int id) : User(name, id) {}

    void payFees() {
        if (isRegistered) {
            hasPaid = true;
            cout << "Staff Member " << name << " has paid the monthly fees." << endl;
        } else {
            cout << "Staff Member " << name << " is not registered for transport." << endl;
        }
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
    void recordAttendance(User& user) {
        if (user.isActive()) {
            cout << "Attendance recorded for " << user.getName() << "." << endl;
        } else {
            cout << user.getName() << " is not active." << endl;
        }
    }
};

int main() {
    Student student1("Ali Adnan", 1);
    student1.registerForTransport();
    student1.payFees();

    Teacher teacher1("Dr. Ahmed", 2);
    teacher1.registerForTransport();
    teacher1.payFees();

    StaffMember staff1("Mr. Khan", 3);
    staff1.registerForTransport();
    staff1.payFees();

    Route route1("Route 1", "Stop A", "Stop B");

    Attendance attendance;
    attendance.recordAttendance(student1);
    attendance.recordAttendance(teacher1);
    attendance.recordAttendance(staff1);

    // Demonstrate operator overloading
    Student student2("Ali Adnan", 1);
    cout << (student1 == student2 ? "Students are the same." : "Students are different.") << endl;
    cout << student1 << endl;

    return 0;
}









