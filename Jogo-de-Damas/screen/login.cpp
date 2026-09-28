#include <raylib.h>
#include <string>

#include "../usuario.h"

using namespace std;

enum class AcaoTelaLogin
{
    VOLTAR,
    ENTRAR_MENU
};

AcaoTelaLogin telaLogin(string& usuarioLogado)
{
    string nickname = "";
    string senha = "";

    bool digitandoNickname = false;
    bool digitandoSenha = false;

    string mensagem = "";

    while (!WindowShouldClose())
    {
        // =========================
        // CAMPOS
        // =========================

        Rectangle campoNickname = {
            390, 220, 500, 50
        };

        Rectangle campoSenha = {
            390, 330, 500, 50
        };

        Rectangle botaoLogin = {
            390, 430, 240, 60
        };

        Rectangle botaoVoltar = {
            390, 520, 240, 50
        };

        // =========================
        // ENTRADA DO TECLADO
        // =========================

        int tecla = GetCharPressed();

        while (tecla > 0)
        {
            if (digitandoNickname)
            {
                if (nickname.size() < 49)
                {
                    nickname += (char)tecla;
                }
            }

            if (digitandoSenha)
            {
                if (senha.size() < 49)
                {
                    senha += (char)tecla;
                }
            }

            tecla = GetCharPressed();
        }

        // =========================
        // BACKSPACE
        // =========================

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (digitandoNickname)
            {
                if (!nickname.empty())
                {
                    nickname.pop_back();
                }
            }

            if (digitandoSenha)
            {
                if (!senha.empty())
                {
                    senha.pop_back();
                }
            }
        }

        // =========================
        // MOUSE
        // =========================

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Campo nickname
            if (CheckCollisionPointRec(mouse, campoNickname))
            {
                digitandoNickname = true;
                digitandoSenha = false;
                mensagem = "";
            }

            // Campo senha
            else if (CheckCollisionPointRec(mouse, campoSenha))
            {
                digitandoNickname = false;
                digitandoSenha = true;
                mensagem = "";
            }

            // Botão login
            else if (CheckCollisionPointRec(mouse, botaoLogin))
            {
                digitandoNickname = false;
                digitandoSenha = false;

                if (nickname.empty() || senha.empty())
                {
                    mensagem = "Preencha todos os campos!";
                }
                else
                {
                    if (verificarLogin(nickname, senha))
                    {
                        usuarioLogado = nickname;
                        return AcaoTelaLogin::ENTRAR_MENU;
                    }
                    else
                    {
                        mensagem = "Nickname ou senha incorretos!";
                    }
                }
            }

            // Botão voltar
            else if (CheckCollisionPointRec(mouse, botaoVoltar))
            {
                return AcaoTelaLogin::VOLTAR;
            }

            // Clique fora dos campos
            else
            {
                digitandoNickname = false;
                digitandoSenha = false;
            }
        }

        // =========================
        // SENHA OCULTA
        // =========================

        int tamanhoSenha = senha.size();

        string senhaOculta = "";

        for (int i = 0; i < tamanhoSenha; i++)
        {
            senhaOculta += "*";
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
            "LOGIN",
            500,
            120,
            40,
            DARKGRAY
        );

        // =========================
        // NICKNAME
        // =========================

        DrawText(
            "Nickname:",
            390,
            185,
            20,
            DARKGRAY
        );

        DrawRectangleRec(
            campoNickname,
            LIGHTGRAY
        );

        DrawText(
            nickname.c_str(),
            405,
            235,
            20,
            BLACK
        );

        // Cursor do nickname
        if (digitandoNickname && ((int)GetTime() % 2 == 0))
        {
            int larguraTexto = MeasureText(
                nickname.c_str(),
                20
            );

            DrawLine(
                405 + larguraTexto,
                232,
                405 + larguraTexto,
                253,
                BLACK
            );
        }

        // =========================
        // SENHA
        // =========================

        DrawText(
            "Senha:",
            390,
            295,
            20,
            DARKGRAY
        );

        DrawRectangleRec(
            campoSenha,
            LIGHTGRAY
        );

        DrawText(
            senhaOculta.c_str(),
            405,
            345,
            20,
            BLACK
        );

        // Cursor da senha
        if (digitandoSenha && ((int)GetTime() % 2 == 0))
        {
            int larguraTexto = MeasureText(
                senhaOculta.c_str(),
                20
            );

            DrawLine(
                405 + larguraTexto,
                342,
                405 + larguraTexto,
                363,
                BLACK
            );
        }

        // =========================
        // BOTÃO LOGIN
        // =========================

        DrawRectangleRec(
            botaoLogin,
            DARKBLUE
        );

        DrawText(
            "Entrar",
            485,
            450,
            25,
            WHITE
        );

        // =========================
        // BOTÃO VOLTAR
        // =========================

        DrawRectangleRec(
            botaoVoltar,
            DARKGRAY
        );

        DrawText(
            "Voltar",
            480,
            535,
            20,
            WHITE
        );

        // =========================
        // MENSAGEM
        // =========================

        if (!mensagem.empty())
        {
            DrawText(
                mensagem.c_str(),
                390,
                590,
                20,
                RED
            );
        }

        EndDrawing();
    }

    return AcaoTelaLogin::VOLTAR;
}