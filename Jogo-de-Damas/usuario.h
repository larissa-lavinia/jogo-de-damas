#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

struct Usuario
{
    int id;
    string nickname;
    string senha;
};

string salvarUsuario(Usuario usuario);
void listarUsuarios();
bool nicknameExiste(string nickname);
bool verificarLogin(string nickname, string senha);
#endif