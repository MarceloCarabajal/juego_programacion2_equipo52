#include "NivelStart.h"

NivelStart::NivelStart() {
    _fuente.loadFromFile("recursos/PressStart2P-Regular.ttf");
    _texto.setFont(_fuente);
    _texto.setCharacterSize(28);
    _texto.setFillColor(sf::Color(255, 255, 0));

}

void NivelStart::setNivel(int numero) {
    _continuar = false;

    _texto.setString("NIVEL " + std::to_string(numero));

    // Obtener el tamaño real del texto
    sf::FloatRect bounds = _texto.getLocalBounds();

    // Centrado en la ventana 800x600
    float x = (800 - bounds.width) / 2 - bounds.left;
    float y = (600 - bounds.height) / 2 - bounds.top;

    _texto.setPosition(x, y);
}


void NivelStart::procesarEvento(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        _continuar = true;
    }
}

void NivelStart::draw(sf::RenderWindow& window) {
    window.draw(_texto);
}
