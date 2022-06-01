#include "tictactoe.h"

char empty = '-';

TicTacToe* createTicTacToe(){
    TicTacToe* t = (TicTacToe*)malloc(sizeof(TicTacToe));
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            t->table[i][j] = empty;
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

int play(TicTacToe* t, int i, int j, char mark){
    if (t->table[i][j] != empty)
        return 0;
    
    t->table[i][j] = mark;
    return 1;
}

int isWin(TicTacToe* t, char mark){
    int i, j;

    // verificar
    
    // vertical
    for (i = 0; i < 3; i++)
        if(t->table[i][0] == mark && t->table[i][1] == mark && t->table[i][2] == mark)
            return 1;
    
    // horizontal
    for (j = 0; j < 3; j++)
        if(t->table[0][j] == mark && t->table[1][j] == mark && t->table[2][j] == mark)
            return 1;
    
    // diagonal principal e secundaria
    if(t->table[0][0] == mark && t->table[1][1] == mark && t->table[2][2] == mark)
        return 1;
    if(t->table[0][2] == mark && t->table[1][1] == mark && t->table[2][0] == mark)
        return 1;
    

    // não ganhou
    return 0;
}

int someoneWin(TicTacToe* t){
    int i, j;

    // verificar
    
    // vertical
    for (i = 0; i < 3; i++)
        if(t->table[i][0] == t->table[i][1] && t->table[i][1] == t->table[i][2] && t->table[i][2] != empty)
            return 1;
    
    // horizontal
    for (j = 0; j < 3; j++)
        if(t->table[0][j] == t->table[1][j] && t->table[1][j] == t->table[2][j] && t->table[2][j] != empty)
            return 1;
    
    // diagonal principal e secundaria
    if(t->table[0][0] == t->table[1][1] && t->table[1][1] == t->table[2][2] && t->table[2][2] != empty)
        return 1;
    if(t->table[0][2] == t->table[1][1] && t->table[1][1] == t->table[2][0] && t->table[2][0] != empty)
        return 1;

    // não ganhou
    return 0;
}

int isFull(TicTacToe* t){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if(t->table[i][j] == empty){
                return 0;
            }
        }
    }
    return 1;
}