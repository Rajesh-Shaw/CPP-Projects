# ✅ To-Do List Manager (C++)

A simple and practical console-based **To-Do List Manager** built using **C++**.  
This program helps users manage daily tasks — you can **add**, **view**, **mark as done**, **delete**, and **save tasks** for later use.  
All data is saved automatically in a file (`tasks.txt`) for persistence.

---

## 📘 Features

- ➕ **Add Task** – Add a new task with a short description.  
- 👀 **View Tasks** – Display all current tasks with their status (✅ Done / ⏳ Pending).  
- ✔️ **Mark Task as Done** – Update any task to mark it as completed.  
- ❌ **Delete Task** – Remove completed or unwanted tasks from the list.  
- 💾 **Save & Load Automatically** – All tasks are saved in `tasks.txt` and reloaded when you open the program again.  
- 🧠 **Error Handling** – Detects invalid inputs and handles file issues gracefully.

---

## 🧩 Example

### 🎯 Sample Interaction

=====================================
TO-DO LIST MANAGER
1.	Add Task
2.	View Tasks
3.	Mark Task as Done
4.	Delete Task
5.	Exit & Save

---

Enter your choice (1-5): 2
---------------------- To-Do Tasks ---------------------
1.	Wake up at 6:30 AM [Done]
2.	Prepare and eat a healthy breakfast [Done]
3.	Complete C++ project (To-Do App) [Pending]
4.	Read a book (15 mins before bed) [Pending]


---

## 📁 File Storage Format
All tasks are stored in a simple text file:  
`tasks.txt`

Example content:
Wake up at 6:30 AM
1
Complete C++ project (To-Do App)
0
Read a book (15 mins before bed)
0

Here:
- `1` → Task Done  
- `0` → Task Pending  

---

## ⚙️ How to Run

1. Open your terminal or PowerShell and navigate to the project directory:
   ```bash
   cd "To-Do List Manager"
2.	Compile the program:
3.	g++ main.cpp -o todo
4.	Run the executable:
5.	./todo

---

## 💡 Concepts Used
•	File Handling (ifstream, ofstream)
•	Arrays and Structures
•	Input Validation
•	Loops and Conditional Statements
•	Persistent Storage

---

## 📚 Learning Outcome
This project helps you understand:
•	How to store and retrieve data from files
•	Handling user input safely
•	Building menu-driven applications
•	Managing structured data using arrays and structs

---

## 👨‍💻 Author
Rajesh Shaw
📧 Email: rkshaw5200@gmail.com
💻 GitHub: Rajesh-Shaw