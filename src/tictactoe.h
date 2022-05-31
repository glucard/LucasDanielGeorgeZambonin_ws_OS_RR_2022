#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct tictactoe {
    char table[3][3];
} TicTacToe;

TicTacToe* createTicTacToe();
void destroyTicTacToe(TicTacToe* t);
void printTicTacToe(TicTacToe* t);

#endif