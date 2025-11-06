#pragma once
#include <SFML/Graphics.hpp>

class Plataforma : public sf::Drawable {
public:
	Plataforma(); // Constructor por defecto para arrays
	Plataforma(float x, float y, float w, float h);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// getters que vamos a usar
	const sf::FloatRect getBounds() const { return _body.getGlobalBounds(); }
	const sf::FloatRect getCollider() const { return getBounds(); }

private:
	sf::RectangleShape _body;
};
