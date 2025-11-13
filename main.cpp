#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Puntaje.h"
#include "juego/Menu.h"
#include "juego/EstadosJuego.h"
#include "juego/GameOver.h"
#include "juego/Victoria.h"

int main()
{
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
        bool cambiarEstado = false;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // ======= MENU =======
            if (estado == EstadoJuego::MENU) {
                menu.procesarEvento(event, window);
            }
            // ======= GAME OVER =======
            else if (estado == EstadoJuego::GAME_OVER) {
                gameOver.procesarEvento(event, window);
                // Verificar inmediatamente después de procesar el evento
                if (gameOver.volverAlMenu()) {
                    gameOver.reset();
                    menu.reset(); // Resetear el flag del menu para evitar iniciar juego inmediatamente
                    estado = EstadoJuego::MENU;
                    cambiarEstado = true;
                    break; // Salir del loop de eventos para evitar procesar el mismo evento en Menu
                }
            }
            // ======= VICTORIA =======
            else if (estado == EstadoJuego::VICTORIA) {
                victoria.procesarEvento(event, window);
                // Verificar inmediatamente después de procesar el evento
                if (victoria.volverAlMenu()) {
                    victoria.reset();
                    menu.reset(); // Resetear el flag del menu para evitar iniciar juego inmediatamente
                    estado = EstadoJuego::MENU;
                    cambiarEstado = true;
                    break; // Salir del loop de eventos para evitar procesar el mismo evento en Menu
                }
            }
        }
        
        // Si se cambió el estado, saltar el dibujado y continuar
        if (cambiarEstado) {
            continue;
        }

        // ======= MENU =======
        if (estado == EstadoJuego::MENU) {
            if (menu.estaIniciandoJuego()) {
                menu.reset();
                // Reiniciar el nivel para empezar un juego nuevo
                nivel = Nivel();
                puntaje.reset();
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
            window.clear();
            gameOver.draw(window);
            window.display();
        }

        // ======= VICTORIA =======
        else if (estado == EstadoJuego::VICTORIA) {
            window.clear();
            window.draw(victoria);
            window.display();
        }
    }

    return 0;
}
