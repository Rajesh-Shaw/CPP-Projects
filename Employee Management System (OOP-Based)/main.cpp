#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include<sstream>
#include <limits>
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
                 << setw(10) << getRole() << " | "
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
        double calculateSalary() const override{
            return (baseSalary + bonus);
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
            return (baseSalary + (projects * 1000));
        }

        string getRole() const override{
            return "Developer";
        }

        string serialize() const override{
            return to_string(id) + "," +name + "," + to_string(baseSalary) + ",Developer," + to_string(projects) + "\n"; 
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
            return (baseSalary + (workingHours * 50));
        }

        string getRole() const override{
            return "Intern";
        }

        string serialize() const override{
            return to_string(id) + "," + name + "," + to_string(baseSalary) + ",Intern," + to_string(workingHours) + "\n";
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
            int id, roleChoice;
            string name;
            double base;

            cout << "Enter Employee ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // cin.ignore();

            for (auto e : employees) 
            {
                if (e->getId() == id) 
                {
                    cout << "Error: Employee ID already exists!\n";
                    return;
                }
            }

            cout << "Enter Name: ";
            getline(cin, name);

            cout<< "Enter Base Salary: ";
            cin >> base;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Select Role:\n1. Manager\n2. Developer\n3. Intern\nEnter: ";
            cin >> roleChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(roleChoice)
            {
                case 1:{
                    double bonus;
                    cout << "Enter Bonus: ";
                    cin >> bonus;
                    employees.push_back(new Manager(id, name, base, bonus));
                    break;
                }
                case 2:{
                    int projects;
                    cout << "Enter Number of Projects: ";
                    cin >> projects;
                    employees.push_back(new Developer(id, name, base, projects));
                    break;
                }
                case 3:{
                    int hours;
                    cout << "Enter Working Hours: ";
                    cin >> hours;
                    employees.push_back(new Intern(id, name, base, hours));
                    break;
                }
                default:
                    cout << "Invalid role!\n";
            }
            cout << "Employee added successfully!\n";
        }

        void viewEmployees() const
        {
            cout << "\n-----------------------------------------------------------\n";
            cout << "ID    | Name            | Role       | Salary\n";
            cout <<"-----------------------------------------------------------\n";
            for(auto e : employees)
                e->display();
            cout <<"-----------------------------------------------------------\n";
        }

        void searchEmployee() const
        {
            int id;
            cout << "Enter Employee ID to search: ";
            cin >> id;
            bool found = false;
            for(auto e : employees)
            {
                if(e->getId() == id)
                {
                    cout << "\nEmployee Found:\n";
                    e->display();
                    found = true;
                    break;
                }
            }
            if(!found)
                cout << "Employee not found.\n";
        }

        void saveToFile() const
        {
            ofstream out("employees.txt");
            for(auto e : employees)
                out << e->serialize();
            out.close();
        }

        void loadFromFile()
        {
            ifstream in("employees.txt");
            if(!in) return;

            string line;
            while(getline(in, line))
            {
                if(line.empty())
                    continue;
                
                stringstream ss(line);
                string idStr, name, baseStr, role, extraStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, baseStr, ',');
                getline(ss, role, ',');
                getline(ss, extraStr, ',');

                int id = stoi(idStr);
                double base = stod(baseStr);

                if(role == "Manager")
                    employees.push_back(new Manager(id, name, base, stod(extraStr)));
                else if(role == "Developer")
                    employees.push_back(new Developer(id, name, base, stoi(extraStr)));
                else if(role == "Intern")
                    employees.push_back(new Intern(id, name, base, stoi(extraStr)));

            }
            in.close();
        }
};



// Main Funtion
int main()
{
    EmployeeSystem system;
    system.menu();
    return 0;
}