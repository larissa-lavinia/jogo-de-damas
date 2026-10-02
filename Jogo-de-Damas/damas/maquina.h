#ifndef MAQUINA_H
#define MAQUINA_H

#include "peca.h"

struct Jogada
{
    int linhaInicial;
    int colunaInicial;
    int linhaFinal;
    int colunaFinal;
};

bool escolherJogadaMaquina(Cor jogador, Jogada& jogada);

#endif