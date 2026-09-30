#ifndef LOGIN_H
#define LOGIN_H

#include <string>

enum class AcaoTelaLogin
{
    VOLTAR,
    ENTRAR_MENU
};

AcaoTelaLogin telaLogin(
    std::string& usuarioLogado
);

#endif