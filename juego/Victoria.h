#pragma once
#include <SFML/Graphics.hpp>

class Victoria : public sf::Drawable {
public:
    Victoria();

    void inicializar(int puntajeFinal);
    void procesarEvento(const sf::Event& event, sf::RenderWindow& window);
    bool volverAlMenu() const;
    void reset();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Font _fuente;
    sf::Text _textoTitulo;
    sf::Text _textoPuntaje;
    sf::Text _textoSubtitulo;
    bool _volverAlMenu;
    int _puntajeFinal = 0;
};
