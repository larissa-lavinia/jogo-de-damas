#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

struct sonsJogo{
    Sound movimento;
    Sound virarDama;
    Sound vitoria;
    Sound erro;
};

void tocarSomMovimento();
void tocarSomVitoria();
void tocarSomVirarDama();
void tocarSomErro();
void carregarSons();
void descarregarSons();

#endif

