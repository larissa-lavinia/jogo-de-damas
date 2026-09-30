#include "jogo.h"

#include <raylib.h>
#include <string>

#include "../damas/jogo.h"
#include "../damas/tabuleiro.h"
#include "../damas/peca.h"

using namespace std;

// ==========================================================
// CORES DA INTERFACE
// ==========================================================

const Color FUNDO_JOGO = {
    20, 54, 45, 255
};

const Color VERDE_PAINEL = {
    27, 67, 55, 255
};

const Color MADEIRA = {
    91, 55, 32, 255
};

const Color MADEIRA_CLARA = {
    125, 78, 44, 255
};

const Color DOURADO = {
    218, 158, 55, 255
};

const Color CREME = {
    246, 239, 220, 255
};

const Color CASA_CLARA = {
    239, 216, 174, 255
};

const Color CASA_ESCURA = {
    117, 76, 48, 255
};

// ==========================================================
// DESENHA BOTÃO
// ==========================================================

void desenharBotaoJogo(
    Rectangle botao,
    const char* texto,
    Color cor,
    bool hover
)
{
    // Sombra
    DrawRectangleRounded(
        {
            botao.x + 4,
            botao.y + 5,
            botao.width,
            botao.height
        },
        0.18f,
        12,
        Fade(BLACK, 0.30f)
    );

    Color corBotao = cor;

    if (hover)
    {
        corBotao = Color{
            (unsigned char)(cor.r + 15),
            (unsigned char)(cor.g + 15),
            (unsigned char)(cor.b + 15),
            cor.a
        };
    }

    // Corpo
    DrawRectangleRounded(
        botao,
        0.18f,
        12,
        corBotao
    );

    // Borda
    DrawRectangleRoundedLines(
        botao,
        0.18f,
        12,
        Fade(WHITE, 0.15f)
    );

    int tamanhoTexto = 18;

    int larguraTexto =
        MeasureText(texto, tamanhoTexto);

    DrawText(
        texto,
        (int)(
            botao.x +
            (botao.width - larguraTexto) / 2
        ),
        (int)(
            botao.y +
            (botao.height - tamanhoTexto) / 2
        ),
        tamanhoTexto,
        WHITE
    );
}

// ==========================================================
// DESENHA PEÇA
// ==========================================================

void desenharPeca(
    peca &pecaAtual,
    float centroX,
    float centroY,
    float raio
)
{
    Color corPeca;

    if (pecaAtual.cor == BRANCA)
    {
        corPeca = Color{
            242,
            235,
            216,
            255
        };
    }
    else
    {
        corPeca = Color{
            42,
            40,
            38,
            255
        };
    }

    // ======================================================
    // SOMBRA DA PEÇA
    // ======================================================

    DrawCircle(
        (int)(centroX + 3),
        (int)(centroY + 5),
        raio,
        Fade(BLACK, 0.35f)
    );

    // ======================================================
    // PEÇA
    // ======================================================

    DrawCircle(
        (int)centroX,
        (int)centroY,
        raio,
        corPeca
    );

    // ======================================================
    // BORDA EXTERNA
    // ======================================================

    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio,
        MADEIRA
    );

    // ======================================================
    // DETALHE INTERNO
    // ======================================================

    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio - 6,
        Fade(MADEIRA, 0.45f)
    );

    // ======================================================
    // DAMA
    // ======================================================

    if (pecaAtual.tipo == DAMA)
    {
        DrawCircle(
            (int)centroX,
            (int)centroY,
            raio * 0.48f,
            DOURADO
        );

        DrawCircleLines(
            (int)centroX,
            (int)centroY,
            raio * 0.48f,
            Color{
                120,
                82,
                30,
                255
            }
        );

        const char* texto = "D";

        int tamanho = 27;

        int largura =
            MeasureText(texto, tamanho);

        DrawText(
            texto,
            (int)(centroX - largura / 2),
            (int)(centroY - tamanho / 2 - 2),
            tamanho,
            WHITE
        );
    }
}

// ==========================================================
// TELA DO JOGO
// ==========================================================

void telaJogo(const string &usuarioLogado)
{
    // ======================================================
    // INICIA PARTIDA
    // ======================================================

    iniciarPartida();

    // ======================================================
    // CONTROLE
    // ======================================================

    Cor jogadorAtual = BRANCA;

    bool pecaSelecionada = false;

    int linhaInicial = -1;
    int colunaInicial = -1;

    string mensagem =
        "Selecione uma peca para comecar.";

    // ======================================================
    // CONFIGURAÇÃO
    // ======================================================

    const float tamanhoTabuleiro = 540.0f;
    const float tamanhoCasa =
        tamanhoTabuleiro / 8.0f;

    while (!WindowShouldClose())
    {
        // ==================================================
        // DIMENSÕES
        // ==================================================

        int larguraTela =
            GetScreenWidth();

        int alturaTela =
            GetScreenHeight();

        // ==================================================
        // POSIÇÃO DO TABULEIRO
        // ==================================================

        float painelLateralX =
            larguraTela - 310.0f;

        float inicioX =
            45.0f;

        float inicioY =
            (alturaTela - tamanhoTabuleiro) / 2.0f + 15.0f;

        // ==================================================
        // ESC
        // ==================================================

        if (IsKeyPressed(KEY_ESCAPE))
        {
            return;
        }

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        Rectangle botaoVoltar = {
            painelLateralX + 35,
            alturaTela - 90,
            240,
            50
        };

        Vector2 mouse =
            GetMousePosition();

        bool hoverVoltar =
            CheckCollisionPointRec(
                mouse,
                botaoVoltar
            );

        // ==================================================
        // CLIQUE NO TABULEIRO
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // ==============================================
            // BOTÃO VOLTAR
            // ==============================================

            if (hoverVoltar)
            {
                return;
            }

            // ==============================================
            // TABULEIRO
            // ==============================================

            if (
                mouse.x >= inicioX &&
                mouse.x < inicioX + tamanhoTabuleiro &&
                mouse.y >= inicioY &&
                mouse.y < inicioY + tamanhoTabuleiro
            )
            {
                int coluna =
                    (int)(
                        (mouse.x - inicioX) /
                        tamanhoCasa
                    );

                int linha =
                    (int)(
                        (mouse.y - inicioY) /
                        tamanhoCasa
                    );

                // ==========================================
                // NENHUMA PEÇA SELECIONADA
                // ==========================================

                if (!pecaSelecionada)
                {
                    if (!tabuleiro[linha][coluna].ocupada)
                    {
                        mensagem =
                            "Essa casa esta vazia.";
                    }
                    else if (
                        tabuleiro[linha][coluna].cor
                        != jogadorAtual
                    )
                    {
                        mensagem =
                            "Essa peca nao pertence a voce.";
                    }
                    else
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        pecaSelecionada = true;

                        mensagem =
                            "Escolha a casa de destino.";
                    }
                }

                // ==========================================
                // PEÇA JÁ SELECIONADA
                // ==========================================

                else
                {
                    // --------------------------------------
                    // CLICOU EM OUTRA PEÇA DO MESMO JOGADOR
                    // --------------------------------------

                    if (
                        tabuleiro[linha][coluna].ocupada &&
                        tabuleiro[linha][coluna].cor
                        == jogadorAtual
                    )
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        mensagem =
                            "Nova peca selecionada.";
                    }

                    // --------------------------------------
                    // TENTA MOVIMENTAR
                    // --------------------------------------

                    else
                    {
                        bool jogadaRealizada =
                            realizarJogada(
                                linhaInicial,
                                colunaInicial,
                                linha,
                                coluna,
                                jogadorAtual
                            );

                        if (jogadaRealizada)
                        {
                            mensagem =
                                "Movimento realizado!";

                            // Troca jogador
                            if (jogadorAtual == BRANCA)
                            {
                                jogadorAtual = PRETA;
                            }
                            else
                            {
                                jogadorAtual = BRANCA;
                            }

                            pecaSelecionada = false;

                            linhaInicial = -1;
                            colunaInicial = -1;
                        }
                        else
                        {
                            mensagem =
                                "Movimento invalido.";
                        }
                    }
                }
            }
        }

        // ==================================================
        // DESENHO
        // ==================================================

        BeginDrawing();

        // ==================================================
        // FUNDO
        // ==================================================

        ClearBackground(FUNDO_JOGO);

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
                Fade(WHITE, 0.012f)
            );
        }

        // ==================================================
        // BARRA SUPERIOR
        // ==================================================

        DrawRectangle(
            0,
            0,
            larguraTela,
            72,
            MADEIRA
        );

        DrawRectangle(
            0,
            69,
            larguraTela,
            3,
            DOURADO
        );

        // ==================================================
        // TÍTULO
        // ==================================================

        DrawText(
            "DAMAS",
            30,
            14,
            34,
            Color{
                255,
                225,
                150,
                255
            }
        );

        DrawText(
            "PARTIDA",
            34,
            48,
            11,
            Fade(WHITE, 0.75f)
        );

        // ==================================================
        // USUÁRIO
        // ==================================================

        string textoUsuario =
            usuarioLogado;

        DrawText(
            textoUsuario.c_str(),
            230,
            27,
            20,
            CREME
        );

        DrawText(
            "Jogador",
            230,
            48,
            11,
            Fade(WHITE, 0.60f)
        );

        // ==================================================
        // PAINEL LATERAL
        // ==================================================

        DrawRectangle(
            (int)painelLateralX,
            72,
            310,
            alturaTela - 72,
            VERDE_PAINEL
        );

        // ==================================================
        // CARD DE TURNO
        // ==================================================

        Rectangle cardTurno = {
            painelLateralX + 35,
            105,
            240,
            105
        };

        DrawRectangleRounded(
            {
                cardTurno.x + 4,
                cardTurno.y + 5,
                cardTurno.width,
                cardTurno.height
            },
            0.08f,
            10,
            Fade(BLACK, 0.25f)
        );

        DrawRectangleRounded(
            cardTurno,
            0.08f,
            10,
            CREME
        );

        DrawText(
            "VEZ DO JOGADOR",
            (int)cardTurno.x + 20,
            (int)cardTurno.y + 15,
            13,
            Color{
                110,
                90,
                70,
                255
            }
        );

        // ==================================================
        // INDICADOR DA COR
        // ==================================================

        Color corTurno;

        if (jogadorAtual == BRANCA)
        {
            corTurno = Color{
                242,
                235,
                216,
                255
            };
        }
        else
        {
            corTurno = Color{
                42,
                40,
                38,
                255
            };
        }

        DrawCircle(
            (int)cardTurno.x + 38,
            (int)cardTurno.y + 63,
            18,
            corTurno
        );

        DrawCircleLines(
            (int)cardTurno.x + 38,
            (int)cardTurno.y + 63,
            18,
            MADEIRA
        );

        string textoTurno;

        if (jogadorAtual == BRANCA)
        {
            textoTurno = "Brancas";
        }
        else
        {
            textoTurno = "Pretas";
        }

        DrawText(
            textoTurno.c_str(),
            (int)cardTurno.x + 68,
            (int)cardTurno.y + 53,
            22,
            Color{
                77,
                47,
                27,
                255
            }
        );

        // ==================================================
        // ÁREA DE INSTRUÇÃO
        // ==================================================

        DrawText(
            "COMO JOGAR",
            (int)painelLateralX + 35,
            240,
            15,
            DOURADO
        );

        DrawText(
            "1. Selecione uma peca",
            (int)painelLateralX + 35,
            270,
            15,
            CREME
        );

        DrawText(
            "2. Escolha o destino",
            (int)painelLateralX + 35,
            296,
            15,
            CREME
        );

        DrawText(
            "3. Realize sua jogada",
            (int)painelLateralX + 35,
            322,
            15,
            CREME
        );

        // ==================================================
        // LINHA DECORATIVA
        // ==================================================

        DrawLine(
            (int)painelLateralX + 35,
            365,
            (int)painelLateralX + 275,
            365,
            Fade(DOURADO, 0.50f)
        );

        // ==================================================
        // MENSAGEM
        // ==================================================

        DrawText(
            "STATUS",
            (int)painelLateralX + 35,
            395,
            15,
            DOURADO
        );

        // Fundo da mensagem
        Rectangle areaMensagem = {
            painelLateralX + 35,
            425,
            240,
            80
        };

        DrawRectangleRounded(
            areaMensagem,
            0.08f,
            10,
            Fade(BLACK, 0.18f)
        );

        DrawText(
            mensagem.c_str(),
            (int)areaMensagem.x + 15,
            (int)areaMensagem.y + 18,
            15,
            CREME
        );

        // ==================================================
        // TABULEIRO - SOMBRA
        // ==================================================

        DrawRectangle(
            (int)inicioX + 10,
            (int)inicioY + 12,
            (int)tamanhoTabuleiro,
            (int)tamanhoTabuleiro,
            Fade(BLACK, 0.40f)
        );

        // ==================================================
        // MOLDURA DE MADEIRA
        // ==================================================

        float margemTabuleiro = 18.0f;

        DrawRectangleRounded(
            {
                inicioX - margemTabuleiro,
                inicioY - margemTabuleiro,
                tamanhoTabuleiro +
                    margemTabuleiro * 2,
                tamanhoTabuleiro +
                    margemTabuleiro * 2
            },
            0.025f,
            8,
            MADEIRA
        );

        // ==================================================
        // DETALHE DA MOLDURA
        // ==================================================

        DrawRectangleRoundedLines(
            {
                inicioX - margemTabuleiro + 4,
                inicioY - margemTabuleiro + 4,
                tamanhoTabuleiro +
                    margemTabuleiro * 2 - 8,
                tamanhoTabuleiro +
                    margemTabuleiro * 2 - 8
            },
            0.025f,
            8,
            MADEIRA_CLARA
        );

        // ==================================================
        // TABULEIRO
        // ==================================================

        for (int linha = 0; linha < TABTAM; linha++)
        {
            for (int coluna = 0; coluna < TABTAM; coluna++)
            {
                float x =
                    inicioX +
                    coluna * tamanhoCasa;

                float y =
                    inicioY +
                    linha * tamanhoCasa;

                // ==========================================
                // COR DA CASA
                // ==========================================

                Color corCasa;

                if ((linha + coluna) % 2 == 0)
                {
                    corCasa = CASA_CLARA;
                }
                else
                {
                    corCasa = CASA_ESCURA;
                }

                DrawRectangle(
                    (int)x,
                    (int)y,
                    (int)tamanhoCasa + 1,
                    (int)tamanhoCasa + 1,
                    corCasa
                );

                // ==========================================
                // CASA SELECIONADA
                // ==========================================

                if (
                    pecaSelecionada &&
                    linha == linhaInicial &&
                    coluna == colunaInicial
                )
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(DOURADO, 0.30f)
                    );

                    DrawRectangleLinesEx(
                        {
                            x + 4,
                            y + 4,
                            tamanhoCasa - 8,
                            tamanhoCasa - 8
                        },
                        5,
                        DOURADO
                    );
                }

                // ==========================================
                // CASA SOB O MOUSE
                // ==========================================

                if (
                    mouse.x >= x &&
                    mouse.x < x + tamanhoCasa &&
                    mouse.y >= y &&
                    mouse.y < y + tamanhoCasa
                )
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(WHITE, 0.08f)
                    );
                }

                // ==========================================
                // PEÇA
                // ==========================================

                if (tabuleiro[linha][coluna].ocupada)
                {
                    Vector2 centro = {
                        x + tamanhoCasa / 2.0f,
                        y + tamanhoCasa / 2.0f
                    };

                    desenharPeca(
                        tabuleiro[linha][coluna],
                        centro.x,
                        centro.y,
                        tamanhoCasa * 0.35f
                    );
                }
            }
        }

        // ==================================================
        // COORDENADAS DO TABULEIRO
        // ==================================================

        for (int i = 0; i < 8; i++)
        {
            string numero =
                to_string(i);

            DrawText(
                numero.c_str(),
                (int)(
                    inicioX - 13
                ),
                (int)(
                    inicioY +
                    i * tamanhoCasa +
                    30
                ),
                14,
                CREME
            );

            DrawText(
                numero.c_str(),
                (int)(
                    inicioX +
                    i * tamanhoCasa +
                    30
                ),
                (int)(
                    inicioY +
                    tamanhoTabuleiro +
                    5
                ),
                14,
                CREME
            );
        }

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        desenharBotaoJogo(
            botaoVoltar,
            "Voltar ao menu",
            MADEIRA,
            hoverVoltar
        );

        // ==================================================
        // RODAPÉ
        // ==================================================

        DrawText(
            "ESC - voltar ao menu",
            30,
            alturaTela - 25,
            13,
            Fade(WHITE, 0.55f)
        );

        EndDrawing();
    }
}