#pragma once
#include "tabuleiro.h"

bool podeMoverSimples(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

bool podeCapturar(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

bool validarJogada(int tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);