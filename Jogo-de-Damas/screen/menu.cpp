#include <raylib.h>
#include <string>

using namespace std;

enum class AcaoMenu
{
    NOVA_PARTIDA,
    CONTINUAR_PARTIDA,
    HISTORICO,
    DESLOGAR
};

AcaoMenu menu(string usuarioLogado)
{
    while (!WindowShouldClose())
    {
        Rectangle botaoNovaPartida = {
            490, 280, 300, 60
        };

        Rectangle botaoContinuar = {
            490, 360, 300, 60
        };

        Rectangle botaoHistorico = {
            490, 440, 300, 60
        };

        Rectangle botaoDeslogar = {
            490, 520, 300, 60
        };

        bool clicou = false;

        AcaoMenu acao = AcaoMenu::HISTORICO;

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, botaoNovaPartida))
            {
                acao = AcaoMenu::NOVA_PARTIDA;
                clicou = true;
            }
            else if (CheckCollisionPointRec(mouse, botaoContinuar))
            {
                acao = AcaoMenu::CONTINUAR_PARTIDA;
                clicou = true;
            }
            else if (CheckCollisionPointRec(mouse, botaoHistorico))
            {
                acao = AcaoMenu::HISTORICO;
                clicou = true;
            }
            else if (CheckCollisionPointRec(mouse, botaoDeslogar))
            {
                acao = AcaoMenu::DESLOGAR;
                clicou = true;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "JOGO DE DAMAS",
            430,
            120,
            40,
            DARKGRAY
        );

        string mensagemUsuario = "Ola, " + usuarioLogado + "!";

        DrawText(
            mensagemUsuario.c_str(),
            500,
            200,
            25,
            DARKGRAY
        );

        DrawRectangleRec(
            botaoNovaPartida,
            DARKGREEN
        );

        DrawText(
            "Nova partida",
            565,
            298,
            25,
            WHITE
        );

        DrawRectangleRec(
            botaoContinuar,
            DARKBLUE
        );

        DrawText(
            "Continuar partida",
            540,
            378,
            25,
            WHITE
        );

        DrawRectangleRec(
            botaoHistorico,
            GRAY
        );

        DrawText(
            "Historico",
            590,
            458,
            25,
            WHITE
        );

        DrawRectangleRec(
            botaoDeslogar,
            DARKGRAY
        );

        DrawText(
            "Deslogar",
            590,
            538,
            20,
            WHITE
        );

        EndDrawing();

        if (clicou)
        {
            return acao;
        }
    }

    return AcaoMenu::DESLOGAR;
}