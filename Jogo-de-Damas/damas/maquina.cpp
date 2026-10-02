#include "maquina.h"

#include "tabuleiro.h"
#include "movimentos.h"
#include "jogo.h"

#include <vector>
#include <random>

using namespace std;

bool escolherJogadaMaquina(Cor jogador, Jogada& jogada)
{
    vector<Jogada> jogadasPossiveis;

    // Percorre todas as peças do jogador
    for (int linhaInicial = 0; linhaInicial < TABTAM; linhaInicial++)
    {
        for (int colunaInicial = 0; colunaInicial < TABTAM; colunaInicial++)
        {
            peca origem = tabuleiro[linhaInicial][colunaInicial];

            // Ignora casas vazias e peças adversárias
            if (!origem.ocupada || origem.cor != jogador)
            {
                continue;
            }

            // Testa todos os destinos possíveis
            for (int linhaFinal = 0; linhaFinal < TABTAM; linhaFinal++)
            {
                for (int colunaFinal = 0; colunaFinal < TABTAM; colunaFinal++)
                {
                    if (validarJogada(
                            tabuleiro,
                            linhaInicial,
                            colunaInicial,
                            linhaFinal,
                            colunaFinal,
                            jogador))
                    {
                        jogadasPossiveis.push_back({
                            linhaInicial,
                            colunaInicial,
                            linhaFinal,
                            colunaFinal
                        });
                    }
                }
            }
        }
    }

    // Não existem jogadas válidas
    if (jogadasPossiveis.empty())
    {
        return false;
    }

    // Escolhe uma jogada aleatória
    static random_device rd;
    static mt19937 gerador(rd());

    uniform_int_distribution<int> distribuicao(
        0,
        static_cast<int>(jogadasPossiveis.size()) - 1
    );

    jogada = jogadasPossiveis[distribuicao(gerador)];

    return true;
}