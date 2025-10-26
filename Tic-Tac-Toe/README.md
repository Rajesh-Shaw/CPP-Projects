# 🎮 Tic-Tac-Toe Game (Two Player)

A simple **console-based Tic-Tac-Toe** game written in **C++**, where two players take turns marking spaces in a 3×3 grid.  
The first player to get three in a row (horizontally, vertically, or diagonally) wins the game!

---

## 🧠 What You’ll Learn
This project helps you understand core C++ concepts:
- 2D arrays (`char board[3][3]`)
- Loops (`for`, `while`)
- Conditional logic (`if`, `else if`)
- Input validation using `cin`
- Functions and code organization

---

## ⚙️ How the Game Works

1. The board starts empty.
2. Player **X** begins and enters a move (row and column from 1 to 3).
3. Players take turns until:
   - One player wins (three in a row, column, or diagonal), or  
   - All cells are filled — it’s a **draw**.
4. The game announces the winner or draw and exits.

---

## 🧩 Code Overview

| Function | Description |
|-----------|--------------|
| `initializeBoard()` | Fills the 3×3 board with spaces `' '` |
| `displayBoard()` | Prints the board neatly in a grid |
| `makeMove(player)` | Reads a player’s move, validates, and updates the board |
| `checkWin(player)` | Checks if a player has won (rows, columns, diagonals) |
| `isDraw()` | Returns true if all cells are filled and no one has won |

---

## 🚀 How to Run

1. **Open terminal** in the project folder.
2. **Compile the code:**
   ```bash
   g++ main.cpp -o tictactoe
3. **Run the program:**
   ```bash
   ./tictactoe


---


## 🧾 Example Gameplay
=====================================
          TIC-TAC-TOE GAME
=====================================
 1   2   3
1   |   |  
 ---+---+---
2   |   |  
 ---+---+---
3   |   |  

Player X, enter your move (row and column 1-3): 1 1
Player O, enter your move (row and column 1-3): 2 2
...
Player X wins!


---

## 🧱 File Structure
Tic-Tac-Toe/
├── main.cpp
└── README.md

---


## 🛠️ Possible Improvements
Highlight the last move
Add a replay option
Add a simple AI (single-player mode)
Track score across rounds
Save game history to file


---

## 👨‍💻 Author
Rajesh Shaw
📘 GitHub: Rajesh-Shaw