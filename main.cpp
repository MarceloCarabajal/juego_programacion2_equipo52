#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Puntaje.h"
#include "juego/Menu.h"
#include "juego/EstadosJuego.h"
#include "juego/GameOver.h"
#include "juego/Victoria.h"

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    EstadoJuego estado = EstadoJuego::MENU;
    Menu menu;
    Nivel nivel;
    Puntaje puntaje;
    GameOver gameOver;
    Victoria victoria;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // ======= MENU =======
            if (estado == EstadoJuego::MENU) {
                menu.procesarEvento(event, window);
            }
        }

        // ======= MENU =======
        if (estado == EstadoJuego::MENU) {
            if (menu.estaIniciandoJuego()) {
                estado = EstadoJuego::JUGANDO;
            }

            window.clear();
            window.draw(menu);
            window.display();
        }

        // ======= JUGANDO =======
        else if (estado == EstadoJuego::JUGANDO) {
            nivel.procesarInput();
            nivel.update();
            puntaje.update(*nivel.getJugador());

            // Verificar si el jugador perdió todas las vidas (Game Over)
            if (nivel.gameOver()) {
                estado = EstadoJuego::GAME_OVER;
            }
            // Verificar si se completó el nivel
            else if (nivel.nivelCompletado()) {
                estado = EstadoJuego::VICTORIA;
            }

            window.clear();
            nivel.dibujarTodo(window);
            window.draw(puntaje);
            window.display();
        }

        // ======= GAME OVER =======
        else if (estado == EstadoJuego::GAME_OVER) {
            gameOver.update();

            window.clear();
            gameOver.draw(window);
            window.display();

            // Si el jugador presiona ENTER, retorna al menú
            if (gameOver.volverAlMenu()) {
                estado = EstadoJuego::MENU;
            }
        }

        // ======= VICTORIA =======
        else if (estado == EstadoJuego::VICTORIA) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                victoria.procesarEvento(event, window);
            }

            if (victoria.volverAlMenu()) {
                estado = EstadoJuego::MENU;
            }

            window.clear();
            window.draw(victoria);
            window.display();
        }
    }

    return 0;
}
