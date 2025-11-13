#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Plataforma.h"
#include "Enemigo.h"
#include "Meta.h"
#include "Colisiones.h"

class Nivel {
public:
	static const int MAX_PLATAFORMAS = 10;
	static const int MAX_ENEMIGOS = 10;

	Nivel();
	void cargarPlataformas(); 
	void posicionarEnemigos();
	void colocarMeta();
	void dibujarTodo(sf::RenderTarget& target);
	
	void update();
	void procesarInput();
	Jugador* getJugador() { return &_jugador; }
	
	bool verificarVictoria() const;
	bool nivelCompletado() const { return _nivelCompletado; }
    bool gameOver() const { return _gameOver; }

private:
	Jugador _jugador;
	Plataforma _plataformas[MAX_PLATAFORMAS];
	Enemigo _enemigos[MAX_ENEMIGOS];
	Meta _meta;
	int _cantidadPlataformas;
	int _cantidadEnemigos;
	bool _nivelCompletado = false;
    bool _gameOver = false;
	
	void verificarColisiones();
};

