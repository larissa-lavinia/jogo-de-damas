#include <raylib.h>
#include "damas/movimentos.h"

#include "config/constantes.h"

#include "usuario.h"
#include "screen/login.cpp"
#include "screen/inicio.cpp"
#include "screen/cadastro.cpp"

enum class OpcaoInicio
{
    SAIR = 0,
    CADASTRO = 1,
    LOGIN = 2
};

int main()
{
    InitWindow(
        Constantes::Tela::LARGURA,
        Constantes::Tela::ALTURA,
        Constantes::Tela::TITULO
    );

    string lll = "aldsldklsd";

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
            telaLogin(lll); // tá dando erro, vou colocar qualquer coisa, qual é o parâmetro?
        }

        if (opcao == OpcaoInicio::SAIR)
        {
            executando = false;
        }
    }

    CloseWindow();

    inicializarTabuleiro(tabuleiro);

    exibirTabuleiro(tabuleiro);

    return 0;
}
