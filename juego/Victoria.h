#pragma once
#include <SFML/Graphics.hpp>

class Victoria : public sf::Drawable {
public:
    Victoria();

    void procesarEvento(const sf::Event& event, sf::RenderWindow& window);
    bool volverAlMenu() const { return _volverAlMenu; }
    void reset();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Font _fuente;
    sf::Text _textoTitulo;
    sf::Text _textoSubtitulo;
    bool _volverAlMenu;
};
