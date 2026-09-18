#include "servidor.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

string gerarCodigoSala()
{
    const string caracteres =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    string codigo;

    for (int i = 0; i < 6; i++)
    {
        codigo += caracteres[rand() % caracteres.size()];
    }

    return codigo;
}

void iniciarServidor()
{
    srand(time(nullptr));

    // =========================
    // CRIAR SOCKET DO SERVIDOR
    // =========================

    int servidor = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor == -1)
    {
        cout << "Erro ao criar socket!" << endl;
        return;
    }

    cout << "Socket criado!" << endl;

    // =========================
    // CONFIGURAR ENDERECO
    // =========================

    sockaddr_in endereco;

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(5000);

    // =========================
    // BIND
    // =========================

    if (bind(
        servidor,
        (sockaddr*)&endereco,
        sizeof(endereco)
    ) == -1)
    {
        cout << "Erro no bind!" << endl;
        close(servidor);
        return;
    }

    cout << "Servidor usando a porta 5000!" << endl;

    // =========================
    // LISTEN
    // =========================

    if (listen(servidor, 2) == -1)
    {
        cout << "Erro no listen!" << endl;
        close(servidor);
        return;
    }

    // =========================
    // CRIAR SALA
    // =========================

    Sala sala;

    sala.codigo = gerarCodigoSala();
    sala.jogador1 = -1;
    sala.jogador2 = -1;
    sala.iniciada = false;

    cout << endl;
    cout << "============================" << endl;
    cout << "      SALA CRIADA" << endl;
    cout << "============================" << endl;
    cout << "Codigo: " << sala.codigo << endl;
    cout << "============================" << endl;

    // =========================
    // JOGADOR 1
    // =========================

    cout << endl;
    cout << "Aguardando jogador 1..." << endl;

    sala.jogador1 = accept(
        servidor,
        nullptr,
        nullptr
    );

    if (sala.jogador1 == -1)
    {
        cout << "Erro ao aceitar jogador 1!" << endl;

        close(servidor);
        return;
    }

    cout << "Jogador 1 conectado!" << endl;

    // =========================
    // JOGADOR 2
    // =========================

    cout << endl;
    cout << "Aguardando jogador 2..." << endl;

    sala.jogador2 = accept(
        servidor,
        nullptr,
        nullptr
    );

    if (sala.jogador2 == -1)
    {
        cout << "Erro ao aceitar jogador 2!" << endl;

        close(sala.jogador1);
        close(servidor);

        return;
    }

    cout << "Jogador 2 conectado!" << endl;

    // =========================
    // INICIAR PARTIDA
    // =========================

    sala.iniciada = true;

    cout << endl;
    cout << "============================" << endl;
    cout << "      PARTIDA INICIADA" << endl;
    cout << "============================" << endl;

    close(sala.jogador1);
    close(sala.jogador2);
    close(servidor);
}