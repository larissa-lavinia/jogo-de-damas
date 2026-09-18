#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

struct Sala
{
    std::string codigo;

    int jogador1;
    int jogador2;

    bool iniciada;
};

void iniciarServidor();

#endif