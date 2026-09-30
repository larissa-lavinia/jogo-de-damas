#ifndef JOGO_H
#define JOGO_H

#include "peca.h"

void iniciarPartida();

bool realizarJogada(
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
);

#endif