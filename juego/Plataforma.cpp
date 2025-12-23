#include "Plataforma.h"

Plataforma::Plataforma() {
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

const sf::FloatRect Plataforma::obtenerLimites() const {
	return _body.getGlobalBounds();
}

const sf::FloatRect Plataforma::obtenerColisionador() const {
	return obtenerLimites();
}

void Plataforma::setColor(const sf::Color& color) {
	_body.setFillColor(color);
}