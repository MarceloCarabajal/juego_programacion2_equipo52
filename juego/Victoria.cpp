#include "Victoria.h"
#include <iostream>

Victoria::Victoria() : _volverAlMenu(false) {
    // Intentar cargar la fuente desde diferentes rutas
    const char* rutas[] = {
        "recursos/PressStart2P-Regular.ttf",
        "../recursos/PressStart2P-Regular.ttf",
        "../../recursos/PressStart2P-Regular.ttf"
    };
    
    bool fuenteCargada = false;
    for (int i = 0; i < 3; i++) {
        if (_fuente.loadFromFile(rutas[i])) {
            fuenteCargada = true;
            break;
        }
    }
    
    if (!fuenteCargada) {
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

    // Texto de puntaje
    _textoPuntaje.setFont(_fuente);
    _textoPuntaje.setCharacterSize(20);
    _textoPuntaje.setFillColor(sf::Color::White);

    // Subtítulo
    _textoSubtitulo.setFont(_fuente);
    _textoSubtitulo.setString("Presiona Enter para volver al menu");
    _textoSubtitulo.setCharacterSize(16);
    _textoSubtitulo.setFillColor(sf::Color::White);

    // Calcular posición centrada
    sf::FloatRect boundsSubtitulo = _textoSubtitulo.getLocalBounds();
    _textoSubtitulo.setOrigin(boundsSubtitulo.left + boundsSubtitulo.width / 2.0f,
                              boundsSubtitulo.top + boundsSubtitulo.height / 2.0f);
    _textoSubtitulo.setPosition(anchoVentana / 2.0f, 400.f);
}

void Victoria::inicializar(int puntajeFinal) {
    _puntajeFinal = puntajeFinal;
    _textoPuntaje.setString("Puntaje Final: " + std::to_string(_puntajeFinal));
    
    // Calcular posición centrada del puntaje
    sf::FloatRect boundsPuntaje = _textoPuntaje.getLocalBounds();
    _textoPuntaje.setOrigin(boundsPuntaje.left + boundsPuntaje.width / 2.0f,
                           boundsPuntaje.top + boundsPuntaje.height / 2.0f);
    _textoPuntaje.setPosition(800.f / 2.0f, 280.f);
}

void Victoria::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _volverAlMenu = true;
    }
}

void Victoria::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_textoTitulo, states);
    target.draw(_textoPuntaje, states);
    target.draw(_textoSubtitulo, states);
}

void Victoria::reset() {
    _volverAlMenu = false;
}
