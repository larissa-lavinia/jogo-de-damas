#include <raylib.h>
#include <string>

#include "cadastro.h"
#include "../usuario/usuario.h"

using namespace std;

// ==========================================================
// CORES
// ==========================================================

const Color FUNDO_CADASTRO = {
    20, 54, 45, 255};

const Color VERDE_PAINEL = {
    27, 67, 55, 255};

const Color MADEIRA = {
    91, 55, 32, 255};

const Color MADEIRA_CLARA = {
    125, 78, 44, 255};

const Color DOURADO = {
    218, 158, 55, 255};

const Color DOURADO_CLARO = {
    255, 225, 150, 255};

const Color CREME = {
    246, 239, 220, 255};

const Color TEXTO = {
    77, 47, 27, 255};

const Color BORDA_CAMPO = {
    190, 174, 145, 255};

// ==========================================================
// DESENHA CAMPO
// ==========================================================

void desenharCampoCadastro(
    Rectangle campo,
    const char *texto,
    const char *placeholder,
    bool ativo)
{
    // ======================================================
    // SOMBRA
    // ======================================================

    DrawRectangleRounded(
        {campo.x + 3,
         campo.y + 4,
         campo.width,
         campo.height},
        0.12f,
        12,
        Fade(BLACK, 0.18f));

    // ======================================================
    // FUNDO
    // ======================================================

    DrawRectangleRounded(
        campo,
        0.12f,
        12,
        Color{
            255,
            252,
            243,
            255});

    // ======================================================
    // BORDA
    // ======================================================

    Color corBorda;

    if (ativo)
    {
        corBorda = DOURADO;
    }
    else
    {
        corBorda = BORDA_CAMPO;
    }

    DrawRectangleRoundedLines(
        campo,
        0.12f,
        12,
        corBorda);

    // ======================================================
    // TEXTO
    // ======================================================

    if (texto[0] != '\0')
    {
        DrawText(
            texto,
            (int)campo.x + 18,
            (int)campo.y + 14,
            19,
            TEXTO);
    }
    else
    {
        DrawText(
            placeholder,
            (int)campo.x + 18,
            (int)campo.y + 14,
            19,
            Color{
                145,
                135,
                120,
                255});
    }
}

// ==========================================================
// DESENHA BOTÃO
// ==========================================================

void desenharBotaoCadastro(
    Rectangle botao,
    const char *texto,
    Color cor,
    bool hover)
{
    // ======================================================
    // SOMBRA
    // ======================================================

    DrawRectangleRounded(
        {botao.x + 4,
         botao.y + 5,
         botao.width,
         botao.height},
        0.18f,
        12,
        Fade(BLACK, 0.30f));

    // ======================================================
    // COR DO BOTÃO
    // ======================================================

    Color corBotao = cor;

    if (hover)
    {
        corBotao = Color{
            (unsigned char)(cor.r + 15),
            (unsigned char)(cor.g + 15),
            (unsigned char)(cor.b + 15),
            cor.a};
    }

    // ======================================================
    // CORPO
    // ======================================================

    DrawRectangleRounded(
        botao,
        0.18f,
        12,
        corBotao);

    // ======================================================
    // BORDA
    // ======================================================

    DrawRectangleRoundedLines(
        botao,
        0.18f,
        12,
        Fade(WHITE, 0.18f));

    // ======================================================
    // TEXTO
    // ======================================================

    int tamanhoTexto = 18;

    int larguraTexto =
        MeasureText(texto, tamanhoTexto);

    DrawText(
        texto,
        (int)(botao.x +
              (botao.width - larguraTexto) / 2),
        (int)(botao.y +
              (botao.height - tamanhoTexto) / 2),
        tamanhoTexto,
        WHITE);
}

// ==========================================================
// TELA DE CADASTRO
// ==========================================================

AcaoTelaCadastro telaCadastro()
{
    // ======================================================
    // DADOS
    // ======================================================

    string nickname = "";
    string senha = "";

    bool digitandoNickname = false;
    bool digitandoSenha = false;

    string mensagem = "";

    bool mensagemSucesso = false;
    bool voltar = false;

    // ======================================================
    // LOOP
    // ======================================================

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
        // CARD CENTRAL
        // ==================================================

        float larguraCard = 560.0f;
        float alturaCard = 610.0f;

        float cardX =
            (larguraTela - larguraCard) / 2.0f;

        float cardY =
            (alturaTela - alturaCard) / 2.0f + 28.0f;

        Rectangle card = {
            cardX,
            cardY,
            larguraCard,
            alturaCard};

        // ==================================================
        // CAMPOS
        // ==================================================

        Rectangle campoNickname = {
            cardX + 60,
            cardY + 180,
            440,
            55};

        Rectangle campoSenha = {
            cardX + 60,
            cardY + 290,
            440,
            55};

        Rectangle botaoCadastrar = {
            cardX + 60,
            cardY + 390,
            270,
            55};

        Rectangle botaoVoltar = {
            cardX + 350,
            cardY + 390,
            150,
            55};

        // ==================================================
        // MOUSE
        // ==================================================

        Vector2 mouse =
            GetMousePosition();

        bool hoverCadastrar =
            CheckCollisionPointRec(
                mouse,
                botaoCadastrar);

        bool hoverVoltar =
            CheckCollisionPointRec(
                mouse,
                botaoVoltar);

        // ==================================================
        // ENTRADA DO TECLADO
        // ==================================================

        int tecla = GetCharPressed();

        while (tecla > 0)
        {
            // ----------------------------------------------
            // NICKNAME
            // ----------------------------------------------

            if (digitandoNickname)
            {
                if (nickname.size() < 49)
                {
                    nickname += (char)tecla;
                    mensagem = "";
                    mensagemSucesso = false;
                }
            }

            // ----------------------------------------------
            // SENHA
            // ----------------------------------------------

            if (digitandoSenha)
            {
                if (senha.size() < 49)
                {
                    senha += (char)tecla;
                    mensagem = "";
                    mensagemSucesso = false;
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
        // ESC
        // ==================================================

        if (IsKeyPressed(KEY_ESCAPE))
        {
            voltar = true;
        }

        // ==================================================
        // CLIQUES
        // ==================================================

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // ==============================================
            // NICKNAME
            // ==============================================

            if (
                CheckCollisionPointRec(
                    mouse,
                    campoNickname))
            {
                digitandoNickname = true;
                digitandoSenha = false;

                mensagem = "";
                mensagemSucesso = false;
            }

            // ==============================================
            // SENHA
            // ==============================================

            else if (
                CheckCollisionPointRec(
                    mouse,
                    campoSenha))
            {
                digitandoNickname = false;
                digitandoSenha = true;

                mensagem = "";
                mensagemSucesso = false;
            }

            // ==============================================
            // CADASTRAR
            // ==============================================

            else if (
                CheckCollisionPointRec(
                    mouse,
                    botaoCadastrar))
            {
                digitandoNickname = false;
                digitandoSenha = false;

                // ------------------------------------------
                // VALIDAÇÃO
                // ------------------------------------------

                if (
                    nickname.empty() ||
                    senha.empty())
                {
                    mensagem =
                        "Preencha todos os campos!";

                    mensagemSucesso = false;
                }
                else
                {
                    // --------------------------------------
                    // CRIA USUÁRIO
                    // --------------------------------------

                    Usuario usuario;

                    usuario.id = 1;
                    usuario.nickname = nickname;
                    usuario.senha = senha;

                    // --------------------------------------
                    // SALVA
                    // --------------------------------------

                    mensagem =
                        salvarUsuario(usuario);

                    // --------------------------------------
                    // SUCESSO
                    // --------------------------------------

                    if (
                        mensagem ==
                        "Usuario cadastrado com sucesso!")
                    {
                        nickname = "";
                        senha = "";

                        mensagemSucesso = true;
                    }
                    else
                    {
                        mensagemSucesso = false;
                    }
                }
            }

            // ==============================================
            // VOLTAR
            // ==============================================

            else if (
                CheckCollisionPointRec(
                    mouse,
                    botaoVoltar))
            {
                digitandoNickname = false;
                digitandoSenha = false;

                voltar = true;
            }

            // ==============================================
            // CLIQUE FORA
            // ==============================================

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

        for (size_t i = 0; i < senha.size(); i++)
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

        ClearBackground(FUNDO_CADASTRO);

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
                Fade(WHITE, 0.012f));
        }

        // ==================================================
        // BARRA SUPERIOR
        // ==================================================

        DrawRectangle(
            0,
            0,
            larguraTela,
            72,
            MADEIRA);

        DrawRectangle(
            0,
            69,
            larguraTela,
            3,
            DOURADO);

        // ==================================================
        // LOGO
        // ==================================================

        DrawText(
            "DAMAS",
            30,
            14,
            34,
            DOURADO_CLARO);

        DrawText(
            "CADASTRO",
            34,
            48,
            11,
            Fade(WHITE, 0.75f));

        // ==================================================
        // SOMBRA DO CARD
        // ==================================================

        DrawRectangleRounded(
            {card.x + 8,
             card.y + 10,
             card.width,
             card.height},
            0.035f,
            12,
            Fade(BLACK, 0.35f));

        // ==================================================
        // CARD
        // ==================================================

        DrawRectangleRounded(
            card,
            0.035f,
            12,
            CREME);

        // ==================================================
        // BORDA DO CARD
        // ==================================================

        DrawRectangleRoundedLines(
            card,
            0.035f,
            12,
            MADEIRA_CLARA);

        // ==================================================
        // TÍTULO
        // ==================================================

        const char *titulo =
            "Criar conta";

        int tamanhoTitulo = 32;

        int larguraTitulo =
            MeasureText(
                titulo,
                tamanhoTitulo);

        DrawText(
            titulo,
            (int)(cardX +
                  (larguraCard - larguraTitulo) / 2),
            (int)cardY + 48,
            tamanhoTitulo,
            TEXTO);

        // ==================================================
        // SUBTÍTULO
        // ==================================================

        const char *subtitulo =
            "Cadastre-se para começar a jogar";

        int tamanhoSubtitulo = 16;

        int larguraSubtitulo =
            MeasureText(
                subtitulo,
                tamanhoSubtitulo);

        DrawText(
            subtitulo,
            (int)(cardX +
                  (larguraCard - larguraSubtitulo) / 2),
            (int)cardY + 92,
            tamanhoSubtitulo,
            Color{
                120,
                105,
                85,
                255});

        // ==================================================
        // LINHA DECORATIVA
        // ==================================================

        DrawLine(
            (int)cardX + 60,
            (int)cardY + 135,
            (int)cardX + 500,
            (int)cardY + 135,
            Fade(MADEIRA_CLARA, 0.45f));

        // ==================================================
        // LABEL NICKNAME
        // ==================================================

        DrawText(
            "Nickname",
            (int)campoNickname.x,
            (int)campoNickname.y - 27,
            15,
            TEXTO);

        // ==================================================
        // CAMPO NICKNAME
        // ==================================================

        desenharCampoCadastro(
            campoNickname,
            nickname.c_str(),
            "Digite seu nickname",
            digitandoNickname);

        // ==================================================
        // CURSOR NICKNAME
        // ==================================================

        if (
            digitandoNickname &&
            ((int)GetTime() % 2 == 0))
        {
            int larguraTexto =
                MeasureText(
                    nickname.c_str(),
                    19);

            DrawLine(
                (int)campoNickname.x +
                    18 +
                    larguraTexto,
                (int)campoNickname.y + 14,
                (int)campoNickname.x +
                    18 +
                    larguraTexto,
                (int)campoNickname.y + 39,
                TEXTO);
        }

        // ==================================================
        // LABEL SENHA
        // ==================================================

        DrawText(
            "Senha",
            (int)campoSenha.x,
            (int)campoSenha.y - 27,
            15,
            TEXTO);

        // ==================================================
        // CAMPO SENHA
        // ==================================================

        desenharCampoCadastro(
            campoSenha,
            senhaOculta.c_str(),
            "Digite sua senha",
            digitandoSenha);

        // ==================================================
        // CURSOR SENHA
        // ==================================================

        if (
            digitandoSenha &&
            ((int)GetTime() % 2 == 0))
        {
            int larguraTexto =
                MeasureText(
                    senhaOculta.c_str(),
                    19);

            DrawLine(
                (int)campoSenha.x +
                    18 +
                    larguraTexto,
                (int)campoSenha.y + 14,
                (int)campoSenha.x +
                    18 +
                    larguraTexto,
                (int)campoSenha.y + 39,
                TEXTO);
        }

        // ==================================================
        // BOTÃO CADASTRAR
        // ==================================================

        desenharBotaoCadastro(
            botaoCadastrar,
            "Criar conta",
            MADEIRA,
            hoverCadastrar);

        // ==================================================
        // BOTÃO VOLTAR
        // ==================================================

        desenharBotaoCadastro(
            botaoVoltar,
            "Voltar",
            VERDE_PAINEL,
            hoverVoltar);

        // ==================================================
        // MENSAGEM
        // ==================================================

        if (!mensagem.empty())
        {
            Color corMensagem;

            if (mensagemSucesso)
            {
                corMensagem = Color{
                    39,
                    105,
                    72,
                    255};
            }
            else
            {
                corMensagem = Color{
                    170,
                    55,
                    45,
                    255};
            }

            // Fundo da mensagem
            Rectangle areaMensagem = {
                cardX + 60,
                cardY + 470,
                440,
                55};

            DrawRectangleRounded(
                areaMensagem,
                0.10f,
                10,
                Fade(corMensagem, 0.10f));

            DrawRectangleRoundedLines(
                areaMensagem,
                0.10f,
                10,
                Fade(corMensagem, 0.40f));

            int larguraMensagem =
                MeasureText(
                    mensagem.c_str(),
                    15);

            DrawText(
                mensagem.c_str(),
                (int)(areaMensagem.x +
                      (areaMensagem.width -
                       larguraMensagem) /
                          2),
                (int)areaMensagem.y + 18,
                15,
                corMensagem);
        }

        // ==================================================
        // RODAPÉ
        // ==================================================

        DrawText(
            "ESC - voltar",
            30,
            alturaTela - 25,
            13,
            Fade(WHITE, 0.55f));

        // ==================================================
        // FINALIZA FRAME
        // ==================================================

        EndDrawing();

        if (voltar)
        {
            return AcaoTelaCadastro::VOLTAR;
        }
    }

    return AcaoTelaCadastro::VOLTAR;
}
