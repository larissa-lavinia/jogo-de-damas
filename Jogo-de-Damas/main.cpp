
#include <raylib.h>
#include <filesystem>

#include "config/constantes.h"
#include "screen/inicio.h"
#include "screen/jogo.h"
#include "audio/audio.h"

using namespace std;

int main()
{
    InitWindow(
        Constantes::Tela::LARGURA,
        Constantes::Tela::ALTURA,
        Constantes::Tela::TITULO);
 
    InitAudioDevice();  
     carregarSons();
    SetTargetFPS(Constantes::Tela::FPS);

    bool executando = true;

    while (executando && !WindowShouldClose())
    {
        bool temPartidaSalva =
            filesystem::exists("db/partidas.dat");

        OpcaoInicio opcao = inicio(temPartidaSalva);

        switch (opcao)
        {
            case OpcaoInicio::NOVA_PARTIDA:
                telaJogo(false);
                break;

            case OpcaoInicio::CONTINUAR_PARTIDA:
                if (temPartidaSalva)
                {
                    telaJogo(true);
                }
                break;

            case OpcaoInicio::SAIR:
                executando = false;
                break;
        }
    }

    descarregarSons();
    CloseAudioDevice();  
    CloseWindow();

    return 0;
}