#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

// Base class representing a payment
class Payment {
protected:
    // Stores transaction ID and payment amount
    string id;
    float price;

public:
    // Constructor to initialize payment details
    Payment(string i, float p) {
        id = i;
        price = p;
    }

    // Pure virtual function for making payment
    virtual void makePayment() const = 0;

    // Virtual destructor for proper cleanup
    virtual ~Payment() {}
};


// Derived class representing Credit Card payment
class Card : public Payment {
    // Stores the card number
    string cardNo;

public:
    // Constructor to initialize card payment details
    Card(string i, float p, string c)
        : Payment(i, p), cardNo(c) {}

    // Function to display credit card payment details
    void makePayment() const override {
        cout << "Payment through Credit Card" << endl;
        cout << "Transaction ID: " << id << endl;
        cout << "Amount: Rs. " << price << endl;
        cout << "Card Number: " << cardNo << endl;
        cout << "Status: Successful\n" << endl;
    }
};


// Derived class representing UPI payment
class UPI : public Payment {
    // Stores the UPI ID
    string userId;

public:
    // Constructor to initialize UPI payment details
    UPI(string i, float p, string u)
        : Payment(i, p), userId(u) {}

    // Function to display UPI payment details
    void makePayment() const override {
        cout << "Payment through UPI" << endl;
        cout << "Transaction ID: " << id << endl;
        cout << "Amount: Rs. " << price << endl;
        cout << "UPI ID: " << userId << endl;
        cout << "Status: Successful\n" << endl;
    }
};


// Derived class representing Net Banking payment
class NetBanking : public Payment {
    // Stores the bank name
    string bank;

public:
    // Constructor to initialize net banking details
    NetBanking(string i, float p, string b)
        : Payment(i, p), bank(b) {}

    // Function to display net banking payment details
    void makePayment() const override {
        cout << "Payment through Net Banking" << endl;
        cout << "Transaction ID: " << id << endl;
        cout << "Amount: Rs. " << price << endl;
        cout << "Bank Name: " << bank << endl;
        cout << "Status: Successful\n" << endl;
    }
};

int main() {
    // Create a vector to store different payment objects
    vector<unique_ptr<Payment>> paymentList;

    // Add a credit card payment with sample details
    paymentList.push_back(
        make_unique<Card>("C501", 3500, "XXXX-5678")
    );

    // Add a UPI payment with sample details
    paymentList.push_back(
        make_unique<UPI>("U602", 1850, "soham@upi")
    );

    // Add a net banking payment with sample details
    paymentList.push_back(
        make_unique<NetBanking>("N703", 4200, "XYZ Bank")
    );

    cout << "===== PAYMENT SYSTEM =====\n" << endl;

    // Process each payment using runtime polymorphism
    for (const auto& p : paymentList) {
        p->makePayment();
    }

    return 0;
}