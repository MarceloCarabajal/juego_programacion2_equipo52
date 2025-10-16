#pragma once
#include <SFML/Graphics.hpp>

class Pelotita : public sf::Drawable, sf::Transformable {
public:
	Pelotita();
	void cmd();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::CircleShape _body;
	sf::RectangleShape _weapon;
	sf::Vector2f _velocity;
};