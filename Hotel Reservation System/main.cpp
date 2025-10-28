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



void showMenu() {
    cout << "======================================\n";
    cout << "         HOTEL RESERVATION SYSTEM     \n";
    cout << "======================================\n";
    cout << "1. Add Room\n";
    cout << "2. View All Rooms\n";
    cout << "3. Book Room\n";
    cout << "4. View Bookings\n";
    cout << "5. Cancel Booking\n";
    cout << "6. Save Data\n";
    cout << "7. Exit\n";
}

void loadData() {
    ifstream in("rooms.txt");
    if (!in) {
        cout << "No previous data found.\n";
        return;
    }

    roomCount = 0;
    while (in >> rooms[roomCount].roomNumber) {
        in.ignore();
        getline(in, rooms[roomCount].type);
        in >> rooms[roomCount].price >> rooms[roomCount].isBooked;
        in.ignore();
        getline(in, rooms[roomCount].guestName);
        roomCount++;
    }
    in.close();
    cout << "Loaded " << roomCount << " room(s) from file.\n";
}

void saveData() {
    ofstream out("rooms.txt");
    for (int i = 0; i < roomCount; i++) {
        out << rooms[i].roomNumber << "\n"
            << rooms[i].type << "\n"
            << rooms[i].price << "\n"
            << rooms[i].isBooked << "\n"
            << rooms[i].guestName << "\n";
    }
    out.close();
    cout << "Data saved successfully!\n";
}


void addRoom()
{

}

void viewRooms()
{

}

void bookRoom()
{

}

void cancelBooking()
{

}

void viewBookings()
{

}
