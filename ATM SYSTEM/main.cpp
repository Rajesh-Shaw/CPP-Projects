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


void atmMenu(int index) {
    int choice;
    bool running = true;

    while (running) {
        cout << "\n=====================================\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit (Card Out)\n";
        cout << "=====================================\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: checkBalance(index); break;
            case 2: depositMoney(index); break;
            case 3: withdrawMoney(index); break;
            case 4: changePIN(index); break;
            case 5:
                cout << "Card ejected. Thank you!\n";
                running = false;
                break;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}

void checkBalance(int index) {
    cout << "Your current balance is: Rs." << accounts[index].balance << "\n";
}

void depositMoney(int index) {
    double amount;
    cout << "Enter amount to deposit: Rs.";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return;
    }
    accounts[index].balance += amount;
    cout << "Deposited successfully. New balance: Rs." << accounts[index].balance << "\n";
}

void withdrawMoney(int index) {
    double amount;
    cout << "Enter amount to withdraw: Rs.";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return;
    }

    if (amount > accounts[index].balance) {
        cout << "Insufficient funds!\n";
        return;
    }

    accounts[index].balance -= amount;
    cout << "Please take your cash. Remaining balance: Rs." << accounts[index].balance << "\n";
}

void changePIN(int index) {
    int oldPin, newPin;
    cout << "Enter current PIN: ";
    cin >> oldPin;

    if (oldPin != accounts[index].pin) {
        cout << "Incorrect current PIN!\n";
        return;
    }

    cout << "Enter new 4-digit PIN: ";
    cin >> newPin;

    if (newPin < 1000 || newPin > 9999) {
        cout << "PIN must be 4 digits!\n";
        return;
    }

    accounts[index].pin = newPin;
    cout << "PIN changed successfully!\n";
}