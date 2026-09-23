#include <raylib.h>
#include "inicio.h"

int inicio()
{
    while (!WindowShouldClose())
    {
        // =========================
        // BOTÕES
        // =========================

        Rectangle botaoCadastro = {
            490, 300, 300, 60
        };

        Rectangle botaoLogin = {
            490, 390, 300, 60
        };

        Rectangle botaoSair = {
            490, 480, 300, 60
        };

        // =========================
        // MOUSE
        // =========================

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Cadastro
            if (CheckCollisionPointRec(mouse, botaoCadastro))
            {
                return 1;
            }

            // Login
            if (CheckCollisionPointRec(mouse, botaoLogin))
            {
                return 2;
            }

            // Sair
            if (CheckCollisionPointRec(mouse, botaoSair))
            {
                return 0;
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
            150,
            45,
            DARKGRAY
        );

        DrawText(
            "Escolha uma opcao",
            500,
            220,
            20,
            GRAY
        );

        // =========================
        // BOTÃO CADASTRO
        // =========================

        DrawRectangleRec(
            botaoCadastro,
            DARKGREEN
        );

        DrawText(
            "Cadastrar",
            580,
            318,
            25,
            WHITE
        );

        // =========================
        // BOTÃO LOGIN
        // =========================

        DrawRectangleRec(
            botaoLogin,
            DARKBLUE
        );

        DrawText(
            "Login",
            610,
            408,
            25,
            WHITE
        );

        // =========================
        // BOTÃO SAIR
        // =========================

        DrawRectangleRec(
            botaoSair,
            DARKGRAY
        );

        DrawText(
            "Sair",
            620,
            498,
            25,
            WHITE
        );

        EndDrawing();
    }

    return 0;
}