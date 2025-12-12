#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    int year;
    bool available;

public:
    Book() {
        id = 0;
        title = "";
        author = "";
        year = 0;
        available = true;
    }

    Book(int bookID, string bookTitle, string bookAuthor, int bookYear) {
        id = bookID;
        title = bookTitle;
        author = bookAuthor;
        year = bookYear;
        available = true;
    }

    int getID() {
        return id;
    }

    void setID(int bookID) {
        id = bookID;
    }

    string getTitle() {
        return title;
    }

    void setTitle(string bookTitle) {
        title = bookTitle;
    }

    string getAuthor() {
        return author;
    }

    void setAuthor(string bookAuthor) {
        author = bookAuthor;
    }

    int getYear() {
        return year;
    }

    void setYear(int bookYear) {
        year = bookYear;
    }

    bool isAvailable() {
        return available;
    }

    void borrowBook() {
        if (available) {
            available = false;
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
        }
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        if (available) {
            cout << "Status: Available" << endl;
        }
        else {
            cout << "Status: Borrowed" << endl;
        }
    }
};

Book library[100];
int bookCount = 0;

int generateBookID() {
    return 10000 + rand() % 90000;
}

void addNewBook() {
    if (bookCount >= 100) {
        cout << "Library is full!" << endl;
        return;
    }

    string bookTitle, bookAuthor;
    int bookYear;

    cout << "Enter title: ";
    getline(cin, bookTitle);

    cout << "Enter author: ";
    getline(cin, bookAuthor);

    cout << "Enter year: ";
    cin >> bookYear;

    int newID = generateBookID();

    library[bookCount] = Book(newID, bookTitle, bookAuthor, bookYear);

    cout << "Book added successfully!" << endl;
    cout << "Title: " << bookTitle << endl;
    cout << "ID: " << newID << endl;

    bookCount++;
}

void borrowBook() {
    int searchID;
    cout << "Enter Book ID: ";
    cin >> searchID;

    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].getID() == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book not found." << endl;
        return;
    }

    if (library[index].isAvailable()) {
        library[index].borrowBook();
        cout << "You have successfully borrowed '" << library[index].getTitle() << "'." << endl;
    }
    else {
        cout << "This book is already borrowed." << endl;
    }
}

void returnBook() {
    int searchID;
    cout << "Enter Book ID: ";
    cin >> searchID;

    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].getID() == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book not found." << endl;
        return;
    }

    if (!library[index].isAvailable()) {
        library[index].returnBook();
        cout << "You have successfully returned '" << library[index].getTitle() << "'." << endl;
    }
    else {
        cout << "Book was not borrowed." << endl;
    }
}

void displayBookDetails() {
    int searchID;
    cout << "Enter Book ID: ";
    cin >> searchID;

    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].getID() == searchID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book not found." << endl;
    }
    else {
        library[index].display();
    }
}

void listAvailableBooks() {
    int availableCount = 0;

    cout << "Available Books:" << endl;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isAvailable()) {
            cout << "ID: " << library[i].getID() << " | Title: " << library[i].getTitle()
                << " | Author: " << library[i].getAuthor() << " | Year: " << library[i].getYear() << endl;
            availableCount++;
        }
    }

    if (availableCount == 0) {
        cout << "No books available at the moment." << endl;
    }
}

void displayMenu() {
    cout << "\n*************** Welcome to the Library ***************" << endl;
    cout << "Please choose one of the following operations:" << endl;
    cout << "1 - Add a new book" << endl;
    cout << "2 - Borrow a book" << endl;
    cout << "3 - Return a book" << endl;
    cout << "4 - Display details of a book (by ID)" << endl;
    cout << "5 - List all available books" << endl;
    cout << "0 - Exit" << endl;
    cout << "Choice: ";
}

int main() {
    srand(time(0));

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        if (choice == 0) {
            cout << "Thank you for using the Library System! Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1:
            addNewBook();
            break;
        case 2:
            borrowBook();
            break;
        case 3:
            returnBook();
            break;
        case 4:
            displayBookDetails();
            break;
        case 5:
            listAvailableBooks();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Press any key to return to Main Menu!" << endl;
        cin.get();
    }

    return 0;
}