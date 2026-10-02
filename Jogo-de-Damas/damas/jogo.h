#ifndef DAMAS_JOGO_H
#define DAMAS_JOGO_H

#include "peca.h"

const int PONTOS_VITORIA = 12;

struct Partida
{
    bool emAndamento;
    int  pontosBrancas;
    int  pontosPretas;
    Cor  vezDoJogador;   // útil para continuar partida
};

// definida em damas/jogo.cpp
extern Partida partida;

void iniciarPartida();

bool realizarJogada(
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
);

int  ganharPontos(const Partida& p, Cor jogador);
bool partidaFinalizada(const Partida& p);
Cor  vencedor(const Partida& p);

#endif
