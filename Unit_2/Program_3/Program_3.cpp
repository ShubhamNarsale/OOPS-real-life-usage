#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Base class representing a general vehicle
class Vehicle {
protected:
    string id;       // Stores vehicle ID
    string regNo;    // Stores vehicle registration number
    float fuel;      // Stores fuel percentage

public:
    // Constructor to initialize vehicle ID and registration number
    Vehicle(string i, string r) {
        id = i;
        regNo = r;
        fuel = 100.0;  // Initially, fuel is set to 100%
    }

    // Function to start the vehicle engine
    void startEngine() const {
        cout << "Engine started for vehicle: " << id << endl;
    }

    // Function to add fuel to the vehicle
    void refuel(float amount) {
        fuel += amount;

        // Fuel cannot exceed 100%
        if (fuel > 100.0)
            fuel = 100.0;
    }

    // Virtual function to display general vehicle information
    virtual void displayInfo() const {
        cout << "ID: " << id
             << " | Registration: " << regNo
             << " | Fuel: " << fuel << "%" << endl;
    }

    // Virtual destructor for proper destruction of derived objects
    virtual ~Vehicle() {}
};


// Derived class representing a Truck
class Truck : public Vehicle {
    float capacity;  // Stores truck load capacity

public:
    // Constructor initializes Vehicle and truck capacity
    Truck(string i, string r, float c)
        : Vehicle(i, r), capacity(c) {}

    // Overrides the displayInfo() function
    void displayInfo() const override {
        cout << "Type: Truck" << endl;

        // Call displayInfo() of the base class
        Vehicle::displayInfo();

        cout << "Load Capacity: " << capacity << " tons" << endl;
    }
};


// Derived class representing a Delivery Van
class DeliveryVan : public Vehicle {
    int storage;  // Stores storage capacity of the van

public:
    // Constructor initializes Vehicle and storage capacity
    DeliveryVan(string i, string r, int s)
        : Vehicle(i, r), storage(s) {}

    // Overrides the displayInfo() function
    void displayInfo() const override {
        cout << "Type: Delivery Van" << endl;

        // Call displayInfo() of the base class
        Vehicle::displayInfo();

        cout << "Storage Capacity: " << storage << " kg" << endl;
    }
};


// Derived class representing a Delivery Bike
class Bike : public Vehicle {
    bool deliveryBox;  // Stores whether delivery box is available

public:
    // Constructor initializes Vehicle and delivery box status
    Bike(string i, string r, bool box)
        : Vehicle(i, r), deliveryBox(box) {}

    // Overrides the displayInfo() function
    void displayInfo() const override {
        cout << "Type: Delivery Bike" << endl;

        // Call displayInfo() of the base class
        Vehicle::displayInfo();

        // Display delivery box availability
        cout << "Delivery Box: "
             << (deliveryBox ? "Available" : "Not Available") << endl;
    }
};


int main() {

    // Vector of unique pointers to store different types of vehicles
    vector<unique_ptr<Vehicle>> fleet;

    // Add a Truck object to the fleet
    fleet.push_back(
        make_unique<Truck>("V101", "MH14-XY-4582", 12.5)
    );

    // Add a Delivery Van object to the fleet
    fleet.push_back(
        make_unique<DeliveryVan>("V202", "MH14-PQ-6734", 65)
    );

    // Add a Delivery Bike object to the fleet
    fleet.push_back(
        make_unique<Bike>("V303", "MH14-ZA-9216", true)
    );

    // Display heading
    cout << "===== VEHICLE FLEET =====" << endl;

    // Traverse through all vehicles in the fleet
    for (const auto& v : fleet) {

        // Start the engine of the vehicle
        v->startEngine();

        // Display vehicle-specific information
        // This demonstrates runtime polymorphism
        v->displayInfo();

        cout << endl;
    }

    return 0;
}