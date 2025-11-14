#include "GameOver.h"
#include "GestorArchivos.h"
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

    textoPuntaje.setFont(fuente);
    textoPuntaje.setCharacterSize(24);
    textoPuntaje.setFillColor(sf::Color::White);

    textoMejoresPuntajes.setFont(fuente);
    textoMejoresPuntajes.setString("MEJORES PUNTAJES");
    textoMejoresPuntajes.setCharacterSize(18);
    textoMejoresPuntajes.setFillColor(sf::Color::Yellow);

    // Configurar textos de puntajes individuales
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        _puntajes[i].setFont(fuente);
        _puntajes[i].setCharacterSize(14);
        _puntajes[i].setFillColor(sf::Color::White);
        _puntajes[i].setString("");
    }

    centrarTextos();
}

void GameOver::inicializar(int puntajeFinal, const GestorArchivos& gestor) {
    _puntajeFinal = puntajeFinal;
    textoPuntaje.setString("Puntaje Final: " + std::to_string(_puntajeFinal));
    cargarMejoresPuntajes(gestor);
    centrarTextos();
}

void GameOver::cargarMejoresPuntajes(const GestorArchivos& gestor) {
    int cantidad = gestor.getCantidadRegistros();
    
    if (cantidad == 0) {
        textoMejoresPuntajes.setString("MEJORES PUNTAJES");
        // Usar el primer texto de puntaje para mostrar el mensaje
        _puntajes[0].setString("(No hay puntajes guardados)");
        for (int i = 1; i < MAX_PUNTAJES; i++) {
            _puntajes[i].setString("");
        }
        return;
    }

    // Leer todos los puntajes
    int* todosPuntajes = new int[cantidad];
    int leidos = gestor.leerTodos(todosPuntajes, cantidad);
    
    // Ordenar de mayor a menor usando bubble sort
    for (int i = 0; i < leidos - 1; i++) {
        for (int j = 0; j < leidos - 1 - i; j++) {
            if (todosPuntajes[j] < todosPuntajes[j + 1]) {
                // Intercambiar valores
                int temp = todosPuntajes[j];
                todosPuntajes[j] = todosPuntajes[j + 1];
                todosPuntajes[j + 1] = temp;
            }
        }
    }
    
    // Actualizar título
    textoMejoresPuntajes.setString("MEJORES PUNTAJES");
    
    // Mostrar top 5
    int mostrar = (leidos < MAX_PUNTAJES) ? leidos : MAX_PUNTAJES;
    for (int i = 0; i < mostrar; i++) {
        std::string texto = std::to_string(i + 1) + ". " + std::to_string(todosPuntajes[i]);
        _puntajes[i].setString(texto);
    }
    
    // Limpiar los que no se muestran
    for (int i = mostrar; i < MAX_PUNTAJES; i++) {
        _puntajes[i].setString("");
    }
    
    delete[] todosPuntajes;
}

void GameOver::centrarTextos() {
    const float anchoVentana = 800.f;
    const float altoVentana = 600.f;

    // Centrar texto principal
    sf::FloatRect bounds = textoGameOver.getLocalBounds();
    textoGameOver.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoGameOver.setPosition(anchoVentana / 2.f, 120.f);

    // Centrar texto de puntaje final
    bounds = textoPuntaje.getLocalBounds();
    textoPuntaje.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoPuntaje.setPosition(anchoVentana / 2.f, 180.f);

    // Posicionar título de mejores puntajes
    bounds = textoMejoresPuntajes.getLocalBounds();
    textoMejoresPuntajes.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoMejoresPuntajes.setPosition(anchoVentana / 2.f, 240.f);

    // Posicionar lista de puntajes (siempre posicionar todos, aunque estén vacíos)
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        bounds = _puntajes[i].getLocalBounds();
        _puntajes[i].setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        _puntajes[i].setPosition(anchoVentana / 2.f, 280.f + i * 30.f);
    }

    // Centrar texto secundario (instrucción)
    bounds = textoInstruccion.getLocalBounds();
    textoInstruccion.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    textoInstruccion.setPosition(anchoVentana / 2.f, 500.f);
}

void GameOver::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        volver = true;
    }
}

void GameOver::draw(sf::RenderWindow& window) {
    window.draw(textoGameOver);
    window.draw(textoPuntaje);
    window.draw(textoMejoresPuntajes);
    
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        if (_puntajes[i].getString().getSize() > 0) {
            window.draw(_puntajes[i]);
        }
    }
    
    window.draw(textoInstruccion);
}

bool GameOver::volverAlMenu() const {
    return volver;
}

void GameOver::reset() {
    volver = false;
}
