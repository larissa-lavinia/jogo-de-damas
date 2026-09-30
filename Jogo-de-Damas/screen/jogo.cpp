#include "jogo.h"

#include <raylib.h>
#include <string>

#include "../damas/jogo.h"
#include "../damas/tabuleiro.h"
#include "../damas/peca.h"

using namespace std;

void telaJogo(const string &usuarioLogado)
{
    // ==========================================
    // INICIA UMA NOVA PARTIDA
    // ==========================================

    iniciarPartida();

    // ==========================================
    // CONTROLE DA PARTIDA
    // ==========================================

    Cor jogadorAtual = BRANCA;

    bool pecaSelecionada = false;

    int linhaInicial = -1;
    int colunaInicial = -1;

    string mensagem = "";

    // ==========================================
    // CONFIGURAÇÃO DO TABULEIRO
    // ==========================================

    const float tamanhoTabuleiro = 640.0f;
    const float tamanhoCasa = tamanhoTabuleiro / 8.0f;

    while (!WindowShouldClose())
    {
        // ==========================================
        // POSIÇÃO DO TABULEIRO
        // ==========================================

        float inicioX =
            (GetScreenWidth() - tamanhoTabuleiro) / 2.0f;

        float inicioY = 55.0f;

        // ==========================================
        // TECLA ESC
        // ==========================================

        if (IsKeyPressed(KEY_ESCAPE))
        {
            return;
        }

        // ==========================================
        // CLIQUE DO MOUSE
        // ==========================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse = GetMousePosition();

            // Verifica se o clique aconteceu dentro do tabuleiro
            if (mouse.x >= inicioX &&
                mouse.x < inicioX + tamanhoTabuleiro &&
                mouse.y >= inicioY &&
                mouse.y < inicioY + tamanhoTabuleiro)
            {
                int coluna =
                    (int)((mouse.x - inicioX) / tamanhoCasa);

                int linha =
                    (int)((mouse.y - inicioY) / tamanhoCasa);

                // ==========================================
                // SELEÇÃO / MOVIMENTO
                // ==========================================

                if (!pecaSelecionada)
                {
                    // Nenhuma peça selecionada ainda

                    if (!tabuleiro[linha][coluna].ocupada)
                    {
                        mensagem = "Selecione uma peca.";
                    }
                    else if (tabuleiro[linha][coluna].cor != jogadorAtual)
                    {
                        mensagem = "Essa peca nao pertence ao jogador da vez.";
                    }
                    else
                    {
                        // Seleciona a peça
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        pecaSelecionada = true;

                        mensagem = "Escolha onde deseja mover.";
                    }
                }
                else
                {
                    // ==========================================
                    // JÁ EXISTE UMA PEÇA SELECIONADA
                    // ==========================================

                    // Se clicou em outra peça do mesmo jogador,
                    // troca a seleção para essa nova peça.
                    if (
                        tabuleiro[linha][coluna].ocupada &&
                        tabuleiro[linha][coluna].cor == jogadorAtual)
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        mensagem = "Nova peca selecionada.";
                    }
                    else
                    {
                        // ==========================================
                        // TENTA REALIZAR O MOVIMENTO
                        // ==========================================

                        bool jogadaRealizada = realizarJogada(
                            linhaInicial,
                            colunaInicial,
                            linha,
                            coluna,
                            jogadorAtual);

                        if (jogadaRealizada)
                        {
                            mensagem = "Movimento realizado!";

                            // Troca o jogador
                            if (jogadorAtual == BRANCA)
                            {
                                jogadorAtual = PRETA;
                            }
                            else
                            {
                                jogadorAtual = BRANCA;
                            }

                            // Remove a seleção
                            pecaSelecionada = false;

                            linhaInicial = -1;
                            colunaInicial = -1;
                        }
                        else
                        {
                            mensagem = "Movimento invalido.";
                        }
                    }
                }
            }
        }

        // ==========================================
        // DESENHO
        // ==========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // ==========================================
        // TÍTULO
        // ==========================================

        DrawText(
            "JOGO DE DAMAS",
            20,
            15,
            28,
            DARKGRAY);

        // ==========================================
        // USUÁRIO
        // ==========================================

        string textoUsuario =
            "Jogador: " + usuarioLogado;

        DrawText(
            textoUsuario.c_str(),
            250,
            20,
            20,
            DARKGRAY);

        // ==========================================
        // VEZ DO JOGADOR
        // ==========================================

        string textoTurno;

        if (jogadorAtual == BRANCA)
        {
            textoTurno = "Vez das brancas";
        }
        else
        {
            textoTurno = "Vez das pretas";
        }

        DrawText(
            textoTurno.c_str(),
            900,
            20,
            20,
            DARKGRAY);

        // ==========================================
        // TABULEIRO
        // ==========================================

        for (int linha = 0; linha < TABTAM; linha++)
        {
            for (int coluna = 0; coluna < TABTAM; coluna++)
            {
                float x =
                    inicioX + coluna * tamanhoCasa;

                float y =
                    inicioY + linha * tamanhoCasa;

                // ==========================================
                // COR DA CASA
                // ==========================================

                Color corCasa;

                if ((linha + coluna) % 2 == 0)
                {
                    corCasa = RAYWHITE;
                }
                else
                {
                    corCasa = DARKGRAY;
                }

                DrawRectangle(
                    (int)x,
                    (int)y,
                    (int)tamanhoCasa,
                    (int)tamanhoCasa,
                    corCasa);

                // ==========================================
                // CASA SELECIONADA
                // ==========================================

                if (
                    pecaSelecionada &&
                    linha == linhaInicial &&
                    coluna == colunaInicial)
                {
                    DrawRectangleLinesEx(
                        {x + 3,
                         y + 3,
                         tamanhoCasa - 6,
                         tamanhoCasa - 6},
                        5,
                        YELLOW);
                }

                // ==========================================
                // DESENHA A PEÇA
                // ==========================================

                if (tabuleiro[linha][coluna].ocupada)
                {
                    Color corPeca;

                    if (tabuleiro[linha][coluna].cor == BRANCA)
                    {
                        corPeca = BEIGE;
                    }
                    else
                    {
                        corPeca = BLACK;
                    }

                    Vector2 centro = {
                        x + tamanhoCasa / 2.0f,
                        y + tamanhoCasa / 2.0f};

                    DrawCircle(
                        (int)centro.x,
                        (int)centro.y,
                        tamanhoCasa * 0.35f,
                        corPeca);

                    // Borda da peça
                    DrawCircleLines(
                        (int)centro.x,
                        (int)centro.y,
                        tamanhoCasa * 0.35f,
                        DARKGRAY);

                    // ==========================================
                    // IDENTIFICA DAMA
                    // ==========================================

                    if (tabuleiro[linha][coluna].tipo == DAMA)
                    {
                        DrawText(
                            "D",
                            (int)(centro.x - 10),
                            (int)(centro.y - 15),
                            30,
                            RED);
                    }
                }
            }
        }

        // ==========================================
        // MENSAGEM
        // ==========================================

        if (!mensagem.empty())
        {
            DrawText(
                mensagem.c_str(),
                20,
                GetScreenHeight() - 50,
                20,
                DARKGRAY);
        }

        // ==========================================
        // INSTRUÇÃO
        // ==========================================

        DrawText(
            "ESC - voltar ao menu",
            20,
            GetScreenHeight() - 25,
            16,
            GRAY);

        EndDrawing();
    }
}