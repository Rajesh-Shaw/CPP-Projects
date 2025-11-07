# 🚗 Car Rental System (C++ OOP Project)

A **real-world inspired Car Rental System** built in **C++**, demonstrating **Object-Oriented Programming (OOP)** principles like encapsulation, composition, and data persistence.

---

## 🧩 Features
✅ Add new cars to the system  
✅ View available cars  
✅ Rent a car (with customer details)  
✅ Return a car and calculate total bill  
✅ Auto-save and load data using text files  

---

## 🏗️ OOP Concepts Used
| Concept | Description |
|----------|-------------|
| **Class & Object** | Car, Customer, and RentalSystem are defined as separate classes |
| **Encapsulation** | Private data members, public access functions |
| **Composition** | RentalSystem contains Cars and Customers |
| **File I/O** | Save and load car & rental data using text files |

---

## 🧠 How It Works
1. Program loads existing data from files (if available)
2. You can add cars, view available cars, rent or return cars
3. Every rental updates the availability status
4. When you exit, all data is saved automatically

---

## ⚙️ How to Run
```bash
cd "Car Rental System"
g++ main.cpp -o car_rental
./car_rental

```
---

 ## 💡 Example Run

========== CAR RENTAL SYSTEM ==========
1. Add Car
2. View Available Cars
3. Rent a Car
4. Return a Car
5. Exit
--------------------------------------
Enter your choice: 2

Available Cars:
ID: 101 | Tesla Model 3 | $100/day | Available
ID: 102 | BMW X5 | $120/day | Available

Enter your choice: 3
Enter Customer ID: 1
Enter Name: Rajesh
Enter Car ID to rent: 101
Enter rental days: 4
✅ Car rented successfully to Rajesh for 4 days.

---

 ## 👨‍💻 Author
Rajesh Shaw
📧 rkshaw5200@gmail.com
💻 GitHub: Rajesh-Shaw