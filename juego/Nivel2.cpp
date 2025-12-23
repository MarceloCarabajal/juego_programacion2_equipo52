#include "Nivel2.h"

Nivel2::Nivel2() : _cantidadPlataformas(0), _cantidadEnemigos(0), _meta(50.f, 100.f, 50.f, 100.f) {
	cargarPlataformas();
	posicionarEnemigos();
	colocarMeta();
	// reposicionar jugador en el suelo al inicio del nivel
	// la plataforma del suelo está en Y=550 con altura 50, superficie en Y=550
	// el jugador tiene altura 32, así que debe estar en Y=550-32=518
	_jugador.setPosX(100.f);
	_jugador.setPosY(518.f);
	_jugador.setEnSuelo(true);
}

Nivel2::Nivel2(int puntajeInicial) : _cantidadPlataformas(0), _cantidadEnemigos(0), _meta(50.f, 100.f, 50.f, 100.f) {
	_jugador.setPuntaje(puntajeInicial);
	cargarPlataformas();
	posicionarEnemigos();
	colocarMeta();
	// reposicionar jugador en el suelo al inicio del nivel
	_jugador.setPosX(100.f);
	_jugador.setPosY(518.f);
	_jugador.setEnSuelo(true);
}

void Nivel2::cargarPlataformas() {
	_cantidadPlataformas = 0;
	
	// plataforma base (suelo)
	_plataformas[_cantidadPlataformas] = Plataforma(0.f, 550.f, 800.f, 50.f);
	_cantidadPlataformas++;
	
	// Plataformas flotantes - con color diferente (marrón/beige)
	sf::Color colorPlataformaFlotante(139, 90, 43); // Color marrón/beige para plataformas flotantes
	
	// ruta hacia la meta: plataformas escalonadas del lado izquierdo
	// primera plataforma - inicio del camino
	_plataformas[_cantidadPlataformas] = Plataforma(50.f, 480.f, 120.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// segunda plataforma - un poco más arriba y a la derecha
	_plataformas[_cantidadPlataformas] = Plataforma(200.f, 420.f, 100.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// tercera plataforma - más arriba, acercándose a la meta
	_plataformas[_cantidadPlataformas] = Plataforma(100.f, 360.f, 100.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// cuarta plataforma - casi a la altura de la meta
	_plataformas[_cantidadPlataformas] = Plataforma(50.f, 280.f, 120.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// quinta plataforma - a la altura de la meta, permite llegar
	_plataformas[_cantidadPlataformas] = Plataforma(20.f, 220.f, 100.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// plataforma final - justo antes de la meta, permite el salto final
	// posicionada para que el jugador pueda saltar fácilmente a la meta
	_plataformas[_cantidadPlataformas] = Plataforma(40.f, 180.f, 80.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	// plataformas del lado derecho - para dificultad adicional
	_plataformas[_cantidadPlataformas] = Plataforma(650.f, 450.f, 100.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(600.f, 350.f, 80.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
	
	_plataformas[_cantidadPlataformas] = Plataforma(700.f, 250.f, 80.f, 20.f);
	_plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
	_cantidadPlataformas++;
}

void Nivel2::posicionarEnemigos() {
	_cantidadEnemigos = 0;
	
	// enemigos en el suelo - patrullando áreas estratégicas
	// la plataforma del suelo está en Y=550 con altura 50, superficie en Y=550
	// los enemigos tienen altura 50, así que deben estar en Y=550-50=500 para estar sobre la superficie
	_enemigos[_cantidadEnemigos] = Enemigo(150.f, 500.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(100.f, 250.f);
	_cantidadEnemigos++;
	
	_enemigos[_cantidadEnemigos] = Enemigo(400.f, 500.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(350.f, 500.f);
	_cantidadEnemigos++;
	
	_enemigos[_cantidadEnemigos] = Enemigo(650.f, 500.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(600.f, 750.f);
	_cantidadEnemigos++;
	
	// enemigos en plataformas intermedias - más desafiantes
	// plataforma en Y=420 con altura 20, superficie en Y=420, enemigo altura 50, posición Y=420-50=370
	_enemigos[_cantidadEnemigos] = Enemigo(250.f, 370.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(200.f, 300.f);
	_cantidadEnemigos++;
	
	// plataforma en Y=360 con altura 20, superficie en Y=360, enemigo altura 50, posición Y=360-50=310
	_enemigos[_cantidadEnemigos] = Enemigo(150.f, 310.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(100.f, 200.f);
	_cantidadEnemigos++;
	
	// enemigo en plataforma cerca de la meta - desafío final
	// plataforma en Y=180 con altura 20, superficie en Y=180, enemigo altura 50, posición Y=180-50=130
	_enemigos[_cantidadEnemigos] = Enemigo(90.f, 130.f);
	_enemigos[_cantidadEnemigos].setLimitePatrullaje(40.f, 140.f);
	_cantidadEnemigos++;
}

void Nivel2::colocarMeta() {
	// meta en la parte superior izquierda - requiere llegar saltando por las plataformas
}

void Nivel2::procesarInput() {
	_jugador.procesarComandos();
}

void Nivel2::update() {
	_jugador.update();
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		_enemigos[i].update();
	}
	
	for (int i = 0; i < _cantidadPlataformas; i++) {
		_plataformas[i].update();
	}
	
	verificarColisiones();
}

void Nivel2::verificarColisiones() {
	bool estaSobreAlgunaPlataforma = false;
	
	for (int i = 0; i < _cantidadPlataformas; i++) {
		Colisiones::jugadorVsPlataforma(_jugador, _plataformas[i]);
		
		if (_jugador.estaSobrePlataforma(_plataformas[i].obtenerLimites())) {
			estaSobreAlgunaPlataforma = true;
		}
	}
	
	if (!estaSobreAlgunaPlataforma && _jugador.estaEnSuelo()) {
		_jugador.setEnSuelo(false);
	}
	
	for (int i = 0; i < _cantidadEnemigos; i++) {
		Colisiones::jugadorVsEnemigo(_jugador, _enemigos[i]);
	}
	
	// verificar colisión con Meta
	if (_meta.verificarLlegada(_jugador)) {
        _nivelCompletado = true;
	}
	
	// verificar si el jugador perdió todas las vidas
    if (_jugador.getVidas() <= 0) {
       _gameOver = true;
	}
}


void Nivel2::dibujarTodo(sf::RenderTarget& target) {
	for (int i = 0; i < _cantidadPlataformas; i++) {
		target.draw(_plataformas[i]);
	}
	
	// Dibujar enemigos vivos o que están en proceso de desaparecer
	for (int i = 0; i < _cantidadEnemigos; i++) {
		if (_enemigos[i].estaVivo() || _enemigos[i].estaMuriendo()) {
			target.draw(_enemigos[i]);
		}
	}
	
	target.draw(_meta);
	
	target.draw(_jugador);
}

Jugador& Nivel2::getJugador() {
	return _jugador;
}

bool Nivel2::verificarVictoria() const {
	return _meta.estaAlcanzada();
}

bool Nivel2::nivelCompletado() const {
	return _nivelCompletado;
}

bool Nivel2::gameOver() const {
	return _gameOver;
}

