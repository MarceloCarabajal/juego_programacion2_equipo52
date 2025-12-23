#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "juego/Background.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lara Bros");
    window.setFramerateLimit(60);

    EstadoJuego estado = EstadoJuego::MENU;
    GestorArchivos gestor("juego/puntajes.dat");
    Menu menu;

    // Cargar sonido de inicio del juego
    sf::SoundBuffer bufferSonido;
    sf::Sound sonidoInicio;
    bool sonidoCargado = false;
    
    // Intentar cargar el sonido desde múltiples rutas
    const char* rutasSonido[] = {
        "recursos/sounds/lara_sound.wav",
        "../recursos/sounds/lara_sound.wav",
        "../../recursos/sounds/lara_sound.wav",
        "sounds/lara_sound.wav",
        ""
    };
    
    for (int i = 0; i < 5; i++) {
        if (bufferSonido.loadFromFile(rutasSonido[i])) {
            sonidoInicio.setBuffer(bufferSonido);
            sonidoInicio.setLoop(true); // Reproducir en bucle continuo
            sonidoCargado = true;
            std::cout << "Sonido cargado desde: " << rutasSonido[i] << std::endl;
            break;
        }
    }
    
    if (!sonidoCargado) {
        std::cerr << "Warning: No se pudo cargar el sonido lara_sound.wav" << std::endl;
    }

    // Backgrounds para cada nivel (usando clase Background)
    Background fondo1("nivel1.jpg");
    Background fondo2("nivel2.jpg");
    Background fondo3("nivel3.jpg");
    
    fondo1.setTamanoVentana(800.f, 600.f);
    fondo2.setTamanoVentana(800.f, 600.f);
    fondo3.setTamanoVentana(800.f, 600.f);

    // Niveles
    Nivel nivel1;
    Nivel2 nivel2;
    Nivel3 nivel3;

    NivelStart nivelStart;
    int nivelActual = 1;
    int puntajeAcumulado = 0; // Puntaje acumulado entre niveles

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
                // Detener el sonido cuando hay game over
                if (sonidoCargado && sonidoInicio.getStatus() == sf::Sound::Playing) {
                    sonidoInicio.stop();
                }
                
                gameOver.procesarEvento(event, window);
                if (gameOver.volverAlMenu()) {
                    gameOver.reset();
                    menu.reset();
                    estado = EstadoJuego::MENU;
                }
            }

            // VICTORIA
            else if (estado == EstadoJuego::VICTORIA) {
                // Detener el sonido cuando hay victoria
                if (sonidoCargado && sonidoInicio.getStatus() == sf::Sound::Playing) {
                    sonidoInicio.stop();
                }
                
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
            // Detener el sonido cuando estamos en el menú
            if (sonidoCargado && sonidoInicio.getStatus() == sf::Sound::Playing) {
                sonidoInicio.stop();
            }
            
            if (menu.estaIniciandoJuego()) {
                menu.reset();

                nivelActual = 1;
                puntajeAcumulado = 0; // Resetear puntaje acumulado al iniciar nuevo juego
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
                
                // Iniciar el sonido cuando empieza a jugar (se reproducirá en bucle)
                if (sonidoCargado && sonidoInicio.getStatus() != sf::Sound::Playing) {
                    sonidoInicio.play();
                }
            }

            window.clear();
            nivelStart.dibujar(window);
            window.display();
        }

        // JUGANDO (cualquier nivel)
        else if (estado == EstadoJuego::JUGANDO) {

            // Selección dinámica del nivel actual
            if (nivelActual == 1) {
                nivel1.procesarInput();
                nivel1.update();
                puntaje.update(nivel1.getJugador());

                if (nivel1.gameOver()) {
                    puntajeAcumulado += nivel1.getJugador().getPuntaje(); // Sumar puntaje del nivel actual
                    gestor.guardar(puntajeAcumulado);
                    gameOver.inicializar(puntajeAcumulado, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel1.nivelCompletado()) {
                    puntajeAcumulado += nivel1.getJugador().getPuntaje(); // Sumar puntaje del nivel 1
                    nivelActual = 2;
                    nivel2 = Nivel2(puntajeAcumulado); // Pasar puntaje acumulado al nivel 2
                    nivelStart.setNivel(nivelActual);
                    nivelStart.reset();
                    estado = EstadoJuego::NIVEL_START;
                }
                else {
                    window.clear();
                    window.draw(fondo1);
                    nivel1.dibujarTodo(window);
                    window.draw(puntaje);
                    window.display();
                }
            }

            else if (nivelActual == 2) {
                nivel2.procesarInput();
                nivel2.update();
                puntaje.update(nivel2.getJugador());

                if (nivel2.gameOver()) {
                    puntajeAcumulado = nivel2.getJugador().getPuntaje(); // El puntaje ya incluye el acumulado
                    gestor.guardar(puntajeAcumulado);
                    gameOver.inicializar(puntajeAcumulado, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel2.nivelCompletado()) {
                    puntajeAcumulado = nivel2.getJugador().getPuntaje(); // El puntaje ya incluye el acumulado
                    nivelActual = 3;
                    nivel3 = Nivel3(puntajeAcumulado); // Pasar puntaje acumulado al nivel 3
                    nivelStart.setNivel(nivelActual);
                    nivelStart.reset();
                    estado = EstadoJuego::NIVEL_START;
                }
                else {
                    window.clear();
                    window.draw(fondo2);
                    nivel2.dibujarTodo(window);
                    window.draw(puntaje);
                    window.display();
                }
            }

            else if (nivelActual == 3) {
                nivel3.procesarInput();
                nivel3.update();
                puntaje.update(nivel3.getJugador());

                if (nivel3.gameOver()) {
                    puntajeAcumulado = nivel3.getJugador().getPuntaje(); // El puntaje ya incluye el acumulado
                    gestor.guardar(puntajeAcumulado);
                    gameOver.inicializar(puntajeAcumulado, gestor);
                    estado = EstadoJuego::GAME_OVER;
                }
                else if (nivel3.nivelCompletado()) {
                    puntajeAcumulado = nivel3.getJugador().getPuntaje(); // El puntaje ya incluye el acumulado
                    gestor.guardar(puntajeAcumulado);
                    victoria.inicializar(puntajeAcumulado);
                    estado = EstadoJuego::VICTORIA;
                }

                window.clear();
                window.draw(fondo3);
                nivel3.dibujarTodo(window);
                window.draw(puntaje);
                window.display();
            }
        }

        // GAME OVER
        else if (estado == EstadoJuego::GAME_OVER) {
            window.clear();
            gameOver.dibujar(window);
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
