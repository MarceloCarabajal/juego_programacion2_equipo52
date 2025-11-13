#include "Victoria.h"
#include <iostream>

Victoria::Victoria() : _volverAlMenu(false) {
    if (!_fuente.loadFromFile("recursos/PressStart2P-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente en Victoria" << std::endl;
    }

    const float anchoVentana = 800.f;
    const float altoVentana = 600.f;

    // === Texto principal ===
    _textoTitulo.setFont(_fuente);
    _textoTitulo.setString("¡Victoria!");
    _textoTitulo.setCharacterSize(24);
    _textoTitulo.setFillColor(sf::Color::Yellow);
    _textoTitulo.setStyle(sf::Text::Bold);

    // Calcular posición centrada
    sf::FloatRect boundsTitulo = _textoTitulo.getLocalBounds();
    _textoTitulo.setOrigin(boundsTitulo.left + boundsTitulo.width / 2.0f,
                           boundsTitulo.top + boundsTitulo.height / 2.0f);
    _textoTitulo.setPosition(anchoVentana / 2.0f, 200.f);

    // Subtítulo
    _textoSubtitulo.setFont(_fuente);
    _textoSubtitulo.setString("Presiona Enter para volver al menu");
    _textoSubtitulo.setCharacterSize(16);
    _textoSubtitulo.setFillColor(sf::Color::White);

    // Calcular posición centrada
    sf::FloatRect boundsSubtitulo = _textoSubtitulo.getLocalBounds();
    _textoSubtitulo.setOrigin(boundsSubtitulo.left + boundsSubtitulo.width / 2.0f,
                              boundsSubtitulo.top + boundsSubtitulo.height / 2.0f);
    _textoSubtitulo.setPosition(anchoVentana / 2.0f, 350.f);
}

void Victoria::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _volverAlMenu = true;
    }
}

void Victoria::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_textoTitulo, states);
    target.draw(_textoSubtitulo, states);
}
