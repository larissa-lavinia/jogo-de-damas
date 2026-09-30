#ifndef PECA_H
#define PECA_H

enum Cor { BRANCA, PRETA };

enum TipoPeca { NORMAL, DAMA };

struct peca{
    Cor cor;
    TipoPeca tipo;
    int linha;
    int coluna; //posicao atual
    bool ocupada;
};

void tornarDama(peca& p);

bool operator==(const peca& a, const peca& b);
bool operator!=(const peca& a, const peca& b);

char caracterePeca(const peca& p);

void imprimirPeca(const peca& p);

#endif