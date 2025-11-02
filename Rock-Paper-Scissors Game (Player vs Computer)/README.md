# 🎮 Rock–Paper–Scissors Game (Player vs Computer)

A fun **C++ console game** where you play **Rock, Paper, Scissors** against the computer.  
This project helps you practice **decision-making logic**, **loops**, **user input validation**, and **random number generation** in C++.

---

## 🧩 Features

✅ Play against the computer  
✅ Randomized computer choices  
✅ Validates user input (prevents crashes)  
✅ Keeps track of total **Wins**, **Losses**, and **Draws**  
✅ Option to **Play Again** or **Exit**  
✅ Beginner-friendly and fully commented  

---

## 🧠 Game Rules

- **Rock beats Scissors**  
- **Scissors beat Paper**  
- **Paper beats Rock**  
- If both choose the same, it’s a **Draw**

---

## ⚙️ How It Works

1. Player selects an option:
    Rock
    Paper
    Scissors
    Exit
2. Computer randomly chooses its move.
3. The game compares both choices and declares the winner.
4. Scores are updated and displayed after each round.
5. Player can choose to play again or exit.

---

## 🖥️ Example Output

=====================================
ROCK - PAPER - SCISSORS 🎮

Choose your move:
    Rock
    Paper
    Scissors
    Exit
    Enter your choice (1-4): 1

Computer chose: Scissors
✅ You win this round!
Current Score: You = 1 | Computer = 0 | Draws = 0
Play again? (1 = Yes, 0 = No): 1


---

## 🧰 Concepts Used

- `if-else` decision making  
- `switch` statements  
- `rand()` and `srand()` for randomness  
- Loops and functions  
- Input validation using `cin.clear()` and `cin.ignore()`  

---

## 📦 How to Compile and Run

    ```bash
    g++ main.cpp -o rps_game
    ./rps_game


🚀 Future Enhancements
    Add best of 5 / 10 mode
    Add sound or animation effects (for fun)
    Add multiplayer mode (2 players)

👨‍💻 Author
Rajesh Shaw