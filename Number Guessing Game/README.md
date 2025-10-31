🎮 Number Guessing Game (C++)
🧠 Overview
The Number Guessing Game is a fun console-based C++ game where the computer randomly selects a number, and the player tries to guess it.
The game gives hints — “Too high!” or “Too low!” — and tracks the number of attempts and score.
It also includes difficulty levels to make it more interesting!
________________________________________
🏗️ Features
✅ Random number generation
✅ Easy, Medium, Hard difficulty levels
✅ Score calculation based on attempts
✅ Option to play multiple rounds
✅ Input validation (handles invalid input safely)
________________________________________
⚙️ Concepts Used
•	Loops (while, for)
•	Conditional statements (if-else)
•	Random number generation (rand(), srand())
•	Functions
•	Basic game logic and scoring system
•	Input validation using cin.fail() and cin.clear()
________________________________________
🖥️ How It Works (Step by Step)
1.	The player selects a difficulty level:
o	Easy → 1–50
o	Medium → 1–100
o	Hard → 1–200
2.	The game generates a random number within that range.
3.	The player guesses the number, and the program responds with hints:
o	“Too High!”
o	“Too Low!”
4.	The player’s number of attempts determines the score.
5.	After each round, the player can choose to play again or exit.
________________________________________
🧩 Example Gameplay
=====================================
        NUMBER GUESSING GAME
=====================================

Choose Difficulty Level:
1. Easy (1–50)
2. Medium (1–100)
3. Hard (1–200)
Enter Your Choice (1–3): 2

I have selected a number between 1 and 100.
Try to guess it!

Enter your guess: 50
Too low! Try again.
Enter your guess: 75
Too high! Try again.
Enter your guess: 62
🎉 Congratulations! You guessed it in 3 attempts.
Your score: 70

Play again? (y/n): y

________________________________________
🧾 Future Improvements
•	Add a timer for speed-based scoring
•	Maintain a leaderboard of best scores
•	Add sound or color effects for better UI
________________________________________
🏁 Author
👨‍💻 Rajesh Shaw
📂 Repository: CPP-Projects