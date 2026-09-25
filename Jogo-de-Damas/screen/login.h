#pragma once

#include <string>
using namespace std;

enum class AcaoTelaLogin
{
    VOLTAR
};

bool verificarLogin(string nickname, string senha);
AcaoTelaLogin telaLogin();