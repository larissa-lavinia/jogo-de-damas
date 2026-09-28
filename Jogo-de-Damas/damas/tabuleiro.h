#pragma once 

//Mudei os define para const para não correr riscos
//Verificar se consegue usar no movimentos.hpp mesmo com const 
const int casaVazia = 0;
const int pecaJogador1 = 1;
const int pecaJogador2 = 2;
const int TABTAM = 8;

// Usa extern para avisar ao compilador que a variável existe
// Podem ocorrer erros de redefinição (duplicidade) quando múltiplos arquivos .cpp incluírem o tabuleiro.h.
extern int tabuleiro[TABTAM][TABTAM]; //tabuleiro não pode ser const pq será sempre modificado

void inicializarTabuleiro(int tabuleiro[TABTAM][TABTAM]);

void exibirTabuleiro(int tabuleiro[TABTAM][TABTAM]);