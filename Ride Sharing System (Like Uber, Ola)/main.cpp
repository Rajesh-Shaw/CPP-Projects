#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include<ctime>
using namespace std;

class User{
    protected:
        int id;
        string name;
    
    public:
        User(){}
        User(int i, string n) : id(i), name(n) {}
        virtual ~User() {}

        int getId() const {return id;}
        string getName() const {return name;}
};


class Driver : public User {
        string vehicleType;
        string vehicleNumber;
        bool available;
    
    public:
        Driver(){}
        Driver(int i, string n, string type, string num, bool avail = true)
        : User(i, n), vehicleType(type), vehicleNumber(num), available(avail) {}

        string getVehicleType() const {return vehicleType;}
        string getVehicleNumber() const {return vehicleNumber;}

        bool isAvailable() const {return available;}
        void setAvailable(bool a){available = a;}

        void display() const{
            cout << setw(5) << id << " | "
                 << setw(15) << name << " | "
                 << setw(10) << vehicleType << " | "
                 << setw(12) << vehicleNumber << " | "
                 << (available ? "Available" : "Busy") << endl;
        }

        string serialize() const{
            return to_string(id) + "," + name + "," + vehicleType + "," + vehicleNumber + "," + (available ? "1" : "0") + "\n";
        }
};


class Ride
{
        int rideId;
        int riderId;
        int driverId;
        double distance;
        double fare;
        string vehicleType;

    public:
        Ride(){}
        Ride(int rId, int rider, int driver, double dist, string vtype, double f)
            : rideId(rId), riderId(rider), driverId(driver), distance(dist), fare(f), vehicleType(vtype){}
        
        void display() const{
            cout << setw(5) << rideId << " | "
                << setw(8) << riderId << " | "
                << setw(8) << driverId << " | "
                << setw(8) << distance << " km | "
                << setw(10) << vehicleType << " | "
                << "Rs." << fare << endl; 
        }

        string serialize() const 
        {
            return to_string(rideId) + "," + to_string(riderId) + "," +
                to_string(driverId) + "," + to_string(distance) + "," +
                vehicleType + "," + to_string(fare) + "\n";
        }
};



class RideSharingSystem
{
        vector<Driver> drivers;
        vector<Ride> rides;
        int rideCounter = 1000;

    public:
        RideSharingSystem()
        {
            srand(time(0));
            loadDrivers();
            loadRides();
        }

        ~RideSharingSystem()
        {
            saveDrivers();
            saveRides();
        }

        void menu()
        {
            int choice;
            do{
                cout << "\n========================================\n";
                cout << "         RIDE SHARING SYSTEM (OOP)\n";
                cout << "========================================\n";
                cout << "1. View Available Drivers\n";
                cout << "2. Book a Ride\n";
                cout << "3. View Ride History\n";
                cout << "4. Exit & Save\n";
                cout << "----------------------------------------\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch(choice)
                {
                    case 1: viewDrivers(); break;
                    case 2: bookRide(); break;
                    case 3: viewRides(); break;
                    case 4: saveDrivers();
                            saveRides();
                            cout << "Data saved successfully!\n"; break;
                    default:
                            cout << "Invalid choice! Try again.\n";       
                }

            }while(choice !=4);
        }

        void viewDrivers() const{
            cout << "\n----------------------- DRIVERS -----------------------------\n";
            cout << "ID    | Name            | Vehicle    | Number        | Status\n";
            cout << "-------------------------------------------------------------\n";
            for (auto &d : drivers)
                d.display();
            cout << "-------------------------------------------------------------\n";
    
        }

        void bookRide()
        {
            string riderName;
            int riderId;
            double distance;
            string vtype;

            cout << "Enter Rider ID: ";
            cin >> riderId;
            cin.ignore();
            cout << "Enter Rider Name: ";
            getline(cin, riderName);
            cout << "Enter Vehicle Type (Car/Bike/Auto): ";
            getline(cin, vtype);
            cout << "Enter Distance (km): ";
            cin >> distance;

            for (auto &d : drivers) 
            {
                if (d.getVehicleType() == vtype && d.isAvailable()) 
                {
                    double fare = calculateFare(vtype, distance);
                    int rideId = rideCounter++;

                    rides.push_back(Ride(rideId, riderId, d.getId(), distance, vtype, fare));
                    d.setAvailable(false);

                    cout << "\nRide Booked Successfully!\n";
                    cout << "Ride ID: " << rideId << "\nDriver: " << d.getName() << "\nFare: Rs." << fare << "\n";
                    return;
                }
            }

            cout << "No available driver for selected vehicle type.\n";

        }


        double calculateFare(const string &type, double distance)
        {
            if (type == "Car") return distance * 15;
            if (type == "Bike") return distance * 7;
            if (type == "Auto") return distance * 10;
            return distance * 12;
        }

        void viewRides() const{
            cout << "\n---------------- RIDE HISTORY --------------------------------\n";
            cout << "ID    | RiderID  | DriverID | Distance   | Vehicle     |   Fare\n";
            cout << "--------------------------------------------------------------\n";
            for (auto &r : rides)
                r.display();
            cout << "--------------------------------------------------------------\n";
        }

        void loadDrivers()
        {
            ifstream in("drivers.txt");
            if (!in) 
            {
                cout << "No driver data found. Adding sample drivers...\n";
                drivers.push_back(Driver(1, "Ramesh", "Car", "WB12AB1234"));
                drivers.push_back(Driver(2, "Suresh", "Bike", "WB14XY9876"));
                drivers.push_back(Driver(3, "Anil", "Auto", "WB15QW5643"));
                saveDrivers();
                return;
            }

            string line;
            while (getline(in, line)) 
            {
                if (line.empty()) continue;
                stringstream ss(line);
                string idStr, name, type, num, availStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, type, ',');
                getline(ss, num, ',');
                getline(ss, availStr, ',');

                drivers.push_back(Driver(stoi(idStr), name, type, num, availStr == "1"));
            }
            in.close();

        }


        void saveDrivers() const{
            ofstream out("drivers.txt");
            for (auto &d : drivers)
                out << d.serialize();
            out.close();
        }


        void loadRides()
        {
            ifstream in("rides.txt");
            if (!in) return;
            string line;

            while (getline(in, line)) 
            {
                if (line.empty()) continue;
                stringstream ss(line);
                string rideIdStr, riderIdStr, driverIdStr, distStr, vtype, fareStr;
                getline(ss, rideIdStr, ',');
                getline(ss, riderIdStr, ',');
                getline(ss, driverIdStr, ',');
                getline(ss, distStr, ',');
                getline(ss, vtype, ',');
                getline(ss, fareStr, ',');

                rides.push_back(Ride(stoi(rideIdStr), stoi(riderIdStr), stoi(driverIdStr),
                                    stod(distStr), vtype, stod(fareStr)));
            }
            in.close();
        }

        void saveRides() const{
            ofstream out("rides.txt");
            for (auto &r : rides)
                out << r.serialize();
            out.close();
        }
};


int main()
{
    RideSharingSystem system;
    system.menu();
    return 0;
}