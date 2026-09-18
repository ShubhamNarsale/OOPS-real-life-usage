#include <iostream>
#include <string>
using namespace std;

// Abstract base class representing an employee
class Employee
{
protected:
    // Employee details accessible by derived classes
    int id;
    string empName;
    string dept;

public:
    // Constructor to initialize employee details
    Employee(int i, string n, string d)
    {
        id = i;
        empName = n;
        dept = d;
    }

    // Function to display basic employee information
    void showInfo() const
    {
        cout << "ID: " << id
             << " | Name: " << empName
             << " | Department: " << dept;
    }

    // Pure virtual function for calculating salary
    virtual double calculateSalary() const = 0;
};

// Derived class representing a full-time employee
class FullTimeEmployee : public Employee
{
private:
    // Monthly salary of the full-time employee
    double monthlySalary;

public:
    // Constructor to initialize full-time employee details
    FullTimeEmployee(int i, string n, string d, double salary)
        : Employee(i, n, d)
    {
        monthlySalary = salary;
    }

    // Calculate and return the monthly salary
    double calculateSalary() const override
    {
        return monthlySalary;
    }

    // Display full-time employee details and salary
    void display() const
    {
        showInfo();

        cout << " | Type: Full-Time"
             << " | Salary: Rs. "
             << calculateSalary() << endl;
    }
};

// Derived class representing a part-time employee
class PartTimeEmployee : public Employee
{
private:
    // Hourly rate and total working hours
    double ratePerHour;
    int totalHours;

public:
    // Constructor to initialize part-time employee details
    PartTimeEmployee(int i, string n, string d, double rate, int hours)
        : Employee(i, n, d)
    {
        ratePerHour = rate;
        totalHours = hours;
    }

    // Calculate salary using hourly rate and total hours
    double calculateSalary() const override
    {
        return ratePerHour * totalHours;
    }

    // Display part-time employee details and salary
    void display() const
    {
        showInfo();

        cout << " | Type: Part-Time"
             << " | Salary: Rs. "
             << calculateSalary() << endl;
    }
};

// Derived class representing an intern
class Intern : public Employee
{
private:
    // Monthly stipend received by the intern
    double monthlyStipend;

public:
    // Constructor to initialize intern details
    Intern(int i, string n, string d, double stipend)
        : Employee(i, n, d)
    {
        monthlyStipend = stipend;
    }

    // Return the monthly stipend
    double calculateSalary() const override
    {
        return monthlyStipend;
    }

    // Display intern details and stipend
    void display() const
    {
        showInfo();

        cout << " | Type: Intern"
             << " | Stipend: Rs. "
             << calculateSalary() << endl;
    }
};

int main()
{
    // Create objects for different types of employees
    FullTimeEmployee emp1(301, "Vinod", "Human Resources", 55000);
    PartTimeEmployee emp2(302, "Rushikesh", "Marketing", 250, 80);
    Intern emp3(303, "Roshan", "Research", 15000);

    cout << "===== Employee Salary Details =====" << endl;

    // Display details of all employees
    emp1.display();
    emp2.display();
    emp3.display();

    return 0;
}