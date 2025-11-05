#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_BOOKS = 100;

struct Book
{
    int id;
    string title;
    string author;
    bool isIssued;
};

Book library[MAX_BOOKS];
int bookCount = 0;

// funtion declarations
void showMenu();
void loadFromFile();
void saveToFile();
void addBook();
void viewBooks();
void searchBook();
void issueBook();
void returnBook();
int findBookById(int id);

int main()
{
    loadFromFile();
    int choice;

    cout << "=======================================================\n";
    cout << "              LIBRARY MANAGEMENT SYSTEM                \n";
    cout << "=======================================================\n";

    while(true)
    {
        showMenu();
        cout << "Enter your choice (1-7): ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch(choice)
        {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: saveToFile(); break;
            case 7: saveToFile();
                    cout << "Exiting... Data saved successfully!\n";
                    return 0;
            default: 
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n";
    }
    return 0;
}


// funtion definitions

void showMenu()
{
    cout << "\n1. Add Book\n";
    cout << "2. View All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Issue Book\n";
    cout << "5. Return Book\n";
    cout << "6. Save to File\n";
    cout << "7. Exit\n";
}


void loadFromFile()
{
    ifstream in("library.txt");
    if(!in)
    {
        bookCount = 0;
        cout << "No previous Data Found";
        return;
    }

    bookCount = 0;
    while(in >> library[bookCount].id)
    {
        in.ignore();
        getline(in, library[bookCount].title);
        getline(in, library[bookCount].author);
        in >> library[bookCount].isIssued;
        in.ignore();
        bookCount++;
        if(bookCount >= MAX_BOOKS)
            break;
    }
    in.close();
    cout << "Loaded " << bookCount << " book(s) from file.\n";
}

void saveToFile()
{
    ofstream out("library.txt");
    for(int i=0; i<bookCount; i++)
    {
        out << library[i].id << "\n"
            << library[i].title << "\n"
            << library[i].author << "\n"
            << library[i].isIssued << "\n";
    }
    out.close();
    cout << "Data saved succesfully.\n";
}

void addBook()
{
    if(bookCount >= MAX_BOOKS)
    {
        cout << "Library full! Cannot add more Books.\n";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> library[bookCount].id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, library[bookCount].title);
    cout << "Enter Author: ";
    getline(cin, library[bookCount].author);
    library[bookCount].isIssued = false;

    bookCount++;
    cout << "Book added succesfully.\n";
}

void viewBooks()
{
    if(bookCount == 0)
    {
        cout << "No Books available.\n";
        return ;
    }

    cout << "\n--- Library Book ---\n";
    for(int i=0; i<bookCount; i++)
    {
        cout << "ID: " << library[i].id
             << " | Title: " << library[i].title
             << " | Author: " << library[i].author
             << " | Status: " << (library[i].isIssued ? "Issued" : "Available") << "\n";
    }
}

int findBookById(int id)
{
    for(int i=0; i<bookCount; i++)
    {
        if(library[i].id == id)
            return i;
    }
    return -1;
}

void searchBook()
{
    cout << "Enter Book ID to search: ";
    int id;
    cin >> id;

    int idx = findBookById(id);
    if(idx == -1)
    {
        cout << "Book not found.\n";
        return;
    }

    cout << "Found: " << library[idx].title << " by " 
                        << library[idx].author << " | Status : "
                        << (library[idx].isIssued ? "Issued" : "Available") << "\n";
}

void issueBook()
{
    cout << "Enter Book ID to issue: ";
    int id;
    cin >> id;

    int idx = findBookById(id);
    if(idx == -1)
    {
        cout << "Book not found.\n";
        return;
    }

    if(library[idx].isIssued)
    {
        cout << "Book already issued.\n";
        return;
    }

    library[idx].isIssued = true;
    cout << "Book issued successfully.\n";
}

void returnBook()
{
    cout << "Enter Book ID to return: ";
    int id;
    cin >> id;

    int idx = findBookById(id);
    if (idx == -1) 
    {
        cout << "Book not found.\n";
        return;
    }

    if (!library[idx].isIssued) 
    {
        cout << "This book wasn't issued.\n";
        return;
    }

    library[idx].isIssued = false;
    cout << "Book returned successfully.\n";
}