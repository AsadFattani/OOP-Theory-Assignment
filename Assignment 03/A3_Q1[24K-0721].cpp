#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int maxUsers = 100;
const int maxVehicles = 10;
const int maxSeats = 60;

class Vehicle;
class Route;
class Seat;
class User;
class Booking;
class Driver;

void throwError(const string& msg) {
    cout << "Error: " << msg << endl;
    return;
}

class Route {
    public:
        string start, end;
        double distance;

        Route() {}

        Route(const string& S, const string& E, double D) {
            start = S;
            end = E;
            distance = D;
        }
};

class Driver {
    public:
        string name, license;

        Driver() {}

        Driver(const string& N, const string& L) {
            name = N;
            license = L;
        }
};

class User {
    protected:
        string name;
        bool paid;

    public:
        User() { 
            paid = false; 
        }

        User(const string& N) {
            name = N;
            paid = false;
        }

        void makePayment() { 
            paid = true;
        }

        bool hasPaid() const {
            return paid; 
        }

        string getName() const {
            return name; 
        }

        virtual string getType() = 0;
        virtual double baseFare() = 0;
};

class Student : public User {
    public:
        Student(const string& N) : User(N) {}

        string getType() override { 
            return "Student"; 
        }

        double baseFare() override { 
            return 5000;
         }
};

class Faculty : public User {
    public:
        Faculty(const string& N) : User(N) {}

        string getType() { 
            return "Faculty"; 
        }

        double baseFare() {
            return 3000;
        }
};

class Seat {
    bool booked;
    bool forFaculty;
    int seatNumber;
    User* assignedUser;

    public:
        Seat() {
            booked = false;
            forFaculty = false;
            seatNumber = 0;
            assignedUser = NULL;
        }

        Seat(int num, bool isFaculty) {
            seatNumber = num;
            forFaculty = isFaculty;
            booked = false;
            assignedUser = NULL;
        }

        bool isBooked() const { 
            return booked; 
        
        }

        bool isFacultySeat() const { 
            return forFaculty;
        }

        int getSeatNumber() const { 
            return seatNumber;
        }


        void assign(User* user) {
            booked = true;
            assignedUser = user;
        }

};

class Vehicle {
    protected:
        Driver* driver;
        Route* route;
        bool isAC;
        Seat seats[maxSeats];
        int totalSeats;
        string vehicleId;
        virtual int seatCapacity() const = 0;

    public:
        Vehicle() {
            driver = NULL;
            route = NULL;
        }

        Vehicle(const string& id, bool ac, Driver* d, Route* r) {
            vehicleId = id;
            isAC = ac;
            driver = d;
            route = r;
        }


        void createSeats(int count, bool isFaculty) {
            totalSeats = count;
            for (int i = 0; i < count; i++) {
                seats[i] = Seat(i + 1, isFaculty);
            }
        }

        Seat* getSeat(int seatNo) {
            if (seatNo > 0 && seatNo <= totalSeats) {
                return &seats[seatNo - 1];
            }
            return NULL;
        }

        string getId() const { return vehicleId; }

        double calculateFare(User* user) const {
            if(isAC) {
                return user->baseFare() + 2000;
            }
            else {
                return user->baseFare();
            }
        }

        void showSeats() {
            for (int i = 0; i < totalSeats; i++) {
                cout << "Seat " << seats[i].getSeatNumber()
                    << " - " << (seats[i].isBooked() ? "Booked" : "Available")
                    << " - For: " << (seats[i].isFacultySeat() ? "Faculty" : "Student") << endl;
            }
        }
    };

    class Bus : public Vehicle {
    public:
        Bus(const string& ID, bool AC, Driver* D, Route* R) : Vehicle(ID, AC, D, R) {
            createSeats(52, false);
        }

        int seatCapacity() const override { 
            return 52;
         }
};

class Coaster : public Vehicle {
    public:
        Coaster(const string& ID, bool AC, Driver* D, Route* R) : Vehicle(ID, AC, D, R) {
            createSeats(32, true);
        }

        int seatCapacity() const override { 
            return 32;
        }
};

class Booking {
    User* user;
    Vehicle* vehicle;
    int seatNo;

public:
    Booking() {}

    Booking(User* U, Vehicle* V, int SN) {
        user = U;
        vehicle = V;
        seatNo = SN;

        if (!user->hasPaid()) {
            throwError("Payment required before booking.");
            return;
        }

        Seat* seat = vehicle->getSeat(seatNo);
        if (seat == NULL || seat->isBooked()) {
            throwError("Seat not available.");
            return;
        }

        if (seat->isFacultySeat() && user->getType() != "Faculty") {
            throwError("Only faculty can book this seat.");
            return;
        }

        if (!seat->isFacultySeat() && user->getType() != "Student") {
            throwError("Only students can book this seat.");
            return;
        }

        seat->assign(user);
        saveBooking();
        cout << "Booking Successful! " << endl;
    }

    void saveBooking() {
        ofstream fout;
        fout.open("bookings.txt", ios::app);
        if (fout.is_open()) {
            fout << user->getName() << "," << user->getType() << "," << vehicle->getId() << "," << seatNo << endl;
            fout.close();
        }
    }
};

Vehicle* vehicles[maxVehicles];
User* users[maxUsers];
int vehicleCount = 0;
int userCount = 0;

int main() {
    Driver* d1 = new Driver("Sherlock Holmes", "SH221B");
    Driver* d2 = new Driver("John Watson", "JW123");

    Route* r1 = new Route("Baker Street", "Scotland Yard",  12.5);
    Route* r2 = new Route("Bart's Hospital",  "Diogenes Club", 18.3);

    vehicles[vehicleCount++] = new Bus("HOLMES-1", true, d1, r1);
    vehicles[vehicleCount++] = new Coaster("WATSON-X",  false, d2, r2);

    users[userCount++] = new Student("Molly Hooper");
    users[userCount++] = new Faculty("Inspector Lestrade");
    users[userCount++] = new Student("Mrs Hudson");
    users[userCount++] = new Faculty("Mycroft Holmes");

    for (int i = 0; i < userCount;  i++) {
        users[i]->makePayment();
    }

    Booking b1(users[0], vehicles[0], 8);
    Booking b2(users[1], vehicles[1],  15);
    Booking b3(users[2], vehicles[0], 17);
    Booking b4(users[3],  vehicles[1], 13);

    cout << endl << "===== HOLMES-1 Bus Seats: =====" << endl;
    vehicles[0]->showSeats();
    cout << endl << "===== WATSON-X Coaster Seats: ====="  << endl;
    vehicles[1]->showSeats();

    return 0;
}
