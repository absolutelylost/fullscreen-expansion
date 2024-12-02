#define NOMINMAX // protects against discrepancy with max function in windows.h built in max()
#include <iostream>
#include <cstdlib> // for system() to clear the screen (optional)
#include <limits>
#include "headers/readConfig.hpp"
#include "headers/windowDisplay.hpp"
#include <string>

using namespace std;
namespace FullScreenDisplay
{
    bool configRead = false;

    void clearScreen()
    {
        system("cls");
    }

    void displayMenu()
    {
        cout << "====================\n";
        cout << "      Main Menu\n";
        cout << "1. Full Screen Multi-Display\n";
        cout << "2. Normal Monitor Display\n";
        cout << "3. EXIT\n";
    }

    void processRequest(int choice, string substring)
    {
        // if (!configRead)

        vector<int> configuration = readConfig(choice);

        if (configuration.size() == 0)
        {
            return;
        }

        char *c_substring = const_cast<char *>(substring.data()); //.c_str();
        // configRead = true;
        processWindowChanges(configuration, c_substring);
    }

    void handleSelection(int choice)
    {
        string substring;

        switch (choice)
        {
        case 1:
            std::cout << "Enter window name substring to be affected:";
            std::getline(std::cin, substring); // Read full line of input, including spaces
            // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
            processRequest(choice, substring);
            cout << "Changing configuration for full screen display...\n";
            break;
        case 2:
            std::cout << "Enter window name substring to be affected:";
            std::getline(std::cin, substring); // Read full line of input, including spaces
            // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
            processRequest(choice, substring);
            cout << "Changing configuration to small monitor display\n";
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice...\n";
        }
    }

    int getValidInput(int min, int max)
    {
        int choice;
        while (true)
        {
            cout << "Please select an option (" << min << "-" << max << "): ";

            // check if the input is a valid integer value
            if (cin >> choice && choice >= min && choice <= max)
            {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline character
                return choice;                                                 // valid input, return the choice
            }
            else
            {
                // handle invalid input
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid characters
                cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            }
        }
    }

}

int main()
{
    int choice = 0;
    do
    {
        FullScreenDisplay::clearScreen();
        FullScreenDisplay::displayMenu();
        // Get valid user input
        choice = FullScreenDisplay::getValidInput(1, 3); // The options range from 1 to 4

        FullScreenDisplay::handleSelection(choice);

        if (choice != 3)
        {
            cout << "Press enter to continue...\n";
            cin.ignore(); // leftover newline
            cin.get();    // wait for the user to press enter
        }

    } while (choice != 3);

    return 0;
}
