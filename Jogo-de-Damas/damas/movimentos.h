#pragma once
#include "tabuleiro.h"

bool podeMoverSimples(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

bool podeCapturar(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

bool validarJogada(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

void moverPeca(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
