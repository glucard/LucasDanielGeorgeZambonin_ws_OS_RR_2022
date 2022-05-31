#include "tictactoe.h"

TicTacToe* createTicTacToe(){
    TicTacToe* t = (TicTacToe*)malloc(sizeof(TicTacToe));
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            t->table[i][j] = '-';
    return t;
}

void destroyTicTacToe(TicTacToe* t){
    free(t);
}

void printTicTacToe(TicTacToe* t){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++)
            printf("%c ", t->table[i][j]);
        printf("\n");
    }
}

