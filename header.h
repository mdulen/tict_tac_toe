#ifndef GAME_H
#define GAME_H

#include <stdio.h>

// Maximum number of players supported
#define MAX_PLAYERS 3

// Maximum length for player names
#define MAX_NAME_LEN 20

// Structure to hold player information
typedef struct {

    char name[MAX_NAME_LEN]; // Player name
    char symbol;             // Symbol used on the board (e.g., X, O)
    int isComputer;          // Flag to indicate if player is a computer (1 = yes, 0 = no)
    
} Player;


// Function prototypes for all game logic
char** createBoard(int size);
void freeBoard(char** board, int size);
void displayBoard(char** board, int size);
int isValidMove(char** board, int size, int row, int col);
void logMove(FILE* logFile, Player player, int row, int col);
int checkWin(char** board, int size, char symbol);
int checkDraw(char** board, int size);
void getPlayerMove(Player player, int size, int* row, int* col, char** board);
void playGame(int size, int numPlayers, Player players[]);

#endif // GAME_H
