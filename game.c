#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Dynamically create a game board of given size
char** createBoard(int size) {
    char** board = (char**)malloc(size * sizeof(char*));

    for (int i = 0; i < size; i++) {
        board[i] = (char*)malloc(size * sizeof(char));

        for (int j = 0; j < size; j++) {
            board[i][j] = ' '; // Initialize each cell with a space
        }
    }
    return board;
}

// Free memory allocated for the board
void freeBoard(char** board, int size) {

    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

// Display the current state of the board, including column and row numbers
void displayBoard(char** board, int size) {
    // Print column numbers at the top
    printf("\n    ");

    for (int j = 0; j < size; j++) {
        printf("%2d ", j + 1); // Column numbers start from 1
    }
    printf("\n");

    // Print each row of the board
    for (int i = 0; i < size; i++) {
        // Print horizontal separators
        printf("   ");
        for (int j = 0; j < size; j++) {
            printf("---");
            if (j < size - 1) printf("+");
        }
        printf("\n");

        // Print row number and cell contents
        printf("%2d |", i + 1); // Row numbers start from 1

        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]); // Print cell content
            if (j < size - 1) printf("|");
        }
        printf("\n");
    }

    // Print bottom horizontal separators
    printf("   ");

    for (int j = 0; j < size; j++) {
        printf("---");
        if (j < size - 1) printf("+");
    }
    printf("\n\n");
}

// Check if a move is valid (within bounds and on an empty cell)
int isValidMove(char** board, int size, int row, int col) {
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}

// Log each move to a file
void logMove(FILE* logFile, Player player, int row, int col) {
    fprintf(logFile, "%s (%c) moved to [%d,%d]\n", player.name, player.symbol, row + 1, col + 1);
}

// Check if a player has won the game
int checkWin(char** board, int size, char symbol) {
    int win;

    // Check rows
    for (int i = 0; i < size; i++) {
        win = 1;

        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) { win = 0; break; }
        }
        if (win) return 1;
    }

    // Check columns
    for (int j = 0; j < size; j++) {
        win = 1;

        for (int i = 0; i < size; i++) {
            if (board[i][j] != symbol) { win = 0; break; }
        }
        if (win) return 1;
    }

    // Check main diagonal
    win = 1;

    for (int i = 0; i < size; i++) {
        if (board[i][i] != symbol) { win = 0; break; }
    }
    if (win) return 1;

    // Check anti-diagonal
    win = 1;

    for (int i = 0; i < size; i++) {
        if (board[i][size - i - 1] != symbol) { win = 0; break; }
    }
    return win;
}

// Check if the board is full and no one has won
int checkDraw(char** board, int size) {

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)

            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Get move input from player or generate random move for computer
void getPlayerMove(Player player, int size, int* row, int* col, char** board) {
    if (player.isComputer) {

        // Random move for computer
        do {

            *row = rand() % size;
            *col = rand() % size;

        } while (!isValidMove(board, size, *row, *col));
        
        printf("%s (%c) played at [%d,%d]\n", player.name, player.symbol, *row + 1, *col + 1);
    } else {
        // User input
        while (1) {

            printf("%s (%c), enter your move (row and column) or 0 0 to exit: ", player.name, player.symbol);

            if (scanf("%d %d", row, col) != 2) {

                while (getchar() != '\n'); // Clear invalid input
                printf("Invalid input. Please enter two numbers.\n");
                continue;
            }

            if (*row == 0 && *col == 0) {

                *row = -2; // Special flag to exit
                *col = -2;
                return;
            }

            (*row)--; (*col)--; // Convert to 0-based index

            if (isValidMove(board, size, *row, *col)) {
                break;

            } else {
                printf("Invalid move. Try again.\n");
            }
        }
    }
}

// Main game loop
void playGame(int size, int numPlayers, Player players[]) {
    char** board = createBoard(size);

    FILE* logFile = fopen("game_log.txt", "a"); // Open log file

    if (!logFile) {

        perror("Error opening log file");
        exit(1);
    }

    int currentPlayer = 0, row, col;

    while (1) {

        displayBoard(board, size);
        getPlayerMove(players[currentPlayer], size, &row, &col, board);

        if (row == -2 && col == -2) {

            printf("Game exited by player.\n");
            break;
        }

        board[row][col] = players[currentPlayer].symbol;
        logMove(logFile, players[currentPlayer], row, col);

        if (checkWin(board, size, players[currentPlayer].symbol)) {

            displayBoard(board, size);
            printf("%s wins!\n", players[currentPlayer].name);
            break;
        }

        if (checkDraw(board, size)) {

            displayBoard(board, size);
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer + 1) % numPlayers; // Next player's turn
    }

    fclose(logFile);
    freeBoard(board, size);
}

// Entry point of the program
int main() {

    srand(time(NULL)); // Seed random number generator
    int size, mode;
    Player players[MAX_PLAYERS];

    printf("Welcome to Modular Tic-Tac-Toe!\n");

    // Get board size from user
    do {

        printf("Enter board size (3-10): ");
        scanf("%d", &size);

    } while (size < 3 || size > 10);

    // Game mode selection
    printf("Select Game Mode:\n1. Two-player\n2. User vs Computer\n3. Three-player\n0. Exit\nChoice: ");
    scanf("%d", &mode);

    if (mode == 0) {

        printf("Exiting the game. Goodbye!\n");

        return 0;
    }

    // Setup players based on mode
    if (mode == 1) {

        strcpy(players[0].name, "Player1");
        players[0].symbol = 'X';
        players[0].isComputer = 0;

        strcpy(players[1].name, "Player2");
        players[1].symbol = 'O';
        players[1].isComputer = 0;

        playGame(size, 2, players);

    } else if (mode == 2) { 
    
        strcpy(players[0].name, "User");
        players[0].symbol = 'X';
        players[0].isComputer = 0;

        strcpy(players[1].name, "Computer");
        players[1].symbol = 'O';
        players[1].isComputer = 1;

        playGame(size, 2, players);

    } else if (mode == 3) { 

        for (int i = 0; i < 3; i++) {

            printf("Enter name for Player %d: ", i + 1);
            scanf("%19s", players[i].name);

            players[i].symbol = (i == 0) ? 'X' : (i == 1) ? 'O' : 'Z';

            printf("Is %s a computer? (1 for Yes, 0 for No): ", players[i].name);
            scanf("%d", &players[i].isComputer);
        }
        playGame(size, 3, players);

    } else {
        printf("Invalid mode selected.\n");
    }

    return 0;
}
