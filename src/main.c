#include "tictactoe.h"
#include<time.h>

char marks[2] = {'o', 'x'};

int main(){
    TicTacToe* t = createTicTacToe();
    srand(time(NULL));
    int turn = 1, count = 0;
    int x, y;
    while(1){
        printTicTacToe(t);
        printf("--- %c turn ---\n", marks[turn]);
        // scanf("%d %d", &y, &x);
        y = rand() % 3;
        x = rand() % 3;
        while(!play(t, y, x, marks[turn])){
            y = rand() % 3;
            x = rand() % 3;
        }
        if(isWin(t, marks[turn]))
            break;
        if(isFull(t)){
            printf("Deu Velha");
            return 0;
        }
        turn = !turn;
    }
    printTicTacToe(t);
    printf("%c ganhou!!!\n", marks[turn]);
    destroyTicTacToe(t);
    
    return 0;
}