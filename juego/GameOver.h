#pragma once
#include <SFML/Graphics.hpp>

class GameOver {
public:
    GameOver();

    void update();
    void draw(sf::RenderWindow& window);
    bool volverAlMenu() const;

private:
    sf::Font fuente;
    sf::Text textoGameOver;
    sf::Text textoInstruccion;

    bool volver = false;

    void centrarTextos();
};
