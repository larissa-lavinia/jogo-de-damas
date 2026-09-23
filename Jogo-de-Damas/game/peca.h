#pragma once //substitui o ifndef

enum Cor { BRANCA, PRETA };

enum TipoPeca { NORMAL, DAMA };

struct peca{
    Cor cor;
    TipoPeca tipo;
    int linha;
    int coluna; //posicao atual
};

//funcoes relacionadas a peça (isoladamente)
void tornarDama(peca& p);

//facilita na hora de comparar duas peças (verificar se são a mesma peça), pois naturamente o C++ nao consegue compara duas struct com "==" e "!=")
bool operator==(const peca& a, const peca& b);
bool operator!=(const peca& a, const peca& b);


// retorna o caractere que representa a peça no tabuleiro 
// 'b' = branca normal, 'B' = branca dama, 'p' = preta normal, 'P' = preta dama.
char caracterePeca(const peca& p);

void imprimirPeca(const peca& p); //visualizar em texo
