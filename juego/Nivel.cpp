#include "Nivel.h"

Nivel::Nivel() : _cantidadPlataformas(0), _cantidadEnemigos(0), _meta(700.f, 100.f, 50.f, 100.f) {
	cargarPlataformas();
	posicionarEnemigos();
	colocarMeta();
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

void Nivel::colocarMeta() {
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
	bool estaSobreAlgunaPlataforma = false;
	
	for (int i = 0; i < _cantidadPlataformas; i++) {
		Colisiones::jugadorVsPlataforma(_jugador, _plataformas[i]);
		
		if (_jugador.estaSobrePlataforma(_plataformas[i].getBounds())) {
			estaSobreAlgunaPlataforma = true;
		}
	}
	
	if (!estaSobreAlgunaPlataforma && _jugador.isOnGround()) {
		_jugador.setEnSuelo(false);
	}
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		Colisiones::jugadorVsEnemigo(_jugador, _enemigos[i]);
	}
	
	// Verificar colisión con Meta
	if (_meta.verificarLlegada(_jugador)) {
        _nivelCompletado = true;
	}
	
	// Verificar si el jugador perdió todas las vidas
    if (_jugador.getVidas() <= 0) {
       _gameOver = true;
	}
}


void Nivel::dibujarTodo(sf::RenderTarget& target) {
	for (int i = 0; i < _cantidadPlataformas; i++) {
		target.draw(_plataformas[i]);
	}
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		target.draw(_enemigos[i]);
	}
	
	target.draw(_meta);
	
	target.draw(_jugador);
}

bool Nivel::verificarVictoria() const {
	return _meta.estaAlcanzada();
}

