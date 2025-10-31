#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Jugador : public sf::Drawable {
public:
	Jugador();

	void update();
	void cmd();
	void checkCollision(const sf::FloatRect& platformBounds);
	const sf::FloatRect getBounds() const { return _body.getGlobalBounds(); }
	
	bool isOnGround() const { return _enSuelo; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape _body;
	sf::Vector2f _velocidad;
	float _gravedad;
	float _velocidadSalto;
	bool _enSuelo;
};
