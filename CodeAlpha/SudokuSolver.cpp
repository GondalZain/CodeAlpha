#include <SFML/Graphics.hpp>  // Include SFML graphics library for window handling and drawing
#include <iostream>           // Include iostream for console output

const int N = 9;              // Size of the Sudoku grid
const int SIZE = 50;          // Size of each cell in the grid

// Function to check if a number can be placed in a specific position
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        // Check if the number is present in the row or column
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check if the number is present in the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;  // If number is not present, it is safe to place it
}

// Recursive function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N)  // If we have reached the end of the grid, the Sudoku is solved
        return true;
    if (col == N) {  // If column index goes out of bounds, move to the next row
        row++;
        col = 0;
    }
    if (grid[row][col] != 0)  // If the current cell is already filled, move to the next cell
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= N; num++) {  // Try all possible numbers
        if (isSafe(grid, row, col, num)) {  // Check if the number can be placed
            grid[row][col] = num;  // Place the number

            if (solveSudoku(grid, row, col + 1))  // Recursively try to solve the rest of the grid
                return true;

            grid[row][col] = 0;  // Backtrack if placing the number doesn't lead to a solution
        }
    }
    return false;  // Return false if no number can be placed in the current cell
}

// Function to draw the Sudoku grid on the window
void drawGrid(sf::RenderWindow& window, int grid[N][N]) {
    window.clear(sf::Color::White);  // Clear the window with white color

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  // Load font for drawing numbers
        std::cout << "Could not load font\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Draw each cell as a rectangle
            sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
            cell.setPosition(j * SIZE, i * SIZE);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            // Draw the number in the cell if it is not zero
            if (grid[i][j] != 0) {
                sf::Text number;
                number.setFont(font);
                number.setString(std::to_string(grid[i][j]));
                number.setCharacterSize(SIZE / 2);
                number.setFillColor(sf::Color::Black);
                number.setPosition(j * SIZE + SIZE / 4, i * SIZE + SIZE / 8);
                window.draw(number);
            }
        }
    }
    window.display();  // Display the window
}

int main() {
    // Initial Sudoku grid with some pre-filled values
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    sf::RenderWindow window(sf::VideoMode(N * SIZE, N * SIZE), "Sudoku Solver");  // Create a window

    bool solved = solveSudoku(grid, 0, 0);  // Attempt to solve the Sudoku puzzle

    while (window.isOpen()) {  // Main loop to keep the window open
        sf::Event event;
        while (window.pollEvent(event)) {  // Poll for window events
            if (event.type == sf::Event::Closed)  // If the close button is clicked, close the window
                window.close();
        }

        drawGrid(window, grid);  // Draw the Sudoku grid
    }

    if (!solved) {  // If the Sudoku puzzle could not be solved, print a message
        std::cout << "No solution exists" << std::endl;
    }

    return 0;
}
