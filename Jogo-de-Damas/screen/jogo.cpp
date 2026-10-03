
#include "jogo.h"

#include <raylib.h>
#include <string>

#include "../damas/jogo.h"
#include "../damas/tabuleiro.h"
#include "../damas/peca.h"
#include "../damas/maquina.h"
#include "../damas/salvamento.h"
#include "../audio/audio.h"

using namespace std;

// ==========================================================
// CORES DA INTERFACE
// ==========================================================

const Color FUNDO_JOGO = {20, 54, 45, 255};
const Color VERDE_PAINEL = {27, 67, 55, 255};
const Color MADEIRA = {91, 55, 32, 255};
const Color MADEIRA_CLARA = {125, 78, 44, 255};
const Color DOURADO = {218, 158, 55, 255};
const Color CREME = {246, 239, 220, 255};
const Color CASA_CLARA = {239, 216, 174, 255};
const Color CASA_ESCURA = {117, 76, 48, 255};

// ==========================================================
// DESENHA BOTÃO
// ==========================================================

void desenharBotaoJogo(
    Rectangle botao,
    const char *texto,
    Color cor,
    bool hover)
{
    DrawRectangleRounded(
        {botao.x + 4, botao.y + 5,
         botao.width, botao.height},
        0.18f, 12, Fade(BLACK, 0.30f));

    Color corBotao = cor;

    if (hover)
    {
        corBotao = Color{
            (unsigned char)(cor.r + 15),
            (unsigned char)(cor.g + 15),
            (unsigned char)(cor.b + 15),
            cor.a};
    }

    DrawRectangleRounded(botao, 0.18f, 12, corBotao);

    DrawRectangleRoundedLines(
        botao, 0.18f, 12,
        Fade(WHITE, 0.15f));

    int tamanhoTexto = 18;
    int larguraTexto = MeasureText(texto, tamanhoTexto);

    DrawText(
        texto,
        (int)(botao.x + (botao.width - larguraTexto) / 2),
        (int)(botao.y + (botao.height - tamanhoTexto) / 2),
        tamanhoTexto,
        WHITE);
}

// ==========================================================
// DESENHA PEÇA
// ==========================================================

void desenharPeca(
    peca &pecaAtual,
    float centroX,
    float centroY,
    float raio)
{
    Color corPeca;

    if (pecaAtual.cor == BRANCA)
    {
        corPeca = Color{242, 235, 216, 255};
    }
    else
    {
        corPeca = Color{42, 40, 38, 255};
    }

    DrawCircle(
        (int)(centroX + 3),
        (int)(centroY + 5),
        raio,
        Fade(BLACK, 0.35f));

    DrawCircle(
        (int)centroX,
        (int)centroY,
        raio,
        corPeca);

    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio,
        MADEIRA);

    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio - 6,
        Fade(MADEIRA, 0.45f));

    if (pecaAtual.tipo == DAMA)
    {
        DrawCircle(
            (int)centroX,
            (int)centroY,
            raio * 0.48f,
            DOURADO);

        DrawCircleLines(
            (int)centroX,
            (int)centroY,
            raio * 0.48f,
            Color{120, 82, 30, 255});

        const char *texto = "D";
        int tamanho = 27;
        int largura = MeasureText(texto, tamanho);

        DrawText(
            texto,
            (int)(centroX - largura / 2),
            (int)(centroY - tamanho / 2 - 2),
            tamanho,
            WHITE);
    }
}

// ==========================================================
// TELA DO JOGO
// ==========================================================

void telaJogo(bool continuarPartida)
{
    // ======================================================
    // INICIA OU CARREGA A PARTIDA
    // ======================================================

    Cor jogadorAtual = BRANCA;

    if (continuarPartida)
    {
        if (!carregarPartida(jogadorAtual))
        {
            // Se o arquivo não existir ou estiver inválido,
            // inicia uma nova partida.
            iniciarPartida();
            jogadorAtual = BRANCA;
        }
    }
    else
    {
        iniciarPartida();
        jogadorAtual = BRANCA;

        // Descarta o salvamento da partida anterior.
        excluirPartidaSalva();
    }

    partida.vezDoJogador = jogadorAtual;

    // ======================================================
    // CONTROLE DA PARTIDA
    // ======================================================

    bool pecaSelecionada = false;
    bool partidaEncerrada = false;

    int linhaInicial = -1;
    int colunaInicial = -1;

    string mensagem = "Selecione uma peca para comecar.";

    // ======================================================
    // CONTROLE DA ANIMAÇÃO DA MÁQUINA
    // ======================================================

    bool animandoMaquina = false;

    float tempoAnimacao = 0.0f;
    const float duracaoAnimacao = 0.7f;

    Jogada jogadaMaquina;
    peca pecaAnimada;

    // ======================================================
    // CONFIGURAÇÃO DO TABULEIRO
    // ======================================================

    const float tamanhoTabuleiro = 540.0f;
    const float tamanhoCasa = tamanhoTabuleiro / 8.0f;

    while (!WindowShouldClose())
    {
        int larguraTela = GetScreenWidth();
        int alturaTela = GetScreenHeight();

        float painelLateralX = larguraTela - 310.0f;
        float inicioX = 45.0f;

        float inicioY =
            (alturaTela - tamanhoTabuleiro) / 2.0f + 15.0f;

        // ==================================================
        // ESC: SALVA E VOLTA AO MENU
        // ==================================================

        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (partida.emAndamento && !partidaEncerrada)
            {
                salvarPartida(jogadorAtual);
            }
            else
            {
                excluirPartidaSalva();
            }

            return;
        }

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        Rectangle botaoVoltar = {
            painelLateralX + 35,
            (float)(alturaTela - 90),
            240,
            50
        };

        Vector2 mouse = GetMousePosition();

        bool hoverVoltar = CheckCollisionPointRec(
            mouse,
            botaoVoltar
        );

        // ==================================================
        // POP-UP DE FIM DE PARTIDA
        // ==================================================

        bool fimDePartida =
            !partida.emAndamento || partidaEncerrada;

        Rectangle cardVitoria = {
            larguraTela / 2.0f - 210,
            alturaTela / 2.0f - 130,
            420,
            260
        };

        Rectangle botaoVitoria = {
            cardVitoria.x + 90,
            cardVitoria.y + cardVitoria.height - 80,
            240,
            50
        };

        bool hoverVitoria =
            fimDePartida &&
            CheckCollisionPointRec(mouse, botaoVitoria);

        // ==================================================
        // RETOMA AUTOMATICAMENTE O TURNO DA MÁQUINA
        // ==================================================

        if (partida.emAndamento &&
            !partidaEncerrada &&
            jogadorAtual == PRETA &&
            !animandoMaquina)
        {
            if (escolherJogadaMaquina(PRETA, jogadaMaquina))
            {
                pecaAnimada = tabuleiro
                    [jogadaMaquina.linhaInicial]
                    [jogadaMaquina.colunaInicial];

                tempoAnimacao = 0.0f;
                animandoMaquina = true;

                mensagem = "A maquina esta pensando...";
            }
            else
            {
                mensagem =
                    "Voce venceu! A maquina nao tem jogadas.";

                partidaEncerrada = true;
                excluirPartidaSalva();
            }
        }

        // ==================================================
        // CLIQUE DO MOUSE
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hoverVoltar || hoverVitoria)
            {
                if (partida.emAndamento && !partidaEncerrada)
                {
                    salvarPartida(jogadorAtual);
                }
                else
                {
                    excluirPartidaSalva();
                }

                return;
            }

            // A pessoa só joga com as brancas.
            if (partida.emAndamento &&
                !partidaEncerrada &&
                !animandoMaquina &&
                jogadorAtual == BRANCA &&
                mouse.x >= inicioX &&
                mouse.x < inicioX + tamanhoTabuleiro &&
                mouse.y >= inicioY &&
                mouse.y < inicioY + tamanhoTabuleiro)
            {
                int coluna = (int)(
                    (mouse.x - inicioX) / tamanhoCasa
                );

                int linha = (int)(
                    (mouse.y - inicioY) / tamanhoCasa
                );

                // ==========================================
                // NENHUMA PEÇA SELECIONADA
                // ==========================================

                if (!pecaSelecionada)
                {
                    if (!tabuleiro[linha][coluna].ocupada)
                    {
                        mensagem = "Essa casa esta vazia.";
                    }
                    else if (
                        tabuleiro[linha][coluna].cor != BRANCA)
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
                    // Permite selecionar outra peça branca.
                    if (tabuleiro[linha][coluna].ocupada &&
                        tabuleiro[linha][coluna].cor == BRANCA)
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        mensagem = "Nova peca selecionada.";
                    }
                    else
                    {
                        bool jogadaRealizada = realizarJogada(
                            linhaInicial,
                            colunaInicial,
                            linha,
                            coluna,
                            BRANCA
                        );

                        if (jogadaRealizada)
                        {
                            pecaSelecionada = false;
                            linhaInicial = -1;
                            colunaInicial = -1;

                            mensagem = "Voce jogou!";

                            jogadorAtual = PRETA;
                            partida.vezDoJogador = PRETA;

                            if (!partida.emAndamento)
                            {
                                excluirPartidaSalva();
                                mensagem = "Fim da partida!";
                                tocarSomVitoria();
                            }
                            else
                            {
                                // Salva a posição depois da jogada
                                // humana, antes da resposta da máquina.
                                salvarPartida(PRETA);

                                if (escolherJogadaMaquina(
                                        PRETA,
                                        jogadaMaquina))
                                {
                                    pecaAnimada = tabuleiro
                                        [jogadaMaquina.linhaInicial]
                                        [jogadaMaquina.colunaInicial];

                                    tempoAnimacao = 0.0f;
                                    animandoMaquina = true;

                                    mensagem =
                                        "A maquina esta pensando...";
                                }
                                else
                                {
                                    mensagem =
                                        "Voce venceu! A maquina nao tem jogadas.";
                                tocarSomVitoria();
                                    partidaEncerrada = true;
                                    excluirPartidaSalva();
                                }
                            }
                        }
                        else
                        {
                            mensagem = "Movimento invalido.";
                            tocarSomErro();
                        }
                    }
                }
            }
        }

        // ==================================================
        // ATUALIZA A ANIMAÇÃO DA MÁQUINA
        // ==================================================

        if (animandoMaquina)
        {
            tempoAnimacao += GetFrameTime();

            if (tempoAnimacao >= duracaoAnimacao)
            {
                bool maquinaJogou = realizarJogada(
                    jogadaMaquina.linhaInicial,
                    jogadaMaquina.colunaInicial,
                    jogadaMaquina.linhaFinal,
                    jogadaMaquina.colunaFinal,
                    PRETA
                );

                animandoMaquina = false;

                if (maquinaJogou)
                {
                    jogadorAtual = BRANCA;
                    partida.vezDoJogador = BRANCA;

                    if (partida.emAndamento)
                    {
                        // Salva o estado após a jogada da máquina.
                        salvarPartida(BRANCA);

                        mensagem =
                            "Sua vez! Selecione uma peca.";
                    }
                    else
                    {
                        excluirPartidaSalva();
                        mensagem = "Fim da partida!";
                        tocarSomVitoria();
                    }
                }
                else
                {
                    mensagem =
                        "Nao foi possivel realizar a jogada.";

                    partidaEncerrada = true;
                    excluirPartidaSalva();
                }
            }
        }

        // ==================================================
        // DESENHO
        // ==================================================

        BeginDrawing();

        ClearBackground(FUNDO_JOGO);

        for (int y = 0; y < alturaTela; y += 40)
        {
            DrawLine(
                0, y,
                larguraTela, y,
                Fade(WHITE, 0.012f)
            );
        }

        DrawRectangle(
            0, 0,
            larguraTela, 72,
            MADEIRA
        );

        DrawRectangle(
            0, 69,
            larguraTela, 3,
            DOURADO
        );

        DrawText(
            "DAMAS",
            30, 14,
            34,
            Color{255, 225, 150, 255}
        );

        DrawText(
            "PARTIDA",
            34, 48,
            11,
            Fade(WHITE, 0.75f)
        );

        // Identificação genérica, sem login.
        DrawText("Jogador", 230, 27, 20, CREME);
        DrawText("Brancas", 230, 48, 11, Fade(WHITE, 0.60f));

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
            {cardTurno.x + 4, cardTurno.y + 5,
             cardTurno.width, cardTurno.height},
            0.08f, 10, Fade(BLACK, 0.25f)
        );

        DrawRectangleRounded(
            cardTurno, 0.08f, 10, CREME
        );

        DrawText(
            "VEZ DO JOGADOR",
            (int)cardTurno.x + 20,
            (int)cardTurno.y + 15,
            13,
            Color{110, 90, 70, 255}
        );

        Color corTurno =
            (jogadorAtual == BRANCA)
                ? Color{242, 235, 216, 255}
                : Color{42, 40, 38, 255};

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

        string textoTurno =
            (jogadorAtual == BRANCA) ? "Brancas" : "Pretas";

        DrawText(
            textoTurno.c_str(),
            (int)cardTurno.x + 68,
            (int)cardTurno.y + 53,
            22,
            Color{77, 47, 27, 255}
        );

        // ==================================================
        // INSTRUÇÕES
        // ==================================================

        DrawText(
            "COMO JOGAR",
            (int)painelLateralX + 35,
            240, 15, DOURADO
        );

        DrawText(
            "1. Selecione uma peca",
            (int)painelLateralX + 35,
            270, 15, CREME
        );

        DrawText(
            "2. Escolha o destino",
            (int)painelLateralX + 35,
            296, 15, CREME
        );

        DrawText(
            "3. Realize sua jogada",
            (int)painelLateralX + 35,
            322, 15, CREME
        );

        DrawLine(
            (int)painelLateralX + 35,
            365,
            (int)painelLateralX + 275,
            365,
            Fade(DOURADO, 0.50f)
        );

        // ==================================================
        // STATUS
        // ==================================================

        DrawText(
            "STATUS",
            (int)painelLateralX + 35,
            395, 15, DOURADO
        );

        Rectangle areaMensagem = {
            painelLateralX + 35,
            425,
            240,
            80
        };

        DrawRectangleRounded(
            areaMensagem,
            0.08f, 10,
            Fade(BLACK, 0.18f)
        );

        DrawText(
            mensagem.c_str(),
            (int)areaMensagem.x + 15,
            (int)areaMensagem.y + 18,
            15, CREME
        );

        // ==================================================
        // PLACAR
        // ==================================================

        DrawText(
            "PLACAR",
            (int)painelLateralX + 35,
            525, 15, DOURADO
        );

        Rectangle areaPlacar = {
            painelLateralX + 35,
            550,
            240,
            50
        };

        DrawRectangleRounded(
            areaPlacar,
            0.08f, 10,
            Fade(BLACK, 0.18f)
        );

        DrawCircle(
            (int)areaPlacar.x + 20,
            (int)areaPlacar.y + 25,
            9,
            Color{245, 235, 216, 255}
        );

        DrawText(
            TextFormat(
                "Brancas: %d",
                ganharPontos(partida, BRANCA)
            ),
            (int)areaPlacar.x + 36,
            (int)areaPlacar.y + 18,
            14, CREME
        );

        DrawCircle(
            (int)areaPlacar.x + 140,
            (int)areaPlacar.y + 25,
            9,
            Color{42, 40, 38, 255}
        );

        DrawCircleLines(
            (int)areaPlacar.x + 140,
            (int)areaPlacar.y + 25,
            9,
            Fade(WHITE, 0.40f)
        );

        DrawText(
            TextFormat(
                "Pretas: %d",
                ganharPontos(partida, PRETA)
            ),
            (int)areaPlacar.x + 156,
            (int)areaPlacar.y + 18,
            14, CREME
        );

        // ==================================================
        // SOMBRA E MOLDURA DO TABULEIRO
        // ==================================================

        DrawRectangle(
            (int)inicioX + 10,
            (int)inicioY + 12,
            (int)tamanhoTabuleiro,
            (int)tamanhoTabuleiro,
            Fade(BLACK, 0.40f)
        );

        float margemTabuleiro = 18.0f;

        DrawRectangleRounded(
            {inicioX - margemTabuleiro,
             inicioY - margemTabuleiro,
             tamanhoTabuleiro + margemTabuleiro * 2,
             tamanhoTabuleiro + margemTabuleiro * 2},
            0.025f, 8, MADEIRA
        );

        DrawRectangleRoundedLines(
            {inicioX - margemTabuleiro + 4,
             inicioY - margemTabuleiro + 4,
             tamanhoTabuleiro + margemTabuleiro * 2 - 8,
             tamanhoTabuleiro + margemTabuleiro * 2 - 8},
            0.025f, 8, MADEIRA_CLARA
        );

        // ==================================================
        // TABULEIRO E PEÇAS
        // ==================================================

        for (int linha = 0; linha < TABTAM; linha++)
        {
            for (int coluna = 0; coluna < TABTAM; coluna++)
            {
                float x = inicioX + coluna * tamanhoCasa;
                float y = inicioY + linha * tamanhoCasa;

                Color corCasa =
                    ((linha + coluna) % 2 == 0)
                        ? CASA_CLARA
                        : CASA_ESCURA;

                DrawRectangle(
                    (int)x,
                    (int)y,
                    (int)tamanhoCasa + 1,
                    (int)tamanhoCasa + 1,
                    corCasa
                );

                if (pecaSelecionada &&
                    linha == linhaInicial &&
                    coluna == colunaInicial)
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(DOURADO, 0.30f)
                    );

                    DrawRectangleLinesEx(
                        {x + 4, y + 4,
                         tamanhoCasa - 8,
                         tamanhoCasa - 8},
                        5, DOURADO
                    );
                }

                if (mouse.x >= x &&
                    mouse.x < x + tamanhoCasa &&
                    mouse.y >= y &&
                    mouse.y < y + tamanhoCasa)
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(WHITE, 0.08f)
                    );
                }

                bool ehOrigemAnimada =
                    animandoMaquina &&
                    linha == jogadaMaquina.linhaInicial &&
                    coluna == jogadaMaquina.colunaInicial;

                if (tabuleiro[linha][coluna].ocupada &&
                    !ehOrigemAnimada)
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
        // ANIMAÇÃO DA PEÇA DA MÁQUINA
        // ==================================================

        if (animandoMaquina)
        {
            float progresso = tempoAnimacao / duracaoAnimacao;

            if (progresso > 1.0f)
            {
                progresso = 1.0f;
            }

            float xInicial =
                inicioX +
                jogadaMaquina.colunaInicial * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float yInicial =
                inicioY +
                jogadaMaquina.linhaInicial * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float xFinal =
                inicioX +
                jogadaMaquina.colunaFinal * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float yFinal =
                inicioY +
                jogadaMaquina.linhaFinal * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float centroX =
                xInicial + (xFinal - xInicial) * progresso;

            float centroY =
                yInicial + (yFinal - yInicial) * progresso;

            desenharPeca(
                pecaAnimada,
                centroX,
                centroY,
                tamanhoCasa * 0.35f
            );
        }

        // ==================================================
        // COORDENADAS DO TABULEIRO
        // ==================================================

        for (int i = 0; i < 8; i++)
        {
            string numero = to_string(i);

            DrawText(
                numero.c_str(),
                (int)(inicioX - 13),
                (int)(inicioY + i * tamanhoCasa + 30),
                14, CREME
            );

            DrawText(
                numero.c_str(),
                (int)(inicioX + i * tamanhoCasa + 30),
                (int)(inicioY + tamanhoTabuleiro + 5),
                14, CREME
            );
        }

        // ==================================================
        // BOTÃO VOLTAR E RODAPÉ
        // ==================================================

        desenharBotaoJogo(
            botaoVoltar,
            "Voltar ao menu",
            MADEIRA,
            hoverVoltar
        );

        DrawText(
            "ESC - voltar ao menu",
            30,
            alturaTela - 25,
            13,
            Fade(WHITE, 0.55f)
        );

        // ==================================================
        // POP-UP DE FIM DE PARTIDA
        // ==================================================

        if (!partida.emAndamento || partidaEncerrada)
        {
            DrawRectangle(
                0, 0,
                larguraTela, alturaTela,
                Fade(BLACK, 0.65f)
            );

            DrawRectangleRounded(
                {cardVitoria.x + 5,
                 cardVitoria.y + 6,
                 cardVitoria.width,
                 cardVitoria.height},
                0.08f, 10, Fade(BLACK, 0.35f)
            );

            DrawRectangleRounded(
                cardVitoria,
                0.08f, 10, CREME
            );

            DrawRectangleRoundedLines(
                cardVitoria,
                0.08f, 10, DOURADO
            );

            Color corTextoEscuro = {77, 47, 27, 255};

            const char *subtitulo = "FIM DA PARTIDA";

            DrawText(
                subtitulo,
                (int)(cardVitoria.x +
                      (cardVitoria.width -
                       MeasureText(subtitulo, 14)) / 2),
                (int)cardVitoria.y + 28,
                14,
                Color{110, 90, 70, 255}
            );

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
                      (cardVitoria.width -
                       MeasureText(titulo, 32)) / 2),
                (int)cardVitoria.y + 65,
                32,
                corTextoEscuro
            );

            const char *placarFinal = TextFormat(
                "Brancas %d  x  %d Pretas",
                ganharPontos(partida, BRANCA),
                ganharPontos(partida, PRETA)
            );

            DrawText(
                placarFinal,
                (int)(cardVitoria.x +
                      (cardVitoria.width -
                       MeasureText(placarFinal, 20)) / 2),
                (int)cardVitoria.y + 125,
                20,
                corTextoEscuro
            );

            desenharBotaoJogo(
                botaoVitoria,
                "Voltar ao menu",
                MADEIRA,
                hoverVitoria
            );
        }

        EndDrawing();
    }

    // ======================================================
    // SALVA AO FECHAR A JANELA
    // ======================================================

    if (partida.emAndamento && !partidaEncerrada)
    {
        salvarPartida(jogadorAtual);
    }
    else
    {
        excluirPartidaSalva();
    }
}