#include <iostream>
#include <string>
using namespace std;

// Base class representing a general bank account
class Account {
protected:
    string accNo;       // Stores account number
    string holder;      // Stores account holder name
    double balance;     // Stores account balance

public:
    // Constructor to initialize account details
    Account(string a, string h, double b) {
        accNo = a;
        holder = h;
        balance = b;
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully." << endl;
    }

    // Virtual function to withdraw money
    virtual void withdraw(double amount) {

        // Check whether sufficient balance is available
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful." << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    // Pure virtual function for calculating interest
    virtual void calculateInterest() const = 0;

    // Virtual function to display account details
    virtual void displayInfo() const {
        cout << "Account Number: " << accNo << endl;
        cout << "Holder Name: " << holder << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    // Virtual destructor
    virtual ~Account() {}
};


// Derived class for Savings Account
class SavingsAccount : public Account {
public:
    // Constructor calls the base class constructor
    SavingsAccount(string a, string h, double b)
        : Account(a, h, b) {}

    // Override function to calculate savings account interest
    void calculateInterest() const override {
        cout << "Interest: Rs. " << balance * 0.04 << endl;
    }
};


// Derived class for Current Account
class CurrentAccount : public Account {
public:
    // Constructor calls the base class constructor
    CurrentAccount(string a, string h, double b)
        : Account(a, h, b) {}

    // Override function for current account interest
    void calculateInterest() const override {
        cout << "Current Account has no interest." << endl;
    }
};


// Derived class for Fixed Deposit Account
class FixedDepositAccount : public Account {
    int years;  // Stores FD duration in years

public:
    // Constructor initializes account details and FD duration
    FixedDepositAccount(string a, string h, double b, int y)
        : Account(a, h, b), years(y) {}

    // Override function to calculate FD interest
    void calculateInterest() const override {
        cout << "Interest: Rs. " << balance * 0.07 * years << endl;
    }
};


int main() {

    // Variables for taking account details from the user
    string accNo, name;
    double balance;
    int choice, years;

    cout << "===== BANKING SYSTEM =====" << endl;

    // Take account number from the user
    cout << "Enter Account Number: ";
    cin >> accNo;

    // Clear the input buffer before using getline()
    cin.ignore();

    // Take account holder name
    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    // Take initial account balance
    cout << "Enter Initial Balance: ";
    cin >> balance;

    // Display account type options
    cout << "\nSelect Account Type:" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Current Account" << endl;
    cout << "3. Fixed Deposit Account" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    // Base class pointer
    Account* account = nullptr;

    // Create Savings Account object
    if (choice == 1) {
        account = new SavingsAccount(accNo, name, balance);
    }

    // Create Current Account object
    else if (choice == 2) {
        account = new CurrentAccount(accNo, name, balance);
    }

    // Create Fixed Deposit Account object
    else if (choice == 3) {
        cout << "Enter FD Duration (years): ";
        cin >> years;

        account = new FixedDepositAccount(accNo, name, balance, years);
    }

    // Handle invalid account type
    else {
        cout << "Invalid choice." << endl;
        return 0;
    }

    int option;
    double amount;

    // Repeat the menu until the user chooses Exit
    do {

        cout << "\n===== MENU =====" << endl;
        cout << "1. Display Account Details" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Calculate Interest" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        // Perform operation according to user's choice
        switch (option) {

            // Display account information
            case 1:
                account->displayInfo();
                break;

            // Deposit money
            case 2:
                cout << "Enter deposit amount: ";
                cin >> amount;
                account->deposit(amount);
                break;

            // Withdraw money
            case 3:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                account->withdraw(amount);
                break;

            // Calculate account interest
            case 4:
                account->calculateInterest();
                break;

            // Exit the banking system
            case 5:
                cout << "Thank you for using the Banking System." << endl;
                break;

            // Handle invalid menu option
            default:
                cout << "Invalid choice." << endl;
        }

    } while (option != 5);

    // Release the dynamically allocated account object
    delete account;

    return 0;
}