#include <raylib.h>
#include "config/constantes.h"

#include "usuario.h"

#include "screen/login.h"
#include "screen/inicio.h"
#include "screen/cadastro.h"

enum class OpcaoInicio
{
    SAIR = 0,
    CADASTRO = 1,
    LOGIN = 2
};

int main(){
    InitWindow(
        Constantes::Tela::LARGURA,
        Constantes::Tela::ALTURA,
        Constantes::Tela::TITULO
    );

    SetTargetFPS(Constantes::Tela::FPS);

    bool executando = true;

    while (executando && !WindowShouldClose())
    {
        OpcaoInicio opcao = static_cast<OpcaoInicio>(inicio());

        if (opcao == OpcaoInicio::CADASTRO)
        {
            telaCadastro();
        }

        if (opcao == OpcaoInicio::LOGIN)
        {
            telaLogin();
        }

        if (opcao == OpcaoInicio::SAIR)
        {
            executando = false;
        }
    }

    CloseWindow();

    return 0;
}