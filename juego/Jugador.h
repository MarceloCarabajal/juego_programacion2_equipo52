#pragma once
#include <SFML/Graphics.hpp>

class Jugador : public sf::Drawable {
public:
	Jugador();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape _body;
};
