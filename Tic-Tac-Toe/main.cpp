#include <iostream>
using namespace std;

char board[3][3]; 

void initializeBoard();
void displayBoard();
bool makeMove(char player);
bool checkWin(char player);
bool isDraw();


int main() 
{
    char currentPlayer = 'X';
    bool gameOver = false;
    initializeBoard();
    cout << "=====================================\n";
    cout << "          TIC-TAC-TOE GAME           \n";
    cout << "=====================================\n";

    while(!gameOver)
    {
        displayBoard();
        cout << "Player " << currentPlayer << ", enter your move (row and column 1-3): ";
        if(!makeMove(currentPlayer))
        {
            cout << "Invalid Move! Try again.\n";
            continue;
        }

        if(checkWin(currentPlayer))
        {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        else if(isDraw())
        {
            displayBoard();
            cout << "It's a draw!\n";
            gameOver = true;
        }
        else
        {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    cout << "Game over. Thanks for playing!\n";
    return 0;
}


void initializeBoard()
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j] = ' ';
}

void displayBoard()
{
    cout << "\n";
    cout << "  1   2   3\n";
    for(int i=0; i<3; i++)
    {
        cout << i+1 << " ";
        for(int j=0; j<3; j++)
        {
            cout << board[i][j];
            if(j<2)
                cout <<" | ";
        }
        cout << "\n";
        if(i<2)
            cout << " ---+---+---\n";
    }
}

bool makeMove(char player)
{
    int row, col;
    // cin >> row >> col;
    if(!(cin >> row >> col)) 
    {
        cin.clear();            // clear error flag
        cin.ignore(1000, '\n'); // discard invalid input
        cout << "Invalid input. Please enter numbers only.\n";
        return false;
    }


    if(row<1 || row > 3 || col < 1 || col >3)  // validate input
        return false;
    
    row--;
    col--;

    if(board[row][col] != ' ')
        return false;
    
    board[row][col] = player;
    return true;
}



bool checkWin(char player)
{
    for(int i=0; i<3; i++)
    {
        // Check rows and columns
        if( (board[i][0] == player && board[i][1] == player && board[i][2] == player ) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        {
                return true;
        }
    }
        
        // Check diagonals
    if( (board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
            (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }

    return false;
}

bool isDraw()
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if(board[i][j]== ' ')
                return false;
        }
    return true;
}