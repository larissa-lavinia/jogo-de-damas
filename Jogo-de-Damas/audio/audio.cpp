#include <raylib.h>
#include "audio.h"

sonsJogo sons;

void carregarSons()
{
    sons.movimento = LoadSound("audio/movimento.MP3");
    sons.virarDama = LoadSound("audio/virar_dama.mp3");
    sons.vitoria = LoadSound("audio/vitoria.mp3");
    sons.erro = LoadSound("audio/erro.mp3");
}

void descarregarSons()
{

    UnloadSound(sons.movimento);
    UnloadSound(sons.virarDama);
    UnloadSound(sons.vitoria);
    UnloadSound(sons.erro);
}

void tocarSomMovimento()
{
    PlaySound(sons.movimento);
}
void tocarSomVitoria()
{
    SetSoundVolume(sons.vitoria, 0.45f);
    PlaySound(sons.vitoria);
}
void tocarSomErro(){
    SetSoundVolume(sons.erro, 0.75f);
    PlaySound(sons.erro);

}
void tocarSomVirarDama()
{
    SetSoundVolume(sons.virarDama, 0.30f);
    PlaySound(sons.virarDama);
}
