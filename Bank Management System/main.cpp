#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;

const int MAX_ACCOUNTS = 100;

struct Account
{
    int accNo;
    string name;
    double balance;
};

Account accounts[MAX_ACCOUNTS];
int accountCount=0;

void showMenu();
void loadFromFile();
void saveToFile();
void createAccount();
void viewAllAccounts();
int findAccountIndex(int accNo);
void depositMoney();
void withdrawMoney();
void deleteAccount();

int main()
{
    loadFromFile();

    int choice = 0;
    while(true)
    {
        showMenu();
        cout << "Enter your choice (1-8): ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }

        switch(choice)
        {
            case 1: createAccount(); break;
            case 2: viewAllAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: deleteAccount(); break;
            case 6: saveToFile(); break;
            case 7: saveToFile(); 
                    cout << "Exiting... Goodbye!\n";
                    return 0;
            case 8: loadFromFile(); break;
            default :
                    cout << "Unknown choice. Try again.\n";
        }
        cout << "\n";
    }
    return 0;
}



void showMenu()
{
    cout << "========================================\n";
    cout << "         BANK MANAGEMENT SYSTEM         \n";
    cout << "========================================\n";
    cout << "1. Create Account\n";
    cout << "2. View All Accounts\n";
    cout << "3. Deposit Money\n";
    cout << "4. Withdraw Money\n";
    cout << "5. Delete Account\n";
    cout << "6. Save Data to File\n";
    cout << "7. Exit (save and quit)\n";
    cout << "8. Reload from file (discard unsaved changes)\n";

}

void loadFromFile()
{
    ifstream in("accounts.txt");
    if(!in)
    {
        accountCount = 0;
        return;
    }

    accountCount = 0;
    string line;
    while (accountCount < MAX_ACCOUNTS && getline(in, line)) 
    {
        stringstream ss(line);
        string accStr, name, balStr;

        if (!getline(ss, accStr, ',')) continue;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, balStr)) continue;

        accounts[accountCount].accNo = stoi(accStr);
        accounts[accountCount].name = name;
        accounts[accountCount].balance = stod(balStr);
        accountCount++;
        
    }
    in.close();
    cout << "Loaded " << accountCount << "account(s) from file.\n";
}

void saveToFile()
{
    ofstream out("accounts.txt");
    for(int i=0; i<accountCount; i++)
    {
        out << accounts[i].accNo << "," << accounts[i].name << "," << accounts[i].balance << "\n";
    }
    out.close();
    cout << "Data saved (" << accountCount << " account(s)).\n";
}

void createAccount()
{
    if (accountCount >= MAX_ACCOUNTS) 
    {
        cout << "Cannot create more accounts. Increase MAX_ACCOUNTS.\n";
        return;
    }

    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;
    // check duplicate
    if (findAccountIndex(acc) != -1) 
    {
        cout << "Account with this number already exists.\n";
        return;
    }

     cout << "Enter Name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    double bal;
    cin >> bal;

    accounts[accountCount].accNo = acc;
    accounts[accountCount].name = name;
    accounts[accountCount].balance = bal;
    accountCount++;

    cout << "Account created successfully.\n";
}

void viewAllAccounts()
{
    if (accountCount == 0) 
    {
        cout << "No accounts to display.\n";
        return;
    }

    cout << "Accounts list:\n";
    for (int i = 0; i < accountCount; i++) 
    {
        cout << "Acc#: " << accounts[i].accNo
            << " | Name: " << accounts[i].name
            << " | Balance: " << accounts[i].balance << "\n";
    }
}

int findAccountIndex(int accNo)     // Return -1 if not found.
{
    for (int i = 0; i < accountCount; i++) 
    {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}


void depositMoney() 
{
    cout << "Enter Account Number: ";
    int acc; 
    cin >> acc;

    int idx = findAccountIndex(acc);
    if (idx == -1) 
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter amount to deposit: ";
    double amt; 
    cin >> amt;
    if (amt <= 0) 
    {
        cout << "Amount must be positive.\n";
        return;
    }

    accounts[idx].balance += amt;
    cout << "Deposit successful. New balance: " << accounts[idx].balance << "\n";
}


void withdrawMoney() 
{
    cout << "Enter Account Number: ";
    int acc; 
    cin >> acc;
    int idx = findAccountIndex(acc);
    if (idx == -1) 
    {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter amount to withdraw: ";
    double amt; 
    cin >> amt;
    if (amt <= 0) 
    {
        cout << "Amount must be positive.\n";
        return;
    }

    if (amt > accounts[idx].balance) 
    {
        cout << "Insufficient balance.\n";
        return;
    }

    accounts[idx].balance -= amt;
    cout << "Withdrawal successful. Remaining balance: " << accounts[idx].balance << "\n";
}


void deleteAccount() 
{
    cout << "Enter Account Number to delete: ";
    int acc; 
    cin >> acc;
    int idx = findAccountIndex(acc);
    if (idx == -1) 
    {
        cout << "Account not found.\n";
        return;
    }

    // Move all elements after idx one step left
    for (int i = idx; i < accountCount - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    accountCount--;
    cout << "Account deleted.\n";
}

