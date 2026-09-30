#ifndef MENU_H
#define MENU_H

#include <string>

enum class AcaoMenu
{
    NOVA_PARTIDA,
    CONTINUAR_PARTIDA,
    HISTORICO,
    DESLOGAR
};

AcaoMenu menu(const std::string& usuarioLogado);

#endif