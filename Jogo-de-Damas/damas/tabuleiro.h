#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "peca.h"

const int TABTAM = 8;

extern peca tabuleiro[TABTAM][TABTAM];

void inicializarTabuleiro(
    peca tabuleiro[TABTAM][TABTAM]
);

void exibirTabuleiro(
    peca tabuleiro[TABTAM][TABTAM]
);

#endif
