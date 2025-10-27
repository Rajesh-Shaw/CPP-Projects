#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROOMS = 100;

struct Room {
    int roomNumber;
    string type;
    double price;
    bool isBooked;
    string guestName;
};

Room rooms[MAX_ROOMS];
int roomCount = 0;

void showMenu();
void loadData();
void saveData();
void addRoom();
void viewRooms();
void bookRoom();
void cancelBooking();
void viewBookings();


int main() 
{
    loadData();

    int choice;
    while (true) 
    {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
    
        switch (choice) 
        {
            case 1: addRoom(); break;
            case 2: viewRooms(); break;
            case 3: bookRoom(); break;
            case 4: viewBookings(); break;
            case 5: cancelBooking(); break;
            case 6: saveData(); break;
            case 7:
                saveData();
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
        cout << "\n";
    }
    return 0;
}