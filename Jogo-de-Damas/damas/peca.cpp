#include "peca.h"

#include <iostream>

using namespace std;

void tornarDama(peca& p)
{
    p.tipo = DAMA;
}

char caracterePeca(const peca& p)
{
    if (p.cor == BRANCA && p.tipo == NORMAL)
    {
        return 'b';
    }

    if (p.cor == BRANCA && p.tipo == DAMA)
    {
        return 'B';
    }

    if (p.cor == PRETA && p.tipo == NORMAL)
    {
        return 'p';
    }

    if (p.cor == PRETA && p.tipo == DAMA)
    {
        return 'P';
    }

    return '?';
}

void imprimirPeca(const peca& p)
{
    cout << caracterePeca(p);

    cout << "(linha "
         << p.linha
         << ", coluna: "
         << p.coluna
         << ")" << endl;
}
