# 🧠 Realistic Quiz Game (C++ Project)

## 🎯 Overview
A fully interactive, realistic-feeling console **Quiz Game** built in **C++**, featuring levels, scoring, animation-like effects, and personalized messages.

---

## ⚙️ Features
- 👤 Player name input
- 🎮 3 difficulty levels (Easy / Medium / Hard)
- 🕓 “Thinking…” and “Checking…” animations
- ✅ +10 for correct answers, ❌ −5 for wrong ones
- 💬 Personalized feedback after every quiz
- 🔁 Replay / Exit options
- ⌛ Uses `this_thread::sleep_for()` for timing

---

## 💻 How to Run
1. Open your terminal or IDE (VS Code / Code::Blocks).
2. Compile the file:
   ```bash
   g++ main.cpp -o quiz_game
3. Run the game::
   ```bash
   ./quiz_game



=====================================
          🧠 QUIZ GAME 2.0
=====================================
Loading quiz engine....
System ready...

Enter your name: Rajesh
Welcome, Rajesh! Let's test your knowledge today.

Choose Difficulty Level:
1. 🟢 Easy
2. 🟠 Medium
3. 🔴 Hard
4. ❌ Exit
Enter your choice (1-4): 2

Starting 🟠 Medium Level Quiz for Rajesh...
Preparing questions...

Q1: Which planet is closest to the Sun?
A) Earth
B) Venus
C) Mercury
D) Mars
Your answer (A-D): C
Checking answer...
✅ Correct!

...

=====================================
             QUIZ RESULT
=====================================
Player: Rajesh
Total Score: 25
🏆 Excellent, Rajesh! You're a quiz master!
=====================================


---

## 🧩 Concepts Used
- Functions and structs
- Conditionals and loopss
- String and character handling
- Timed delays using chrono and thread
- Console-based animations

---

## 👨‍💻 Author
Rajesh Shaw