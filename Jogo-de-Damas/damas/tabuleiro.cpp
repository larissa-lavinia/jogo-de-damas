// Não sei se o tipo de arquivo tá certo
// Talvez tenha que colar no .h ou criar um .hpp
#include <stdio.h>
#include "tabuleiro.h"
#include "peca (1).h"

void inicializarTabuleiro(peca tabuleiro[TABTAM][TABTAM]){ // Verificar se essa passagem de tabuleiro/matriz está correta
    //Inicializar tabuleiro
    for(int i = 0; i < TABTAM; i++)
        for(int j = 0; j < TABTAM; j++){
            tabuleiro[i][j].linha = i;
            tabuleiro[i][j].coluna = j;

            if((i+j) % 2 != 0){
                if(i<3){
                    tabuleiro[i][j].cor = BRANCA;
                    tabuleiro[i][j].ocupada = true;
                    tabuleiro[i][j].tipo = NORMAL;
                }
                else if(i>4){
                    tabuleiro[i][j].cor = PRETA;
                    tabuleiro[i][j].ocupada = true;
                    tabuleiro[i][j].tipo = NORMAL;
                }
                else
                    tabuleiro[i][j].ocupada = false; // casas vazias do meio
            }
            else
                tabuleiro[i][j].ocupada = false; // casas vazias ímpares
        }
}

// Apaguei a função imprimir tabuleiro, por que era só uma verificação de
