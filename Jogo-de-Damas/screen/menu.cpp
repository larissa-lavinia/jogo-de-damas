#include <raylib.h>
#include <string>

#include "menu.h"

using namespace std;

// ==========================================================
// FUNÇÃO AUXILIAR PARA DESENHAR BOTÃO
// ==========================================================

void desenharBotao(
    Rectangle botao,
    const char* texto,
    Color cor,
    bool hover,
    int tamanhoTexto = 22
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

    // Cor do botão
    Color corBotao = cor;

    if (hover)
    {
        // Clareia o botão quando o mouse passa
        corBotao = Color{
            (unsigned char)min(255, cor.r + 20),
            (unsigned char)min(255, cor.g + 20),
            (unsigned char)min(255, cor.b + 20),
            cor.a
        };
    }

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

    // Centraliza o texto
    int larguraTexto = MeasureText(texto, tamanhoTexto);

    float textoX =
        botao.x + (botao.width - larguraTexto) / 2.0f;

    float textoY =
        botao.y + (botao.height - tamanhoTexto) / 2.0f - 2;

    DrawText(
        texto,
        (int)textoX,
        (int)textoY,
        tamanhoTexto,
        WHITE
    );
}

// ==========================================================
// MENU
// ==========================================================

AcaoMenu menu(const string& usuarioLogado)
{
    while (!WindowShouldClose())
    {
        // ==================================================
        // DIMENSÕES DA TELA
        // ==================================================

        int larguraTela = GetScreenWidth();
        int alturaTela = GetScreenHeight();

        // ==================================================
        // POSIÇÃO DO CARTÃO
        // ==================================================

        float larguraCard = 520.0f;
        float alturaCard = 520.0f;

        float cardX =
            (larguraTela - larguraCard) / 2.0f;

        float cardY =
            (alturaTela - alturaCard) / 2.0f + 25;

        // ==================================================
        // BOTÕES
        // ==================================================

        Rectangle botaoNovaPartida = {
            cardX + 70,
            cardY + 170,
            380,
            60
        };

        Rectangle botaoContinuar = {
            cardX + 70,
            cardY + 245,
            380,
            60
        };

        Rectangle botaoHistorico = {
            cardX + 70,
            cardY + 320,
            380,
            60
        };

        Rectangle botaoDeslogar = {
            cardX + 70,
            cardY + 395,
            380,
            50
        };

        // ==================================================
        // MOUSE
        // ==================================================

        Vector2 mouse = GetMousePosition();

        bool hoverNovaPartida =
            CheckCollisionPointRec(
                mouse,
                botaoNovaPartida
            );

        bool hoverContinuar =
            CheckCollisionPointRec(
                mouse,
                botaoContinuar
            );

        bool hoverHistorico =
            CheckCollisionPointRec(
                mouse,
                botaoHistorico
            );

        bool hoverDeslogar =
            CheckCollisionPointRec(
                mouse,
                botaoDeslogar
            );

        // ==================================================
        // CLIQUE
        // ==================================================

        bool clicou = false;

        AcaoMenu acao = AcaoMenu::HISTORICO;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hoverNovaPartida)
            {
                acao = AcaoMenu::NOVA_PARTIDA;
                clicou = true;
            }
            else if (hoverContinuar)
            {
                acao = AcaoMenu::CONTINUAR_PARTIDA;
                clicou = true;
            }
            else if (hoverHistorico)
            {
                acao = AcaoMenu::HISTORICO;
                clicou = true;
            }
            else if (hoverDeslogar)
            {
                acao = AcaoMenu::DESLOGAR;
                clicou = true;
            }
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
        // TEXTURA VISUAL DO FUNDO
        // ==================================================

        for (int y = 0; y < alturaTela; y += 40)
        {
            DrawLine(
                0,
                y,
                larguraTela,
                y,
                Fade(
                    Color{255, 255, 255, 255},
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

        // Linha dourada da barra
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
        // PERFIL DO USUÁRIO
        // ==================================================

        DrawCircle(
            larguraTela - 55,
            39,
            22,
            Color{
                218,
                158,
                55,
                255
            }
        );

        // Cabeça
        DrawCircle(
            larguraTela - 55,
            33,
            7,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // Corpo
        DrawCircle(
            larguraTela - 55,
            47,
            10,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // Nome
        string nomeUsuario = usuarioLogado;

        DrawText(
            nomeUsuario.c_str(),
            larguraTela - 230,
            30,
            18,
            WHITE
        );

        DrawText(
            "Jogador",
            larguraTela - 230,
            51,
            12,
            Fade(WHITE, 0.65f)
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
        // CARD PRINCIPAL
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
        // DETALHE SUPERIOR DO CARD
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

        const char* titulo = "Jogo de Damas";

        int larguraTitulo =
            MeasureText(titulo, 34);

        DrawText(
            titulo,
            (int)(cardX + (larguraCard - larguraTitulo) / 2),
            (int)cardY + 35,
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
            "Escolha uma opcao para continuar";

        int larguraSubtitulo =
            MeasureText(subtitulo, 16);

        DrawText(
            subtitulo,
            (int)(cardX + (larguraCard - larguraSubtitulo) / 2),
            (int)cardY + 82,
            16,
            Color{
                110,
                100,
                88,
                255
            }
        );

        // ==================================================
        // PEQUENA DECORAÇÃO
        // ==================================================

        DrawLine(
            (int)cardX + 70,
            (int)cardY + 125,
            (int)cardX + 190,
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
            (int)cardX + 330,
            (int)cardY + 125,
            (int)cardX + 450,
            (int)cardY + 125,
            Color{
                218,
                158,
                55,
                255
            }
        );

        // ==================================================
        // BOTÃO NOVA PARTIDA
        // ==================================================

        desenharBotao(
            botaoNovaPartida,
            "Nova partida",
            Color{
                35,
                125,
                82,
                255
            },
            hoverNovaPartida,
            22
        );

        // ==================================================
        // BOTÃO CONTINUAR
        // ==================================================

        desenharBotao(
            botaoContinuar,
            "Continuar partida",
            Color{
                52,
                91,
                126,
                255
            },
            hoverContinuar,
            22
        );

        // ==================================================
        // BOTÃO HISTÓRICO
        // ==================================================

        desenharBotao(
            botaoHistorico,
            "Historico",
            Color{
                142,
                105,
                58,
                255
            },
            hoverHistorico,
            22
        );

        // ==================================================
        // BOTÃO DESLOGAR
        // ==================================================

        desenharBotao(
            botaoDeslogar,
            "Deslogar",
            Color{
                110,
                82,
                66,
                255
            },
            hoverDeslogar,
            18
        );

        // ==================================================
        // RODAPÉ DO CARD
        // ==================================================

        DrawText(
            "Escolha uma opcao para jogar",
            (int)cardX + 145,
            (int)cardY + 470,
            13,
            Color{
                130,
                120,
                105,
                255
            }
        );

        EndDrawing();

        // ==================================================
        // RETORNO
        // ==================================================

        if (clicou)
        {
            return acao;
        }
    }

    return AcaoMenu::DESLOGAR;
}