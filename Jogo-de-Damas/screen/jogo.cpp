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

<<<<<<< Updated upstream
        // ==========================================
=======
        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        Rectangle botaoVoltar = {
            painelLateralX + 35,
            (float)(alturaTela - 90),
            240,
            50};

        Vector2 mouse = GetMousePosition();

        bool hoverVoltar = CheckCollisionPointRec(
            mouse,
            botaoVoltar);

        // ==================================================
        // POP-UP DE FIM DE PARTIDA (posição)
        // ==================================================

        bool fimDePartida =
            !partida.emAndamento || partidaEncerrada;

        Rectangle cardVitoria = {
            larguraTela / 2.0f - 210,
            alturaTela / 2.0f - 130,
            420,
            260};

        Rectangle botaoVitoria = {
            cardVitoria.x + 90,
            cardVitoria.y + cardVitoria.height - 80,
            240,
            50};

        bool hoverVitoria =
            fimDePartida &&
            CheckCollisionPointRec(mouse, botaoVitoria);

        // ==================================================
>>>>>>> Stashed changes
        // CLIQUE DO MOUSE
        // ==========================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
<<<<<<< Updated upstream
            Vector2 mouse = GetMousePosition();

            // Verifica se o clique aconteceu dentro do tabuleiro
            if (mouse.x >= inicioX &&
=======
            // Botão voltar (ou botão do pop-up de fim de partida)
            if (hoverVoltar || hoverVitoria)
            {
                return;
            }

            // A pessoa só pode jogar quando for sua vez.
            // Durante a animação, jogadorAtual é PRETA.
            if (
                partida.emAndamento &&
                !partidaEncerrada &&
                !animandoMaquina &&
                jogadorAtual == BRANCA &&
                mouse.x >= inicioX &&
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
                            // Troca o jogador
                            if (jogadorAtual == BRANCA)
=======
                            mensagem = "Voce jogou!";

                            // ==================================
                            // PREPARA O TURNO DA MÁQUINA
                            // ==================================

                            jogadorAtual = PRETA;

                            mensagem = "A maquina esta pensando...";

                            // Se a jogada da pessoa terminou a partida
                            // (12 pontos), a máquina não joga.
                            if (!partida.emAndamento)
                            {
                                mensagem = "Fim da partida!";
                            }

                            // Escolhe a jogada, mas ainda não
                            // altera o tabuleiro.
                            else if (escolherJogadaMaquina(
                                    PRETA,
                                    jogadaMaquina))
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
        // ==========================================
=======
        // ==================================================
        // ATUALIZA A ANIMAÇÃO DA MÁQUINA
        // ==================================================

        if (animandoMaquina)
        {
            tempoAnimacao += GetFrameTime();

            if (tempoAnimacao >= duracaoAnimacao)
            {
                // Só altera o tabuleiro quando a animação termina.
                bool maquinaJogou = realizarJogada(
                    jogadaMaquina.linhaInicial,
                    jogadaMaquina.colunaInicial,
                    jogadaMaquina.linhaFinal,
                    jogadaMaquina.colunaFinal,
                    PRETA);

                animandoMaquina = false;

                if (maquinaJogou)
                {
                    jogadorAtual = BRANCA;

                    if (partida.emAndamento)
                    {
                        mensagem = "Sua vez! Selecione uma peca.";
                    }
                    else
                    {
                        mensagem = "Fim da partida!";
                    }
                }
                else
                {
                    mensagem =
                        "Nao foi possivel realizar a jogada.";

                    partidaEncerrada = true;
                }
            }
        }

        // ==================================================
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
        // ==========================================
        // TABULEIRO
        // ==========================================
=======
        // ==================================================
        // INSTRUÇÕES
        // ==================================================

        DrawText(
            "COMO JOGAR",
            (int)painelLateralX + 35,
            240, 15, DOURADO);

        DrawText(
            "1. Selecione uma peca",
            (int)painelLateralX + 35,
            270, 15, CREME);

        DrawText(
            "2. Escolha o destino",
            (int)painelLateralX + 35,
            296, 15, CREME);

        DrawText(
            "3. Realize sua jogada",
            (int)painelLateralX + 35,
            322, 15, CREME);

        // Linha decorativa
        DrawLine(
            (int)painelLateralX + 35,
            365,
            (int)painelLateralX + 275,
            365,
            Fade(DOURADO, 0.50f));

        // ==================================================
        // STATUS
        // ==================================================

        DrawText(
            "STATUS",
            (int)painelLateralX + 35,
            395, 15, DOURADO);

        Rectangle areaMensagem = {
            painelLateralX + 35,
            425,
            240,
            80};

        DrawRectangleRounded(
            areaMensagem,
            0.08f, 10,
            Fade(BLACK, 0.18f));

        DrawText(
            mensagem.c_str(),
            (int)areaMensagem.x + 15,
            (int)areaMensagem.y + 18,
            15, CREME);

        // ==================================================
        // PLACAR
        // ==================================================

        DrawText(
            "PLACAR",
            (int)painelLateralX + 35,
            525, 15, DOURADO);

        Rectangle areaPlacar = {
            painelLateralX + 35,
            550,
            240,
            50};

        DrawRectangleRounded(
            areaPlacar,
            0.08f, 10,
            Fade(BLACK, 0.18f));

        // Brancas (metade esquerda)
        DrawCircle(
            (int)areaPlacar.x + 20,
            (int)areaPlacar.y + 25,
            9,
            Color{245, 235, 216, 255});

        DrawText(
            TextFormat("Brancas: %d", ganharPontos(partida, BRANCA)),
            (int)areaPlacar.x + 36,
            (int)areaPlacar.y + 18,
            14, CREME);

        // Pretas (metade direita)
        DrawCircle(
            (int)areaPlacar.x + 140,
            (int)areaPlacar.y + 25,
            9,
            Color{42, 40, 38, 255});

        DrawCircleLines(
            (int)areaPlacar.x + 140,
            (int)areaPlacar.y + 25,
            9,
            Fade(WHITE, 0.40f));

        DrawText(
            TextFormat("Pretas: %d", ganharPontos(partida, PRETA)),
            (int)areaPlacar.x + 156,
            (int)areaPlacar.y + 18,
            14, CREME);

        // ==================================================
        // TABULEIRO: SOMBRA
        // ==================================================

        DrawRectangle(
            (int)inicioX + 10,
            (int)inicioY + 12,
            (int)tamanhoTabuleiro,
            (int)tamanhoTabuleiro,
            Fade(BLACK, 0.40f));

        // ==================================================
        // MOLDURA DE MADEIRA
        // ==================================================

        float margemTabuleiro = 18.0f;

        DrawRectangleRounded(
            {inicioX - margemTabuleiro,
             inicioY - margemTabuleiro,
             tamanhoTabuleiro + margemTabuleiro * 2,
             tamanhoTabuleiro + margemTabuleiro * 2},
            0.025f, 8,
            MADEIRA);

        DrawRectangleRoundedLines(
            {inicioX - margemTabuleiro + 4,
             inicioY - margemTabuleiro + 4,
             tamanhoTabuleiro + margemTabuleiro * 2 - 8,
             tamanhoTabuleiro + margemTabuleiro * 2 - 8},
            0.025f, 8,
            MADEIRA_CLARA);

        // ==================================================
        // TABULEIRO E PEÇAS
        // ==================================================
>>>>>>> Stashed changes

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

        // ==================================================
        // POP-UP DE FIM DE PARTIDA
        // ==================================================

        if (!partida.emAndamento || partidaEncerrada)
        {
            // Escurece o fundo
            DrawRectangle(
                0, 0,
                larguraTela, alturaTela,
                Fade(BLACK, 0.65f));

            // Sombra e card
            DrawRectangleRounded(
                {cardVitoria.x + 5,
                 cardVitoria.y + 6,
                 cardVitoria.width,
                 cardVitoria.height},
                0.08f, 10,
                Fade(BLACK, 0.35f));

            DrawRectangleRounded(cardVitoria, 0.08f, 10, CREME);

            DrawRectangleRoundedLines(
                cardVitoria, 0.08f, 10, DOURADO);

            Color corTextoEscuro = {77, 47, 27, 255};

            // Subtítulo
            const char *subtitulo = "FIM DA PARTIDA";

            DrawText(
                subtitulo,
                (int)(cardVitoria.x +
                      (cardVitoria.width - MeasureText(subtitulo, 14)) / 2),
                (int)cardVitoria.y + 28,
                14,
                Color{110, 90, 70, 255});

            // Vencedor
            // Se a partida acabou por pontos, usa vencedor(partida).
            // Se acabou porque a máquina ficou sem jogadas, as brancas vencem.
            bool brancasVenceram =
                partida.emAndamento
                    ? true
                    : (vencedor(partida) == BRANCA);

            const char *titulo =
                brancasVenceram
                    ? "Brancas venceram!"
                    : "Pretas venceram!";

            DrawText(
                titulo,
                (int)(cardVitoria.x +
                      (cardVitoria.width - MeasureText(titulo, 32)) / 2),
                (int)cardVitoria.y + 65,
                32,
                corTextoEscuro);

            // Placar final
            const char *placarFinal = TextFormat(
                "Brancas %d  x  %d Pretas",
                ganharPontos(partida, BRANCA),
                ganharPontos(partida, PRETA));

            DrawText(
                placarFinal,
                (int)(cardVitoria.x +
                      (cardVitoria.width - MeasureText(placarFinal, 20)) / 2),
                (int)cardVitoria.y + 125,
                20,
                corTextoEscuro);

            // Botão
            desenharBotaoJogo(
                botaoVitoria,
                "Voltar ao menu",
                MADEIRA,
                hoverVitoria);
        }

        EndDrawing();
    }
}
