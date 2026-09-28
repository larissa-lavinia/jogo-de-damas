#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int cliente = socket(AF_INET, SOCK_STREAM, 0);

    if (cliente == -1)
    {
        cout << "Erro ao criar socket!" << endl;
        return 1;
    }

    cout << "Socket criado!" << endl;

    sockaddr_in endereco;

    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(5000);

    inet_pton(AF_INET, "192.168.0.9", &endereco.sin_addr);

    if (connect(cliente, (sockaddr*)&endereco, sizeof(endereco)) == -1)
    {
        cout << "Erro ao conectar ao servidor!" << endl;
        close(cliente);
        return 1;
    }

    cout << "Conectado ao servidor!" << endl;

    string mensagem = "Ola servidor!";

    send(cliente, mensagem.c_str(), mensagem.size() + 1, 0);

    char resposta[100] = {};

    recv(cliente, resposta, sizeof(resposta), 0);

    cout << "Resposta do servidor: " << resposta << endl;

    close(cliente);

    return 0;
}