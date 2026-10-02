#include "movimentos.h"
#include <cmath>

void moverPeca(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
)
{
    // Guarda os dados da peça que está sendo movida
    Cor corPeca =
        tabuleiro[linhaInicial][colunaInicial].cor;

    TipoPeca tipoPeca =
        tabuleiro[linhaInicial][colunaInicial].tipo;

    // Verifica se é uma captura
    bool captura =
        abs(linhaFinal - linhaInicial) >= 2 &&
        abs(colunaFinal - colunaInicial) >= 2;

    // =====================================================
    // SE FOR CAPTURA, ENCONTRA A PEÇA NO CAMINHO
    // =====================================================

    if (captura)
    {
        int diferencaLinha =
            linhaFinal - linhaInicial;

        int diferencaColuna =
            colunaFinal - colunaInicial;

        int direcaoLinha =
            (diferencaLinha > 0) ? 1 : -1;

        int direcaoColuna =
            (diferencaColuna > 0) ? 1 : -1;

        int linhaAtual =
            linhaInicial + direcaoLinha;

        int colunaAtual =
            colunaInicial + direcaoColuna;

        while (linhaAtual != linhaFinal &&
               colunaAtual != colunaFinal)
        {
            if (tabuleiro[linhaAtual][colunaAtual].ocupada)
            {
                // Remove a peça capturada
                tabuleiro[linhaAtual][colunaAtual].ocupada = false;

                break;
            }

            linhaAtual += direcaoLinha;
            colunaAtual += direcaoColuna;
        }
    }

    // =====================================================
    // MOVE A PEÇA
    // =====================================================

    tabuleiro[linhaFinal][colunaFinal].cor = corPeca;
    tabuleiro[linhaFinal][colunaFinal].tipo = tipoPeca;
    tabuleiro[linhaFinal][colunaFinal].ocupada = true;

    tabuleiro[linhaFinal][colunaFinal].linha =
        linhaFinal;

    tabuleiro[linhaFinal][colunaFinal].coluna =
        colunaFinal;

    // Libera a posição antiga
    tabuleiro[linhaInicial][colunaInicial].ocupada = false;

    // =====================================================
    // PROMOÇÃO
    // =====================================================

    if (tipoPeca == NORMAL)
    {
        if (corPeca == BRANCA && linhaFinal == 7)
        {
            tornarDama(tabuleiro[linhaFinal][colunaFinal]);
        }

        if (corPeca == PRETA && linhaFinal == 0)
        {
            tornarDama(tabuleiro[linhaFinal][colunaFinal]);
        }
    }
}

bool podeMoverSimples(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
)
{
    peca origem = tabuleiro[linhaInicial][colunaInicial];
    peca destino = tabuleiro[linhaFinal][colunaFinal];

    // A origem precisa ter uma peça
    if (!origem.ocupada)
    {
        return false;
    }

    // O destino precisa estar vazio
    if (destino.ocupada)
    {
        return false;
    }

    int diferencaLinha = linhaFinal - linhaInicial;
    int diferencaColuna = colunaFinal - colunaInicial;

    int distanciaLinha = abs(diferencaLinha);
    int distanciaColuna = abs(diferencaColuna);

    // =====================================================
    // PEÇA NORMAL
    // =====================================================

    if (origem.tipo == NORMAL)
    {
        // Movimento simples é exatamente uma casa na diagonal
        if (distanciaLinha != 1 || distanciaColuna != 1)
        {
            return false;
        }

        // Brancas andam para baixo
        if (origem.cor == BRANCA &&
            diferencaLinha == 1)
        {
            return true;
        }

        // Pretas andam para cima
        if (origem.cor == PRETA &&
            diferencaLinha == -1)
        {
            return true;
        }

        return false;
    }

    // =====================================================
    // DAMA
    // =====================================================

    if (origem.tipo == DAMA)
    {
        // A dama precisa andar na diagonal
        if (distanciaLinha != distanciaColuna)
        {
            return false;
        }

        // A dama precisa andar pelo menos uma casa
        if (distanciaLinha == 0)
        {
            return false;
        }

        // Verifica se existe alguma peça no caminho
        int direcaoLinha =
            (diferencaLinha > 0) ? 1 : -1;

        int direcaoColuna =
            (diferencaColuna > 0) ? 1 : -1;

        int linhaAtual = linhaInicial + direcaoLinha;
        int colunaAtual = colunaInicial + direcaoColuna;

        while (linhaAtual != linhaFinal &&
               colunaAtual != colunaFinal)
        {
            if (tabuleiro[linhaAtual][colunaAtual].ocupada)
            {
                return false;
            }

            linhaAtual += direcaoLinha;
            colunaAtual += direcaoColuna;
        }

        return true;
    }

    return false;
}

bool podeCapturar(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal
)
{
    peca origem = tabuleiro[linhaInicial][colunaInicial];
    peca destino = tabuleiro[linhaFinal][colunaFinal];

    // A origem precisa ter uma peça
    if (!origem.ocupada)
    {
        return false;
    }

    // O destino precisa estar vazio
    if (destino.ocupada)
    {
        return false;
    }

    int diferencaLinha = linhaFinal - linhaInicial;
    int diferencaColuna = colunaFinal - colunaInicial;

    int distanciaLinha = abs(diferencaLinha);
    int distanciaColuna = abs(diferencaColuna);

    // A jogada precisa ser diagonal
    if (distanciaLinha != distanciaColuna)
    {
        return false;
    }

    // Não pode ficar na mesma posição
    if (distanciaLinha == 0)
    {
        return false;
    }

    // =====================================================
    // PEÇA NORMAL
    // =====================================================

    if (origem.tipo == NORMAL)
    {
        // Uma peça normal captura pulando exatamente
        // duas casas na diagonal.
        if (distanciaLinha != 2)
        {
            return false;
        }

        int linhaMeio =
            (linhaInicial + linhaFinal) / 2;

        int colunaMeio =
            (colunaInicial + colunaFinal) / 2;

        peca meio = tabuleiro[linhaMeio][colunaMeio];

        // Precisa existir uma peça adversária no meio
        if (!meio.ocupada)
        {
            return false;
        }

        if (meio.cor == origem.cor)
        {
            return false;
        }

        // IMPORTANTE:
        // Não verificamos mais a direção.
        //
        // Portanto:
        // BRANCA pode capturar para frente ou para trás.
        // PRETA pode capturar para frente ou para trás.

        return true;
    }

    // =====================================================
    // DAMA
    // =====================================================

    if (origem.tipo == DAMA)
    {
        int direcaoLinha =
            (diferencaLinha > 0) ? 1 : -1;

        int direcaoColuna =
            (diferencaColuna > 0) ? 1 : -1;

        int linhaAtual =
            linhaInicial + direcaoLinha;

        int colunaAtual =
            colunaInicial + direcaoColuna;

        int quantidadePecas = 0;

        // Percorre todas as casas entre origem e destino
        while (linhaAtual != linhaFinal &&
               colunaAtual != colunaFinal)
        {
            if (tabuleiro[linhaAtual][colunaAtual].ocupada)
            {
                // Se for nossa própria peça,
                // a dama não pode passar por ela.
                if (tabuleiro[linhaAtual][colunaAtual].cor == origem.cor)
                {
                    return false;
                }

                quantidadePecas++;
            }

            linhaAtual += direcaoLinha;
            colunaAtual += direcaoColuna;
        }

        // Para uma captura válida precisa existir
        // exatamente UMA peça adversária no caminho.
        if (quantidadePecas != 1)
        {
            return false;
        }

        return true;
    }

    return false;
}

bool existeCapturaDisponivel(
    peca tabuleiro[TABTAM][TABTAM],
    Cor jogador
)
{
    for (int lInicial = 0; lInicial < TABTAM; lInicial++)
    {
        for (int cInicial = 0; cInicial < TABTAM; cInicial++)
        {
            if (!tabuleiro[lInicial][cInicial].ocupada ||
                tabuleiro[lInicial][cInicial].cor != jogador)
            {
                continue;
            }

            for (int lFinal = 0; lFinal < TABTAM; lFinal++)
            {
                for (int cFinal = 0; cFinal < TABTAM; cFinal++)
                {
                    if (podeCapturar(tabuleiro, lInicial, cInicial, lFinal, cFinal))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool validarJogada(
    peca tabuleiro[TABTAM][TABTAM],
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
)
{
    // Se existe captura no tabuleiro, o jogador é obrigado a capturar
    if (existeCapturaDisponivel(tabuleiro, jogador))
    {
        return podeCapturar(tabuleiro, linhaInicial, colunaInicial,
                            linhaFinal, colunaFinal);
    }

    return podeMoverSimples(tabuleiro, linhaInicial, colunaInicial,
                            linhaFinal, colunaFinal);
}
