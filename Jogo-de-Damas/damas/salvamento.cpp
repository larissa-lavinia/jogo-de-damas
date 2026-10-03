
#include "salvamento.h"

#include <fstream>
#include <cstdio>

#include "jogo.h"
#include "tabuleiro.h"
#include "peca.h"

using namespace std;

// Caminho do arquivo onde a partida sera salva.
const char* ARQUIVO_PARTIDA = "db/partidas.dat";

bool salvarPartida(Cor jogadorAtual)
{
    if (!partida.emAndamento)
    {
        excluirPartidaSalva();
        return false;
    }

    ofstream arquivo(ARQUIVO_PARTIDA, ios::binary);

    if (!arquivo)
    {
        return false;
    }

    // Salva o turno e a pontuacao.
    int turno = jogadorAtual;
    int pontosBrancas = partida.pontosBrancas;
    int pontosPretas = partida.pontosPretas;

    arquivo.write((char*)&turno, sizeof(turno));
    arquivo.write((char*)&pontosBrancas, sizeof(pontosBrancas));
    arquivo.write((char*)&pontosPretas, sizeof(pontosPretas));

    // Salva as pecas do tabuleiro.
    for (int linha = 0; linha < TABTAM; linha++)
    {
        for (int coluna = 0; coluna < TABTAM; coluna++)
        {
            int ocupada = tabuleiro[linha][coluna].ocupada;
            int cor = BRANCA;
            int tipo = tabuleiro[linha][coluna].tipo;

            if (ocupada)
            {
                cor = tabuleiro[linha][coluna].cor;
            }

            arquivo.write((char*)&ocupada, sizeof(ocupada));
            arquivo.write((char*)&cor, sizeof(cor));
            arquivo.write((char*)&tipo, sizeof(tipo));
        }
    }

    arquivo.close();

    return !arquivo.fail();
}

bool carregarPartida(Cor& jogadorAtual)
{
    ifstream arquivo(ARQUIVO_PARTIDA, ios::binary);

    if (!arquivo)
    {
        return false;
    }

    // Carrega o turno e a pontuacao.
    int turno;
    int pontosBrancas;
    int pontosPretas;

    arquivo.read((char*)&turno, sizeof(turno));
    arquivo.read((char*)&pontosBrancas, sizeof(pontosBrancas));
    arquivo.read((char*)&pontosPretas, sizeof(pontosPretas));

    if (arquivo.fail())
    {
        return false;
    }

    // Verifica se o turno salvo e valido.
    if (turno != BRANCA && turno != PRETA)
    {
        return false;
    }

    if (pontosBrancas < 0 || pontosPretas < 0)
    {
        return false;
    }

    // Carrega as pecas do tabuleiro.
    for (int linha = 0; linha < TABTAM; linha++)
    {
        for (int coluna = 0; coluna < TABTAM; coluna++)
        {
            int ocupada;
            int cor;
            int tipo;

            arquivo.read((char*)&ocupada, sizeof(ocupada));
            arquivo.read((char*)&cor, sizeof(cor));
            arquivo.read((char*)&tipo, sizeof(tipo));

            if (arquivo.fail())
            {
                return false;
            }

            if ((ocupada != 0 && ocupada != 1) ||
                (tipo != NORMAL && tipo != DAMA))
            {
                return false;
            }

            if (ocupada &&
                cor != BRANCA &&
                cor != PRETA)
            {
                return false;
            }

            peca& atual = tabuleiro[linha][coluna];

            atual.linha = linha;
            atual.coluna = coluna;
            atual.ocupada = ocupada;
            atual.tipo = (TipoPeca)tipo;

            if (ocupada)
            {
                atual.cor = (Cor)cor;
            }
            else
            {
                atual.cor = BRANCA;
            }
        }
    }

    arquivo.close();

    // Atualiza os dados da partida.
    jogadorAtual = (Cor)turno;

    partida.emAndamento = true;
    partida.pontosBrancas = pontosBrancas;
    partida.pontosPretas = pontosPretas;
    partida.vezDoJogador = jogadorAtual;

    return true;
}

bool existePartidaSalva()
{
    ifstream arquivo(ARQUIVO_PARTIDA, ios::binary);

    return arquivo.good();
}

void excluirPartidaSalva()
{
    remove(ARQUIVO_PARTIDA);
}