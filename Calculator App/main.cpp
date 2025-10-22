#include<iostream>
using namespace std;

void showMenu();
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main()
{
    double num1, num2;
    int choice;

    while(true)
    {
        cout << "\n";
        showMenu();

        cout << "Enter your choice (1-5): ";
        cin  >> choice;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }


        if(choice == 5)
        {
            cout << "Exiting... Goodbye!"<<endl;
            break;
        }

        cout << "Enter First Number : ";
        cin  >> num1;
        cout << "Enter Second Number : ";
        cin  >> num2;
    

        switch(choice)
        {
            case 1: 
                cout << "Result: " << add(num1, num2) << endl; 
                break;
            case 2: 
                cout << "Result: " << subtract(num1, num2) << endl; 
                break;
            case 3: 
                cout << "Result: " << multiply(num1, num2) << endl; 
                break;
            case 4: 
                if(num2 == 0)
                    cout << "Error: Division by zero not allowed!" << endl; 
                else
                    cout << "Result: " << divide(num1, num2) << endl; 
                break;
            default: 
                cout << "Invalid choice! Please try again." << endl; 
        }
    }

    return 0;
}


void showMenu()
{
    cout << "========================================" << endl;
    cout << "             CALCULATOR APP             " << endl;
    cout << "========================================" << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;
    cout << "5. Exit" << endl;
}


double add(double a, double b)
{
    return a+b;
}

double subtract(double a, double b)
{
    return a-b;
}

double multiply(double a, double b)
{
    return a*b;
}

double divide(double a, double b)
{
    return a/b;
}
