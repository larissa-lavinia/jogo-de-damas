#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>
#include "../damas/peca.h"

struct sonsJogo{
    Sound movimento;
    Sound virarDama;
    Sound vitoria;
    Sound vitoriaMaquina;
    Sound erro;
};

void tocarSomMovimento();
void tocarSomVitoria();
void tocarSomVitoria(Cor vencedor);
void tocarSomVirarDama();
void tocarSomErro();
void carregarSons();
void descarregarSons();

#endif

