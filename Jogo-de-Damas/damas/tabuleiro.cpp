
// Não sei se o tipo de arquivo tá certo
// Talvez tenha que colar no .h ou criar um .hpp
#include <stdio.h>
#include "tabuleiro.h"

int tabuleiro[TABTAM][TABTAM]; // Alocação real da memória que esta extern no tabuleiro.h

void inicializarTabuleiro(int tabuleiro[TABTAM][TABTAM]){ // Verificar se essa passagem de tabuleiro/matriz está correta
    //Inicializar tabuleiro
    for(int i = 0; i < TABTAM; i++)
        for(int j = 0; j < TABTAM; j++){
            if((i+j) % 2 != 0){
                if(i<3)
                    tabuleiro[i][j] = pecaJogador1;
                else if(i>4)
                    tabuleiro[i][j] = pecaJogador2;
                else
                    tabuleiro[i][j] = casaVazia; // casas vazias do meio
            }
            else
                tabuleiro[i][j] = casaVazia; // casas vazias ímpares
        }
}

void exibirTabuleiro(int tabuleiro[TABTAM][TABTAM]){
    for (int i=0; i < TABTAM; i++){
        for (int j=0; j < TABTAM; j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}