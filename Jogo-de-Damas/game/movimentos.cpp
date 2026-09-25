//lembrar de modificar os .hpp

#include <cmath>
#include "tabuleiro.h" //por isso acho que talvez as funções do tabuleiro devem estar no .h
#include "movimentos.h"
// o código usa as variaveis globais declaradas em tabuleiro.


bool podeMoverSimples(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    //Linha e coluna iniciais seriam a que a peça está no momento que pede a validação
    // Já as finais é pra onde a peça irá depois
    if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador1){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
             linhaFinal == linhaInicial + 1 && 
              (abs(colunaFinal - colunaInicial)) == 1){ //não entendo pq usar abs aqui
            return true; // Movimento válido
        }else
            return false; // Movimento inválido
    }

    if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador2){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
             linhaFinal == linhaInicial - 1 &&
              (abs(colunaFinal - colunaInicial)) == 1){ //não entendo pq usar abs aqui
            return true; // Movimento válido
        }else
            return false; // Movimento inválido
    }

    return false; // Casa inicial vazia
}



bool podeCapturar(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    int linhaMeio = (linhaFinal + linhaInicial) / 2;
    int colunaMeio = (colunaFinal + colunaInicial) / 2;
    // Meio é onde vai estar a peça do adversario, já que na captura "pula duas casas"

    if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador1){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
         (abs(linhaFinal - linhaInicial) == 2) &&
          (abs(colunaFinal - colunaInicial) == 2) &&
           tabuleiro[linhaMeio][colunaMeio] == pecaJogador2){
           return true; // Movimento válido
        }else
           return false; // Movimento inválido
     }

     if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador2){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
           (abs(linhaFinal - linhaInicial) == 2) &&
            (abs(colunaFinal - colunaInicial) == 2) &&
             tabuleiro[linhaMeio][colunaMeio] == pecaJogador1){
            return true; // Movimento válido
        }else
            return false; // Movimento inválido
    }

    return false; // Casa inicial vazia
}



bool validarJogada(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    if (podeCapturar(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal)){
        return true;
    }
    if (podeMoverSimples(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal)) {
        return true;
    }

    return false;
}
//Essa função parece ser redundante

