#pragma once
#include <SFML/Graphics.hpp>

class GameOver {
public:
    GameOver();

    void procesarEvento(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool volverAlMenu() const;
    void reset();

private:
    sf::Font fuente;
    sf::Text textoGameOver;
    sf::Text textoInstruccion;

    bool volver = false;

    void centrarTextos();
};
