/*
-----------------------------------------
Project Title : Advanced Calculator
Language      : C++
Internship    : CodSoft C++ Programming

Description:
This program is a simple command-line calculator that performs
basic arithmetic operations such as addition, subtraction,
multiplication, and division. It allows the user to enter two
numbers, choose an operation, displays the result, handles
division by zero, and supports multiple calculations.

Author : Chandrika Mannem
-----------------------------------------
*/

#include <iostream>
#include <limits>
using namespace std;

int main() {
    double num1, num2, result;
    char op, choice;

    cout << "*************************************\n";
    cout << "      ADVANCED CALCULATOR\n";
    cout << "*************************************\n";

    do {
        // Input first number
        cout << "\nEnter first number: ";
        while (!(cin >> num1)) {
            cout << "Invalid input! Enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Input operator
        cout << "Enter operation (+, -, *, /): ";
        cin >> op;

        // Input second number
        cout << "Enter second number: ";
        while (!(cin >> num2)) {
            cout << "Invalid input! Enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (op) {
            case '+':
                result = num1 + num2;
                cout << "Result = " << result << endl;
                break;

            case '-':
                result = num1 - num2;
                cout << "Result = " << result << endl;
                break;

            case '*':
                result = num1 * num2;
                cout << "Result = " << result << endl;
                break;

            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    cout << "Result = " << result << endl;
                } else {
                    cout << "Error! Division by zero is not allowed.\n";
                }
                break;

            default:
                cout << "Invalid operator!\n";
        }

        cout << "\nDo you want to perform another calculation? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    cout << "\nThank you for using the Advanced Calculator!\n";

    return 0;
}
