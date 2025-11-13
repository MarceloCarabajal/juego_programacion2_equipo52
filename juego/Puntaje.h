#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Jugador.h"

class Puntaje : public sf::Drawable {
private:
    sf::Font _fuente;
    sf::Text _textoPuntaje;
    sf::Text _textoVidas;
    sf::Text _textoTiempo;
    sf::Clock _reloj;

    float _tiempoTranscurrido;

public:
    Puntaje();

    void update(const Jugador& jugador);
    void reset();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
