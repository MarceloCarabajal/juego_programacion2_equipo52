#include "Plataforma.h"

Plataforma::Plataforma() {
	// Constructor por defecto: inicializa con valores por defecto
	_body.setSize({ 0.f, 0.f });
	_body.setFillColor(sf::Color(80, 200, 120));
	_body.setPosition(0.f, 0.f);
}

Plataforma::Plataforma(float x, float y, float w, float h) {
	_body.setSize({ w, h });
	_body.setFillColor(sf::Color(80, 200, 120)); // verde
	_body.setPosition(x, y);
}

void Plataforma::update() {
	//  por ahora no va a hacer nada
}

void Plataforma::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_body, states);
}
