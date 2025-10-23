# 🏦 Bank Management System (Core C++ Version)

A simple **Bank Management System** written in **pure C++** using only core language features — no STL containers like `vector`.  
It demonstrates how to use **arrays**, **structures**, and **file handling** to manage records manually.

---

## 🚀 Features

✅ Create new bank accounts  
✅ View all existing accounts  
✅ Deposit money  
✅ Withdraw money (with balance check)  
✅ Delete accounts  
✅ Save and load data from file (`accounts.txt`)  
✅ Input validation and user-friendly menu  

---

## 🧠 Concepts Covered

This project is designed for **beginners learning core C++**, focusing on:

| Concept | Description |
|----------|--------------|
| `struct` | Used to group account details (`accNo`, `name`, `balance`) |
| Arrays | Used instead of vectors to store fixed number of accounts |
| Loops & Conditions | For user interaction and program flow |
| File Handling | Saving and loading data persistently |
| Functions | Dividing logic into reusable pieces |
| Input Validation | Prevent invalid user input |

---

## 🧩 Code Structure

BankManagementSystem/
│
├── main.cpp # Main source code
├── accounts.txt # Auto-generated file to store accounts
└── README.md # Project documentation



---

## ⚙️ How It Works

- Accounts are stored in a **fixed-size array** (`MAX_ACCOUNTS = 100`)
- Each account has:
  - Account number (unique ID)
  - Name
  - Balance
- When you create, deposit, withdraw, or delete, the array is updated in memory.
- Data is saved to `accounts.txt` when you choose **Save to File** or **Exit**.

---

## 🧾 File Format

The file `accounts.txt` stores records in this format:

101,Rajesh,1500.50
102,Rahul,2000
103,Raja,500

Each line = one account  
Format → `AccountNumber,Name,Balance`

---

## 💻 How to Compile and Run

### 🪟 On Windows (PowerShell)
```bash
g++ main.cpp -o bank_manager.exe
.\bank_manager.exe



🧭 Future Improvements
    Use std::vector instead of arrays (for dynamic resizing)
    Add account update/edit feature
    Add password protection for accounts
    Improve file format to JSON or CSV
    Add error logging and color-coded output

👨‍💻 Author
    Rajesh Shaw
    📘 GitHub: Rajesh-Shaw