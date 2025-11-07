#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Car
{
    private:
        int id;
        string brand, model;
        double pricePerDay;
        bool available;

    public:
        Car(){}
        Car(int i, string b, string m, double p, bool a=true)
            : id(i), brand(b), model(m), pricePerDay(p), available(a){} 

        void displayCar()
        {
            cout<<"ID: " << id << " | " << brand << " " << model
                <<" | Price per day: Rs." << pricePerDay
                <<" | "<< (available ? "Available" : "Rented") << endl; 
        }
        int getId()
        {
            return id;
        }
        double getPrice()
        {
            return pricePerDay;
        }
        bool isAvailable()
        {
            return available;
        }
        void rent()
        {
            available = false;
        }
        void makeAvailable()
        {
            available = true;
        }

        void setData(int i, string b, string m, double p, bool a)
        {
            id = i;
            brand = b;
            model = m;
            pricePerDay = p;
            available = a;
        }

        string getDataString()
        {
            return to_string(id) + "," + brand  + "," + model  + "," +
                    to_string(pricePerDay)  + "," + to_string(available) + "\n";
        }
};

class Customer
{
    private:
        int id;
        string name;
        int rentedCarId;
        int rentalDays;

    public:
        Customer(): rentedCarId(-1), rentalDays(0){}
        Customer(int i, string n)
            : id(i), name(n), rentedCarId(-1), rentalDays(0){}
        void displayCustomer()
        {
            cout << "Customer ID: " << id << " | Name: " << name << endl;
        }
        void rentCar(int carId, int days)
        {
            rentedCarId = carId;
            rentalDays = days;
        }
        int getRentedCarId()
        {
            return rentedCarId;
        }
        int getRentalDays()
        {
            return rentalDays;
        }
        int getId()
        {
            return id;
        }
        string getName()
        {
            return name;
        }
        void returnCar()
        {
            rentedCarId = -1;
            rentalDays = 0;
        }

        void setData(int i, string n, int carId, int days)
        {
            id = i;
            name = n;
            rentedCarId = carId;
            rentalDays = days;
        }

        string getDataString()
        {
            return to_string(id)  + "," + name  + "," + to_string(rentedCarId)  + "," + to_string(rentalDays) + "\n";
        }
        
};

class RentalSystem
{
    private:
        Car cars[50];
        Customer customers[50];
        int carCount, customerCount;
    
    public:
        RentalSystem() : carCount(0), customerCount(0)
        {
            loadData();
        }

        void menu()
        {
            int choice;
            do
            {
                cout << "\n=========================================\n";
                cout << "             CAR RENTAL SYSTEM           \n";
                cout << "=========================================\n";
                cout << "1. Add Car\n";
                cout << "2. View Available Cars\n";
                cout << "3. Rent a Car\n";
                cout << "4. Return a Car\n";
                cout << "5. Exit & Save\n";
                cout << "-----------------------------------------\n";
                
                cout << "Enter your choice: ";
                if (!(cin >> choice))
                {
                    cout << "Invalid input! Please enter a number.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                switch(choice)
                {
                    case 1: addCar(); break;
                    case 2: viewCars(); break;
                    case 3: rentCar(); break;
                    case 4: returnCar(); break;
                    case 5: saveData();
                            cout << "Data Saved Successfully. Good Bye!\n";
                            break;
                    default: 
                            cout << "Invalid Choice! Try again.\n";
                }

            }while(choice !=5);
        }
        
        void addCar()
        {
            int id; 
            string brand, model;
            double price;

            cout << "Enter Car ID: ";
            cin >> id;
            cin.ignore();

            for (int i = 0; i < carCount; i++) 
            {
                if (cars[i].getId() == id) {
                    cout << "Car ID already exists! Try again.\n";
                    return;
                }
            }

            cout << "Enter Brand: ";
            getline(cin, brand);
            cout << "Enter Model: ";
            getline(cin, model);
            cout << "Enter Price per day: ";
            cin >> price;

            cars[carCount++] = Car(id, brand, model, price);
            cout << "Car added successfully";
            cars[carCount - 1].displayCar();
        }

        void viewCars()
        {
            cout << "\n---------- Available Cars ----------\n";
            for(int i=0; i< carCount; i++)
            {
                if(cars[i].isAvailable())
                {
                    cars[i].displayCar();
                }
            }
            cout << "-----------------------------------\n";
        }

        void rentCar()
        {
            int custId, carId, days;
            string name;

            cout << "Enter Customer ID: ";
            cin >> custId;
            cin.ignore();
            cout << "Enter Customer Name: ";
            getline(cin, name);

            customers[customerCount] = Customer(custId, name);
            
            viewCars();
            cout << "Enter Car ID to rent: ";
            cin >> carId;
            cout << "Enter number of days: ";
            cin >> days;

            for(int i=0; i<carCount; i++)
            {
                if (cars[i].getId() == carId && cars[i].isAvailable())
                {
                    cars[i].rent();
                    customers[customerCount].rentCar(carId, days);
                    cout << "Car rented successfully to " << name << " for " << days << " days.\n";
                    customerCount++;
                    return;
                }
            }
            cout << "Car not available or invalid ID.\n";
        }

        void returnCar()
        {
            int custId;
            cout << "Enter Customer ID: ";
            cin >> custId;

            for (int i = 0; i < customerCount; i++)
            {
                if (customers[i].getId() == custId && customers[i].getRentedCarId() != -1)
                {
                    int carId = customers[i].getRentedCarId();
                    int days = customers[i].getRentalDays();

                    for (int j = 0; j < carCount; j++)
                    {
                        if (cars[j].getId() == carId)
                        {
                            double total = days * cars[j].getPrice();
                            cout << "Car Returned. Total Bill: Rs." << total << endl;
                            cars[j].makeAvailable();
                            customers[i].returnCar();
                            return;
                        }
                    }
                }
            }
            cout << "No active rental found for this customer.\n";
        }

        void saveData()
        {
            ofstream outCars("cars.txt"), outCust("customers.txt");
            for (int i = 0; i < carCount; i++)
            {
                outCars << cars[i].getDataString();
            }
            for (int i = 0; i < customerCount; i++)
            {
                 outCust << customers[i].getDataString();
            }
            outCars.close();
            outCust.close();
        }

        void loadData()
        {
            ifstream inCars("cars.txt");
            if (inCars)
            {
                int id; 
                string brand, model; 
                double price; 
                bool avail;

                while (inCars >> id)
                {
                    inCars.ignore();
                    getline(inCars, brand, ',');
                    getline(inCars, model, ',');
                    inCars >> price; 
                    inCars.ignore();
                    inCars >> avail; 
                    inCars.ignore();
                    cars[carCount++].setData(id, brand, model, price, avail);
                }
                inCars.close();
            }


            ifstream inCust("customers.txt");
            if (inCust) 
            {
                int id, carId, days; 
                string name;

                while (inCust >> id) 
                {
                   inCust.ignore();
                    getline(inCust, name, ',');
                    inCust >> carId; 
                    inCust.ignore();
                    inCust >> days; 
                    inCust.ignore(); 
                    customers[customerCount++].setData(id, name, carId, days);
                }
                inCust.close();
            }
            
        }
};


int main()
{
    RentalSystem app;
    app.menu();
    return 0;
}