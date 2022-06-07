#include "tictactoe.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char marks[2] = {'x', 'o'};
int turn = 0;
int finished = 0;


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
            }

            if(finished) {
                break;
            } else {
                // joga e inverte o turno

                pthread_mutex_lock(&lock);
                play(t, y, x, marks[mark]);
                pthread_mutex_unlock(&lock);

                printf("\n");
                printTicTacToe(t);
                turn = !turn;
            }

            // sleep com proposito de facilitar o entendimento na execução
        } else {
            
            pthread_mutex_lock(&lock);
            if(someoneWin(t) || isFull(t)) {
                finished = 1;
            }
            pthread_mutex_unlock(&lock);
        }

        // caso alguem ganhar, set a flag finished em True
        if(someoneWin(t)) {
            finished = 1;
        }
    }
    // quando sair do loop principal, print a condição final do jogo
    if (!finished){
        printf("Deu velha da lancha\n");
    } else if (isWin(t, marks[mark])) {
        printf("%c GANHOU !!!\n", marks[mark]);
    } else {
        printf("%c PERDEU !!!\n", marks[mark]);
    }

}

int main(){

    if (pthread_mutex_init(&lock, NULL) != 0)
        return 1;
    srand(time(NULL));

    TicTacToe* t = createTicTacToe();

    pthread_t t_player1, t_player2;
    PlayerThreadArgs args1, args2;
    int turn = 1;

    args1.t = t;
    args1.mark = 0;
    args2.t = t;
    args2.mark = 1;

    
    printTicTacToe(t);

    pthread_create(&t_player1, NULL, &player_thread, &args1);
    pthread_create(&t_player2, NULL, &player_thread, &args2);
    pthread_join(t_player1, NULL);
    pthread_join(t_player2, NULL);
    
    destroyTicTacToe(t);
    
    return 0;
}