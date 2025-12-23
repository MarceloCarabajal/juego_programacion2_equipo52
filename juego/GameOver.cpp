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
        if (_fuente.loadFromFile(rutas[i])) {
            fuenteCargada = true;
            break;
        }
    }
    
    if (!fuenteCargada) {
        std::cerr << "Warning: no se pudo cargar la fuente GameOver\n";
    }

    _textoGameOver.setFont(_fuente);
    _textoGameOver.setString("GAME OVER");
    _textoGameOver.setCharacterSize(48); 
    _textoGameOver.setFillColor(sf::Color::Red);
    _textoGameOver.setStyle(sf::Text::Bold);
    _textoGameOver.setPosition(200, 150);

    _textoInstruccion.setFont(_fuente);
    _textoInstruccion.setString("Presiona ENTER para volver al menu");
    _textoInstruccion.setCharacterSize(20);
    _textoInstruccion.setFillColor(sf::Color::White);

    _textoPuntaje.setFont(_fuente);
    _textoPuntaje.setCharacterSize(24);
    _textoPuntaje.setFillColor(sf::Color::White);

    _textoMejoresPuntajes.setFont(_fuente);
    _textoMejoresPuntajes.setString("MEJORES PUNTAJES");
    _textoMejoresPuntajes.setCharacterSize(18);
    _textoMejoresPuntajes.setFillColor(sf::Color::Yellow);

    // Configurar textos de puntajes individuales
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        _puntajes[i].setFont(_fuente);
        _puntajes[i].setCharacterSize(14);
        _puntajes[i].setFillColor(sf::Color::White);
        _puntajes[i].setString("");
    }

    centrarTextos();
}

void GameOver::inicializar(int puntajeFinal, const GestorArchivos& gestor) {
    _puntajeFinal = puntajeFinal;
    _textoPuntaje.setString("Puntaje Final: " + std::to_string(_puntajeFinal));
    cargarMejoresPuntajes(gestor);
    centrarTextos();
}

void GameOver::cargarMejoresPuntajes(const GestorArchivos& gestor) {
    int cantidad = gestor.getCantidadRegistros();
    
    if (cantidad == 0) {
        _textoMejoresPuntajes.setString("MEJORES PUNTAJES");
        // usar el primer texto de puntaje para mostrar el mensaje
        _puntajes[0].setString("(No hay puntajes guardados)");
        for (int i = 1; i < MAX_PUNTAJES; i++) {
            _puntajes[i].setString("");
        }
        return;
    }

    // leer todos los puntajes
    int* todosPuntajes = new int[cantidad];
    int leidos = gestor.leerTodos(todosPuntajes, cantidad);
    
    // ordenar de mayor a menor usando bubble sort (solo si hay más de 1 elemento)
    if (leidos > 1) {
        for (int i = 0; i < leidos - 1; i++) {
            for (int j = 0; j < leidos - 1 - i; j++) {
                if (todosPuntajes[j] < todosPuntajes[j + 1]) {
                    // intercambiar valores
                    int temp = todosPuntajes[j];
                    todosPuntajes[j] = todosPuntajes[j + 1];
                    todosPuntajes[j + 1] = temp;
                }
            }
        }
    }
    
    // actualizar título
    _textoMejoresPuntajes.setString("MEJORES PUNTAJES");
    
    // mostrar top 5
    int mostrar = (leidos < MAX_PUNTAJES) ? leidos : MAX_PUNTAJES;
    for (int i = 0; i < mostrar; i++) {
        std::string texto = std::to_string(i + 1) + ". " + std::to_string(todosPuntajes[i]);
        _puntajes[i].setString(texto);
    }
    
    // limpiar los que no se muestran
    for (int i = mostrar; i < MAX_PUNTAJES; i++) {
        _puntajes[i].setString("");
    }
    
    delete[] todosPuntajes;
}

void GameOver::centrarTextos() {
    const float anchoVentana = 800.f;
    const float altoVentana = 600.f;

    // centrar texto principal
    sf::FloatRect bounds = _textoGameOver.getLocalBounds();
    _textoGameOver.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    _textoGameOver.setPosition(anchoVentana / 2.f, 120.f);

    // centrar texto de puntaje final
    bounds = _textoPuntaje.getLocalBounds();
    _textoPuntaje.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    _textoPuntaje.setPosition(anchoVentana / 2.f, 180.f);

    // posicionar título de mejores puntajes
    bounds = _textoMejoresPuntajes.getLocalBounds();
    _textoMejoresPuntajes.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    _textoMejoresPuntajes.setPosition(anchoVentana / 2.f, 240.f);

    // posicionar lista de puntajes (siempre posicionar todos, aunque estén vacíos)
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        bounds = _puntajes[i].getLocalBounds();
        _puntajes[i].setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        _puntajes[i].setPosition(anchoVentana / 2.f, 280.f + i * 30.f);
    }

    // centrar texto secundario (instruccion)
    bounds = _textoInstruccion.getLocalBounds();
    _textoInstruccion.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    _textoInstruccion.setPosition(anchoVentana / 2.f, 500.f);
}

void GameOver::procesarEvento(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _volver = true;
    }
}

void GameOver::dibujar(sf::RenderWindow& window) {
    window.draw(_textoGameOver);
    window.draw(_textoPuntaje);
    window.draw(_textoMejoresPuntajes);
    
    for (int i = 0; i < MAX_PUNTAJES; i++) {
        if (_puntajes[i].getString().getSize() > 0) {
            window.draw(_puntajes[i]);
        }
    }
    
    window.draw(_textoInstruccion);
}

bool GameOver::volverAlMenu() const {
    return _volver;
}

void GameOver::reset() {
    _volver = false;
}
