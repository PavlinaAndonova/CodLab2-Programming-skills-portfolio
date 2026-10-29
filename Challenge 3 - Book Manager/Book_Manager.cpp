
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Book { // Class to represent a book
public:
    string title;
    string author;
    int pages;
    int id;
    bool borrowed;

    Book(string t, string a, int p, int i, bool b) { // Constructor to initialize a book object
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    void display() { // Function to display book details
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPages: " << pages;
        cout << "\nID: " << id;
        cout << "\nStatus: ";
        if (borrowed) // Check if the book is borrowed
            cout << "Borrowed";
        else
            cout << "Available";
        cout << "\n";
    }
};

int main() {
    vector<Book> books; // Vector to store all the books
    ifstream file("bookData.txt"); // Open the file containing book data

    if (!file.is_open()) { // Check if the file was opened successfully
        cout << "Error: Could not open bookData.txt\n";
        return 1;
    }

    string line;
    while (getline(file, line)) { // Read each line from the file
        stringstream ss(line);
        string title, author, pagesText, idText, status;

        if (getline(ss, title, ',') && 
            getline(ss, author, ',') &&
            getline(ss, pagesText, ',') &&
            getline(ss, idText, ',') &&
            getline(ss, status)) {

            try {
                int pages = stoi(pagesText); // Convert pages from string to int
                int id = stoi(idText); //

                // Remove spaces before checking the status
                if (!status.empty() && status[0] == ' ') // Check if the first character is a space
                    status.erase(0, 1); // Remove the first character (space) from the status string

                bool borrowed = // Check if the book is borrowed based on the status
                    (status == "1" || status == "Borrowed" ||
                     status == "borrowed" || status == "true");

                books.emplace_back(title, author, pages, id, borrowed); // Add the book to the vector
            }
            catch (...) { // Catch any exceptions thrown by stoi (e.g., invalid number format)
                cout << "Skipping invalid book data.\n";
            }
        }
    }

    file.close();

    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. View all books\n";
        cout << "2. View an individual book\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) { // Display all books
            for (Book &book : books) { // Iterate through the vector of books
                book.display(); // Display each book's details
            }
        }
        else if (choice >= 2 && choice <= 4) { // Handle individual book operations
            int searchID; // Variable to store the book ID entered by the user
            cout << "Enter book ID: ";
            cin >> searchID;

            bool found = false; // Flag to check if the book with the given ID was found

            for (Book &book : books) {
                if (book.id == searchID) {
                    found = true;

                    if (choice == 2) {
                        book.display();
                    }
                    else if (choice == 3) {
                        if (!book.borrowed) {
                            book.borrowed = true;
                            cout << "Book borrowed successfully.\n";
                        }
                        else {
                            cout << "This book is already borrowed.\n";
                        }
                    }
                    else {
                        if (book.borrowed) {
                            book.borrowed = false;
                            cout << "Book returned successfully.\n";
                        }
                        else {
                            cout << "This book is not borrowed.\n";
                        }
                    }
                    break;
                }
            }

            if (!found) {
                cout << "Book ID not found.\n";
            }
        }
        else if (choice != 5) {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5); // Continue the loop until the user chooses to exit

    cout << "Goodbye!\n";
    return 0;
}
