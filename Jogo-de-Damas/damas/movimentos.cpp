//lembrar de modificar os .hpp

#include <cmath>
#include "tabuleiro.h" //por isso acho que talvez as funções do tabuleiro devem estar no .h
#include "movimentos.h"
#include "peca (1).h"
// o código usa as variaveis globais declaradas em tabuleiro.

void moverPeca(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    tabuleiro[linhaFinal][colunaFinal].cor = tabuleiro[linhaInicial][colunaInicial].cor;
    tabuleiro[linhaFinal][colunaFinal].tipo = tabuleiro[linhaInicial][colunaInicial].tipo;
    tabuleiro[linhaFinal][colunaFinal].ocupada = true;

    tabuleiro[linhaInicial][colunaInicial].ocupada = false;
}

bool podeMoverSimples(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    // Linha e coluna iniciais seriam a que a peça está no momento que pede a validação
    // Já as finais é pra onde a peça irá depois

    peca origem = tabuleiro[linhaInicial][colunaInicial];
    peca destino = tabuleiro[linhaFinal][colunaFinal];

    // Se a origem estiver vazia, não tem como o movimento acontecer
    if (!origem.ocupada) {
        return false;
    }

    // Destino ocupado?
    if (destino.ocupada) {
        return false;
    }

    // Casa da diagonal (direita ou esquerda) vazia?
    if (abs(colunaFinal - colunaInicial) != 1) {
        return false;
    }

    // Validação caso seja uma peça normal
    if (origem.tipo == NORMAL) {
        if (origem.cor == BRANCA && linhaFinal == linhaInicial + 1) {
            return true;
        }
        if (origem.cor == PRETA && linhaFinal == linhaInicial - 1) {
            return true;
        }
        return false;
    }

    // Validação caso seja uma peça dama (Não consegui pensar em como delimitar o movimento, para que impeçaa de passar por cima de alguma peça da mesmas cor)
    /*if (origem.tipo == DAMA) {
        if () {
            return true;
        }
    }*/

    return false;
}

bool podeCapturar(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    int linhaMeio = (linhaFinal + linhaInicial) / 2;
    int colunaMeio = (colunaFinal + colunaInicial) / 2;
    // Meio é onde vai estar a peça do adversario, já que na captura "pula duas casas"

    peca origem = tabuleiro[linhaInicial][colunaInicial];
    peca destino = tabuleiro[linhaFinal][colunaFinal];
    peca meio = tabuleiro[linhaMeio][colunaMeio];

    // Se a origem estiver vazia, não tem como o movimento acontecer
    if (!origem.ocupada) {
        return false;
    }

    // Destino ocupado?
    if (destino.ocupada) {
        return false;
    }

    // Pulo de 2 casas na diagonal
    if (abs(linhaFinal - linhaInicial) != 2 || abs(colunaFinal - colunaInicial) != 2) {
        return false;
    }

    if(origem.tipo == NORMAL)
        if (meio.ocupada && meio.cor != origem.cor) {
            if (origem.tipo == NORMAL) {
                if (origem.cor == BRANCA && linhaFinal == linhaInicial + 2) return true;
                if (origem.cor == PRETA && linhaFinal == linhaInicial - 2) return true;
                return false;
            }

//            // Dama não tem delimitações de captura (preciso pensar em como fazer essa captura de peças,
//            // pois não consigo pensar em como verificar se há uma peça intermediária em qualquer diagonal
//            if (origem.tipo == DAMA){
//                int j == colunaInicial;
//                for(int i = linhaInicial; i <= linhaFinal; i++){
//                    tabuleiro[i][j] ==;
//                }
//                return true;
//            }
        }

    return false;
}

// Verificar se alguma peça do jogador da vez pode realizar um movimento de captura (Função em desenvolvimento)
/*bool existeCapturaObrigatoria(peca tabuleiro[TABTAM][TABTAM], Cor jogadorAtual) {
    for (int i = 0; i < TABTAM; i++) {
        for (int j = 0; j < TABTAM; j++) {
            if (tabuleiro[i][j].ocupada && tabuleiro[i][j].cor == jogadorAtual) {
            }
        }
    }

    return false; // Não tem nenhuma captura disponível
}*/

bool validarJogada(peca tabuleiro[TABTAM][TABTAM], int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal){
    if (podeCapturar(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal))
        return true;
    else if (podeMoverSimples(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal))
        return true;

    return false;
}
//Essa função parece ser redundante
