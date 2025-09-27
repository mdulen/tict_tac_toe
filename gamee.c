#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10  // Maximum board size

// Initialize the board with empty spaces
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
}

// Display the board with row and column numbers (1-based)
void displayBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    // Print column numbers
    printf("   ");
    for (int j = 0; j < size; j++) {
        printf(" %d  ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        if (i > 0) {
            printf("   ");
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }

        // Print row number
        printf("%d  ", i + 1);
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
    }
}

// Check if a player has won
int checkWin(char board[MAX_SIZE][MAX_SIZE], int size, char symbol) {
    // Check rows and columns
    for (int i = 0; i < size; i++) {
        int rowCount = 0, colCount = 0;
        for (int j = 0; j < size; j++) {
            if (board[i][j] == symbol) rowCount++;
            if (board[j][i] == symbol) colCount++;
        }
        if (rowCount == size || colCount == size) return 1;
    }

    // Check diagonals
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < size; i++) {
        if (board[i][i] == symbol) diag1++;
        if (board[i][size - i - 1] == symbol) diag2++;
    }
    if (diag1 == size || diag2 == size) return 1;

    return 0;
}

int main() {
    int size, players;
    char board[MAX_SIZE][MAX_SIZE];
    char symbols[3] = {'X', 'O', 'Z'};

    // Input board size
    printf("Enter board size (3 to 10): ");
    scanf("%d", &size);
    if (size < 3 || size > 10) {
        printf("Invalid size!\n");
        return 1;
    }

    // Input number of players
    printf("Enter number of players (2 or 3): ");
    scanf("%d", &players);
    if (players < 2 || players > 3) {
        printf("Invalid number of players!\n");
        return 1;
    }

    initializeBoard(board, size);

    int totalMoves = size * size;
    int moveCount = 0;
    int currentPlayer = 0;

    // Main game loop
    while (moveCount < totalMoves) {
        displayBoard(board, size);

        int row, col;
        printf("Player %d (%c), enter row and column (1-based): ", currentPlayer + 1, symbols[currentPlayer]);
        scanf("%d %d", &row, &col);

        // Convert to 0-based internally
        row--;
        col--;

        // Validate move
        if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make move
        board[row][col] = symbols[currentPlayer];
        moveCount++;

        // Check for win
        if (checkWin(board, size, symbols[currentPlayer])) {
            displayBoard(board, size);
            printf("Player %d (%c) wins!\n", currentPlayer + 1, symbols[currentPlayer]);
            return 0;
        }

        // Next player
        currentPlayer = (currentPlayer + 1) % players;
    }

    displayBoard(board, size);
    printf("It's a draw!\n");
    return 0;
}
