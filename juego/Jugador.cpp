#include "Jugador.h"

Jugador::Jugador() 
	: Entidad(100.f, 100.f, 32.f, 32.f), _gravedad(0.8f), _velocidadSalto(-12.0f), _enSuelo(false) {
	_body.setSize({ ancho, alto });
	_body.setFillColor(sf::Color::Red);
	_body.setPosition(posX, posY);
	_vidas = 3;
	_puntaje = 0;
}

void Jugador::cmd() {
	// movimiento horizontal
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velX = -5.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velX = 5.0f;
	}
	else {
		velX = 0.0f;
	}
	
	// salto
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && _enSuelo) {
		velY = _velocidadSalto;
		_enSuelo = false;
	}
}

void Jugador::update() {
	// Aplicar gravedad
	if (!_enSuelo) {
		velY += _gravedad;
	}
	
	// Limitar velocidad de caída
	if (velY > 15.0f) {
		velY = 15.0f;
	}
	
	// Actualizar posición usando velocidad de Entidad
	posX += velX;
	posY += velY;
	
	// Limitar a los bordes de la pantalla
	if (posX < 0) {
		posX = 0;
		velX = 0;
	}
	if (posX + ancho > 800) {
		posX = 800 - ancho;
		velX = 0;
	}
	if (posY < 0) {
		posY = 0;
		velY = 0;
	}
	if (posY + alto > 600) {
		posY = 600 - alto;
		velY = 0;
		_enSuelo = true;
	}
	
	// Sincronizar sprite con posición de Entidad
	_body.setPosition(posX, posY);
}

void Jugador::checkCollision(const sf::FloatRect& platformBounds) {
	sf::FloatRect jugadorBounds = getRectanguloColision();
	
	if (jugadorBounds.intersects(platformBounds)) {
		if (velY > 0 && jugadorBounds.top < platformBounds.top) {
			posY = platformBounds.top - alto;
			velY = 0;
			_enSuelo = true;
			_body.setPosition(posX, posY);
		}
	}
}


void Jugador::checkCollisionEnemigo(const sf::FloatRect& enemigoBounds) {
    sf::FloatRect jugadorBounds = _body.getGlobalBounds();

    if (jugadorBounds.intersects(enemigoBounds)) {
        // Determinamos si la colision fue desde arriba
        float jugadorBottom = jugadorBounds.top + jugadorBounds.height;
        float enemigoTop = enemigoBounds.top;

        if (_velocidad.y > 0 && jugadorBottom - enemigoTop < 10.f) {
            // Colisión desde arriba: rebota
            _velocidad.y = _velocidadSalto / 1.5f; // rebote leve
            _puntaje += 100; // suma puntos
            
        }
        else {
            // Colisión lateral o inferior: pierde una vida
            _vidas--;
            _body.setPosition(100.f, 100.f); // reinicia posición
            _velocidad = {0.f, 0.f};
        }
    }
}


void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_body, states);
}
