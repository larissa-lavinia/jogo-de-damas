#pragma once
#include "tabuleiro.h"

bool podeMoverSimples(peca tabuleiro[TABTAM][TABTAM], peca linhaInicial, peca colunaInicial, peca linhaFinal, peca colunaFinal);

bool podeCapturar(peca tabuleiro[TABTAM][TABTAM], peca linhaInicial, peca colunaInicial, peca linhaFinal, peca colunaFinal);

bool validarJogada(peca tabuleiro[TABTAM][TABTAM], peca linhaInicial, peca colunaInicial, peca linhaFinal, peca colunaFinal);
