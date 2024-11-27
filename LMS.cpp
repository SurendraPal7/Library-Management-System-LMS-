#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    int id;
    string title;
    string author;
    bool available;
    string borrower;
};

Book library[MAX_BOOKS];
int numBooks = 0;

void addBook() {
    if (numBooks >= MAX_BOOKS) {
        cout << "Library is full. Cannot add more books." << endl;
        return;
    }

    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.id;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == newBook.id) {
            cout << "A book with this ID already exists. Please use a unique ID." << endl;
            return;
        }
    }

    cin.ignore(); 
    cout << "Enter Book Title: ";
    getline(cin, newBook.title);
    cout << "Enter Book Author: ";
    getline(cin, newBook.author);
    newBook.available = true;
    library[numBooks++] = newBook;

    cout << "Book added successfully!" << endl;
}

void searchBookById() {
    int id;
    cout << "Enter Book ID: ";
    cin >> id;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id) {
            cout << "Book Found: " << library[i].title << " by " << library[i].author << endl;
            cout << "Availability: " << (library[i].available ? "Available" : "Issued to " + library[i].borrower) << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void searchBookByTitle() {
    string title;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, title);
    
    for (int i = 0; i < numBooks; i++) {
        if (library[i].title == title) {
            cout << "Book Found: " << library[i].title << " by " << library[i].author << endl;
            cout << "Availability: " << (library[i].available ? "Available" : "Issued to " + library[i].borrower) << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id) {
            if (library[i].available) {
                cout << "Enter Borrower's Name: ";
                cin.ignore();  
                getline(cin, library[i].borrower); 
                library[i].available = false;
                cout << "Book issued to " << library[i].borrower << endl;
            } else {
                cout << "Book is already issued to " << library[i].borrower << endl;
            }
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id) {
            if (!library[i].available) {
                library[i].available = true;
                library[i].borrower = "";
                cout << "Book returned successfully!" << endl;
            } else {
                cout << "This book is not issued to anyone." << endl;
            }
            return;
        }
    }
    cout << "Book not found!" << endl;
}

bool compareById(const Book &a, const Book &b) {
    return a.id < b.id;
}

bool compareByTitle(const Book &a, const Book &b) {
    return a.title < b.title;
}

void deleteBook() {
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id) {
            for (int j = i; j < numBooks - 1; j++) {
                library[j] = library[j + 1];
            }
            numBooks--; 
            cout << "Book with ID " << id << " deleted successfully!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void displayBooks() {
    if (numBooks == 0) {
        cout << "No books in the library!" << endl;
        return;
    }

    cout << "Sort books by: 1. ID  2. Title" << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        sort(library, library + numBooks, compareById);
    } else if (choice == 2) {
        sort(library, library + numBooks, compareByTitle);
    }

    for (int i = 0; i < numBooks; i++) {
        cout << "ID: " << library[i].id << ", Title: " << library[i].title << ", Author: " << library[i].author;
        cout << ", Status: " << (library[i].available ? "Available" : "Issued to " + library[i].borrower) << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Display All Books\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBookById();
                break;
            case 3:
                searchBookByTitle();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                displayBooks();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
