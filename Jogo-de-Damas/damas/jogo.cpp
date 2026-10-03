
#include "jogo.h"
#include "../audio/audio.h"
#include "movimentos.h"
#include "tabuleiro.h"

// emAndamento, pontosBrancas, pontosPretas, vezDoJogador
Partida partida = { false, 0, 0, BRANCA };

void iniciarPartida()
{
    inicializarTabuleiro(tabuleiro);

    partida.emAndamento   = true;
    partida.pontosBrancas = 0;
    partida.pontosPretas  = 0;
    partida.vezDoJogador  = BRANCA;
}

bool realizarJogada(
    int linhaInicial,
    int colunaInicial,
    int linhaFinal,
    int colunaFinal,
    Cor jogador
)
{
    // Verifica se as posições estão dentro do tabuleiro.
    if (linhaInicial < 0 || linhaInicial >= TABTAM ||
        colunaInicial < 0 || colunaInicial >= TABTAM ||
        linhaFinal < 0 || linhaFinal >= TABTAM ||
        colunaFinal < 0 || colunaFinal >= TABTAM)
    {
        return false;
    }

    // Verifica se existe uma peça na posição inicial.
    if (!tabuleiro[linhaInicial][colunaInicial].ocupada)
    {
        return false;
    }

    // Verifica se a peça pertence ao jogador que está jogando.
    if (tabuleiro[linhaInicial][colunaInicial].cor != jogador)
    {
        return false;
    }

    // Verifica se o movimento segue as regras.
    if (!validarJogada(
            tabuleiro,
            linhaInicial,
            colunaInicial,
            linhaFinal,
            colunaFinal,
            jogador))
    {
        return false;
    }

    // Verifica se é uma captura antes de mover a peça.
    bool foiCaptura = podeCapturar(
        tabuleiro,
        linhaInicial,
        colunaInicial,
        linhaFinal,
        colunaFinal
    );

    // Executa o movimento.
    moverPeca(
        tabuleiro,
        linhaInicial,
        colunaInicial,
        linhaFinal,
        colunaFinal
    );

    tocarSomMovimento();
 
    // Soma ponto para quem capturou
    if (foiCaptura)
    {
        if (jogador == BRANCA)
        {
            partida.pontosBrancas++;
        }
        else
        {
            partida.pontosPretas++;
        }
    }

    // Verifica se a partida terminou.
    if (partidaFinalizada(partida))
    {
        partida.emAndamento = false;
    }

    // Atualiza o jogador da próxima vez.
    if (partida.emAndamento)
    {
        partida.vezDoJogador = (jogador == BRANCA)
            ? PRETA
            : BRANCA;
    }

    return true;
}

int ganharPontos(const Partida& p, Cor jogador)
{
    return (jogador == BRANCA)
        ? p.pontosBrancas
        : p.pontosPretas;
}

bool partidaFinalizada(const Partida& p)
{
    return p.pontosBrancas >= PONTOS_VITORIA ||
           p.pontosPretas  >= PONTOS_VITORIA;
}

Cor vencedor(const Partida& p)
{
    return (p.pontosBrancas >= PONTOS_VITORIA)
        ? BRANCA
        : PRETA;
}