# 🚗 Smart Parking System (C++)

A console-based **Smart Parking System** simulation written in **C++**.  
It mimics a real parking lot management system using file storage as a local database.

---

## 🧠 Features
- Automatic parking slot assignment
- Vehicle entry/exit with real-time fee calculation
- File-based persistence (`parking_data.txt`)
- View current parking status
- Minimal, command-line interface

---

## 🏗️ Project Structure
📁 SmartParkingSystem
┣ 📄 main.cpp
┣ 📄 parking_data.txt ← auto-created
┗ 📄 README.md

---

## ⚙️ Compilation & Run
```bash
    g++ main.cpp -o parking
    ./parking
 ```


---

## 🧪 Sample Run
====================================
      SMART PARKING SYSTEM
====================================
1. Vehicle Entry
2. Vehicle Exit
3. View Parking Status
4. Exit & Save
------------------------------------
Enter your choice: 1
Enter vehicle plate number: WB12AB1234
Vehicle WB12AB1234 parked at slot 1

Enter your choice: 2
Enter vehicle plate number: WB12AB1234
 Parking Duration: 1.00 hours
 Parking Fee: ₹20

---

## 🚀 Future Improvements
Integrate MySQL database for data persistence
Add GUI or web dashboard
IoT version using ESP32 + IR Sensors + Wi-Fi
Add QR-based payment system

---

## 👨‍💻 Author
Rajesh Shaw