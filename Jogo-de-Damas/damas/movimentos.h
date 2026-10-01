#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H

#include "peca.h"
#include "tabuleiro.h"

void moverPeca(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
);

bool podeMoverSimples(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
);

bool podeCapturar(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
);

bool validarJogada(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
);

#endif
