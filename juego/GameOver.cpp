#include "GameOver.h"
#include <iostream>

GameOver::GameOver() {
    const char* rutas[] = {
        "recursos/PressStart2P-Regular.ttf",
        "../recursos/PressStart2P-Regular.ttf",
        "../../recursos/PressStart2P-Regular.ttf"
    };
    
    bool fuenteCargada = false;
    for (int i = 0; i < 3; i++) {
        if (fuente.loadFromFile(rutas[i])) {
            fuenteCargada = true;
            break;
        }
    }
    
    if (!fuenteCargada) {
        std::cerr << "Warning: no se pudo cargar la fuente GameOver\n";
    }

    textoGameOver.setFont(fuente);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setCharacterSize(48); 
    textoGameOver.setFillColor(sf::Color::Red);
    textoGameOver.setStyle(sf::Text::Bold);
    textoGameOver.setPosition(200, 150);

    textoInstruccion.setFont(fuente);
    textoInstruccion.setString("Presiona ENTER para volver al menu");
    textoInstruccion.setCharacterSize(20);
    textoInstruccion.setFillColor(sf::Color::White);

    centrarTextos();
}

void GameOver::centrarTextos() {
    const float anchoVentana = 800.f;
    const float altoVentana = 600.f;

    // Centrar texto principal
    sf::FloatRect bounds = textoGameOver.getLocalBounds();
    textoGameOver.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoGameOver.setPosition(anchoVentana / 2.f, altoVentana / 2.f - 80.f);

    // Centrar texto secundario
    bounds = textoInstruccion.getLocalBounds();
    textoInstruccion.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoInstruccion.setPosition(anchoVentana / 2.f, altoVentana / 2.f + 60.f);
}

void GameOver::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        volver = true;
    }
}

void GameOver::draw(sf::RenderWindow& window) {
    window.draw(textoGameOver);
    window.draw(textoInstruccion);
}

bool GameOver::volverAlMenu() const {
    return volver;
}

void GameOver::reset() {
    volver = false;
}
