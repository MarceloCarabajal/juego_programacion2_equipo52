#pragma once
#include <SFML/Graphics.hpp>

class NivelStart {
private:
    sf::Font _fuente;
    sf::Text _texto;
    bool _continuar = false;

public:
    NivelStart();

    void setNivel(int numero);
    void procesarEvento(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    bool continuar() const { return _continuar; }
    void reset() { _continuar = false; }
};
