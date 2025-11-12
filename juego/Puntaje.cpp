#include "Puntaje.h"
#include <iostream>

Puntaje::Puntaje() : _tiempoTranscurrido(0.f) {
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
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
    }

    _textoPuntaje.setFont(_fuente);
    _textoVidas.setFont(_fuente);
    _textoTiempo.setFont(_fuente);

    _textoPuntaje.setCharacterSize(14);
    _textoVidas.setCharacterSize(14);
    _textoTiempo.setCharacterSize(14);

    _textoPuntaje.setFillColor(sf::Color::White);
    _textoVidas.setFillColor(sf::Color::White);
    _textoTiempo.setFillColor(sf::Color::White);

    _textoPuntaje.setPosition(10.f, 10.f);
    _textoVidas.setPosition(10.f, 30.f);
    _textoTiempo.setPosition(10.f, 50.f);
}

void Puntaje::update(const Jugador& jugador) {
    _tiempoTranscurrido = _reloj.getElapsedTime().asSeconds();

    _textoPuntaje.setString("Puntaje: " + std::to_string(jugador.getPuntaje()));
    _textoVidas.setString("Vidas: " + std::to_string(jugador.getVidas()));
    _textoTiempo.setString("Tiempo: " + std::to_string(static_cast<int>(_tiempoTranscurrido)));
}

void Puntaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_textoPuntaje, states);
    target.draw(_textoVidas, states);
    target.draw(_textoTiempo, states);
}
