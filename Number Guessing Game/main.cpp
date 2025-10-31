#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void showMenu();
int getRandomNumber(int max);
bool playGame(int maxNumber, int maxAttempts);

int main()
{
    srand(time(0));
    int choice;
    bool playAgain = true;

    cout << "=====================================\n";
    cout << "        NUMBER GUESSING GAME         \n";
    cout << "=====================================\n";

    while(playAgain)
    {
        showMenu();
        cout << "Enter Your choice(1-4): ";
        if(!(cin  >> choice))
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        

        if(choice == 4)
        {
            cout << "Exiting game. Thanks for playing!\n";
            break;
        }

        switch(choice)
        {
            case 1: 
                    playAgain = playGame(10, 5);
                    break;
            case 2: 
                    playAgain = playGame(50, 7);
                    break;
            case 3: 
                    playAgain = playGame(100, 10);
                    break;
            default:
                    cout << "Invalid choice! Try again!\n";
        }
        cout << "\n";
    }
    return 0;
}



void showMenu()
{
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy    (1-10)\n";
    cout << "2. Medium  (1-50)\n";
    cout << "3. Hard    (1-100)\n";
    cout << "4. Exit\n";
}


int getRandomNumber(int max)
{
    return rand() % max +1;
}



bool playGame(int maxNumber, int maxAttempts)
{
    int secretNumber = getRandomNumber(maxNumber);
    int guess, attempts = 0;

    cout << "\nA secret number has been chosen between 1 and " << maxNumber << "!\n";
    while(attempts < maxAttempts)
    {
        cout << "Enter Your Guess: ";
        if(!(cin >> guess))
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        attempts++;

        if(guess == secretNumber)
        {
            int score = (maxAttempts - attempts + 1) * 10;
            cout << "Coorect! You guessed it in " << attempts << " attempts.\n";
            cout << "Your score: " << score << " points.\n";
            break;
        }
        else if(guess < secretNumber)
        {
            cout << "Too low! Try again.\n";
        }
        else
        {
            cout << "Too high! Try again.\n";
        }
    }
    cout << "\nYou've used all attempts. The number was: " << secretNumber << "\n";
    
    char again;
    cout << "Play again? (y/n): ";
    cin >> again;
    return (again == 'y' || again == 'Y');
}