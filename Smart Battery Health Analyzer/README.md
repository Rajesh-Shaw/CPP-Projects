# Smart Battery Health Analyzer (Simulation)

**Language:** C++  
**Purpose:** Simulate battery behavior (voltage, current, temperature, SoC), log data, analyze health and predict remaining life.

---

## Features
- Simulates voltage, current, temperature, and SoC (State of Charge).
- Logs readings to `battery_log.csv`.
- Continuous simulation mode (fast steps).
- Force charge simulation (plug in).
- Shows last readings, statistics (avg/min/max).
- Predicts time to full/empty based on last current.
- Estimates remaining cycles and health (simple model).
- Alerts on critical conditions (high temperature, voltage anomaly, very low SoC).

---

## Files
- `main.cpp` — main simulation program
- `battery_log.csv` — auto-created log file (CSV)
- `README.md` — this document

---

## How to compile
Make sure you have `g++` supporting C++17.

```bash
g++ main.cpp -o battery_analyzer -std=c++17
./battery_analyzer

```

---

## Example sequence to test
Start program.
Choose 1 multiple times to generate readings and check alerts.
Use 2 to run a long simulation (e.g., 500 steps).
Use 4 to view the last 10 readings.
Use 5 to view statistics.
Use 7 to predict time to full/empty based on last reading.
Use 6 to see a basic remaining life estimate.
Optional: Use 3 to simulate being plugged in (charging).


## Notes & Extensions

This is a simulation with simplified physics. Real battery modeling is more complex.

You can extend the project with:
Real sensor input (Arduino/ESP32) sending readings to this program.
Database storage (MySQL / SQLite) instead of CSV.
Visualization (plot logs using Python/Excel).
Smarter lifetime prediction (regression on logged cycles).
GUI dashboard.

## Author
Rajesh Shaw