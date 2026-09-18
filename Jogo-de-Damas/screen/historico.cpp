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
        // =========================
        // BOTÕES
        // =========================

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

        // =========================
        // MOUSE
        // =========================

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, botaoNovaPartida))
            {
                return AcaoMenu::NOVA_PARTIDA;
            }

            else if (CheckCollisionPointRec(mouse, botaoContinuar))
            {
                return AcaoMenu::CONTINUAR_PARTIDA;
            }

            else if (CheckCollisionPointRec(mouse, botaoHistorico))
            {
                return AcaoMenu::HISTORICO;
            }

            else if (CheckCollisionPointRec(mouse, botaoDeslogar))
            {
                return AcaoMenu::DESLOGAR;
            }
        }

        // =========================
        // DESENHO
        // =========================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================
        // TÍTULO
        // =========================

        DrawText(
            "JOGO DE DAMAS",
            430,
            120,
            40,
            DARKGRAY
        );

        // =========================
        // USUÁRIO
        // =========================

        string mensagemUsuario = "Ola, " + usuarioLogado + "!";

        DrawText(
            mensagemUsuario.c_str(),
            500,
            200,
            25,
            DARKGRAY
        );

        // =========================
        // NOVA PARTIDA
        // =========================

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

        // =========================
        // CONTINUAR PARTIDA
        // =========================

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

        // =========================
        // HISTÓRICO
        // =========================

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

        // =========================
        // DESLOGAR
        // =========================

        DrawRectangleRec(
            botaoDeslogar,
            DARKGRAY
        );

        DrawText(
            "Deslogar",
            590,
            538,
            25,
            WHITE
        );

        EndDrawing();
    }

    return AcaoMenu::DESLOGAR;
}