#include "jogo.h"
#include "../audio/audio.h"
#include "movimentos.h"
#include "tabuleiro.h"
#include <raylib.h>
//emAndamento, pontosBrancas, pontosPretas, vezDoJogador
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
            colunaFinal,
            jogador))
    {
        return false;
    }

    // Descobre se é captura ANTES de mover
    // (depois do movimento a peça capturada já foi removida)
    bool foiCaptura = podeCapturar(
        tabuleiro,
        linhaInicial,
        colunaInicial,
        linhaFinal,
        colunaFinal
    );

    // Executa o movimento
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

    // Encerra a partida se alguém chegou ao limite
    if (partidaFinalizada(partida))
    {
        partida.emAndamento = false;
    }

    return true;


}

int ganharPontos(const Partida& p, Cor jogador)
{
    return (jogador == BRANCA) ? p.pontosBrancas : p.pontosPretas;
}

bool partidaFinalizada(const Partida& p)
{
    return p.pontosBrancas >= PONTOS_VITORIA ||
           p.pontosPretas  >= PONTOS_VITORIA;
}

Cor vencedor(const Partida& p)
{
    return (p.pontosBrancas >= PONTOS_VITORIA) ? BRANCA : PRETA;
}

