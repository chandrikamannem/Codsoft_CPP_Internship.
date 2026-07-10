#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));

    char playAgain;

    do
    {
        int difficulty, maxRange;

        cout << "\n**************************************\n";
        cout << "      NUMBER GUESSING GAME\n";
        cout << "**************************************\n";
        cout << "Select Difficulty Level\n";
        cout << "1. Easy (1 - 50)\n";
        cout << "2. Medium (1 - 100)\n";
        cout << "3. Hard (1 - 200)\n";
        cout << "Enter your choice: ";
        cin >> difficulty;

        switch (difficulty)
        {
            case 1:
                maxRange = 50;
                break;
            case 2:
                maxRange = 100;
                break;
            case 3:
                maxRange = 200;
                break;
            default:
                cout << "Invalid choice! Medium level selected.\n";
                maxRange = 100;
        }

        int randomNumber = rand() % maxRange + 1;
        int guess;
        int attempts = 0;

        cout << "\nI have selected a number between 1 and "
             << maxRange << ".\n";
        cout << "Try to guess it!\n";

        do
        {
            cout << "\nEnter your guess: ";
            cin >> guess;

            attempts++;

            if (guess > randomNumber)
            {
                cout << "Too High! Try Again.";
            }
            else if (guess < randomNumber)
            {
                cout << "Too Low! Try Again.";
            }
            else
            {
                cout << "\nCongratulations! You guessed the correct number.\n";
                cout << "Number: " << randomNumber << endl;
                cout << "Attempts: " << attempts << endl;

                if (attempts <= 5)
                    cout << "Excellent Performance!\n";
                else if (attempts <= 10)
                    cout << "Good Job!\n";
                else
                    cout << "Keep Practicing!\n";
            }

        } while (guess != randomNumber);

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "\nThank you for playing!\n";

    return 0;
}