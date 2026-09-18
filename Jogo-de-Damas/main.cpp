#include <raylib.h>
#include <string>

#include "config/constantes.h"

#include "usuario.h"
#include "screen/login.cpp"
#include "screen/inicio.cpp"
#include "screen/cadastro.cpp"
#include "screen/menu.cpp"

using namespace std;

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

    SetTargetFPS(Constantes::Tela::FPS);

    bool executando = true;
    bool logado = false;

    string usuarioLogado = "";

    TraceLog(LOG_INFO, "Programa iniciado");

    while (executando && !WindowShouldClose())
    {
        TraceLog(LOG_INFO, "Entrando no loop principal");

        if (!logado)
        {
            TraceLog(LOG_INFO, "Usuario nao esta logado");
            TraceLog(LOG_INFO, "Chamando inicio()");

            OpcaoInicio opcao =
                static_cast<OpcaoInicio>(inicio());

            TraceLog(LOG_INFO, "inicio() retornou");

            if (opcao == OpcaoInicio::CADASTRO)
            {
                TraceLog(LOG_INFO, "Abrindo cadastro");
                telaCadastro();
            }

            if (opcao == OpcaoInicio::LOGIN)
            {
                TraceLog(LOG_INFO, "Abrindo login");

                AcaoTelaLogin acaoLogin =
                    telaLogin(usuarioLogado);

                if (acaoLogin == AcaoTelaLogin::ENTRAR_MENU)
                {
                    TraceLog(LOG_INFO, "Login realizado");
                    logado = true;
                }
            }

            if (opcao == OpcaoInicio::SAIR)
            {
                TraceLog(LOG_INFO, "Saindo do programa");
                executando = false;
            }
        }
        else
        {
            TraceLog(LOG_INFO, "Usuario logado");
            TraceLog(LOG_INFO, "Abrindo menu");

            AcaoMenu acaoMenu =
                menu(usuarioLogado);

            TraceLog(
                LOG_INFO,
                "Acao do menu: %d",
                (int)acaoMenu
            );
            
            TraceLog(LOG_INFO, "menu() retornou");

            if (acaoMenu == AcaoMenu::DESLOGAR)
            {
                TraceLog(LOG_INFO, "Usuario deslogado");

                usuarioLogado = "";
                logado = false;
            }
        }
    }

    TraceLog(LOG_INFO, "Fechando janela");

    CloseWindow();

    return 0;
}