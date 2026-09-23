#include "peca.h"
#include <iostream>
using namespace std;


void tornarDama(peca& p)
{
    p.tipo = DAMA ;
}

bool operator==(const peca& a, const peca& b)
{
    return a.cor == b.cor && a.tipo == b.tipo && a.linha == b.linha && a.coluna == b.coluna;
}

bool operator!=(const peca& a, const peca& b)
{
    return a.cor != b.cor || a.tipo != b.tipo || a.linha != b.linha || a.coluna != b.coluna;

    //return !(a == b);
}

char caracterePeca(const peca& p)
{
    if(p.cor == BRANCA && p.tipo == NORMAL){
        return 'b';
    }

    else if(p.cor == BRANCA && p.tipo == DAMA){
        return 'B';
    }

    else if(p.cor == PRETA && p.tipo == NORMAL){
        return 'p';
    }

    else if(p.cor == PRETA && p.tipo == DAMA){
        return 'P';
    }

    //caso de segurança (nao deve acontecer)
    return '?';
}


void imprimirPeca(const peca& p)
{
    cout << caracterePeca(p);

    //linha e coluna da peça
    cout << "(linha " << p.linha << ", coluna: " << p.coluna << ")" << endl;
}