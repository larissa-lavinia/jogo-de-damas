#pragma once

#include <string>

enum class AcaoTelaLogin
{
    VOLTAR
};

bool verificarLogin(std::string nickname, std::string senha);
AcaoTelaLogin telaLogin();