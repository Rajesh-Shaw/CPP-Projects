#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;


// Base Class
class Employee
{
    protected:
        int id;
        string name;
        double baseSalary;
    
    public:
        Employee(){}
        Employee(int i, string n, double s): id(i), name(n), baseSalary(s){}
        virtual ~Employee(){}

        virtual double calculateSalary() const = 0;
        virtual string getRole() const = 0;

        virtual void display() const{
            cout << setw(5) << id << " | "
                 << setw(15) << name << " | "
                 << setw(10) << getRole << " | "
                 << "Rs." << setw(10) << fixed << setprecision(2) << calculateSalary() << endl;
        }

        virtual string serialize() const {
            return to_string(id) + "," + name + "," + to_string(baseSalary) + "," + getRole() + "\n";
        }

        int getId() const{
            return id;
        }

        string getName() const{
            return name;
        }

};


// Derived class
// manager

class Manager : public Employee
{
    double bonus;
    public:
        Manager(int i, string n, double s, double b) : Employee(i, n, s), bonus(b){}

        string getRole() const override{
            return "Manager";
        }
        string serialize()const override{
            return to_string(id) + "," + name + "," + to_string(baseSalary) + ",Manager," + to_string(bonus) + "\n";
        }

};


// Developer
class Developer : public Employee
{
    int projects;

    public:
        Developer(int i, string n, double s, int p)
            : Employee(i, n, s), projects(p) {}
        
        double calculateSalary() const override{
            return baseSalary + (projects * 1000);
        }

        string getRole() const override{
            return "Developer";
        }

        string serialize() const override{
            return to_string(id) + "," +name + "," + to_string(baseSalary) + ",Developer" + to_string(projects) + "\n"; 
        }
};


//intern
class Intern : public Employee
{
    int workingHours;
    public:
        Intern(int i, string n, double s, int h)
            : Employee(i, n, s), workingHours(h){}

        double calculateSalary() const override{
            return baseSalary + (workingHours * 50);
        }

        string getRole() const override{
            return "Intern";
        }

        string serialize() const override{
            return to_string(id) + "," + name + "," + to_string(baseSalary) + ",Intern" + to_string(workingHours) + "\n";
        }
};


//system class

class EmployeeSystem
{
    vector<Employee*> employees;

    public:
        EmployeeSystem()
        {
            loadFromFile();
        }
        ~EmployeeSystem()
        {
            saveToFile();
            for(auto e: employees) delete e;
        }
    
        void menu()
        {
            int choice;
            do{
                cout << "\n===========================================\n";
                cout << "        EMPLOYEE MANAGEMENT SYSTEM\n";
                cout << "===========================================\n";
                cout << "1. Add Employee\n";
                cout << "2. View All Employees\n";
                cout << "3. Search Employee by ID\n";
                cout << "4. Exit & Save\n";
                cout << "-------------------------------------------\n";

                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();


                switch (choice) 
                {
                    case 1: addEmployee(); break;
                    case 2: viewEmployees(); break;
                    case 3: searchEmployee(); break;
                    case 4: 
                        saveToFile();
                        cout << "Data saved successfully. Goodbye!\n";
                        break;
                    default: cout << "Invalid choice!\n";
                }
        
            }while(choice != 4);
        }

        void addEmployee()
        {

        }

        void viewEmployees() const
        {

        }

        void searchEmployee() const
        {

        }

        void saveToFile() const
        {

        }

        void loadFromFile()
        {

        }
};



// Main Funtion
int main()
{
    EmployeeSystem system;
    system.menu();
    return 0;
}