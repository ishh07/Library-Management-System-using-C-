#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo; // Name of the student to whom the book is issued
    Book* next;
};

class Library {
private:
    Book* head;

public:
    Library() : head(nullptr) {}

    // Add new book to the library
    void addBook(int id, string title, string author) {
        Book* newBook = new Book{id, title, author, false, "", nullptr};
        if (!head) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
        cout << "Book added successfully.\n";
    }

    // Search for a book by title or ID
    void searchBook(string title) {
        Book* temp = head;
        while (temp) {
            if (temp->title == title) {
                cout << "Book Found: ID: " << temp->id << ", Title: " << temp->title
                     << ", Author: " << temp->author
                     << ", Status: " << (temp->isIssued ? "Issued" : "Available") << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void searchBook(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Book Found: ID: " << temp->id << ", Title: " << temp->title
                     << ", Author: " << temp->author
                     << ", Status: " << (temp->isIssued ? "Issued" : "Available") << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    // Issue a book to a student
    void issueBook(int id, string studentName) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                if (!temp->isIssued) {
                    temp->isIssued = true;
                    temp->issuedTo = studentName;
                    cout << "Book issued to " << studentName << ".\n";
                } else {
                    cout << "Book is already issued to " << temp->issuedTo << ".\n";
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    // Return a book to the library
    void returnBook(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                if (temp->isIssued) {
                    temp->isIssued = false;
                    temp->issuedTo = "";
                    cout << "Book returned successfully.\n";
                } else {
                    cout << "Book is not issued.\n";
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    // List all books in the library
    void listAllBooks() {
        if (!head) {
            cout << "No books in the library.\n";
            return;
        }
        Book* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << ", Title: " << temp->title
                 << ", Author: " << temp->author
                 << ", Status: " << (temp->isIssued ? "Issued" : "Available") << endl;
            temp = temp->next;
        }
    }

    // Delete a book from the library
    void deleteBook(int id) {
        if (!head) {
            cout << "No books to delete.\n";
            return;
        }
        if (head->id == id) {
            Book* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Book deleted successfully.\n";
            return;
        }
        Book* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }
        if (temp->next) {
            Book* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author, studentName;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search Book by Title\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();  // Ignore the newline character
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                lib.searchBook(title);
                break;
            case 3:
                cout << "Enter book ID to search: ";
                cin >> id;
                lib.searchBook(id);
                break;
            case 4:
                cout << "Enter book ID to issue: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, studentName);
                lib.issueBook(id, studentName);
                break;
            case 5:
                cout << "Enter book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                lib.listAllBooks();
                break;
            case 7:
                cout << "Enter book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
