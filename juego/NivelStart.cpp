#include "NivelStart.h"
#include <iostream>

const float NivelStart::TIEMPO_ESPERA = 2.5f; // 2.5 segundos antes de continuar automáticamente

NivelStart::NivelStart() {
    // intentar cargar la fuente desde diferentes rutas
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
        std::cerr << "Warning: no se pudo cargar la fuente NivelStart\n";
    }
    
    _texto.setFont(_fuente);
    _texto.setCharacterSize(28);
    _texto.setFillColor(sf::Color(255, 255, 0));
}

void NivelStart::setNivel(int numero) {
    _continuar = false;
    _reloj.restart(); // reiniciar el temporizador cuando se cambia de nivel

    _texto.setString("NIVEL " + std::to_string(numero));

    // obtener el tamaño real del texto
    sf::FloatRect bounds = _texto.getLocalBounds();

    // centrado en la ventana 800x600
    float x = (800 - bounds.width) / 2 - bounds.left;
    float y = (600 - bounds.height) / 2 - bounds.top;

    _texto.setPosition(x, y);
}

void NivelStart::update() {
    // si ha pasado el tiempo de espera, continuar automáticamente
    if (_reloj.getElapsedTime().asSeconds() >= TIEMPO_ESPERA) {
        _continuar = true;
    }
}

void NivelStart::procesarEvento(const sf::Event& event) {
    // no hacer nada - la pantalla siempre espera el tiempo completo
    // esto evita que se avance accidentalmente al presionar una tecla
}

void NivelStart::dibujar(sf::RenderWindow& window) {
    window.draw(_texto);
}

bool NivelStart::continuar() const {
    return _continuar;
}

void NivelStart::reset() {
    _continuar = false;
    _reloj.restart(); // Reiniciar el temporizador
}