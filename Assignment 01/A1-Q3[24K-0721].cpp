#include <iostream>
using namespace std;

class User {
private:
    string name;
    int age;
    string licenseType;
    string contactInfo;
    int userID;

public:
    User(string n, int a, string l, string c, int id) : name(n), age(a), licenseType(l), contactInfo(c), userID(id){}
    void updateDetails(string n, int a, string l, string c){
        name = n;
        age = a;
        licenseType = l;
        contactInfo = c;
    }

    int getUserID() {
        return userID;
    }

    string getLicenseType() {
        return licenseType;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    string getContactInfo() {
        return contactInfo;
    }
};

class Vehicle {
private:
    string model;
    double rentalPricePerDay;
    string eligibility;

public:
    Vehicle(string m, double r, string e) : model(m), rentalPricePerDay(r), eligibility(e) {}
    string getModel(){
        return model;
    }

    double getRentalPricePerDay(){
        return rentalPricePerDay;
    }

    string getEligibility(){
        return eligibility;
    }
};

class RentalSystem {
private:
    User* users[100];
    Vehicle* vehicles[100];
    int userCount;
    int vehicleCount;

public:
    RentalSystem() : userCount(0), vehicleCount(0) {}
    void registerUser(string name, int age, string licenseType, string contactInfo, int userID) {
        users[userCount++] = new User(name, age, licenseType, contactInfo, userID);
    }

    void updateUser(int userID, string name, int age, string licenseType, string contactInfo) {
        for (int i = 0; i < userCount; ++i) {
            if (users[i]->getUserID() == userID) {
                users[i]->updateDetails(name, age, licenseType, contactInfo);
                break;
            }
        }
    }

    void addVehicle(string model, double rentalPricePerDay, string eligibility) {
        vehicles[vehicleCount++] = new Vehicle(model, rentalPricePerDay, eligibility);
    }

    void displayVehicles() {
        for (int i = 0; i < vehicleCount; ++i) {
            cout << "Model: " << vehicles[i]->getModel() << ", Price per day: " << vehicles[i]->getRentalPricePerDay() << ", Eligibility: " << vehicles[i]->getEligibility() << endl;
        }
    }

    void displayUsers() {
        for (int i = 0; i < userCount; ++i) {
            cout << "User ID: " << users[i]->getUserID() << ", Name: " << users[i]->getName() << ", Age: " << users[i]->getAge() << ", License Type: " << users[i]->getLicenseType() << ", Contact Info: " << users[i]->getContactInfo() << endl;
        }
    }

    void rentVehicle(int userID, string model) {
        User* user = nullptr;
        for (int i = 0; i < userCount; ++i) {
            if (users[i]->getUserID() == userID) {
                user = users[i];
                break;
            }
        }

        if (user == nullptr) {
            cout << "User not found!" << endl;
            return;
        }

        for (int i = 0; i < vehicleCount; ++i) {
            if (vehicles[i]->getModel() == model) {
                if (vehicles[i]->getEligibility() == user->getLicenseType()) {
                    cout << "Vehicle rented successfully!" << endl;
                } else {
                    cout << "You are not eligible to rent this vehicle." << endl;
                }
                return;
            }
        }

        cout << "Vehicle not found!" << endl;
    }

    ~RentalSystem() {
        for (int i = 0; i < userCount; ++i) {
            delete users[i];
        }
        for (int i = 0; i < vehicleCount; ++i) {
            delete vehicles[i];
        }
    }
};

int main() {
    RentalSystem system;
    system.registerUser("Aamir Adnan", 25, "Full", "123-456-7890", 1);
    system.addVehicle("Toyota Camry", 50.0, "Full");
    system.addVehicle("Honda Civic", 40.0, "Intermediate");
    system.displayVehicles();
    system.displayUsers();
    system.rentVehicle(1, "Toyota Camry");
    system.rentVehicle(1, "Honda Civic");
    return 0;
}









