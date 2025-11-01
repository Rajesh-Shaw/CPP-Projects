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

}

string getComputerChoice()
{

}

string getPlayerChoice()
{

}

string findWinner(string player, string computer)
{

}

bool playAgainPrompt()
{

}
