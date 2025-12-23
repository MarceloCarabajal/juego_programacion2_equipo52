#include "Background.h"
#include <iostream>

Background::Background() : _anchoVentana(800.f), _altoVentana(600.f) {
}

Background::Background(const std::string& nombreImagen) : _anchoVentana(800.f), _altoVentana(600.f) {
    cargarImagen(nombreImagen);
}

void Background::cargarImagen(const std::string& nombreImagen) {
    // intentar cargar desde multiples rutas (igual que Jugador y Enemigo)
    // las imágenes estan en recursos/sprites/background/
    const char* rutasBase[] = {
        "recursos/sprites/background/",
        "../recursos/sprites/background/",
        "../../recursos/sprites/background/",
        "recursos/background/",
        "../recursos/background/",
        "../../recursos/background/",
        ""
    };
    
    bool imagenCargada = false;
    std::string rutaExitosa = "";
    
    for (int i = 0; i < 7; i++) {
        std::string rutaCompleta = std::string(rutasBase[i]) + nombreImagen;
        
        if (_textura.loadFromFile(rutaCompleta)) {
            sf::Vector2u tamano = _textura.getSize();
            if (tamano.x > 0 && tamano.y > 0) {
                imagenCargada = true;
                rutaExitosa = rutaCompleta;
                std::cout << "Background cargado desde: " << rutaExitosa 
                          << " (tamaño: " << tamano.x << "x" << tamano.y << ")" << std::endl;
                break;
            }
        }
    }
    
    if (!imagenCargada) {
        std::cerr << "ERROR: No se pudo cargar el background: " << nombreImagen << std::endl;
        std::cerr << "Creando textura de fallback (negro)..." << std::endl;
        // Crear textura de fallback (negro)
        _textura.create(800, 600);
        sf::Image img;
        img.create(800, 600, sf::Color::Black);
        _textura.update(img);
    }
    
    _sprite.setTexture(_textura);
    setTamanoVentana(_anchoVentana, _altoVentana);
}

void Background::setTamanoVentana(float ancho, float alto) {
    _anchoVentana = ancho;
    _altoVentana = alto;
    
    sf::Vector2u tamanoTextura = _textura.getSize();
    if (tamanoTextura.x > 0 && tamanoTextura.y > 0) {
        // escalar el sprite para cubrir toda la ventana
        float escalaX = _anchoVentana / static_cast<float>(tamanoTextura.x);
        float escalaY = _altoVentana / static_cast<float>(tamanoTextura.y);
        _sprite.setScale(escalaX, escalaY);
        _sprite.setPosition(0.f, 0.f);
    }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_sprite.getTexture() != nullptr) {
        target.draw(_sprite, states);
    }
}

