#include <raylib.h>
#include <string>

#include "login.h"
#include "../usuario/usuario.h"

using namespace std;

// ==========================================================
// BOTÃO
// ==========================================================

void desenharBotaoLogin(
    Rectangle botao,
    const char* texto,
    Color cor,
    bool hover,
    int tamanhoTexto
)
{
    // Sombra
    DrawRectangleRounded(
        {
            botao.x + 4,
            botao.y + 6,
            botao.width,
            botao.height
        },
        0.20f,
        12,
        Fade(BLACK, 0.25f)
    );

    Color corBotao = cor;

    if (hover)
    {
        corBotao = Color{
            (unsigned char)(cor.r + 20),
            (unsigned char)(cor.g + 20),
            (unsigned char)(cor.b + 20),
            cor.a
        };
    }

    // Corpo
    DrawRectangleRounded(
        botao,
        0.20f,
        12,
        corBotao
    );

    // Borda
    DrawRectangleRoundedLines(
        botao,
        0.20f,
        12,
        Fade(WHITE, 0.15f)
    );

    // Texto centralizado
    int larguraTexto =
        MeasureText(texto, tamanhoTexto);

    float textoX =
        botao.x +
        (botao.width - larguraTexto) / 2.0f;

    float textoY =
        botao.y +
        (botao.height - tamanhoTexto) / 2.0f - 2;

    DrawText(
        texto,
        (int)textoX,
        (int)textoY,
        tamanhoTexto,
        WHITE
    );
}

// ==========================================================
// CAMPO DE TEXTO
// ==========================================================

void desenharCampoLogin(
    Rectangle campo,
    const char* texto,
    bool selecionado,
    int tamanhoTexto = 20
)
{
    // Fundo do campo
    Color corCampo = Color{
        255,
        250,
        239,
        255
    };

    DrawRectangleRounded(
        campo,
        0.15f,
        10,
        corCampo
    );

    // Borda
    Color corBorda;

    if (selecionado)
    {
        corBorda = Color{
            218,
            158,
            55,
            255
        };
    }
    else
    {
        corBorda = Color{
            205,
            195,
            178,
            255
        };
    }

    DrawRectangleRoundedLines(
        campo,
        0.15f,
        10,
        corBorda
    );

    // Texto
    DrawText(
        texto,
        (int)campo.x + 18,
        (int)campo.y + 14,
        tamanhoTexto,
        Color{
            55,
            50,
            45,
            255
        }
    );
}

// ==========================================================
// TELA DE LOGIN
// ==========================================================

AcaoTelaLogin telaLogin(string& usuarioLogado)
{
    string nickname = "";
    string senha = "";

    bool digitandoNickname = false;
    bool digitandoSenha = false;

    string mensagem = "";

    while (!WindowShouldClose())
    {
        // ==================================================
        // DIMENSÕES
        // ==================================================

        int larguraTela = GetScreenWidth();
        int alturaTela = GetScreenHeight();

        // ==================================================
        // CARD
        // ==================================================

        float larguraCard = 520.0f;
        float alturaCard = 570.0f;

        float cardX =
            (larguraTela - larguraCard) / 2.0f;

        float cardY =
            (alturaTela - alturaCard) / 2.0f + 25;

        // ==================================================
        // CAMPOS
        // ==================================================

        Rectangle campoNickname = {
            cardX + 60,
            cardY + 165,
            400,
            55
        };

        Rectangle campoSenha = {
            cardX + 60,
            cardY + 270,
            400,
            55
        };

        // ==================================================
        // BOTÕES
        // ==================================================

        Rectangle botaoLogin = {
            cardX + 60,
            cardY + 365,
            400,
            60
        };

        Rectangle botaoVoltar = {
            cardX + 60,
            cardY + 440,
            400,
            50
        };

        // ==================================================
        // MOUSE
        // ==================================================

        Vector2 mouse = GetMousePosition();

        bool hoverLogin =
            CheckCollisionPointRec(
                mouse,
                botaoLogin
            );

        bool hoverVoltar =
            CheckCollisionPointRec(
                mouse,
                botaoVoltar
            );

        // ==================================================
        // ENTRADA DO TECLADO
        // ==================================================

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

        // ==================================================
        // BACKSPACE
        // ==================================================

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

        // ==================================================
        // MOUSE / CLIQUES
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Campo nickname
            if (CheckCollisionPointRec(
                    mouse,
                    campoNickname))
            {
                digitandoNickname = true;
                digitandoSenha = false;
                mensagem = "";
            }

            // Campo senha
            else if (CheckCollisionPointRec(
                         mouse,
                         campoSenha))
            {
                digitandoNickname = false;
                digitandoSenha = true;
                mensagem = "";
            }

            // Botão login
            else if (hoverLogin)
            {
                digitandoNickname = false;
                digitandoSenha = false;

                if (nickname.empty() || senha.empty())
                {
                    mensagem =
                        "Preencha todos os campos!";
                }
                else
                {
                    if (verificarLogin(
                            nickname,
                            senha))
                    {
                        usuarioLogado = nickname;

                        return
                            AcaoTelaLogin::ENTRAR_MENU;
                    }
                    else
                    {
                        mensagem =
                            "Nickname ou senha incorretos!";
                    }
                }
            }

            // Botão voltar
            else if (hoverVoltar)
            {
                return AcaoTelaLogin::VOLTAR;
            }

            // Clique fora
            else
            {
                digitandoNickname = false;
                digitandoSenha = false;
            }
        }

        // ==================================================
        // SENHA OCULTA
        // ==================================================

        string senhaOculta = "";

        for (int i = 0; i < (int)senha.size(); i++)
        {
            senhaOculta += "*";
        }

        // ==================================================
        // DESENHO
        // ==================================================

        BeginDrawing();

        // ==================================================
        // FUNDO
        // ==================================================

        ClearBackground(
            Color{
                24,
                72,
                56,
                255
            }
        );

        // ==================================================
        // TEXTURA
        // ==================================================

        for (int y = 0; y < alturaTela; y += 40)
        {
            DrawLine(
                0,
                y,
                larguraTela,
                y,
                Fade(
                    Color{
                        255,
                        255,
                        255,
                        255
                    },
                    0.015f
                )
            );
        }

        // ==================================================
        // BARRA SUPERIOR
        // ==================================================

        DrawRectangle(
            0,
            0,
            larguraTela,
            78,
            Color{
                77,
                47,
                27,
                255
            }
        );

        DrawRectangle(
            0,
            76,
            larguraTela,
            4,
            Color{
                218,
                158,
                55,
                255
            }
        );

        // ==================================================
        // LOGO
        // ==================================================

        DrawText(
            "DAMAS",
            35,
            18,
            36,
            Color{
                255,
                225,
                150,
                255
            }
        );

        DrawText(
            "JOGO DE TABULEIRO",
            38,
            53,
            12,
            Fade(WHITE, 0.75f)
        );

        // ==================================================
        // SOMBRA DO CARD
        // ==================================================

        DrawRectangleRounded(
            {
                cardX + 8,
                cardY + 10,
                larguraCard,
                alturaCard
            },
            0.04f,
            12,
            Fade(BLACK, 0.30f)
        );

        // ==================================================
        // CARD
        // ==================================================

        DrawRectangleRounded(
            {
                cardX,
                cardY,
                larguraCard,
                alturaCard
            },
            0.04f,
            12,
            Color{
                247,
                241,
                226,
                255
            }
        );

        // ==================================================
        // DETALHE DOURADO
        // ==================================================

        DrawRectangleRounded(
            {
                cardX,
                cardY,
                larguraCard,
                8
            },
            0.04f,
            12,
            Color{
                218,
                158,
                55,
                255
            }
        );

        // ==================================================
        // TÍTULO
        // ==================================================

        const char* titulo =
            "Entrar";

        int larguraTitulo =
            MeasureText(titulo, 34);

        DrawText(
            titulo,
            (int)(
                cardX +
                (larguraCard - larguraTitulo) / 2
            ),
            (int)cardY + 40,
            34,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // ==================================================
        // SUBTÍTULO
        // ==================================================

        const char* subtitulo =
            "Entre na sua conta para continuar";

        int larguraSubtitulo =
            MeasureText(subtitulo, 16);

        DrawText(
            subtitulo,
            (int)(
                cardX +
                (larguraCard - larguraSubtitulo) / 2
            ),
            (int)cardY + 88,
            16,
            Color{
                110,
                100,
                88,
                255
            }
        );

        // ==================================================
        // DECORAÇÃO
        // ==================================================

        DrawLine(
            (int)cardX + 60,
            (int)cardY + 125,
            (int)cardX + 185,
            (int)cardY + 125,
            Color{
                218,
                158,
                55,
                255
            }
        );

        DrawCircle(
            (int)cardX + 260,
            (int)cardY + 125,
            5,
            Color{
                218,
                158,
                55,
                255
            }
        );

        DrawLine(
            (int)cardX + 335,
            (int)cardY + 125,
            (int)cardX + 460,
            (int)cardY + 125,
            Color{
                218,
                158,
                55,
                255
            }
        );

        // ==================================================
        // LABEL NICKNAME
        // ==================================================

        DrawText(
            "Nickname",
            (int)campoNickname.x,
            (int)campoNickname.y - 27,
            16,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // ==================================================
        // CAMPO NICKNAME
        // ==================================================

        desenharCampoLogin(
            campoNickname,
            nickname.c_str(),
            digitandoNickname
        );

        // Cursor nickname
        if (
            digitandoNickname &&
            ((int)GetTime() % 2 == 0)
        )
        {
            int larguraTexto =
                MeasureText(
                    nickname.c_str(),
                    20
                );

            DrawLine(
                (int)campoNickname.x +
                    18 +
                    larguraTexto,
                (int)campoNickname.y + 13,
                (int)campoNickname.x +
                    18 +
                    larguraTexto,
                (int)campoNickname.y + 40,
                Color{
                    77,
                    47,
                    27,
                    255
                }
            );
        }

        // ==================================================
        // LABEL SENHA
        // ==================================================

        DrawText(
            "Senha",
            (int)campoSenha.x,
            (int)campoSenha.y - 27,
            16,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // ==================================================
        // CAMPO SENHA
        // ==================================================

        desenharCampoLogin(
            campoSenha,
            senhaOculta.c_str(),
            digitandoSenha
        );

        // Cursor senha
        if (
            digitandoSenha &&
            ((int)GetTime() % 2 == 0)
        )
        {
            int larguraTexto =
                MeasureText(
                    senhaOculta.c_str(),
                    20
                );

            DrawLine(
                (int)campoSenha.x +
                    18 +
                    larguraTexto,
                (int)campoSenha.y + 13,
                (int)campoSenha.x +
                    18 +
                    larguraTexto,
                (int)campoSenha.y + 40,
                Color{
                    77,
                    47,
                    27,
                    255
                }
            );
        }

        // ==================================================
        // BOTÃO ENTRAR
        // ==================================================

        desenharBotaoLogin(
            botaoLogin,
            "Entrar",
            Color{
                35,
                125,
                82,
                255
            },
            hoverLogin,
            22
        );

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        desenharBotaoLogin(
            botaoVoltar,
            "Voltar",
            Color{
                110,
                82,
                66,
                255
            },
            hoverVoltar,
            18
        );

        // ==================================================
        // MENSAGEM
        // ==================================================

        if (!mensagem.empty())
        {
            int larguraMensagem =
                MeasureText(
                    mensagem.c_str(),
                    16
                );

            float mensagemX =
                cardX +
                (larguraCard - larguraMensagem) / 2.0f;

            DrawText(
                mensagem.c_str(),
                (int)mensagemX,
                (int)cardY + 510,
                16,
                Color{
                    170,
                    55,
                    45,
                    255
                }
            );
        }

        // ==================================================
        // RODAPÉ
        // ==================================================

        DrawText(
            "Acesse sua conta para continuar jogando",
            (int)cardX + 130,
            (int)cardY + 545,
            13,
            Color{
                130,
                120,
                105,
                255
            }
        );

        EndDrawing();
    }

    return AcaoTelaLogin::VOLTAR;
}