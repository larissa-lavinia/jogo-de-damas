#ifndef MOVIMENTOS_HPP_INCLUDED
#define MOVIMENTOS_HPP_INCLUDED

#include <cmath>
#include "tabuleiro.h"

bool podeMoverSimples(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
     if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador1){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
           linhaFinal == linhaInicial + 1 &&
           (abs(colunaFinal - colunaInicial)) == 1){
            return true; // Movimento válido
        }else
            return false; // Movimento inválido
     }

     if(tabuleiro[linhaInicial][colunaInicial] == pecaJogador2){
        if(tabuleiro[linhaFinal][colunaFinal] == casaVazia &&
           linhaFinal == linhaInicial - 1 &&
           (abs(colunaFinal - colunaInicial)) == 1){
            return true; // Movimento válido
        }else
            return false; // Movimento inválido
     }

     return false; // Casa inicial vazia
}

bool podeCapturar(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    int linhaMeio = (linhaFinal + linhaInicial) / 2;
    int colunaMeio = (colunaFinal + colunaInicial) / 2;

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



#endif
