#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <ctime>
#include <algorithm>


using namespace std;
using steady_clock = chrono::steady_clock;

struct Reading 
{
    time_t ts;
    double voltage;     // Volts
    double current;     // Amps (+ for charging, - for discharging)
    double temperature; // Celsius
    double soc;         // State of Charge % (0-100)
    int cycleCount;     // simulated cycle count at time
};

// Simple file name
const string LOGFILE = "battery_log.csv";

// Simulation parameters (tweak to test behaviors)
struct BatteryParams 
{
    double capacity_ah = 2.5;            // battery nominal capacity in Ah (example small battery)
    double nominal_voltage = 3.7;        // nominal cell voltage
    double full_voltage = 4.2;           // voltage at full charge
    double empty_voltage = 3.0;          // voltage at empty
    double internal_resistance = 0.05;   // ohms, affects voltage under load
    int cycle_life = 1000;               // nominal cycle life
    double health = 1.0;                 // 1.0 = 100% health, decay over cycles
};

class BatterySimulator 
{
private:
    BatteryParams params;
    Reading current;
    int cycles; // full cycles completed
    std::mt19937 rng;

public:
    BatterySimulator()
    {
        rng.seed((unsigned)chrono::system_clock::now().time_since_epoch().count());
        params = BatteryParams();
        cycles = 50; // start with some used cycles (you can change)
        current.ts = time(nullptr);
        current.soc = 80.0; // start SoC
        current.voltage = getVoltageFromSoC(current.soc);
        current.current = -0.5; // discharging initial current (A)
        current.temperature = 30.0; // Celsius
        current.cycleCount = cycles;
    }

    // Convert SoC (%) to approximate voltage (simple linear approximation between empty & full)
    double getVoltageFromSoC(double soc) const {
        double v = params.empty_voltage + (params.full_voltage - params.empty_voltage) * (soc / 100.0);
        // Factor in internal resistance drop if high current - we won't apply here
        return v * params.health;
    }

    // Simulate a single time-step reading.
    Reading step(bool externalChargeCommand = false) {
        // small random fluctuations
        uniform_real_distribution<double> noise(-0.02, 0.02);
        uniform_real_distribution<double> tempNoise(-0.2, 0.2);

        // Decide current: if externalChargeCommand true -> charging positive current
        if (externalChargeCommand) {
            // gentle charging current depending on health and capacity
            double chargeA = 0.5 + (rng() % 200) / 400.0; // 0.5 - 1.0 A
            current.current = chargeA;
        } else {
            // discharge current varies (simulate device load)
            double base = -0.2; // small idle draw
            uniform_real_distribution<double> load(-2.0, -0.1);
            current.current = load(rng) * (0.8 + 0.4 * (1 - params.health)); // heavier draws as health falls
        }

        // Temperature change based on current (charging/discharging warms battery)
        current.temperature += (abs(current.current) * 0.05) + tempNoise(rng);

        // Update SoC: ΔQ = I * dt / Capacity
        double dt_hours = 1.0 / 3600.0; // simulate 1 second -> hour fraction
        double deltaAh = current.current * dt_hours; // Amps * hours
        double socDelta = (deltaAh / params.capacity_ah) * 100.0;
        current.soc += socDelta;

        // Clamp SoC
        if (current.soc > 100.0) current.soc = 100.0;
        if (current.soc < 0.0) current.soc = 0.0;

        // Voltage tracks SoC (simple model) with internal resistance effect
        double baseVoltage = getVoltageFromSoC(current.soc);
        double vdrop = current.current * params.internal_resistance; // V = I * R
        current.voltage = baseVoltage - vdrop + noise(rng);

        // Simple cycle detection: when SoC crosses from high to low we may increment partial cycles
        static double soc_prev = current.soc;
        // detect a full charge then discharge progression (simplified)
        if (soc_prev > 95.0 && current.soc < 20.0) {
            cycles++;
            params.health -= 0.0005; // degrade health a little per cycle
            if (params.health < 0.5) params.health = 0.5; // don't let health go below 50% for this sim
        }
        soc_prev = current.soc;

        // timestamp
        current.ts = time(nullptr);
        current.cycleCount = cycles;

        return current;
    }

    // Force charge for N seconds (simulate plugging in)
    vector<Reading> runChargeForSeconds(int seconds) {
        vector<Reading> out;
        for (int i = 0; i < seconds; ++i) {
            Reading r = step(true);
            out.push_back(r);
            // speed up simulation without real delay
        }
        return out;
    }

    // Getter for current snapshot
    Reading getCurrent() const { return current; }

    // Provide estimated remaining cycle life (simple linear model)
    int estimatedRemainingCycles() const {
        int used = cycles;
        int remaining = max(0, params.cycle_life - used);
        return remaining;
    }

    // Estimate battery health percentage
    double healthPercent() const {
        return params.health * 100.0;
    }

    // Expose params for tuning or display
    BatteryParams getParams() const { return params; }
};

// Utilities: CSV log header and append
void initLogFile() {
    ifstream fin(LOGFILE);
    if (fin.good()) {
        fin.close();
        return; // exists
    }
    ofstream out(LOGFILE);
    out << "timestamp,voltage(V),current(A),temperature(C),SoC(%),cycleCount\n";
    out.close();
}

void appendLog(const Reading &r) {
    ofstream out(LOGFILE, ios::app);
    if (!out) return;
    out << r.ts << ",";
    out << fixed << setprecision(3) << r.voltage << ",";
    out << fixed << setprecision(3) << r.current << ",";
    out << fixed << setprecision(2) << r.temperature << ",";
    out << fixed << setprecision(2) << r.soc << ",";
    out << r.cycleCount << "\n";
    out.close();
}

// Read all log entries back into vector
vector<Reading> readLog() {
    vector<Reading> ret;
    ifstream in(LOGFILE);
    if (!in) return ret;

    string line;
    getline(in, line); // header
    while (getline(in, line)) {
        if (line.empty()) continue;
        // parse CSV
        // timestamp,voltage,current,temperature,soc,cycleCount
        std::istringstream ss(line);
        string token;
        Reading r;
        getline(ss, token, ','); r.ts = (time_t)stoll(token);
        getline(ss, token, ','); r.voltage = stod(token);
        getline(ss, token, ','); r.current = stod(token);
        getline(ss, token, ','); r.temperature = stod(token);
        getline(ss, token, ','); r.soc = stod(token);
        getline(ss, token, ','); r.cycleCount = stoi(token);
        ret.push_back(r);
    }
    in.close();
    return ret;
}

// Simple analysis functions
void showLastReadings(int n = 10) {
    auto logs = readLog();
    if (logs.empty()) {
        cout << "No logs available.\n";
        return;
    }
    int start = max(0, (int)logs.size() - n);
    cout << "\nLast " << (int)logs.size() - start << " readings:\n";
    cout << "Time\t\tVoltage(V)\tCurrent(A)\tTemp(C)\tSoC(%)\tCycles\n";
    for (int i = start; i < (int)logs.size(); ++i) {
        auto &r = logs[i];
        cout << put_time(localtime(&r.ts), "%Y-%m-%d %H:%M:%S") << "\t";
        cout << fixed << setprecision(3) << r.voltage << "\t\t";
        cout << fixed << setprecision(3) << r.current << "\t\t";
        cout << fixed << setprecision(2) << r.temperature << "\t";
        cout << fixed << setprecision(2) << r.soc << "\t";
        cout << r.cycleCount << "\n";
    }
}

void showStats() {
    auto logs = readLog();
    if (logs.empty()) {
        cout << "No logs available.\n";
        return;
    }

    vector<double> volt, curr, temp, socs;
    for (auto &r : logs) {
        volt.push_back(r.voltage);
        curr.push_back(r.current);
        temp.push_back(r.temperature);
        socs.push_back(r.soc);
    }
    auto avg = [](const vector<double> &v){
        return accumulate(v.begin(), v.end(), 0.0) / v.size();
    };
    auto minv = [](const vector<double> &v){
        return *min_element(v.begin(), v.end());
    };
    auto maxv = [](const vector<double> &v){
        return *max_element(v.begin(), v.end());
    };

    cout << fixed << setprecision(3);
    cout << "\n-- Battery Stats (from logs) --\n";
    cout << "Voltage: avg=" << avg(volt) << "V min=" << minv(volt) << "V max=" << maxv(volt) << "V\n";
    cout << "Current: avg=" << avg(curr) << "A min=" << minv(curr) << "A max=" << maxv(curr) << "A\n";
    cout << "Temp:    avg=" << avg(temp) << "C min=" << minv(temp) << "C max=" << maxv(temp) << "C\n";
    cout << "SoC:     avg=" << avg(socs) << "% min=" << minv(socs) << "% max=" << maxv(socs) << "%\n";
}

// Estimate time to empty/full given current SoC and current (simple linear)
void predictTimeToFullEmpty(const Reading &r, const BatteryParams &p) {
    // If current is ~0, cannot estimate
    if (fabs(r.current) < 1e-6) {
        cout << "Current nearly 0A — cannot estimate time to full/empty.\n";
        return;
    }
    double capacityAh = p.capacity_ah * p.health;
    // Remaining Ah to full or empty depending on sign
    if (r.current > 0) {
        // charging: time to 100%
        double remainingAh = capacityAh * (100.0 - r.soc) / 100.0;
        double hours = remainingAh / r.current;
        cout << fixed << setprecision(2) << "Estimated time to full: " << hours << " hours (" << hours*60 << " minutes)\n";
    } else {
        // discharging: time to 0%
        double remainingAh = capacityAh * (r.soc) / 100.0;
        double hours = remainingAh / (-r.current);
        cout << fixed << setprecision(2) << "Estimated time to empty: " << hours << " hours (" << hours*60 << " minutes)\n";
    }
}

// Simple lifetime estimate: project remaining cycles to a point where health becomes e.g. 80% (arbitrary)
void predictRemainingLife(const BatterySimulator &sim) {
    int remCycles = sim.estimatedRemainingCycles();
    double healthP = sim.healthPercent();
    cout << "\nRemaining cycles (based on nominal cycle life): " << remCycles << "\n";
    cout << "Estimated health: " << fixed << setprecision(2) << healthP << "%\n";
    // A very simple projection: assume health reduces linearly to 50% at end of life
    // This is illustrative only
    int cyclesLeftTo50 = remCycles;
    cout << "Simple projection: ~" << cyclesLeftTo50 << " cycles until nominal end-of-life.\n";
}

// Alerts based on thresholds
void checkAlerts(const Reading &r) {
    bool alarm = false;
    if (r.temperature > 60.0) {
        cout << "ALERT: High temperature! (" << r.temperature << " C)\n";
        alarm = true;
    }
    if (r.voltage > 4.25 || r.voltage < 2.9) {
        cout << "ALERT: Voltage anomaly! (" << r.voltage << " V)\n";
        alarm = true;
    }
    if (r.soc < 5.0) {
        cout << "ALERT: Critically low SoC: " << r.soc << "%\n";
        alarm = true;
    }
    if (alarm) {
        cout << ">>> Consider stopping load or charging immediately.\n";
    }
}

// Interactive menu and runner
int mainMenu() {
    cout << "\n==============================\n";
    cout << " Smart Battery Health Analyzer \n";
    cout << "==============================\n";
    cout << "1. Simulate single reading (and log)\n";
    cout << "2. Run continuous simulation (N steps, fast)\n";
    cout << "3. Force charge for N seconds (simulate plug-in)\n";
    cout << "4. Show last readings (tail)\n";
    cout << "5. Show stats (avg/min/max)\n";
    cout << "6. Predict remaining life & cycles\n";
    cout << "7. Predict time to full/empty (last reading)\n";
    cout << "8. Export log to CSV (already in CSV)\n";
    cout << "9. Clear log file\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
    int c;
    cin >> c;
    return c;
}

int main() {
    cout << "Smart Battery Health Analyzer (Simulation)\n";
    initLogFile();
    BatterySimulator sim;

    bool running = true;
    while (running) {
        int choice = mainMenu();
        switch (choice) {
            case 1: {
                auto r = sim.step(false);
                appendLog(r);
                cout << "Logged reading: " << put_time(localtime(&r.ts), "%F %T") << "\n";
                cout << fixed << setprecision(3) << "V=" << r.voltage << " V, I=" << r.current << " A, T=" << r.temperature << " C, SoC=" << r.soc << "%\n";
                checkAlerts(r);
                break;
            }
            case 2: {
                cout << "Enter number of steps to simulate (e.g., 100): ";
                int steps; cin >> steps;
                cout << "Simulating " << steps << " steps...\n";
                for (int i = 0; i < steps; ++i) {
                    auto r = sim.step(false);
                    appendLog(r);
                    // small console update every 10 steps
                    if ((i % 10) == 0) {
                        cout << "." << flush;
                    }
                }
                cout << "\nDone. Check log or view stats.\n";
                break;
            }
            case 3: {
                cout << "Enter seconds to charge (fast sim): ";
                int s; cin >> s;
                auto readings = sim.runChargeForSeconds(s);
                for (auto &r : readings) appendLog(r);
                cout << "Simulated charging for " << s << " seconds (fast-forwarded).\n";
                break;
            }
            case 4: {
                cout << "Last readings tail:\n";
                showLastReadings(10);
                break;
            }
            case 5: {
                showStats();
                break;
            }
            case 6: {
                predictRemainingLife(sim);
                break;
            }
            case 7: {
                auto logs = readLog();
                if (logs.empty()) {
                    cout << "No readings logged yet.\n";
                } else {
                    auto last = logs.back();
                    predictTimeToFullEmpty(last, sim.getParams());
                }
                break;
            }
            case 8: {
                cout << "Log is already a CSV file: " << LOGFILE << "\n";
                break;
            }
            case 9: {
                cout << "Are you sure you want to clear the log? (y/n): ";
                char yn; cin >> yn;
                if (yn == 'y' || yn == 'Y') {
                    ofstream out(LOGFILE, ios::trunc);
                    out << "timestamp,voltage(V),current(A),temperature(C),SoC(%),cycleCount\n";
                    out.close();
                    cout << "Log cleared.\n";
                } else {
                    cout << "Aborted.\n";
                }
                break;
            }
            case 0:
                running = false;
                cout << "Exiting. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
