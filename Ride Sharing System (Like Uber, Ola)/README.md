# 🚕 Ride Sharing System (Uber/Ola Style) - C++ OOP Project

A console-based Ride Sharing System built using **Object-Oriented Programming (OOP)** in **C++**, featuring file-based database storage.

## 🎯 Features
- Add & View Available Drivers
- Book a Ride (Auto assigns available driver)
- Calculate Fare by Vehicle Type
- View Ride History
- Persistent data using text files

## 🧩 Concepts Used
- Classes & Objects
- Inheritance (`User → Driver`)
- Polymorphism (`calculateFare`)
- File I/O as a database
- Encapsulation
- Composition (System managing Drivers & Rides)

## 🗂️ Files
- `main.cpp` — Source code
- `drivers.txt` — Stores registered drivers
- `rides.txt` — Stores completed rides

## 💡 Example Fare Rates
| Vehicle | Rate/km |
|----------|----------|
| Car | ₹15 |
| Bike | ₹7 |
| Auto | ₹10 |

## 🏁 How to Run
1. Compile:
   ```bash
   g++ main.cpp -o RideShare

2. Run:
    ./RideShare
    ```

## 🧠 Sample Output
========================================
         RIDE SHARING SYSTEM (OOP)
========================================
1. View Available Drivers
2. Book a Ride
3. View Ride History
4. Exit & Save
----------------------------------------
Enter your choice: 2
Enter Rider ID: 101
Enter Rider Name: Raj
Enter Vehicle Type (Car/Bike/Auto): Car
Enter Distance (km): 12
✅ Ride Booked Successfully!
Ride ID: 1001
Driver: Ramesh
Fare: Rs.180

## 👨‍💻 Author
Rajesh Shaw
📘 GitHub: Rajesh-Shaw