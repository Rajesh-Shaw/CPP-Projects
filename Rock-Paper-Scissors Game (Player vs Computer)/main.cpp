#include <iostream>
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
using namespace std;

// Function declarations
void showMenu();
string getComputerChoice();
string getPlayerChoice();
string findWinner(string player, string computer);
bool playAgainPrompt();

// Global score counters
int playerScore = 0, computerScore = 0, drawCount = 0;

int main()
{
    srand(time(0)); // Seed random number generator (only once at start)

    cout << "=====================================\n";
    cout << "       ROCK - PAPER - SCISSORS       \n";
    cout << "=====================================\n";

    bool playAgain = true;

    while (playAgain)
    {
        showMenu();
        string playerChoice = getPlayerChoice();
        if (playerChoice == "exit")
        {
            cout << "Exiting game. Thanks for playing!\n";
            break;
        }

        string computerChoice = getComputerChoice();

        cout << "Computer chose: " << computerChoice << "\n";

        string result = findWinner(playerChoice, computerChoice);

        if (result == "win")
        {
            cout << "You win this round!\n";
            playerScore++;
        }
        else if (result == "lose")
        {
            cout << "You lose this round!\n";
            computerScore++;
        }
        else
        {
            cout << "It's a draw!\n";
            drawCount++;
        }

        cout << "\nCurrent Score: You = " << playerScore
             << " | Computer = " << computerScore
             << " | Draws = " << drawCount << "\n";

        playAgain = playAgainPrompt();
    }

    cout << "\nFinal Score:\n";
    cout << "You: " << playerScore << "\nComputer: " << computerScore
         << "\nDraws: " << drawCount << "\n";
    cout << "Thanks for playing!\n";
    return 0;
}




void showMenu()
{
    cout << "\nChoose your move:\n";
    cout << "1. Rock\n";
    cout << "2. Paper\n";
    cout << "3. Scissors\n";
    cout << "4. Exit\n";
}



string getPlayerChoice()
{
    int choice;
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    if (!cin) // Handle invalid input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Enter a number between 1 and 4.\n";
        return getPlayerChoice(); // retry
    }

    switch (choice)
    {
    case 1: return "rock";
    case 2: return "paper";
    case 3: return "scissors";
    case 4: return "exit";
    default:
        cout << "Invalid choice! Try again.\n";
        return getPlayerChoice();
    }
}

// Randomly select computer choice
string getComputerChoice()
{
    int randomNum = rand() % 3 + 1;
    switch (randomNum)
    {
    case 1: return "rock";
    case 2: return "paper";
    case 3: return "scissors";
    default: return "rock"; // fallback
    }
}


string findWinner(string player, string computer)
{
    if (player == computer)
        return "draw";

    if ((player == "rock" && computer == "scissors") ||
        (player == "paper" && computer == "rock") ||
        (player == "scissors" && computer == "paper"))
        return "win";

    return "lose";
}



bool playAgainPrompt()
{
    cout << "\nPlay again? (1 = Yes, 0 = No): ";
    int choice;
    cin >> choice;
    if (!cin)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    return choice == 1;
}