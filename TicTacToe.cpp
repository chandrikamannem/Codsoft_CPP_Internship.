#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer;

void initializeBoard() {
    char ch = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ch++;
        }
    }
    currentPlayer = 'X';
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << endl;
        if (i < 2)
            cout << "---|---|---" << endl;
    }
    cout << endl;
}

bool makeMove(int choice) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (choice < 1 || choice > 9)
        return false;

    if (board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = currentPlayer;
    return true;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }

    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;

    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    char playAgain;

    do {
        initializeBoard();

        while (true) {
            displayBoard();

            int choice;
            cout << "Player " << currentPlayer
                 << ", enter your move (1-9): ";
            cin >> choice;

            if (!makeMove(choice)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }

            if (checkDraw()) {
                displayBoard();
                cout << "The game is a draw!\n";
                break;
            }

            switchPlayer();
        }

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "\nThank you for playing Tic-Tac-Toe!\n";

    return 0;
}
