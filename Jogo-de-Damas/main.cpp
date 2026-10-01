#include <raylib.h>
#include <string>

#include "config/constantes.h"

#include "screen/inicio.h"
#include "screen/login.h"
#include "screen/cadastro.h"
#include "screen/menu.h"
#include "screen/jogo.h"

using namespace std;

int main()
{
    string nomeUsuario = "";

    InitWindow(
        Constantes::Tela::LARGURA,
        Constantes::Tela::ALTURA,
        Constantes::Tela::TITULO);

    SetTargetFPS(Constantes::Tela::FPS);

    bool executando = true;

    while (executando && !WindowShouldClose())
    {
        // =========================
        // TELA INICIAL
        // =========================

        OpcaoInicio opcao = inicio();

        // =========================
        // CADASTRO
        // =========================

        if (opcao == OpcaoInicio::CADASTRO)
        {
            AcaoTelaCadastro resultadoCadastro = telaCadastro();

            if (resultadoCadastro == AcaoTelaCadastro::VOLTAR)
            {
                continue;
            }
        }

        // =========================
        // LOGIN
        // =========================

        else if (opcao == OpcaoInicio::LOGIN)
        {
            AcaoTelaLogin resultado = telaLogin(nomeUsuario);

            if (resultado == AcaoTelaLogin::ENTRAR_MENU)
            {
                // =========================
                // MENU
                // =========================

                bool dentroDoMenu = true;

                while (dentroDoMenu && !WindowShouldClose())
                {
                    AcaoMenu acao = menu(nomeUsuario);

                    if (acao == AcaoMenu::DESLOGAR)
                    {
                        dentroDoMenu = false;
                        nomeUsuario = "";
                    }

                    else if (acao == AcaoMenu::NOVA_PARTIDA)
                    {
                        telaJogo(nomeUsuario);
                    }

                    else if (acao == AcaoMenu::CONTINUAR_PARTIDA)
                    {
                        // Implementaremos depois.
                    }

                    else if (acao == AcaoMenu::HISTORICO)
                    {
                        // Implementaremos depois.
                    }
                }
            }
        }

        // =========================
        // SAIR
        // =========================

        else if (opcao == OpcaoInicio::SAIR)
        {
            executando = false;
        }
    }

    CloseWindow();

    return 0;
}
