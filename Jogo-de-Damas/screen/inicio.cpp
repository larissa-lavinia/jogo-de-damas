
#include <raylib.h>

#include "inicio.h"

using namespace std;

// ==========================================================
// FUNÇÃO AUXILIAR PARA DESENHAR BOTÃO
// ==========================================================

void desenharBotaoInicio(
    Rectangle botao,
    const char* texto,
    Color cor,
    bool hover,
    int tamanhoTexto = 22
)
{
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

    DrawRectangleRounded(
        botao,
        0.20f,
        12,
        corBotao
    );

    DrawRectangleRoundedLines(
        botao,
        0.20f,
        12,
        Fade(WHITE, 0.15f)
    );

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
// TELA INICIAL
// ==========================================================

OpcaoInicio inicio(bool temPartidaSalva)
{
    while (!WindowShouldClose())
    {
        // ==================================================
        // DIMENSÕES DA TELA
        // ==================================================

        int larguraTela = GetScreenWidth();
        int alturaTela = GetScreenHeight();

        // ==================================================
        // CARD PRINCIPAL
        // Mantendo as dimensões e o posicionamento originais
        // ==================================================

        float larguraCard = 520.0f;
        float alturaCard = 500.0f;

        float cardX =
            (larguraTela - larguraCard) / 2.0f;

        float cardY =
            (alturaTela - alturaCard) / 2.0f + 25;

        // ==================================================
        // BOTÕES
        // ==================================================

        Rectangle botaoNovaPartida = {
            cardX + 70,
            cardY + 185,
            380,
            60
        };

        Rectangle botaoContinuar = {
            cardX + 70,
            cardY + 260,
            380,
            60
        };

        Rectangle botaoSair = {
            cardX + 70,
            cardY + 335,
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

        bool hoverSair =
            CheckCollisionPointRec(
                mouse,
                botaoSair
            );

        // ==================================================
        // CLIQUE
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hoverNovaPartida)
            {
                return OpcaoInicio::NOVA_PARTIDA;
            }

            if (hoverContinuar && temPartidaSalva)
            {
                return OpcaoInicio::CONTINUAR_PARTIDA;
            }

            if (hoverSair)
            {
                return OpcaoInicio::SAIR;
            }
        }

        // ==================================================
        // DESENHO
        // ==================================================

        BeginDrawing();

        // ==================================================
        // FUNDO VERDE
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
        // TEXTURA DO FUNDO
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
            Color{77, 47, 27, 255}
        );

        DrawRectangle(
            0,
            76,
            larguraTela,
            4,
            Color{218, 158, 55, 255}
        );

        // ==================================================
        // LOGO
        // ==================================================

        DrawText(
            "DAMAS",
            35,
            18,
            36,
            Color{255, 225, 150, 255}
        );

        DrawText(
            "JOGO DE TABULEIRO",
            38,
            53,
            12,
            Fade(WHITE, 0.75f)
        );

        // ==================================================
        // CARD — SOMBRA
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
            Color{247, 241, 226, 255}
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
            Color{218, 158, 55, 255}
        );

        // ==================================================
        // TÍTULO
        // ==================================================

        const char* titulo = "Bem-vindo";

        int larguraTitulo =
            MeasureText(titulo, 34);

        DrawText(
            titulo,
            (int)(
                cardX +
                (larguraCard - larguraTitulo) / 2
            ),
            (int)cardY + 45,
            34,
            Color{77, 47, 27, 255}
        );

        // ==================================================
        // SUBTÍTULO
        // ==================================================

        const char* subtitulo =
            "Prepare-se para jogar damas";

        int larguraSubtitulo =
            MeasureText(subtitulo, 16);

        DrawText(
            subtitulo,
            (int)(
                cardX +
                (larguraCard - larguraSubtitulo) / 2
            ),
            (int)cardY + 95,
            16,
            Color{110, 100, 88, 255}
        );

        // ==================================================
        // DECORAÇÃO
        // ==================================================

        DrawLine(
            (int)cardX + 70,
            (int)cardY + 140,
            (int)cardX + 190,
            (int)cardY + 140,
            Color{218, 158, 55, 255}
        );

        DrawCircle(
            (int)cardX + 260,
            (int)cardY + 140,
            5,
            Color{218, 158, 55, 255}
        );

        DrawLine(
            (int)cardX + 330,
            (int)cardY + 140,
            (int)cardX + 450,
            (int)cardY + 140,
            Color{218, 158, 55, 255}
        );

        // ==================================================
        // BOTÃO NOVA PARTIDA
        // ==================================================

        desenharBotaoInicio(
            botaoNovaPartida,
            "Iniciar partida",
            Color{35, 125, 82, 255},
            hoverNovaPartida,
            22
        );

        // ==================================================
        // BOTÃO CONTINUAR
        // ==================================================

        Color corContinuar =
            temPartidaSalva
                ? Color{52, 91, 126, 255}
                : Color{130, 130, 130, 255};

        desenharBotaoInicio(
            botaoContinuar,
            "Continuar",
            corContinuar,
            hoverContinuar && temPartidaSalva,
            22
        );

        // ==================================================
        // BOTÃO SAIR
        // ==================================================

        desenharBotaoInicio(
            botaoSair,
            "Sair",
            Color{110, 82, 66, 255},
            hoverSair,
            18
        );

        // ==================================================
        // RODAPÉ
        // ==================================================

        DrawText(
            "Um jogo classico para dois jogadores",
            (int)cardX + 135,
            (int)cardY + 445,
            13,
            Color{130, 120, 105, 255}
        );

        EndDrawing();
    }

    return OpcaoInicio::SAIR;
}