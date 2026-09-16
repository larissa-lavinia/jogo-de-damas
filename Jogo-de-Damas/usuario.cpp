#include <fstream>
#include <iostream>
#include <string>

#include "usuario.h"
#include "config/constantes.h"

using namespace std;

const int TAMANHO_NICKNAME = 50;
const int TAMANHO_SENHA = 50;


string salvarUsuario(Usuario usuario)
{
    if (nicknameExiste(usuario.nickname))
    {
        return "Nickname ja cadastrado!";
    }

    ofstream arquivo(
        Constantes::Db::ARQUIVO_USUARIO,
        ios::binary | ios::app
    );

    if (!arquivo)
    {
        return "Erro ao tentar salvar usuario!";
    }

    arquivo.write(
        (char*)&usuario.id,
        sizeof(usuario.id)
    );

    arquivo.write(
        usuario.nickname.c_str(),
        TAMANHO_NICKNAME
    );

    arquivo.write(
        usuario.senha.c_str(),
        TAMANHO_SENHA
    );

    arquivo.close();

    return "Usuario cadastrado com sucesso!";
}


void listarUsuarios()
{
    ifstream arquivo(
        Constantes::Db::ARQUIVO_USUARIO,
        ios::binary
    );

    Usuario usuario;

    while (arquivo)
    {
        arquivo.read(
            (char*)&usuario.id,
            sizeof(usuario.id)
        );

        char nickname[TAMANHO_NICKNAME];
        char senha[TAMANHO_SENHA];

        arquivo.read(
            nickname,
            TAMANHO_NICKNAME
        );

        arquivo.read(
            senha,
            TAMANHO_SENHA
        );

        if (arquivo)
        {
            usuario.nickname = nickname;
            usuario.senha = senha;

            cout << usuario.id << endl;
            cout << usuario.nickname << endl;
            cout << usuario.senha << endl;
        }
    }

    arquivo.close();
}


bool nicknameExiste(string nickname)
{
    ifstream arquivo(
        Constantes::Db::ARQUIVO_USUARIO,
        ios::binary
    );

    if (!arquivo)
    {
        return false;
    }

    Usuario usuario;

    while (arquivo)
    {
        arquivo.read(
            (char*)&usuario.id,
            sizeof(usuario.id)
        );

        char nicknameArquivo[TAMANHO_NICKNAME];
        char senhaArquivo[TAMANHO_SENHA];

        arquivo.read(
            nicknameArquivo,
            TAMANHO_NICKNAME
        );

        arquivo.read(
            senhaArquivo,
            TAMANHO_SENHA
        );

        if (arquivo)
        {
            usuario.nickname = nicknameArquivo;

            if (usuario.nickname == nickname)
            {
                arquivo.close();
                return true;
            }
        }
    }

    arquivo.close();

    return false;
}