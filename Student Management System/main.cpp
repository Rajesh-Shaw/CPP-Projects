#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
class Student 
{
    public:
        int rollNo;
        string name;
        float marks;

        Student(int r=0, string n="", float m=0.0f)
        : rollNo(r), name(n), marks(m)
        {

        }

        void display() const{
            cout << "Roll No: "<<rollNo<<" | Name: " << name << " | Marks: "<< marks <<endl;
        }
};


void showMenu();
void addStudent(vector<Student>& students);
void displayAll(const vector<Student>& students);
void searchStudent(const vector<Student>& students);
void deleteStudent(vector<Student>& students);
void saveToFile(const vector<Student>& students);
void loadFromFile(vector<Student>& students);

int main()
{
    vector<Student> students;
    int choice;
    loadFromFile(students);

    while(true)
    {
        showMenu();
        cout<<"Enter your choice: ";
        cin>>choice;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        

        switch (choice)
        {
            case 1: addStudent(students);break;
            case 2: displayAll(students);break;
            case 3: searchStudent(students);break;
            case 4: deleteStudent(students);break;
            case 5: saveToFile(students);break;
            case 6: saveToFile(students);
                    cout<<"Exiting... Goodbye!"<<endl;
                    return 0;
            default:
                cout << "Invalid choice! Please try again."<<endl;
        }
        cout<<"\n";
    }
}


void showMenu()
{
    cout << "==============================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM  " << endl;
    cout << "==============================" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display All Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Delete Student" << endl;
    cout << "5. Save to File" << endl;
    cout << "6. Exit" << endl;
}

void addStudent(vector<Student>& students)
{
    int roll;
    string name;
    float marks;

    cout << "Enter Roll No: ";
    cin  >> roll;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Marks: ";
    cin  >> marks;

    students.emplace_back(roll, name, marks);
    cout << "Student added Successfully!" << endl;
}

void displayAll(const vector<Student>& students)
{
    if(students.empty())
    {
        cout << "No Student records found!" << endl;
        return;
    }

    cout << "\n-------------- Students List --------------\n";
    for(const auto& s : students)
        s.display();
}


void searchStudent(const vector<Student>& students)
{
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    for (const auto& s : students) 
    {
        if (s.rollNo == roll) 
        {
            cout << "Student Found:\n";
            s.display();
            return;
        }
    }
    cout << "Student not found!" << endl;
}


void deleteStudent(vector<Student>& students) 
{
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) 
    {
        if (it->rollNo == roll) 
        {
            students.erase(it);
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}


void saveToFile(const vector<Student>& students) 
{
    ofstream file("students.txt");
    for (const auto& s : students)
        file << s.rollNo << "," << s.name << "," << s.marks << "\n";
    file.close();
    cout << "Data saved to file successfully!" << endl;
}

void loadFromFile(vector<Student>& students) 
{
    ifstream file("students.txt");
    if (!file) return;

    students.clear();
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        int roll;
        string name;
        float marks;
        char comma;

        ss >> roll >> comma;
        getline(ss, name, ',');
        ss >> marks;

        students.emplace_back(roll, name, marks);
    }
    file.close();
}