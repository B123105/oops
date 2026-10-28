
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() {
        id = 0;
        title = "";
        author = "";
        issued = false;
    }
};

class Library {
private:
    Book books[100];
    int count;

    void saveToFile() {
        ofstream file("books.txt");

        for (int i = 0; i < count; i++) {
            file << books[i].id << '\n';
            file << books[i].title << '\n';
            file << books[i].author << '\n';
            file << books[i].issued << '\n';
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("books.txt");
        count = 0;

        while (count < 100 &&
               file >> books[count].id) {
            file.ignore(10000, '\n');

            getline(file, books[count].title);
            getline(file, books[count].author);
            file >> books[count].issued;
            file.ignore(10000, '\n');

            count++;
        }

        file.close();
    }

    int findBook(int bookID) {
        for (int i = 0; i < count; i++) {
            if (books[i].id == bookID) {
                return i;
            }
        }
        return -1;
    }

public:
    Library() {
        count = 0;
        loadFromFile();
    }

    void addBook() {
        if (count >= 100) {
            cout << "Library is full!\n";
            return;
        }

        int bookID;
        cout << "Enter Book ID: ";
        cin >> bookID;

        if (findBook(bookID) != -1) {
            cout << "Book ID already exists!\n";
            return;
        }

        books[count].id = bookID;

        cout << "Enter Book Title: ";
        getline(cin >> ws, books[count].title);

        cout << "Enter Author Name: ";
        getline(cin, books[count].author);

        books[count].issued = false;
        count++;

        saveToFile();
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        if (count == 0) {
            cout << "No books available.\n";
            return;
        }

        cout << "\n--- BOOK LIST ---\n";

        for (int i = 0; i < count; i++) {
            cout << "\nBook ID: " << books[i].id;
            cout << "\nTitle: " << books[i].title;
            cout << "\nAuthor: " << books[i].author;
            cout << "\nStatus: "
                 << (books[i].issued ? "Issued" : "Available");
            cout << "\n-------------------\n";
        }
    }

    void searchBook() {
        int bookID;
        cout << "Enter Book ID to search: ";
        cin >> bookID;

        int index = findBook(bookID);

        if (index == -1) {
            cout << "Book not found!\n";
        } else {
            cout << "\nBook ID: " << books[index].id;
            cout << "\nTitle: " << books[index].title;
            cout << "\nAuthor: " << books[index].author;
            cout << "\nStatus: "
                 << (books[index].issued ? "Issued" : "Available")
                 << '\n';
        }
    }

    void issueBook() {
        int bookID;
        cout << "Enter Book ID to issue: ";
        cin >> bookID;

        int index = findBook(bookID);

        if (index == -1) {
            cout << "Book not found!\n";
        } else if (books[index].issued) {
            cout << "Book is already issued!\n";
        } else {
            books[index].issued = true;
            saveToFile();
            cout << "Book issued successfully!\n";
        }
    }

    void returnBook() {
        int bookID;
        cout << "Enter Book ID to return: ";
        cin >> bookID;

        int index = findBook(bookID);

        if (index == -1) {
            cout << "Book not found!\n";
        } else if (!books[index].issued) {
            cout << "This book was not issued.\n";
        } else {
            books[index].issued = false;
            saveToFile();
            cout << "Book returned successfully!\n";
        }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.displayBooks();
                break;
            case 3:
                lib.searchBook();
                break;
            case 4:
                lib.issueBook();
                break;
            case 5:
                lib.returnBook();
                break;
            case 6:
                cout << "Thank you for using the library system!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
