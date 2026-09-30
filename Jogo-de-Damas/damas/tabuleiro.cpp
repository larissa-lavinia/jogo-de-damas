#include <stdio.h>
#include <iostream>

#include "tabuleiro.h"
#include "peca.h"

using namespace std;

peca tabuleiro[TABTAM][TABTAM];

void inicializarTabuleiro(
    peca tabuleiro[TABTAM][TABTAM])
{
    for (int i = 0; i < TABTAM; i++)
    {
        for (int j = 0; j < TABTAM; j++)
        {
            tabuleiro[i][j].linha = i;
            tabuleiro[i][j].coluna = j;
            tabuleiro[i][j].ocupada = false;
            tabuleiro[i][j].tipo = NORMAL;

            if ((i + j) % 2 != 0)
            {
                if (i < 3)
                {
                    tabuleiro[i][j].cor = BRANCA;
                    tabuleiro[i][j].ocupada = true;
                    tabuleiro[i][j].tipo = NORMAL;
                }
                else if (i > 4)
                {
                    tabuleiro[i][j].cor = PRETA;
                    tabuleiro[i][j].ocupada = true;
                    tabuleiro[i][j].tipo = NORMAL;
                }
            }
        }
    }
}

void exibirTabuleiro(
    peca tabuleiro[TABTAM][TABTAM])
{
    cout << "  0 1 2 3 4 5 6 7" << endl;

    for (int i = 0; i < TABTAM; i++)
    {
        cout << i << " ";

        for (int j = 0; j < TABTAM; j++)
        {
            if (tabuleiro[i][j].ocupada)
            {
                cout << caracterePeca(tabuleiro[i][j]) << " ";
            }
            else
            {
                cout << "  ";
            }
        }

        cout << endl;
    }
}
