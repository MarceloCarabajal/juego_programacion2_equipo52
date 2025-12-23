#pragma once
#include <SFML/Graphics.hpp>

class Plataforma : public sf::Drawable {
public:
	Plataforma();
	Plataforma(float x, float y, float w, float h);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::FloatRect obtenerLimites() const;
	const sf::FloatRect obtenerColisionador() const;
	
	// Método para cambiar el color de la plataforma
	void setColor(const sf::Color& color);

private:
	sf::RectangleShape _body;
};
