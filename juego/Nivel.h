#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Plataforma.h"
#include "Enemigo.h"

class Nivel {
public:
	static const int MAX_PLATAFORMAS = 10;
	static const int MAX_ENEMIGOS = 10;

	Nivel();
	void cargarPlataformas(); 
	void posicionarEnemigos();
	void dibujarTodo(sf::RenderTarget& target);
	
	void update();
	void procesarInput();
	Jugador* getJugador() { return &_jugador; }
	
	// placeholder para Meta (gise)
	// void colocarMeta();
	// bool verificarVictoria() const;

private:
	Jugador _jugador;
	Plataforma _plataformas[MAX_PLATAFORMAS];
	Enemigo _enemigos[MAX_ENEMIGOS];
	int _cantidadPlataformas;
	int _cantidadEnemigos;
	
	void verificarColisiones();
};

