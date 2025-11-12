#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Puntaje.h"
#include "juego/Menu.h"
#include "juego/EstadosJuego.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    EstadoJuego estado = EstadoJuego::MENU;
    Menu menu;
    Nivel nivel;
    Puntaje puntaje;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (estado == EstadoJuego::MENU) {
                menu.procesarEvento(event, window);
            }
        }

        if (estado == EstadoJuego::MENU) {
            if (menu.estaIniciandoJuego()) {
                estado = EstadoJuego::JUGANDO;
            }

            window.clear();
            window.draw(menu);
            window.display();
        }
        else if (estado == EstadoJuego::JUGANDO) {
            nivel.procesarInput();
            nivel.update();
            puntaje.update(*nivel.getJugador());

            window.clear();
            nivel.dibujarTodo(window);
            window.draw(puntaje);
            window.display();
        }
    }

    return 0;
}
