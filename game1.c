#include <stdio.h>

void drawBoard (){

    char board [3][3] = { {'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'} };
    for (int i = 0 ; i < 3 ; i++) {
        printf("%c | %c | %c\n",board[i][0],board[i][1],board[i][2]);
    }
}

int main () {
    drawBoard () ;

    return 0 ;
}



#include <stdio.h>

void drawBoard (){

    char board [3][3] = { {'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'} };
    for (int i = 0 ; i < 3 ; i++) {
        printf("%c | %c | %c\n",board[i][0],board[i][1],board[i][2]);
    }
}

int main () {
    drawBoard () ;

    return 0 ;
}