#include "Jugador.h"

Jugador::Jugador() {
	_body.setSize({ 32.f, 32.f });
	_body.setFillColor(sf::Color::Red);
	_body.setPosition(100.f, 100.f);
}

void Jugador::update() {
	// quieda pendiente todavia
}

void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_body, states);
}
