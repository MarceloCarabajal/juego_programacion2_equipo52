#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Plataforma.h"
#include "Enemigo.h"
#include "Meta.h"
#include "Colisiones.h"

class Nivel3 {
public:
    static const int MAX_PLATAFORMAS = 12;
    static const int MAX_ENEMIGOS = 10;

    Nivel3();
    Nivel3(int puntajeInicial); // Constructor con puntaje inicial

    void cargarPlataformas();
    void posicionarEnemigos();
    void colocarMeta();

    void procesarInput();
    void update();
    void dibujarTodo(sf::RenderTarget& target);

    Jugador& getJugador() { return _jugador; }

    bool nivelCompletado() const { return _nivelCompletado; }
    bool gameOver() const { return _gameOver; }

private:
    Jugador _jugador;
    Plataforma _plataformas[MAX_PLATAFORMAS];
    Enemigo _enemigos[MAX_ENEMIGOS];
    Meta _meta;

    int _cantidadPlataformas;
    int _cantidadEnemigos;

    bool _nivelCompletado;
    bool _gameOver;

    void verificarColisiones();
};
