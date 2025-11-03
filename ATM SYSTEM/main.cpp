#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ACCOUNTS = 100;

struct Account {
    int accNo;
    string name;
    int pin;
    double balance;
};

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function declarations
void loadAccounts();
void saveAccounts();
int login();
void atmMenu(int index);
void checkBalance(int index);
void depositMoney(int index);
void withdrawMoney(int index);
void changePIN(int index);

int main() 
{
    loadAccounts();
    cout << "=====================================\n";
    cout << "          REAL ATM SYSTEM            \n";
    cout << "=====================================\n";

    while (true) 
    {
        int index = login();
        if (index == -1)
            break;
        atmMenu(index);
    }

    saveAccounts();
    cout << "System shutting down... Goodbye!\n";
    return 0;
}



void loadAccounts() 
{
    ifstream in("accounts.txt");
    if (!in) 
    {
        accountCount = 0;
        return;
    }

    while (in >> accounts[accountCount].accNo >> accounts[accountCount].name >> accounts[accountCount].pin >> accounts[accountCount].balance) 
    {
        accountCount++;
        if (accountCount >= MAX_ACCOUNTS)
            break;
    }
    in.close();
}


void saveAccounts() 
{
    ofstream out("accounts.txt");
    for (int i = 0; i < accountCount; i++) 
    {
        out << accounts[i].accNo << " "
            << accounts[i].name << " "
            << accounts[i].pin << " "
            << accounts[i].balance << "\n";
    }
    out.close();
}

int login() 
{
    int accNo, enteredPin;
    cout << "\nPlease insert your card (Enter Account Number or 0 to exit): ";
    cin >> accNo;
    if (accNo == 0)
        return -1;

    int index = -1;
    for (int i = 0; i < accountCount; i++) 
    {
        if (accounts[i].accNo == accNo) 
        {
            index = i;
            break;
        }
    }


    if (index == -1) 
    {
        cout << "Account not found!\n";
        return -1;
    }

    cout << "Enter your PIN: ";
    cin >> enteredPin;

    if (enteredPin != accounts[index].pin) 
    {
        cout << "Incorrect PIN! Access denied.\n";
        return -1;
    }

    cout << "\nWelcome, " << accounts[index].name << "!\n";
    return index;
}