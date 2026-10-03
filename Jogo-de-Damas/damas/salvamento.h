
#ifndef SALVAMENTO_H
#define SALVAMENTO_H

#include "peca.h"

bool salvarPartida(Cor jogadorAtual);
bool carregarPartida(Cor& jogadorAtual);
bool existePartidaSalva();
void excluirPartidaSalva();

#endif