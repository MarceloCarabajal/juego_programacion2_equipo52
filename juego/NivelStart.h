#pragma once
#include <SFML/Graphics.hpp>

class NivelStart {
private:
    sf::Font _fuente;
    sf::Text _texto;
    bool _continuar = false;
    sf::Clock _reloj;
    static const float TIEMPO_ESPERA; // Tiempo en segundos antes de continuar automáticamente

public:
    NivelStart();

    void setNivel(int numero);
    void procesarEvento(const sf::Event& event);
    void update(); // Actualizar el temporizador
    void draw(sf::RenderWindow& window);

    bool continuar() const { return _continuar; }
    void reset() { 
        _continuar = false;
        _reloj.restart(); // Reiniciar el temporizador
    }
};
