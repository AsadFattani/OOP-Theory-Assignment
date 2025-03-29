#include <iostream>
using namespace std;

class Vehicle {
    protected:
        int vehicleID;

    public:
        static int activeDeliveries;

        Vehicle(int id) : vehicleID(id) {
            activeDeliveries++;
        }

        virtual void calculateOptimalRoute() {
            cout << "Calculating optimal delivery route for vehicle ID: " << vehicleID << endl;
        }

        virtual void estimateDeliveryTime() {
            cout << "Estimating delivery time for vehicle ID: " << vehicleID << endl;
        }

        static int getActiveDeliveries() {
            return activeDeliveries;
        }

        int getVehicleID() const {
            return vehicleID;
        }

        virtual bool operator==(const Vehicle& vehicle) const {
            return vehicleID == vehicle.getVehicleID();
        }

        friend const Vehicle& resolveConflict(const Vehicle& v1, const Vehicle& v2) {
            return (v1.vehicleID < v2.vehicleID) ? v1 : v2;
        }
};

class RamazanDrone : public Vehicle {
    public:
        RamazanDrone(int id) : Vehicle(id) {}

        void calculateOptimalRoute() {
            cout << "Calculating aerial route for high-speed delivery by Ramazan Drone ID: " << vehicleID << endl;
        }

        void estimateDeliveryTime() {
            cout << "Estimating delivery time for Ramazan Drone ID: " << vehicleID << endl;
        }

        void command(const string& action, int packageID, const string& urgencyLevel = "normal") {
            if (action == "Deliver") {
                if (urgencyLevel == "urgent") {
                    cout << "Ramazan Drone ID: " << vehicleID << " activating high-speed mode to deliver package ID: " << packageID << " on time for iftar." << endl;
                } else {
                    cout << "Ramazan Drone ID: " << vehicleID << " delivering package ID: " << packageID << " at normal speed." << endl;
                }
            }
        }

        bool operator==(const Vehicle& vehicle) const {
            return vehicleID == vehicle.getVehicleID();
        }
};

class RamazanTimeShip : public Vehicle {
    public:
        RamazanTimeShip(int id) : Vehicle(id) {}

        void calculateOptimalRoute() {
            cout << "Verifying historical consistency and calculating route for Ramazan Time Ship ID: " << vehicleID << endl;
        }

        void estimateDeliveryTime() {
            cout << "Estimating delivery time for Ramazan Time Ship ID: " << vehicleID << endl;
        }

        void command(const string& action, int packageID, const string& urgencyLevel = "normal") {
            if (action == "Deliver") {
                if (urgencyLevel == "urgent") {
                    cout << "Ramazan Time Ship ID: " << vehicleID << " validating historical sensitivity for urgent package ID: " << packageID << " before transport." << endl;
                } else {
                    cout << "Ramazan Time Ship ID: " << vehicleID << " delivering package ID: " << packageID << " with standard validation." << endl;
                }
            }
        }

        bool operator==(const Vehicle& vehicle) const {
            return vehicleID == vehicle.getVehicleID();
        }
};

class RamazanHyperPod : public Vehicle {
    public:
        RamazanHyperPod(int id) : Vehicle(id) {}

        void calculateOptimalRoute() {
            cout << "Navigating underground tunnel network for efficient bulk delivery by Ramazan HyperPod ID: " << vehicleID << endl;
        }

        void estimateDeliveryTime() {
            cout << "Estimating delivery time for Ramazan HyperPod ID: " << vehicleID << endl;
        }

        void command(const string& action, int packageID, const string& urgencyLevel = "normal") {
            if (action == "Deliver") {
                cout << "Ramazan HyperPod ID: " << vehicleID << " delivering package ID: " << packageID << " efficiently through the underground tunnel network." << endl;
            }
        }

        bool operator==(const Vehicle& vehicle) const {
            return vehicleID == vehicle.getVehicleID();
        }
};

int Vehicle::activeDeliveries = 0;

int main() {
    RamazanDrone drone(101);
    RamazanTimeShip ship(202);
    RamazanHyperPod pod(303);

    drone.calculateOptimalRoute();
    ship.estimateDeliveryTime();
    pod.command("Deliver", 42, "urgent");

    if (drone == ship) {
        cout << "Drone and Time Ship are equal." << endl;
    } else {
        cout << "Drone and Time Ship are not equal." << endl;
    }

    const Vehicle& betterVehicle = resolveConflict(drone, pod);
    cout << "Better vehicle for the task is Vehicle ID: " << betterVehicle.getVehicleID() << endl;

    cout << "Active deliveries: " << Vehicle::getActiveDeliveries() << endl;

    drone.calculateOptimalRoute();
    drone.estimateDeliveryTime();

    ship.calculateOptimalRoute();
    ship.estimateDeliveryTime();

    pod.calculateOptimalRoute();
    pod.estimateDeliveryTime();

    return 0;
}












