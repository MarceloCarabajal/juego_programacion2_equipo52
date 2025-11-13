#pragma once
#include <SFML/Graphics.hpp>
#include "EstadosJuego.h"

class Menu : public sf::Drawable {
private:
    sf::Font _fuente;
    sf::Text _titulo;
    sf::Text _opcionJugar;
    sf::Text _opcionSalir;

    bool _iniciandoJuego;

public:
    Menu();

    void procesarEvento(const sf::Event& event, sf::RenderWindow& window);
    void update();
    bool estaIniciandoJuego() const { return _iniciandoJuego; }
    void reset() { _iniciandoJuego = false; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
