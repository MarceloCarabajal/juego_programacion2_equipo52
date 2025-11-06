#include "Nivel.h"

Nivel::Nivel() : _cantidadPlataformas(0), _cantidadEnemigos(0) {
	cargarPlataformas();
	posicionarEnemigos();
}

void Nivel::cargarPlataformas() {
	_cantidadPlataformas = 0;
	
	_plataformas[_cantidadPlataformas] = Plataforma(0.f, 550.f, 800.f, 50.f);
	_cantidadPlataformas++;
	
	// Plataformas flotantes (hardcodeadas)
	_plataformas[_cantidadPlataformas] = Plataforma(200.f, 450.f, 100.f, 20.f);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(400.f, 350.f, 100.f, 20.f);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(600.f, 250.f, 100.f, 20.f);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(100.f, 300.f, 80.f, 20.f);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(500.f, 150.f, 80.f, 20.f);
	_cantidadPlataformas++;
}

void Nivel::posicionarEnemigos() {
	_cantidadEnemigos = 0;
	
	_enemigos[_cantidadEnemigos] = Enemigo(300.f, 520.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(250.f, 350.f);
	_cantidadEnemigos++;
	
	_enemigos[_cantidadEnemigos] = Enemigo(500.f, 520.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(450.f, 550.f);
	_cantidadEnemigos++;
	
	_enemigos[_cantidadEnemigos] = Enemigo(150.f, 420.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(100.f, 200.f);
	_cantidadEnemigos++;
}

void Nivel::procesarInput() {
	_jugador.cmd();
}

void Nivel::update() {
	_jugador.update();
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		_enemigos[i].update();
	}
	
	for (int i = 0; i < _cantidadPlataformas; i++) {
		_plataformas[i].update();
	}
	
	verificarColisiones();
}

void Nivel::verificarColisiones() {
	for (int i = 0; i < _cantidadPlataformas; i++) {
		_jugador.checkCollision(_plataformas[i].getCollider());
	}
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		if (_enemigos[i].colisionConJugador(_jugador)) {
			// logica de colision (arriba mata enemigo, lateral quita vida)
			// por ahora solo verificamos, la lógica completa la implementa Gise
			// TODO: Detectar si es colisión desde arriba o lateral
		}
	}
}

void Nivel::dibujarTodo(sf::RenderTarget& target) {
	for (int i = 0; i < _cantidadPlataformas; i++) {
		target.draw(_plataformas[i]);
	}
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		target.draw(_enemigos[i]);
	}
	
	target.draw(_jugador);
	
	// Meta: cuando gise lo implemente
}

