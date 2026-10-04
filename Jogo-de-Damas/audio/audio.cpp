#include <raylib.h>
#include "audio.h"
#include "../damas/peca.h"

sonsJogo sons;

void carregarSons()
{
    sons.movimento = LoadSound("audio/movimento.MP3");
    sons.virarDama = LoadSound("audio/virar_dama.mp3");
    sons.vitoria = LoadSound("audio/vitoria.mp3");
    sons.vitoriaMaquina = LoadSound("audio/vitoriaMaquina.mp3");
    sons.erro = LoadSound("audio/erro.mp3");
    
}

void descarregarSons()
{
    UnloadSound(sons.movimento);
    UnloadSound(sons.virarDama);
    UnloadSound(sons.vitoria);
    UnloadSound(sons.erro);
     UnloadSound(sons.vitoriaMaquina);

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

void tocarSomVitoria(Cor vencedor)
{
    if(vencedor == BRANCA){
        PlaySound(sons.vitoria);
    }else{
         PlaySound(sons.vitoriaMaquina);
    }
        
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
