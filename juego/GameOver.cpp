#include "GameOver.h"
#include <iostream>

GameOver::GameOver() {
    // Intentamos cargar la fuente 
    if (!fuente.loadFromFile("recursos/PressStart2P-Regular.ttf")) {
        std::cerr << "Warning: no se pudo cargar la fuente GameOver (recursos/PressStart2P-Regular.ttf)\n";
        // No devolvemos error: seguimos con fuente por defecto 
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

    // Centrar los textos en sus posiciones iniciales
    centrarTextos();
}

void GameOver::centrarTextos() {
    // Asumimos ventana 800x600 
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

void GameOver::update() {
    // Setear volver cuando se presione Enter
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
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
