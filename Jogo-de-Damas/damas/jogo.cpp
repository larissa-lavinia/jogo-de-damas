#include "jogo.h"

#include "movimentos.h"
#include "tabuleiro.h"

void iniciarPartida()
{
    inicializarTabuleiro(tabuleiro);
}

bool realizarJogada(
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
)
{
    // Verifica se as posições estão dentro do tabuleiro
    if (linhaInicial < 0 || linhaInicial >= TABTAM ||
        colunaInicial < 0 || colunaInicial >= TABTAM ||
        linhaFinal < 0 || linhaFinal >= TABTAM ||
        colunaFinal < 0 || colunaFinal >= TABTAM)
    {
        return false;
    }

    // Verifica se existe uma peça na posição inicial
    if (!tabuleiro[linhaInicial][colunaInicial].ocupada)
    {
        return false;
    }

    // Verifica se a peça pertence ao jogador da vez
    if (tabuleiro[linhaInicial][colunaInicial].cor != jogador)
    {
        return false;
    }

    // Verifica se o movimento segue as regras
    if (!validarJogada(
            tabuleiro,
            linhaInicial,
            colunaInicial,
            linhaFinal,
            colunaFinal))
    {
        return false;
    }

    // Executa o movimento
    moverPeca(
        tabuleiro,
        linhaInicial,
        colunaInicial,
        linhaFinal,
        colunaFinal
    );

    return true;
}