#pragma once
#include <SFML/Graphics.hpp>

class NivelStart {
private:
    sf::Font _fuente;
    sf::Text _texto;
    bool _continuar = false;
    sf::Clock _reloj;
    static const float TIEMPO_ESPERA; 
public:
    NivelStart();

    void setNivel(int numero);
    void procesarEvento(const sf::Event& event);
    void update(); // actualiza el temporizador
    void dibujar(sf::RenderWindow& window);

    bool continuar() const;
    void reset();
};
