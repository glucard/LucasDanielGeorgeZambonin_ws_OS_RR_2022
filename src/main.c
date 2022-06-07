#include "tictactoe.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char marks[2] = {'x', 'o'};
int turn = 0;
int finished = 0;
int is_finished_verified = 1;

// strutura a ser usada como forma de passar argumentos para a função player_thread
typedef struct player_thread_args {
    TicTacToe *t;
    int mark;
} PlayerThreadArgs;

pthread_mutex_t lock;

void* player_thread(void* v_args){
    // "convertendo" argumentos do ponteiro vazio.
    PlayerThreadArgs* args = (PlayerThreadArgs*)v_args;
    TicTacToe* t = args->t;
    int mark = args->mark;

    int x, y;
    // loop principal da thread 
    while(1){
        if(finished){
            break;
        }
        // se o turno for igual a mark da thread ('x' = 0 e 'o' = 1), então é a
        // vez dessa thread jogar.
        if(turn == mark){
            // enquanto o movimento for invalido (espaço já ocupado), tenta novamente
            // com diferentes coordenadas. 
            y = rand() % 3;
            x = rand() % 3;
            while(!verifyPlay(t, y, x, marks[mark])){
                y = rand() % 3;
                x = rand() % 3;
                if (finished) break;
            }
            pthread_mutex_lock(&lock);
            if (is_finished_verified && !finished){
                play(t, y, x, marks[mark]);
                is_finished_verified = 0;
                turn = !turn;
            }
            pthread_mutex_unlock(&lock);
        } else {
            if (!is_finished_verified){
                pthread_mutex_lock(&lock);
                if(someoneWin(t) || isFull(t)) {
                    finished = 1;
                }
                printf("\n");
                printTicTacToe(t);
                is_finished_verified = 1;
                pthread_mutex_unlock(&lock);
            }
        }
    }
    // quando sair do loop principal, print a condição final do jogo
    if (!someoneWin(t)){
        printf("Deu velha da lancha\n");
    } else if (isWin(t, marks[mark])) {
        printf("%c GANHOU !!!\n", marks[mark]);
    } else {
        printf("%c PERDEU !!!\n", marks[mark]);
    }

}

void noThreadPlay(){
    TicTacToe* t = createTicTacToe();
    int npt_finished = 0;
    int x, y;
    int turn = 0;
    while(!npt_finished){
        y = rand() % 3;
        x = rand() % 3;
        while(!verifyPlay(t, y, x, marks[turn])){
            y = rand() % 3;
            x = rand() % 3;
        }
        play(t, y, x, marks[turn]);
        printTicTacToe(t);
        printf("\n");
        turn = !turn;
        if (isFull(t) || someoneWin(t))
            npt_finished = 1;
    }
    if (!someoneWin(t)){
        printf("Deu velha da lancha\n");
    } else if (isWin(t, marks[0])) {
        printf("%c GANHOU !!!\n", marks[0]);
    } else {
        printf("%c GANHOU !!!\n", marks[1]);
    }
    destroyTicTacToe(t);
}

int main(){
    clock_t start, end;
    long double cpu_time_used;
    start = clock();

    if (pthread_mutex_init(&lock, NULL) != 0)
        return 1;
    srand(time(NULL));

    TicTacToe* t = createTicTacToe();
    int turn = 1;

    pthread_t t_player1, t_player2;
    PlayerThreadArgs args1, args2;
    args1.t = t;
    args1.mark = 0;
    args2.t = t;
    args2.mark = 1;

    pthread_create(&t_player1, NULL, &player_thread, &args1);
    pthread_create(&t_player2, NULL, &player_thread, &args2);
    pthread_join(t_player1, NULL);
    pthread_join(t_player2, NULL);
    
    destroyTicTacToe(t);

    // noThreadPlay();
    // for(int i = 0; i < 1000000000; i++);
    end = clock();

    cpu_time_used = ((long double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %Lf\n", cpu_time_used);
    return 0;
}