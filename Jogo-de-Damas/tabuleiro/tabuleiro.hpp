#ifndef TABULEIRO_HPP_INCLUDED
#define TABULEIRO_HPP_INCLUDED

#include <stdio>

#define casaVazia 0
#define pecaJogador1 1
#define pecaJogador2 2
#define TABTAM 8

void inicializarTabuleiro(int tabuleiro[TABTAM][TABTAM]){
    //Inicializar tabuleiro
    for(int i = 0; i < TABTAM; i++)
        for(int j = 0; j < TABTAM; j++){
            if((i+j) % 2 != 0){
                if(i<3)
                    tabuleiro[i][j] = pecaJogador1;
                else if(i>4)
                    tabuleiro[i][j] = pecaJogador2;
                else
                    tabuleiro[i][j] = casaVazia;
            }
            else
                tabuleiro[i][j] = casaVazia;
        }
}

void exibirTabuleiro{}


#endif



