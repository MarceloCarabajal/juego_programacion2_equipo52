#pragma once
#include "Jugador.h"
#include "Enemigo.h"
#include "Plataforma.h"

class Colisiones {
public:
    static void jugadorVsPlataforma(Jugador& jugador, const Plataforma& plataforma);
    static void jugadorVsEnemigo(Jugador& jugador, Enemigo& enemigo);
};
