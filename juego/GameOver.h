#pragma once
#include <SFML/Graphics.hpp>

class GestorArchivos;

class GameOver {
public:
    GameOver();

    void inicializar(int puntajeFinal, const GestorArchivos& gestor);
    void procesarEvento(const sf::Event& event, sf::RenderWindow& window);
    void dibujar(sf::RenderWindow& window);
    bool volverAlMenu() const;
    void reset();

private:
    sf::Font _fuente;
    sf::Text _textoGameOver;
    sf::Text _textoPuntaje;
    sf::Text _textoMejoresPuntajes;
    sf::Text _textoInstruccion;
    sf::Text _puntajes[5]; // Top 5 puntajes

    bool _volver = false;
    int _puntajeFinal = 0;
    static const int MAX_PUNTAJES = 5;

    void centrarTextos();
    void cargarMejoresPuntajes(const GestorArchivos& gestor);
};
