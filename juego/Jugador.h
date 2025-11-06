#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Entidad.h"

class Jugador : public Entidad, public sf::Drawable {
public:
	Jugador();

	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	void cmd();
	void checkCollision(const sf::FloatRect& platformBounds);
	const sf::FloatRect getBounds() const { return getRectanguloColision(); }
	
	// atributos de juego
	int getVidas() const { return _vidas; }
	int getPuntaje() const { return _puntaje; }
	void sumarPuntos(int p) { _puntaje += p; }
	void perderVida() { if (_vidas > 0) _vidas--; }
	
	bool isOnGround() const { return _enSuelo; }

private:
	sf::RectangleShape _body;
	float _gravedad;
	float _velocidadSalto;
	bool _enSuelo;
	int _vidas;
	int _puntaje;
};
