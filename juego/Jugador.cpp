#include "Jugador.h"

Jugador::Jugador() 
	: _velocidad(0.f, 0.f), _gravedad(0.8f), _velocidadSalto(-12.0f), _enSuelo(false) {
	_body.setSize({ 32.f, 32.f });
	_body.setFillColor(sf::Color::Red);
	_body.setPosition(100.f, 100.f);
	_vidas = 3;
	_puntaje = 0;
}

void Jugador::cmd() {
	// movimiento horizontal
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_velocidad.x = -5.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_velocidad.x = 5.0f;
	}
	else {
		_velocidad.x = 0.0f;
	}
	
	// salto
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && _enSuelo) {
		_velocidad.y = _velocidadSalto;
		_enSuelo = false;
	}
}

void Jugador::update() {
	if (!_enSuelo) {
		_velocidad.y += _gravedad;
	}
	
	if (_velocidad.y > 15.0f) {
		_velocidad.y = 15.0f;
	}
	
	_body.move(_velocidad);
	
	sf::Vector2f pos = _body.getPosition();
	if (pos.x < 0) {
		_body.setPosition(0, pos.y);
		_velocidad.x = 0;
	}
	if (pos.x + 32 > 800) {
		_body.setPosition(800 - 32, pos.y);
		_velocidad.x = 0;
	}
	if (pos.y < 0) {
		_body.setPosition(pos.x, 0);
		_velocidad.y = 0;
	}
	if (pos.y + 32 > 600) {
		_body.setPosition(pos.x, 600 - 32);
		_velocidad.y = 0;
		_enSuelo = true;
	}
}

void Jugador::checkCollision(const sf::FloatRect& platformBounds) {
	sf::FloatRect jugadorBounds = _body.getGlobalBounds();
	
	if (jugadorBounds.intersects(platformBounds)) {
		if (_velocidad.y > 0 && jugadorBounds.top < platformBounds.top) {
			_body.setPosition(_body.getPosition().x, platformBounds.top - 32);
			_velocidad.y = 0;
			_enSuelo = true;
		}
	}
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_body, states);
}
