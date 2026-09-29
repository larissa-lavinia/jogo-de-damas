#include <iostream>
using namespace std;

#include "peca (1).h"
#include "movimentos.h"
#include "tabuleiro.h"

void iniciarJogo() {
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;

    inicializarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro);

    while (true)
    {
        cout << endl;

        //por enquanto, pra sair do loop digitar -1 no prieiro linha
        cout << "qual peca deseja mover \n";
        cout << "[linha]: ";
        cin >> linhaInicial;

        if (linhaInicial==-1){
            break;
        }

        cout << "[coluna]: ";
        cin >> colunaInicial;

        cout << endl;

        cout << "para onde deseja mover: \n";
        cout << "[linha]: ";
        cin >> linhaFinal;
        cout << "[coluna]: ";
        cin >> colunaFinal;

        //se o usuario digitar algo que nao é numero
         if (cin.fail()){
            cin.clear(); //limpa estado de erro do cin
            break;
         }

        cout << endl;

        if (podeMoverSimples(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal)){
            moverPeca(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
        }
        else {
            cout << "movimento invalido!" << endl;
        }

        cout << endl;

        exibirTabuleiro(tabuleiro);
    }
}
