#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;


struct Vehicle 
{
    int slotId;
    string plate;
    time_t entryTime;
};


class ParkingSystem 
{
    int totalSlots;
    vector<Vehicle> activeVehicles;
    vector<int> availableSlots;

    public:
        ParkingSystem(int slots = 5) : totalSlots(slots) 
        {
            for (int i = 1; i <= totalSlots; ++i)
                availableSlots.push_back(i);
            loadFromFile();
        }

        ~ParkingSystem() 
        {
            saveToFile();
        }


        void menu() 
        {
            int ch;
            do {
                cout << "\n====================================\n";
                cout << "      SMART PARKING SYSTEM\n";
                cout << "====================================\n";
                cout << "1. Vehicle Entry\n";
                cout << "2. Vehicle Exit\n";
                cout << "3. View Parking Status\n";
                cout << "4. Exit & Save\n";
                cout << "------------------------------------\n";
                cout << "Enter your choice: ";
                cin >> ch;
                cin.ignore();

                switch (ch) {
                    case 1: vehicleEntry(); break;
                    case 2: vehicleExit(); break;
                    case 3: viewStatus(); break;
                    case 4: cout << "Saving & Exiting...\n"; break;
                    default: cout << "Invalid choice!\n";
                }
            } while (ch != 4);
        }



        private:
            void vehicleEntry() 
            {
                if (availableSlots.empty()) 
                {
                    cout << "Parking Full!\n";
                    return;
                }

                string plate;
                cout << "Enter vehicle plate number: ";
                cin >> plate;

                int slot = availableSlots.front();
                availableSlots.erase(availableSlots.begin());

                Vehicle v{slot, plate, time(0)};
                activeVehicles.push_back(v);

                cout << "Vehicle " << plate << " parked at slot " << slot << endl;
            }

            void vehicleExit() 
            {
                string plate;
                cout << "Enter vehicle plate number: ";
                cin >> plate;

                bool found = false;
                for (auto it = activeVehicles.begin(); it != activeVehicles.end(); ++it) 
                {
                    if (it->plate == plate) {
                        found = true;
                        time_t exitTime = time(0);
                        double hours = difftime(exitTime, it->entryTime) / 3600.0;
                        if (hours < 1) hours = 1; // minimum 1 hour
                        double fee = hours * 20; // Rs.20 per hour

                        cout << "Parking Duration: " << fixed << setprecision(2) << hours << " hours\n";
                        cout << "Parking Fee: Rs." << fee << endl;

                        availableSlots.push_back(it->slotId);
                        activeVehicles.erase(it);
                        break;
                    }
                }

                if (!found)
                    cout << "Vehicle not found!\n";
            }


            void viewStatus() 
            {
                cout << "\n===== Current Parking Status =====\n";
                cout << "Total Slots: " << totalSlots << "\n";
                cout << "Available Slots: " << availableSlots.size() << "\n";
                cout << "Occupied: " << activeVehicles.size() << "\n";
                cout << "----------------------------------\n";

                for (auto &v : activeVehicles) {
                    cout << "Slot " << v.slotId << " -> " << v.plate
                        << " | In Time: " << ctime(&v.entryTime);
                }
            }


            void saveToFile() 
            {
                ofstream out("parking_data.txt");
                for (auto &v : activeVehicles) {
                    out << v.slotId << "," << v.plate << "," << v.entryTime << endl;
                }
                out.close();
            }


            void loadFromFile() 
            {
                ifstream in("parking_data.txt");
                if (!in) return;

                string line;
                while (getline(in, line)) 
                {
                    if (line.empty()) continue;

                    stringstream ss(line);
                    string slotStr, plate, timeStr;
                    getline(ss, slotStr, ',');
                    getline(ss, plate, ',');
                    getline(ss, timeStr, ',');

                    Vehicle v;
                    v.slotId = stoi(slotStr);
                    v.plate = plate;
                    v.entryTime = stol(timeStr);

                    activeVehicles.push_back(v);
                }

                in.close();

                // remove taken slots
                for (auto &v : activeVehicles) 
                {
                    auto it = find(availableSlots.begin(), availableSlots.end(), v.slotId);
                    if (it != availableSlots.end())
                        availableSlots.erase(it);
                }
            }

};



int main() 
{
    ParkingSystem system(5);
    system.menu();
    return 0;
}