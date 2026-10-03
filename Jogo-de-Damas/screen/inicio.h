
#ifndef INICIO_H
#define INICIO_H

enum class OpcaoInicio
{
    NOVA_PARTIDA,
    CONTINUAR_PARTIDA,
    SAIR
};

OpcaoInicio inicio(bool temPartidaSalva);

#endif