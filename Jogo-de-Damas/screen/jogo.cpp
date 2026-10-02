
#include "jogo.h"

#include <raylib.h>
#include <string>

#include "../damas/jogo.h"
#include "../damas/tabuleiro.h"
#include "../damas/peca.h"
#include "../damas/maquina.h"

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

    DrawRectangleRounded(
        botao, 0.18f, 12, corBotao);

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

    // Sombra
    DrawCircle(
        (int)(centroX + 3),
        (int)(centroY + 5),
        raio,
        Fade(BLACK, 0.35f));

    // Corpo da peça
    DrawCircle(
        (int)centroX,
        (int)centroY,
        raio,
        corPeca);

    // Borda externa
    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio,
        MADEIRA);

    // Detalhe interno
    DrawCircleLines(
        (int)centroX,
        (int)centroY,
        raio - 6,
        Fade(MADEIRA, 0.45f));

    // Dama
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

void telaJogo(const string &usuarioLogado)
{
    // ======================================================
    // INICIA PARTIDA
    // ======================================================

    iniciarPartida();

    // ======================================================
    // CONTROLE DA PARTIDA
    // ======================================================

    Cor jogadorAtual = BRANCA;

    bool pecaSelecionada = false;
    bool partidaEncerrada = false;

    int linhaInicial = -1;
    int colunaInicial = -1;

    string mensagem =
        "Selecione uma peca para comecar.";

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
        // ==================================================
        // DIMENSÕES
        // ==================================================

        int larguraTela = GetScreenWidth();
        int alturaTela = GetScreenHeight();

        // ==================================================
        // POSIÇÃO DO TABULEIRO
        // ==================================================

        float painelLateralX = larguraTela - 310.0f;
        float inicioX = 45.0f;

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
        // CLIQUE DO MOUSE
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
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
                mouse.x < inicioX + tamanhoTabuleiro &&
                mouse.y >= inicioY &&
                mouse.y < inicioY + tamanhoTabuleiro)
            {
                int coluna = (int)(
                    (mouse.x - inicioX) / tamanhoCasa);

                int linha = (int)(
                    (mouse.y - inicioY) / tamanhoCasa);

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
                        mensagem = "Essa peca nao pertence a voce.";
                    }
                    else
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;
                        pecaSelecionada = true;

                        mensagem = "Escolha a casa de destino.";
                    }
                }

                // ==========================================
                // PEÇA JÁ SELECIONADA
                // ==========================================

                else
                {
                    // Clicou em outra peça branca
                    if (
                        tabuleiro[linha][coluna].ocupada &&
                        tabuleiro[linha][coluna].cor == BRANCA)
                    {
                        linhaInicial = linha;
                        colunaInicial = coluna;

                        mensagem = "Nova peca selecionada.";
                    }
                    else
                    {
                        // Tenta realizar a jogada da pessoa
                        bool jogadaRealizada = realizarJogada(
                            linhaInicial,
                            colunaInicial,
                            linha,
                            coluna,
                            BRANCA);

                        if (jogadaRealizada)
                        {
                            pecaSelecionada = false;
                            linhaInicial = -1;
                            colunaInicial = -1;

                            mensagem = "Voce jogou!";

                            // ==================================
                            // PREPARA O TURNO DA MÁQUINA
                            // ==================================

                            jogadorAtual = PRETA;

                            mensagem = "A maquina esta pensando...";

                            // Se a jogada da pessoa terminou a partida, a máquina não joga.
                            if (!partida.emAndamento)
                            {
                                mensagem = "Fim da partida!";
                            }

                            // Escolhe a jogada, masnão altera o tabuleiro.
                            else if (escolherJogadaMaquina(
                                    PRETA,
                                    jogadaMaquina))
                            {
                                // Guarda uma cópia da peça para desenhá-la durante a animação.
                                pecaAnimada = tabuleiro[
                                    jogadaMaquina.linhaInicial]
                                    [jogadaMaquina.colunaInicial];

                                tempoAnimacao = 0.0f;
                                animandoMaquina = true;
                            }
                            else
                            {
                                mensagem =
                                    "Voce venceu! A maquina nao tem jogadas.";

                                partidaEncerrada = true;
                            }
                        }
                        else
                        {
                            mensagem = "Movimento invalido.";
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
        // DESENHO
        // ==================================================

        BeginDrawing();

        ClearBackground(FUNDO_JOGO);

        // ==================================================
        // TEXTURA DO FUNDO
        // ==================================================

        for (int y = 0; y < alturaTela; y += 40)
        {
            DrawLine(
                0, y,
                larguraTela, y,
                Fade(WHITE, 0.012f));
        }

        // ==================================================
        // BARRA SUPERIOR
        // ==================================================

        DrawRectangle(
            0, 0,
            larguraTela, 72,
            MADEIRA);

        DrawRectangle(
            0, 69,
            larguraTela, 3,
            DOURADO);

        // ==================================================
        // TÍTULO
        // ==================================================

        DrawText(
            "DAMAS",
            30, 14,
            34,
            Color{255, 225, 150, 255});

        DrawText(
            "PARTIDA",
            34, 48,
            11,
            Fade(WHITE, 0.75f));

        // ==================================================
        // USUÁRIO
        // ==================================================

        string textoUsuario = usuarioLogado;

        DrawText(
            textoUsuario.c_str(),
            230, 27,
            20,
            CREME);

        DrawText(
            "Jogador",
            230, 48,
            11,
            Fade(WHITE, 0.60f));

        // ==================================================
        // PAINEL LATERAL
        // ==================================================

        DrawRectangle(
            (int)painelLateralX,
            72,
            310,
            alturaTela - 72,
            VERDE_PAINEL);

        // ==================================================
        // CARD DE TURNO
        // ==================================================

        Rectangle cardTurno = {
            painelLateralX + 35,
            105,
            240,
            105};

        DrawRectangleRounded(
            {cardTurno.x + 4,
             cardTurno.y + 5,
             cardTurno.width,
             cardTurno.height},
            0.08f, 10,
            Fade(BLACK, 0.25f));

        DrawRectangleRounded(
            cardTurno,
            0.08f, 10,
            CREME);

        DrawText(
            "VEZ DO JOGADOR",
            (int)cardTurno.x + 20,
            (int)cardTurno.y + 15,
            13,
            Color{110, 90, 70, 255});

        // Indicador da cor
        Color corTurno;

        if (jogadorAtual == BRANCA)
        {
            corTurno = Color{242, 235, 216, 255};
        }
        else
        {
            corTurno = Color{42, 40, 38, 255};
        }

        DrawCircle(
            (int)cardTurno.x + 38,
            (int)cardTurno.y + 63,
            18,
            corTurno);

        DrawCircleLines(
            (int)cardTurno.x + 38,
            (int)cardTurno.y + 63,
            18,
            MADEIRA);

        string textoTurno =
            (jogadorAtual == BRANCA) ? "Brancas" : "Pretas";

        DrawText(
            textoTurno.c_str(),
            (int)cardTurno.x + 68,
            (int)cardTurno.y + 53,
            22,
            Color{77, 47, 27, 255});

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

        for (int linha = 0; linha < TABTAM; linha++)
        {
            for (int coluna = 0; coluna < TABTAM; coluna++)
            {
                float x = inicioX + coluna * tamanhoCasa;
                float y = inicioY + linha * tamanhoCasa;

                // Cor da casa
                Color corCasa =
                    ((linha + coluna) % 2 == 0)
                    ? CASA_CLARA
                    : CASA_ESCURA;

                DrawRectangle(
                    (int)x,
                    (int)y,
                    (int)tamanhoCasa + 1,
                    (int)tamanhoCasa + 1,
                    corCasa);

                // Casa selecionada
                if (
                    pecaSelecionada &&
                    linha == linhaInicial &&
                    coluna == colunaInicial)
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(DOURADO, 0.30f));

                    DrawRectangleLinesEx(
                        {x + 4, y + 4,
                         tamanhoCasa - 8,
                         tamanhoCasa - 8},
                        5,
                        DOURADO);
                }

                // Realce da casa sob o mouse
                if (
                    mouse.x >= x &&
                    mouse.x < x + tamanhoCasa &&
                    mouse.y >= y &&
                    mouse.y < y + tamanhoCasa)
                {
                    DrawRectangle(
                        (int)x,
                        (int)y,
                        (int)tamanhoCasa,
                        (int)tamanhoCasa,
                        Fade(WHITE, 0.08f));
                }

                // Durante a animação, não desenha a peça
                // na posição original. Ela será desenhada
                // separadamente na posição interpolada.
                bool ehOrigemAnimada =
                    animandoMaquina &&
                    linha == jogadaMaquina.linhaInicial &&
                    coluna == jogadaMaquina.colunaInicial;

                if (
                    tabuleiro[linha][coluna].ocupada &&
                    !ehOrigemAnimada)
                {
                    Vector2 centro = {
                        x + tamanhoCasa / 2.0f,
                        y + tamanhoCasa / 2.0f};

                    desenharPeca(
                        tabuleiro[linha][coluna],
                        centro.x,
                        centro.y,
                        tamanhoCasa * 0.35f);
                }
            }
        }

        // ==================================================
        // ANIMAÇÃO: DESENHA A PEÇA EM MOVIMENTO
        // ==================================================

        if (animandoMaquina)
        {
            // Progresso entre 0.0 e 1.0
            float progresso =
                tempoAnimacao / duracaoAnimacao;

            if (progresso > 1.0f)
            {
                progresso = 1.0f;
            }

            // Centro da casa inicial
            float xInicial =
                inicioX +
                jogadaMaquina.colunaInicial * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float yInicial =
                inicioY +
                jogadaMaquina.linhaInicial * tamanhoCasa +
                tamanhoCasa / 2.0f;

            // Centro da casa final
            float xFinal =
                inicioX +
                jogadaMaquina.colunaFinal * tamanhoCasa +
                tamanhoCasa / 2.0f;

            float yFinal =
                inicioY +
                jogadaMaquina.linhaFinal * tamanhoCasa +
                tamanhoCasa / 2.0f;

            // Interpolação da posição ao longo do tempo
            float centroX =
                xInicial + (xFinal - xInicial) * progresso;

            float centroY =
                yInicial + (yFinal - yInicial) * progresso;

            desenharPeca(
                pecaAnimada,
                centroX,
                centroY,
                tamanhoCasa * 0.35f);
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
                14,
                CREME);

            DrawText(
                numero.c_str(),
                (int)(inicioX + i * tamanhoCasa + 30),
                (int)(inicioY + tamanhoTabuleiro + 5),
                14,
                CREME);
        }

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        desenharBotaoJogo(
            botaoVoltar,
            "Voltar ao menu",
            MADEIRA,
            hoverVoltar);

        // ==================================================
        // RODAPÉ
        // ==================================================

        DrawText(
            "ESC - voltar ao menu",
            30,
            alturaTela - 25,
            13,
            Fade(WHITE, 0.55f));

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
            // Se acabou porque a máquina ficou sem jogadas,
            // a pessoa (brancas) venceu.
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
