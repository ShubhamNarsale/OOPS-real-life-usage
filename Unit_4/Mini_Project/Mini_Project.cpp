#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string category;
    string availability;

public:
    Book() {}

    Book(string i, string t, string a, string c, string av)
        : isbn(i), title(t), author(a), category(c), availability(av) {}

    string getISBN() const {
        return isbn;
    }

    string getAvailability() const {
        return availability;
    }

    void display() const {
        cout << "ISBN: " << isbn
             << " | Title: " << title
             << " | Author: " << author
             << " | Category: " << category
             << " | Status: " << availability << endl;
    }

    string toFileString() const {
        return isbn + "|" + title + "|" + author + "|" +
               category + "|" + availability;
    }

    bool loadFromLine(const string& line) {
        stringstream stream(line);

        if (!getline(stream, isbn, '|'))
            return false;

        if (!getline(stream, title, '|'))
            return false;

        if (!getline(stream, author, '|'))
            return false;

        if (!getline(stream, category, '|'))
            return false;

        if (!getline(stream, availability))
            return false;

        return true;
    }

    void setTitle(string t) {
        title = t;
    }

    void setAuthor(string a) {
        author = a;
    }

    void setCategory(string c) {
        category = c;
    }

    void issueBook() {
        if (availability == "Available") {
            availability = "Issued";
            cout << "Book issued successfully." << endl;
        }
        else {
            cout << "Book is already issued." << endl;
        }
    }

    void returnBook() {
        if (availability == "Issued") {
            availability = "Available";
            cout << "Book returned successfully." << endl;
        }
        else {
            cout << "Book is already available." << endl;
        }
    }
};

// Add a new book
void addBook() {
    ofstream file("library.txt", ios::app);

    if (!file) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    Book book(
        "978-0135166307",
        "C++ Programming",
        "Bjarne Stroustrup",
        "Programming",
        "Available"
    );

    file << book.toFileString() << endl;
    file.close();

    cout << "Book added successfully." << endl;
}

// Search for a book
void searchBook(const string& isbn) {
    ifstream file("library.txt");

    if (!file) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        Book book;

        if (book.loadFromLine(line)) {
            if (book.getISBN() == isbn) {
                cout << "\nBook Found:" << endl;
                book.display();
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Book not found." << endl;
    }

    file.close();
}

// Issue a book
void issueBook(const string& isbn) {
    ifstream input("library.txt");

    if (!input) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(input, line)) {
        Book book;

        if (book.loadFromLine(line)) {

            if (book.getISBN() == isbn) {
                book.issueBook();
                found = true;
            }

            temp << book.toFileString() << endl;
        }
    }

    input.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book not found." << endl;
    }
}

// Return a book
void returnBook(const string& isbn) {
    ifstream input("library.txt");

    if (!input) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(input, line)) {
        Book book;

        if (book.loadFromLine(line)) {

            if (book.getISBN() == isbn) {
                book.returnBook();
                found = true;
            }

            temp << book.toFileString() << endl;
        }
    }

    input.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book not found." << endl;
    }
}

// Update book information
void updateBook(const string& isbn) {
    ifstream input("library.txt");

    if (!input) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(input, line)) {
        Book book;

        if (book.loadFromLine(line)) {

            if (book.getISBN() == isbn) {
                book.setTitle("Advanced C++ Programming");
                book.setAuthor("Robert Lafore");
                book.setCategory("Programming");

                found = true;
                cout << "Book updated successfully." << endl;
            }

            temp << book.toFileString() << endl;
        }
    }

    input.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book not found." << endl;
    }
}

// Generate availability report
void availabilityReport() {
    ifstream file("library.txt");

    if (!file) {
        cerr << "Unable to open library.txt." << endl;
        return;
    }

    string line;

    cout << "\n=== Library Availability Report ===" << endl;

    while (getline(file, line)) {
        Book book;

        if (book.loadFromLine(line)) {
            book.display();
        }
    }

    file.close();
}

int main() {

    // Add books
    addBook();

    // Add another book directly
    ofstream file("library.txt", ios::app);

    if (file) {
        Book book2(
            "978-0321563842",
            "Effective C++",
            "Scott Meyers",
            "Programming",
            "Available"
        );

        Book book3(
            "978-0596009205",
            "Head First Java",
            "Kathy Sierra",
            "Programming",
            "Available"
        );

        file << book2.toFileString() << endl;
        file << book3.toFileString() << endl;

        file.close();
    }

    // Display initial records
    cout << "\n=== Initial Library Records ===" << endl;
    availabilityReport();

    // Search a book
    searchBook("978-0321563842");

    // Issue a book
    cout << "\n=== Issuing Book ===" << endl;
    issueBook("978-0321563842");

    // Return the book
    cout << "\n=== Returning Book ===" << endl;
    returnBook("978-0321563842");

    // Update a book
    cout << "\n=== Updating Book ===" << endl;
    updateBook("978-0135166307");

    // Final availability report
    availabilityReport();

    return 0;
}