# 📚 Library Management System (C++)

A simple **Library Management System** built using **core C++ (no STL)** that manages books using file handling.

---

## 🎯 Features
✅ Add new books  
✅ View all available books  
✅ Search book by ID  
✅ Issue and return books  
✅ Save and load data from file (`library.txt`)  

---

## ⚙️ How It Works
1. Data is stored in a `Book` struct array.  
2. On startup, program loads data from `library.txt`.  
3. User interacts with a **menu system** (add, search, issue, return).  
4. All updates can be saved manually or automatically before exit.

---

## 🧠 Concepts Covered
- File Handling (`fstream`)
- Structs & Arrays
- Loops and Conditional Statements
- Menu-based program flow

---

## 💻 How to Run
```bash
g++ main.cpp -o library_system
./library_system

```
---

##  📝 Example Interaction
1. Add Book
2. View Books
3. Search Book
4. Issue Book
5. Return Book
6. Save to File
7. Exit

Enter your choice: 1
Enter Book ID: 101
Enter Title: The C++ Programming Language
Enter Author: Bjarne Stroustrup
Book added successfully.

---

## 👨‍💻 Author
Rajesh Shaw
📘 GitHub: Rajesh-Shaw