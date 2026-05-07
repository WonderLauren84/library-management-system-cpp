#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cctype>

using namespace std;

// ----------------------------------------------------
// Helper function
// Converts a string to lowercase so searches
// can be case-insensitive
// ----------------------------------------------------
string toLowerCase(string text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
    }

    return text;
}
//-----------------------------------------------------
// Helper Function
// Gets a number from the user and checks for blank
// or non-number input
//-----------------------------------------------------
int getValidNumberInput(string prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);

    if (input == "")
    {
        throw runtime_error("Input cannot be blank.");
    }

    for (size_t i = 0; i < input.length(); i++)
    {
        if (!isdigit(input[i]))
        {
            throw runtime_error("Input must be a number.");
        }
    }

    return stoi(input);
}

// ----------------------------------------------------
// Book class
// Stores information about one book in the library
// ----------------------------------------------------
class Book
{
private:
    int bookID;
    string title;
    string author;
    bool checkedOut;

public:
    // Default constructor
    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        checkedOut = false;
    }

    // Constructor with parameters
    Book(int id, string bookTitle, string bookAuthor)
    {
        bookID = id;
        title = bookTitle;
        author = bookAuthor;
        checkedOut = false;
    }

    // Access functions
    int getBookID() const
    {
        return bookID;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    bool isCheckedOut() const
    {
        return checkedOut;
    }

    // Mutator functions
    void checkOutBook()
    {
        if (checkedOut)
        {
            throw runtime_error("Book is already checked out.");
        }

        checkedOut = true;
    }

    void returnBook()
    {
        if (!checkedOut)
        {
            throw runtime_error("Book was not checked out.");
        }

        checkedOut = false;
    }

    // Display function
    void displayBook() const
    {
        cout << left << setw(8) << bookID
             << setw(50) << title
             << setw(25) << author
             << setw(15) << (checkedOut ? "Checked Out" : "Available")
             << endl;
    }
};

// ----------------------------------------------------
// Person base class
// Used as a parent class for library users
// ----------------------------------------------------
class Person
{
protected:
    int personID;
    string name;

public:
    Person()
    {
        personID = 0;
        name = "";
    }

    Person(int id, string personName)
    {
        personID = id;
        name = personName;
    }

    int getPersonID() const
    {
        return personID;
    }

    string getName() const
    {
        return name;
    }

    virtual void displayPerson() const
    {
        cout << "ID: " << personID << " | Name: " << name << endl;
    }
};

// ----------------------------------------------------
// Member derived class
// Inherits from Person
// ----------------------------------------------------
class Member : public Person
{
private:
    int booksBorrowed;

public:
    Member() : Person()
    {
        booksBorrowed = 0;
    }

    Member(int id, string memberName) : Person(id, memberName)
    {
        booksBorrowed = 0;
    }

    void borrowBook()
    {
        booksBorrowed++;
    }

    void returnBorrowedBook()
    {
        if (booksBorrowed > 0)
        {
            booksBorrowed--;
        }
    }

    int getBooksBorrowed() const
    {
        return booksBorrowed;
    }

    void displayPerson() const override
    {
        cout << "Member ID: " << personID
             << " | Name: " << name
             << " | Books Borrowed: " << booksBorrowed << endl;
    }
};

// ----------------------------------------------------
// Library class
// Uses composition because a library "has" books
// ----------------------------------------------------
class Library
{
private:
    vector<Book> books;
// Composition: Library "has" a collection of Book Objects
public:
    // Add a new book to the library
    void addBook(const Book& newBook)
    {
        books.push_back(newBook);
    }

    // Display all books
    void showAllBooks() const
    {
        if (books.empty())
        {
            cout << "No books in the library." << endl;
            return;
        }

        cout << left << setw(8) << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << endl;

        cout << string(78, '-') << endl;

        for (size_t i = 0; i < books.size(); i++)
        {
            books[i].displayBook();
        }
    }

    // Search for a book by title (case-insensitive & partial match)
    int searchByTitle(string searchTitle) const
    {
        string loweredSearch = toLowerCase(searchTitle);

        for (size_t i = 0; i < books.size(); i++)
        {
            string loweredTitle = toLowerCase(books[i].getTitle());

            if (loweredTitle.find(loweredSearch) != string::npos)
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    // Get book title by index
    string getBookTitleByIndex(int index) const
    {
        if (index >= 0 && index < static_cast<int>(books.size()))
        {
            return books[index].getTitle();
        }

        return "";
    }

    // Show all matching books
    void showMatchingBooks(string searchTitle) const
    {
        string loweredSearch = toLowerCase(searchTitle);
        bool found = false;

        cout << left << setw(8) << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << endl;

        cout << string(78, '-') << endl;

        for (size_t i = 0; i < books.size(); i++)
        {
            string loweredTitle = toLowerCase(books[i].getTitle());

            if (loweredTitle.find(loweredSearch) != string::npos)
            {
                books[i].displayBook();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No matching books found." << endl;
        }
    }

    // Find a book by ID
    int findBookByID(int bookID) const
    {
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].getBookID() == bookID)
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    // Show one book by index
    void showBookByIndex(int index) const
    {
        if (index >= 0 && index < static_cast<int>(books.size()))
        {
            cout << left << setw(8) << "ID"
                 << setw(50) << "Title"
                 << setw(25) << "Author"
                 << setw(15) << "Status"
                 << endl;

            cout << string(78, '-') << endl;
            books[index].displayBook();
        }
    }

    // Check out a book using title
    void checkOutBook(string searchTitle)
    {
        int index = searchByTitle(searchTitle);

        if (index == -1)
        {
            throw runtime_error("Book not found in library.");
        }

        books[index].checkOutBook();
    }

    // Check out a book using ID / index
    void checkOutBookByIndex(int index)
    {
        if (index >= 0 && index < static_cast<int>(books.size()))
        {
            if (books[index].isCheckedOut())
            {
                throw runtime_error("Book is already checked out.");
            }

            books[index].checkOutBook();
            cout << "Book checked out successfully.\n";
        }
        else
        {
            throw runtime_error("Invalid book index.");
        }
    }

    // Return a book using title
    void returnBook(string searchTitle)
    {
        int index = searchByTitle(searchTitle);

        if (index == -1)
        {
            throw runtime_error("Book not found in library.");
        }

        books[index].returnBook();
    }

    // Return a book using ID / index
    void returnBookByIndex(int index)
    {
        if (index >= 0 && index < static_cast<int>(books.size()))
        {
            if (!books[index].isCheckedOut())
            {
                throw runtime_error("Book is already available.");
            }

            books[index].returnBook();
            cout << "Book returned successfully.\n";
        }
        else
        {
            throw runtime_error("Invalid book index.");
        }
    }
};

// ----------------------------------------------------
// Helper function to find member by ID
// ----------------------------------------------------
int findMemberByID(const vector<Member>& members, int memberID)
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].getPersonID() == memberID)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// ----------------------------------------------------
// Main function
// ----------------------------------------------------
int main()
{
    Library myLibrary;
    vector<Member> members;

    members.push_back(Member(1234567, "Jane Doe"));
    members.push_back(Member(2345678, "John Smith"));
    members.push_back(Member(3456789, "Lauren Bennett"));
    members.push_back(Member(4567890, "Susan Forbes"));

    // Starter data
    myLibrary.addBook(Book(1, "C++ Basics", "D. S. Malik"));
    myLibrary.addBook(Book(2, "Object-Oriented Programming", "Robert Lafore"));
    myLibrary.addBook(Book(3, "Add One to COBOL", "A Funny"));
    myLibrary.addBook(Book(4, "Programming Basics", "KYSU Publication"));
    myLibrary.addBook(Book(5, "Programming in C++", "B. Stroustrup"));
    myLibrary.addBook(Book(6, "How Many Slices Would You Like?: Pizza Coding", "Lauren B."));

    int choice;
    string title;

    cout << "======================================" << endl;
    cout << "   LIBRARY MANAGEMENT SYSTEM MENU" << endl;
    cout << "======================================" << endl;

    do
    {
        cout << "\nPlease choose an option:" << endl;
        cout << "1. Show all books" << endl;
        cout << "2. Search for a book by title" << endl;
        cout << "3. Check out a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Display member information" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number from 1 to 6." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1:
                cout << "\nAll books in the library:\n";
                myLibrary.showAllBooks();
                break;

            case 2:
            {
                cout << "Enter the title to search: ";
                getline(cin, title);

                cout << "\nMatching books:\n";
                myLibrary.showMatchingBooks(title);
                break;
            }

            case 3:
            {
                cout << "Enter the title to check out: ";
                getline(cin, title);

                cout << "\nMatching books:\n";
                myLibrary.showMatchingBooks(title);


                try
                {
                    int bookID = getValidNumberInput("Enter Book ID:");
                    int memberID = getValidNumberInput("Enter Member ID:");

                    int foundIndex = myLibrary.findBookByID(bookID);
                    if (foundIndex == -1)
                    {
                        throw runtime_error("Book not found in library.");
                    }

                    int memberIndex = findMemberByID(members, memberID);
                    if (memberIndex == -1)
                    {
                        throw runtime_error("Member ID not found.");
                    }

                    string actualTitle = myLibrary.getBookTitleByIndex(foundIndex);
                    myLibrary.checkOutBookByIndex(foundIndex);
                    members[memberIndex].borrowBook();

                    cout << "\"" << actualTitle << "\" checked out to Member: "
                         << members[memberIndex].getPersonID() << " "
                         << members[memberIndex].getName() << endl;

                    cout << "Reminder: Please return this book within 14 days." << endl;
                }
                catch (runtime_error& e)
                {
                    cout << "Error: " << e.what() << endl;
                }

                break;
            }

            case 4:
            {
                cout << "Enter the title to return: ";
                getline(cin, title);

                cout << "\nMatching books:\n";
                myLibrary.showMatchingBooks(title);

                int bookID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                cin.ignore(1000, '\n');

                int memberID;
                cout << "Enter Member ID: ";
                cin >> memberID;
                cin.ignore(1000, '\n');

                try
                {
                    int foundIndex = myLibrary.findBookByID(bookID);
                    if (foundIndex == -1)
                    {
                        throw runtime_error("Book not found in library.");
                    }

                    int memberIndex = findMemberByID(members, memberID);
                    if (memberIndex == -1)
                    {
                        throw runtime_error("Member ID not found.");
                    }

                    string actualTitle = myLibrary.getBookTitleByIndex(foundIndex);
                    myLibrary.returnBookByIndex(foundIndex);
                    members[memberIndex].returnBorrowedBook();

                    cout << "\"" << actualTitle << "\" returned successfully by Member: "
                         << members[memberIndex].getPersonID() << " "
                         << members[memberIndex].getName() << endl;
                }
                catch (runtime_error& e)
                {
                    cout << "Error: " << e.what() << endl;
                }

                break;
            }

            case 5:
            {
                cout << "\nMember information:\n";

                for (size_t i = 0; i < members.size(); i++)
                {
                    members[i].displayPerson();
                }

                break;
            }

            case 6:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid menu choice. Please enter a number from 1 to 6." << endl;
        }

    } while (choice != 6);

    return 0;
}
