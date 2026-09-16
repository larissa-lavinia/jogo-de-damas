#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
#include <string>

namespace Constantes
{
    namespace Tela
    {
        const int LARGURA = 1280;
        const int ALTURA = 710;

        inline const char* TITULO = "Jogo de Damas";

        const int FPS = 60; // QUADROS POR SEGUNDO
    }

    namespace Tabuleiro
    {
        const int TAMANHO = 8;

        const int TAMANHO_CASA = 80;

        const int LARGURA = TAMANHO * TAMANHO_CASA;
        const int ALTURA = TAMANHO * TAMANHO_CASA;
    }

    namespace Cores
    {
        const Color CASA_CLARA = BEIGE;
        const Color CASA_ESCURA = BROWN;
    }

    namespace Pecas
    {
        const int RAIO = 30;
    }

    namespace Db
    {
        const std::string ARQUIVO_USUARIO = "db/usuarios.dat";
    }
}

#endif