#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Question {
    string question;
    string options[4];
    char correct;
};


// Function prototypes
void showIntro();
void showMenu();
void simulateDelay(string text, int dots = 3, int delay = 500);
void playQuiz(string player, int level);
void showResult(string player, int score);


int main()
{
    srand(time(0));
    string player;
    int choice;

    showIntro();

    cout << "Enter your name: ";
    getline(cin, player);
    cout <<"\nWelcome, " << player << "! Let's test your knowledge today.\n";

    while(true)
    {
        showMenu();
        cout << "\nEnter Your choice(1-4): ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number(1-4).\n";
            continue;
        }

        switch(choice)
        {
            case 1: playQuiz(player, 1); break;
            case 2: playQuiz(player, 2); break;
            case 3: playQuiz(player, 3); break;
            case 4: simulateDelay("Saving progress", 4, 400);
                    cout << "\nGoodbye, " << player << "! Thanks for playing!\n";
                    return 0;
            default: 
                    cout << "Invalid choice! Try again.\n";
        }
    }
}


void showIntro()
{
    cout << "==============================================\n";
    cout << "                   QUIZ GAME                  \n";
    cout << "==============================================\n";
    simulateDelay("Loading quiz engine", 4, 400);
    cout << "\nSystem ready...\n\n";
}

void showMenu()
{
    cout << "\nChoose Difficulty Level: \n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "4. Exit\n";
}

void simulateDelay(string text, int dots, int delay)
{
    cout << text;
    for(int i=0; i<dots; i++)
    {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::microseconds(delay));
    }
    cout << "\n";
}

void playQuiz(string player, int level)
{
    Question easy[] = 
    {
        {"What is 2 + 2?", {"3", "4", "5", "6"}, 'B'},
        {"What color is grass?", {"Blue", "Green", "Red", "Yellow"}, 'B'},
        {"Which animal says 'Moo'?", {"Dog", "Cat", "Cow", "Lion"}, 'C'}
    };

    Question medium[] = 
    {
        {"Which planet is closest to the Sun?", {"Earth", "Venus", "Mercury", "Mars"}, 'C'},
        {"Who invented the telephone?", {"Edison", "Bell", "Newton", "Tesla"}, 'B'},
        {"Which gas do plants absorb?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Helium"}, 'B'}
    };

    Question hard[] = 
    {
        {"Who painted the Mona Lisa?", {"Van Gogh", "Picasso", "Da Vinci", "Michelangelo"}, 'C'},
        {"What is the chemical symbol for Gold?", {"Go", "G", "Au", "Ag"}, 'C'},
        {"Which year did World War II end?", {"1940", "1943", "1945", "1950"}, 'C'}
    };


    Question* questions;
    int totalQuestions = 3;
    string levelName;

    if(level == 1)
    {
        questions = easy;
        levelName = "Easy";
    }
    else if(level ==2)
    {
        questions = medium;
        levelName = "Medium";
    }
    else
    {
        questions = hard;
        levelName = "Hard";
    }

    int score = 0;
    char answer;

    cout << "\nStarting " << levelName << "Level Quiz for " << player << "...\n";
    simulateDelay("Preparing question", 3, 500);

    for(int i=0; i<totalQuestions; i++)
    {
        cout << "\n--------------------------------------\n";
        cout << "Q" << i + 1 << ": " << questions[i].question << endl;
        cout << "A) " << questions[i].options[0] << "\n";
        cout << "B) " << questions[i].options[1] << "\n";
        cout << "C) " << questions[i].options[2] << "\n";
        cout << "D) " << questions[i].options[3] << "\n";
        cout << "--------------------------------------\n";
        cout << "Your answer (A-D): ";

        cin >> answer;
        answer = toupper(answer);

        simulateDelay("Checking answer", 3, 400);

        if(answer == questions[i].correct)
        {
            cout << "Correct!\n";
            score = score + 10;
        }
        else
        {
            cout << "Wrong! Correct answer: " << questions[i].correct << "\n";
            score = score -5;
        }

        this_thread::sleep_for(chrono::microseconds(700));
    }

    showResult(player, score);
}

void showResult(string player, int score)
{
    cout << "\n=====================================\n";
    cout << "             QUIZ RESULT             \n";
    cout << "=====================================\n";
    cout << "Player: " << player << endl;
    cout << "Total Score: " << score << endl;
    
    if (score >= 25)
        cout << "Excellent, " << player << "! You're a quiz master!\n";
    else if (score >= 10)
        cout << "Good effort, " << player << "! Keep learning.\n";
    else
        cout << "Don't worry, " << player << ", you'll do better next time.\n";

    cout << "=====================================\n\n";
}