#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Nivel2.h"
#include "juego/Nivel3.h"
#include "juego/Puntaje.h"
#include "juego/Menu.h"
#include "juego/NivelStart.h"
#include "juego/EstadosJuego.h"
#include "juego/GameOver.h"
#include "juego/Victoria.h"
#include "juego/GestorArchivos.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lara Bros");
    window.setFramerateLimit(60);

    EstadoJuego estado = EstadoJuego::MENU;
    GestorArchivos gestor("juego/puntajes.dat");
    Menu menu;

    // Niveles
    Nivel nivel1;
    Nivel2 nivel2;
    Nivel3 nivel3;

    NivelStart nivelStart;
    int nivelActual = 1;

    Puntaje puntaje;
    GameOver gameOver;
    Victoria victoria;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // MENU
            if (estado == EstadoJuego::MENU) {
                menu.procesarEvento(event, window);
            }

            // PANTALLA "NIVEL X"
            else if (estado == EstadoJuego::NIVEL_START) {
                nivelStart.procesarEvento(event);
            }

            // GAME OVER
            else if (estado == EstadoJuego::GAME_OVER) {
                gameOver.procesarEvento(event, window);
                if (gameOver.volverAlMenu()) {
                    gameOver.reset();
                    menu.reset();
                    estado = EstadoJuego::MENU;
                }
            }

            // VICTORIA
            else if (estado == EstadoJuego::VICTORIA) {
                victoria.procesarEvento(event, window);
                if (victoria.volverAlMenu()) {
                    victoria.reset();
                    menu.reset();
                    estado = EstadoJuego::MENU;
                }
            }
        }

        // LÓGICA DE CADA ESTADO

        // MENU
        if (estado == EstadoJuego::MENU) {
            if (menu.estaIniciandoJuego()) {
                menu.reset();

                nivelActual = 1;
                nivel1 = Nivel();
                puntaje.reset();

                nivelStart.setNivel(nivelActual);
                nivelStart.reset();

                estado = EstadoJuego::NIVEL_START;
            }

            window.clear();
            window.draw(menu);
            window.display();
        }

        // PANTALLA "NIVEL X"
        else if (estado == EstadoJuego::NIVEL_START) {
            // Actualizar el temporizador para continuar automáticamente
            nivelStart.update();
            
            // Verificar si el usuario quiere continuar (por tecla o automáticamente)
            if (nivelStart.continuar()) {
                // Cambiar al nivel correspondiente
                nivelStart.reset(); // Resetear el flag antes de cambiar de estado
                estado = EstadoJuego::JUGANDO;
            }

            window.clear();
            nivelStart.draw(window);
            window.display();
        }

        // JUGANDO (cualquier nivel)
        else if (estado == EstadoJuego::JUGANDO) {

            // Selección dinámica del nivel actual
            if (nivelActual == 1) {
                nivel1.procesarInput();
                nivel1.update();
                puntaje.update(*nivel1.getJugador());

                if (nivel1.gameOver()) {
                    int p = nivel1.getJugador()->getPuntaje();
                    gestor.guardar(p);
                    gameOver.inicializar(p, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel1.nivelCompletado()) {
                    nivelActual = 2;
                    nivel2 = Nivel2();
                    nivelStart.setNivel(nivelActual);
                    nivelStart.reset();
                    estado = EstadoJuego::NIVEL_START;
                }
                else {
                    window.clear();
                    nivel1.dibujarTodo(window);
                    window.draw(puntaje);
                    window.display();
                }
            }

            else if (nivelActual == 2) {
                nivel2.procesarInput();
                nivel2.update();
                puntaje.update(*nivel2.getJugador());

                if (nivel2.gameOver()) {
                    int p = nivel2.getJugador()->getPuntaje();
                    gestor.guardar(p);
                    gameOver.inicializar(p, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel2.nivelCompletado()) {
                    nivelActual = 3;
                    nivel3 = Nivel3();
                    nivelStart.setNivel(nivelActual);
                    nivelStart.reset();
                    estado = EstadoJuego::NIVEL_START;
                }
                else {
                    window.clear();
                    nivel2.dibujarTodo(window);
                    window.draw(puntaje);
                    window.display();
                }
            }

            else if (nivelActual == 3) {
                nivel3.procesarInput();
                nivel3.update();
                puntaje.update(*nivel3.getJugador());

                if (nivel3.gameOver()) {
                    int p = nivel3.getJugador()->getPuntaje();
                    gestor.guardar(p);
                    gameOver.inicializar(p, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel3.nivelCompletado()) {
                    int p = nivel3.getJugador()->getPuntaje();
                    gestor.guardar(p);
                    victoria.inicializar(p);
                    estado = EstadoJuego::VICTORIA;
                }

                window.clear();
                nivel3.dibujarTodo(window);
                window.draw(puntaje);
                window.display();
            }
        }

        // GAME OVER
        else if (estado == EstadoJuego::GAME_OVER) {
            window.clear();
            gameOver.draw(window);
            window.display();
        }

        // VICTORIA FINAL
        else if (estado == EstadoJuego::VICTORIA) {
            window.clear();
            window.draw(victoria);
            window.display();
        }
    }

    return 0;
}
