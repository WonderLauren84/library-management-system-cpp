#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cctype>
#include <queue>
#include <stack>
#include <list>

using namespace std;

/*
----------------------------------------------------
Helper function
Converts a string to lowercase so searches
can be case-insensitive.
----------------------------------------------------
*/
string toLowerCase(string text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        text[i] = static_cast<char>(tolower(static_cast<unsigned char>(text[i])));
    }

    return text;
}

/*
----------------------------------------------------
Helper function
Gets a number from the user and checks for blank
or non-number input before converting it to an int.
This supports exception handling in the menu.
----------------------------------------------------
*/
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

/*
----------------------------------------------------
Book class
Stores information about one book in the library.
This demonstrates classes, data abstraction, and
encapsulation by keeping book data private.
----------------------------------------------------
*/
class Book
{
private:
    int bookID;
    string title;
    string author;
    bool checkedOut;

public:
    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        checkedOut = false;
    }

    Book(int id, string bookTitle, string bookAuthor)
    {
        bookID = id;
        title = bookTitle;
        author = bookAuthor;
        checkedOut = false;
    }

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

    void displayBook() const
    {
        cout << left << setw(8) << bookID
             << setw(50) << title
             << setw(25) << author
             << setw(15) << (checkedOut ? "Checked Out" : "Available")
             << endl;
    }

    // Operator overloading <<
    // Allows a Book object to be displayed using cout.
    friend ostream& operator<<(ostream& out, const Book& book)
    {
        out << left << setw(8) << book.bookID
            << setw(50) << book.title
            << setw(25) << book.author
            << setw(15)
            << (book.checkedOut ? "Checked Out" : "Available");

        return out;
    }
};

/*
----------------------------------------------------
Person base class
Used as a parent class for library users.
The virtual displayPerson function allows derived
classes to override how person information is shown.
----------------------------------------------------
*/
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

/*
----------------------------------------------------
Member derived class
Inherits from Person.
This demonstrates inheritance because Member reuses
personID and name from the Person base class.
----------------------------------------------------
*/
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

    // Overrides the virtual function from Person.
    void displayPerson() const override
    {
        cout << "Member ID: " << personID
             << " | Name: " << name
             << " | Books Borrowed: " << booksBorrowed << endl;
    }
};

/*
----------------------------------------------------
Library class
Uses composition because a Library "has" a collection
of Book objects stored in a vector.
----------------------------------------------------
*/
class Library
{
private:
    // Vector stores the books in the library catalog.
    vector<Book> books;

public:
    void addBook(const Book& newBook)
    {
        books.push_back(newBook);
    }

    void showAllBooks() const
    {
        if (books.empty())
        {
            cout << "No books in the library." << endl;
            return;
        }

        cout << left << setw(8) << "ID"
             << setw(50) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << endl;

        cout << string(98, '-') << endl;

        for (size_t i = 0; i < books.size(); i++)
        {
            // Operator overloading << is used here to display Book objects.
            cout << books[i] << endl;
        }
    }

    // Searches by title using lowercase conversion and partial matching.
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

    string getBookTitleByIndex(int index) const
    {
        if (index >= 0 && index < static_cast<int>(books.size()))
        {
            return books[index].getTitle();
        }

        return "";
    }

    void showMatchingBooks(string searchTitle) const
    {
        string loweredSearch = toLowerCase(searchTitle);
        bool found = false;

        cout << left << setw(8) << "ID"
             << setw(50) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << endl;

        cout << string(98, '-') << endl;

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

    // Searches for a book by its unique book ID.
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

/*
----------------------------------------------------
Helper function
Finds a library member by member ID.
Returns the index if found, or -1 if not found.
----------------------------------------------------
*/
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

/*
----------------------------------------------------
Template function
Displays messages using different data types.
This demonstrates a simple template function.
----------------------------------------------------
*/
template <class T>
void displayMessage(T message)
{
    cout << message << endl;
}

/*
----------------------------------------------------
Main function
Creates the library, member list, queue, stack, and
linked list. The menu allows the user to interact
with the library management system.
----------------------------------------------------
*/
int main()
{
    Library myLibrary;
    vector<Member> members;

    // Queue stores hold requests in first-in, first-out order.
    queue<string> holdRequests;

    // Stack stores recent library actions in last-in, first-out order.
    stack<string> recentActions;

    // Linked list stores library notices that may change over time.
    list<string> libraryNotices;

    members.push_back(Member(1234567, "Jane Doe"));
    members.push_back(Member(2345678, "John Smith"));
    members.push_back(Member(3456789, "Lauren Bennett"));
    members.push_back(Member(4567890, "Susan Forbes"));

    myLibrary.addBook(Book(1, "C++ Basics", "D. S. Malik"));
    myLibrary.addBook(Book(2, "Object-Oriented Programming", "Robert Lafore"));
    myLibrary.addBook(Book(3, "Add One to COBOL", "A Funny"));
    myLibrary.addBook(Book(4, "Programming Basics", "KYSU Publication"));
    myLibrary.addBook(Book(5, "Programming in C++", "B. Stroustrup"));
    myLibrary.addBook(Book(6, "How Many Slices Would You Like?: Pizza Coding", "Lauren B."));

    libraryNotices.push_back("Return books within 14 days.");
    libraryNotices.push_back("Use book ID when checking out books.");
    libraryNotices.push_back("Late fees apply after overdue books.");

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
        cout << "6. Add hold request" << endl;
        cout << "7. Process next hold request" << endl;
        cout << "8. View recent actions" << endl;
        cout << "9. Display library notices" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number from 1 to 10." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1:
            {
                cout << "\nAll books in the library:\n";
                myLibrary.showAllBooks();
                break;
            }

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
                    int bookID = getValidNumberInput("Enter Book ID: ");
                    int memberID = getValidNumberInput("Enter Member ID: ");

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

                    // Recent checkout is added to the stack.
                    recentActions.push("Checked out: " + actualTitle);
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

                try
                {
                    int bookID = getValidNumberInput("Enter Book ID: ");
                    int memberID = getValidNumberInput("Enter Member ID: ");

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

                    // Recent return is added to the stack.
                    recentActions.push("Returned: " + actualTitle);
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
            {
                string requestName;

                cout << "Enter member name for hold request: ";
                getline(cin, requestName);

                if (requestName == "")
                {
                    cout << "Error: Hold request name cannot be blank." << endl;
                }
                else
                {
                    // Queue adds the newest hold request to the back.
                    holdRequests.push(requestName);

                    cout << requestName
                         << " has been added to the hold request queue."
                         << endl;
                }

                break;
            }

            case 7:
            {
                if (holdRequests.empty())
                {
                    cout << "No hold requests in the queue." << endl;
                }
                else
                {
                    // Queue processes the oldest hold request first.
                    cout << "Processing hold request for: "
                         << holdRequests.front()
                         << endl;

                    holdRequests.pop();
                }

                break;
            }

            case 8:
            {
                if (recentActions.empty())
                {
                    cout << "No recent actions available." << endl;
                }
                else
                {
                    // Stack displays the most recent action first.
                    cout << "Most recent library action: "
                         << recentActions.top()
                         << endl;
                }

                break;
            }

            case 9:
            {
                cout << "\nLibrary Notices:\n";

                // Linked list is traversed to display each notice.
                for (const string& notice : libraryNotices)
                {
                    cout << "- " << notice << endl;
                }

                break;
            }

            case 10:
            {
                // Template function is used to display the exit message.
                displayMessage("Exiting program...");
                break;
            }

            default:
            {
                cout << "Invalid menu choice. Please enter a number from 1 to 10." << endl;
                break;
            }
        }

    } while (choice != 10);

    return 0;
}
