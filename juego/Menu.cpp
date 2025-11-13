#include "Menu.h"
#include <iostream>

Menu::Menu() : _iniciandoJuego(false) {
    if (!_fuente.loadFromFile("recursos/PressStart2P-Regular.ttf")) {
        std::cerr << "No se pudo cargar la fuente del menu.\n";
    }

    _titulo.setFont(_fuente);
    _titulo.setString("MINI MARIO BROS");
    _titulo.setCharacterSize(24);
    _titulo.setFillColor(sf::Color::Yellow);
    _titulo.setPosition(200, 150);

    _opcionJugar.setFont(_fuente);
    _opcionJugar.setString("Presiona ENTER para jugar");
    _opcionJugar.setCharacterSize(16);
    _opcionJugar.setFillColor(sf::Color::White);
    _opcionJugar.setPosition(180, 300);

    _opcionSalir.setFont(_fuente);
    _opcionSalir.setString("Presiona ESC para salir");
    _opcionSalir.setCharacterSize(16);
    _opcionSalir.setFillColor(sf::Color(200, 200, 200));
    _opcionSalir.setPosition(210, 350);
}

void Menu::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            _iniciandoJuego = true;
        } else if (event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
}

void Menu::update() {
   
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_titulo, states);
    target.draw(_opcionJugar, states);
    target.draw(_opcionSalir, states);
}
