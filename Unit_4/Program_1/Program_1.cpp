#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    double marks;

public:
    Student() : rollNo(0), marks(0.0) {}

    Student(int r, string n, double m)
        : rollNo(r), name(n), marks(m) {}

    void saveToFile(ofstream& out) const {
        out << rollNo << ',' << name << ',' << marks << '\n';
    }

    bool loadFromLine(const string& line) {
        string rollText;
        string marksText;
        stringstream stream(line);

        if (!getline(stream, rollText, ','))
            return false;

        if (!getline(stream, name, ','))
            return false;

        if (!getline(stream, marksText))
            return false;

        rollNo = stoi(rollText);
        marks = stod(marksText);

        return true;
    }

    void display() const {
        cout << "Roll: " << rollNo
             << " | Name: " << name
             << " | Marks: " << marks << endl;
    }
};

int main() {

    ofstream outFile("students.csv");

    if (!outFile) {
        cerr << "Unable to open students.csv for writing." << endl;
        return 1;
    }

    Student s1(201, "Shubham Narsale", 94.0);
    Student s2(202, "Sarthak Jadhav", 91.0);
    Student s3(203, "Om Patil", 81.5);

    s1.saveToFile(outFile);
    s2.saveToFile(outFile);
    s3.saveToFile(outFile);

    outFile.close();

    ifstream inFile("students.csv");

    if (!inFile) {
        cerr << "Unable to open students.csv for reading." << endl;
        return 1;
    }

    cout << "=== Student Report ===" << endl;

    string line;

    while (getline(inFile, line)) {
        Student student;

        if (student.loadFromLine(line)) {
            student.display();
        }
    }

    return 0;
}