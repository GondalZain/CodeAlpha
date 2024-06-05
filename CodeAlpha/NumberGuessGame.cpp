#include <iostream>        // Include input-output stream library
#include <iomanip>         // Include input-output manipulators library
#include <cstdlib>         // Include standard library
#include <ctime>           // Include time library
#include <fstream>         // Include file stream library
#include <string>          // Include string library
#include <windows.h>       // Include Windows API for console color

#define RESET_COLOR "\033[0m"       // Define reset color escape sequence
#define RED_COLOR "\033[31m"        // Define red color escape sequence
#define GREEN_COLOR "\033[32m"      // Define green color escape sequence
#define YELLOW_COLOR "\033[33m"     // Define yellow color escape sequence
#define BLUE_COLOR "\033[34m"       // Define blue color escape sequence
#define MAGENTA_COLOR "\033[35m"    // Define magenta color escape sequence
#define CYAN_COLOR "\033[36m"       // Define cyan color escape sequence
#define PINK_COLOR "\033[1;35m"     // Define pink color escape sequence

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");        // Clear screen on Windows
#else
    std::cout << "\033[2J\033[1;1H"; // Clears the screen in Unix/Linux/MacOS
#endif
}

// Function to display the main menu
void displayMenu() {
    clearScreen();  // Clear the screen
    int screenWidth = 140;  // Define screen width
    std::string line1 = "======================================";  // Define separator lines
    std::string line2 = " Welcome to the Number Guessing Game! ";  // Define menu title
    std::string line3 = "======================================";  // Define separator lines
    std::cout << "\n\n\n\n\n";  // Print new lines for spacing
    // Print menu title and separator lines
    std::cout << std::setw((screenWidth - 64 + line1.size()) / 2) << BLUE_COLOR << line1 << RESET_COLOR << std::endl;
    std::cout << std::setw((screenWidth - 64 + line2.size()) / 2) << RED_COLOR << line2 << RESET_COLOR << std::endl;
    std::cout << std::setw((screenWidth - 64 + line3.size()) / 2) << BLUE_COLOR << line3 << RESET_COLOR << std::endl;

    // Print menu options with colors
    std::cout << MAGENTA_COLOR << std::setw((screenWidth + 6) / 2) << "1. Play Game" << RESET_COLOR << std::endl;
    std::cout << YELLOW_COLOR << std::setw((screenWidth + 20) / 2) << "2. View Win Records" << RESET_COLOR << std::endl;
    std::cout << CYAN_COLOR << std::setw((screenWidth - 3) / 2) << "3. Exit" << RESET_COLOR << std::endl;
    std::cout << GREEN_COLOR << std::setw((screenWidth + 20) / 2) << "Enter your choice: " << RESET_COLOR;  // Prompt for user input
}

// Function to play the game
void playGame() {
    std::srand(static_cast<unsigned int>(std::time(0)));  // Seed the random number generator

    int randomNumber = std::rand() % 100 + 1;  // Generate a random number between 1 and 100
    int playerGuess = 0;  // Variable to store player's guess
    int attempts = 0;  // Variable to store number of attempts

    int screenWidth = 80;  // Define screen width

    std::string playerName;  // Variable to store player name
    std::cout << "\n\n\n" GREEN_COLOR << std::setw((screenWidth + 56) / 2) << "Enter your name: " << RESET_COLOR;  // Prompt for player name
    std::cin >> playerName;  // Input player name
    clearScreen();  // Clear the screen

    std::cout << "\n\n\n" << YELLOW_COLOR << std::setw((screenWidth + 100) / 2) << "I have selected a number between 1 and 100." << std::endl;  // Display game instructions
    std::cout << std::setw((screenWidth + 64) / 2) << "Can you guess what it is?" << RESET_COLOR << std::endl;

    std::string response = "---";  // Variable to store response message

    // Loop until the player guesses the correct number
    while (playerGuess != randomNumber) {
        // Display game header and current attempts
        std::cout << "\n\n" << BLUE_COLOR << std::setw((screenWidth + 90) / 2) << "======================================" << RESET_COLOR << std::endl;
        std::cout << std::setw((screenWidth + 20) / 2) << BLUE_COLOR << "||" << RESET_COLOR << std::setw(14) << RED_COLOR << "Number Guessing Game" << RESET_COLOR << std::setw(14) << BLUE_COLOR << "||" << RESET_COLOR << std::endl;
        std::cout << BLUE_COLOR << std::setw((screenWidth + 90) / 2) << "======================================" << RESET_COLOR << std::endl;
        std::cout << GREEN_COLOR << std::setw(20) << "Attempts: " << RESET_COLOR << YELLOW_COLOR << attempts << RESET_COLOR << std::flush << std::endl;  // Print attempts count

        // Print player's guess and response
        if (response == "Too high!") {
            std::cout << CYAN_COLOR << std::setw(18) << "Number: " << RESET_COLOR << RED_COLOR << response << RESET_COLOR << std::endl;
        }
        else {
            std::cout << CYAN_COLOR << std::setw(18) << "Number: " << RESET_COLOR << PINK_COLOR << response << RESET_COLOR << std::endl;
        }

        std::cout << GREEN_COLOR << std::setw((screenWidth + 50) / 2) << "Enter your guess: " << RESET_COLOR;  // Prompt for player's guess
        std::cout << CYAN_COLOR;
        std::cin >> playerGuess;  // Input player's guess
        std::cout << RESET_COLOR;  // Reset color

        attempts++;  // Increment attempts count

        clearScreen();  // Clear the screen

        // Determine response based on player's guess
        if (playerGuess > randomNumber) {
            response = "Too high!";
        }
        else if (playerGuess < randomNumber) {
            response = "Too low!";
        }
        else if (playerGuess == randomNumber) {
            // Display congratulations message if guess is correct
            std::cout << "\n\n\n\n\n" << std::setw((screenWidth + 40) / 2) << "Congratulations, " << MAGENTA_COLOR << playerName << RESET_COLOR << "! You guessed the correct number in " << MAGENTA_COLOR << attempts << RESET_COLOR << " attempts!" << std::endl;

            // Save the win record to file
            std::ofstream winFile("win_records.txt", std::ios::app);  // Open win records file in append mode
            if (winFile.is_open()) {  // Check if file is open
                winFile << playerName << " guessed the correct number in " << attempts << " attempts.\n";  // Write win record to file
                winFile.close();  // Close file
            }
        }
        else {
            std::cout << std::setw((screenWidth + 18) / 2) << "Wrong Input " << std::endl;  // Handle invalid input
        }
    }
}

// Function to view win records
void viewWinRecords() {
    clearScreen();  // Clear the screen
    int screenWidth = 80;  // Define screen width
    std::ifstream winFile("win_records.txt");  // Open win records file in input mode
    if (winFile.is_open()) {  // Check if file is open
        std::string line;  // Variable to store each line
        std::cout << "\n\n\n\n\n\n\n" << std::setw((screenWidth) / 2) << RED_COLOR << "************************** Records *************************" << RESET_COLOR << std::endl;  // Print records header
        while (std::getline(winFile, line)) {  // Read each line from file
            std::cout << std::setw((screenWidth + 50 + line.size()) / 2) << line << std::endl;  // Print each record
        }
        std::cout << "\n\n\n\n\n" << std::endl;  // Print new lines for spacing
        winFile.close();  // Close file
    }
    else {
        std::cout << std::setw((screenWidth + 50) / 2) << "No win records found." << std::endl;  // Handle case when no records found
    }
}

int main() {
    int choice;  // Variable to store user's choice

    while (true) {  // Loop until user exits
        displayMenu();  // Display main menu
        std::cin >> choice;  // Input user's choice

        switch (choice) {  // Switch based on user's choice
        case 1:
            playGame();  // Play game
            break;
         case 2:
            viewWinRecords();
            break;
        case 3:
            clearScreen();
            for (int i = 0; i < 12; i++)
            {
                std::cout << "\n";
            }
            std::cout << std::setw(200) << RED_COLOR << "Goodbye!" << RESET_COLOR << std::endl;
            for (int i = 0; i < 20; i++)
            {
                std::cout << "\n";
            }
            system("pause");
            return 0;
        default:
            clearScreen();
            std::cout << std::setw(40)<<RED_COLOR << "Invalid choice. Please try again."<< RESET_COLOR << std::endl;
            break;
        }
        system("pause");
    }

    return 0;
}
