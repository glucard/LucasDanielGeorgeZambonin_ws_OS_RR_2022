#include "tictactoe.h"

int main(){
    TicTacToe* t = createTicTacToe();
    printTicTacToe(t);
    destroyTicTacToe(t);
    
    return 0;
}