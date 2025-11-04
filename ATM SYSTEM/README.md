# 🏧 Real ATM System (C++)

**ATM simulation project** written in **Core C++ (without STL vectors)** that mimics a real-world ATM experience — including login with PIN, balance check, deposits, withdrawals, and PIN change, all with persistent data storage.

---

## 🚀 Features

✅ Multiple Accounts (loaded from `accounts.txt`)  
✅ Secure PIN Login  
✅ Deposit / Withdraw / Check Balance  
✅ Change PIN Option  
✅ Persistent Storage — data saved in a file  
✅ Realistic ATM Menu Flow  
✅ Simple Console UI — easy to use and extend  

---

## 🧩 How It Works

1. The program loads all account data from `accounts.txt`.
2. The user “inserts a card” by entering their **account number**.
3. The system asks for the **PIN** for authentication.
4. Once logged in, the user can:
   - Check Balance  
   - Deposit Money  
   - Withdraw Money  
   - Change PIN  
   - Exit (Card Eject)
5. Any changes are automatically saved back to `accounts.txt`.

---

## 🗂️ Example `accounts.txt`

```txt
1001 Rajesh 1234 5000
1002 Neha 4321 3500
1003 Aman 2222 8000

Each line = AccountNumber Name PIN Balance

=====================================
          REAL ATM SYSTEM
=====================================

Please insert your card (Enter Account Number or 0 to exit): 1001
Enter your PIN: 1234

Welcome, Rajesh!

=====================================
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Change PIN
5. Exit (Card Out)
=====================================
Enter your choice (1-5): 1
Your current balance is: Rs.5000

🧠 Concepts Used
•	File Handling (ifstream, ofstream)
•	Functions & Structs
•	Loops and Conditionals
•	Authentication Logic
•	Data Persistence
•	Simple Menu-Driven Program
________________________________________
🛠️ Setup & Run
1.	Create a folder (e.g., ATM System).
2.	Place main.cpp and accounts.txt inside it.
3.	Open terminal or VS Code and compile:
4.	g++ main.cpp -o atm
5.	Run:
6.	./atm
________________________________________
📚 Future Improvements
•	Add transaction history
•	Support for new account creation
•	Limit login attempts
•	Use password masking for PIN entry
•	Replace text file with database (next level)
________________________________________
👨‍💻 Author: 
Rajesh Shaw
GitHub: Rajesh-Shaw
