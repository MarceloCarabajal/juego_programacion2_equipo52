#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Puntaje.h"
#include "juego/GestorArchivos.h"
#include <iostream>

int main()
{
    // prueba de gestor de archivos
    GestorArchivos gestor;
    std::cout << "=== PRUEBA DE GESTOR ARCHIVOS ===" << std::endl;
    
    // guardar diferentes puntajes de prueba (por ahora  para ver si funciona)
    int cantidadActual = gestor.getCantidadRegistros();
    if (cantidadActual == 0) {
        std::cout << "Guardando puntajes de prueba..." << std::endl;
        gestor.guardar(500);
        gestor.guardar(1200);
        gestor.guardar(2500);
        gestor.guardar(1800);
        std::cout << "Puntajes de prueba guardados!" << std::endl;
    } else {
        std::cout << "Ya existen " << cantidadActual << " puntajes guardados." << std::endl;
    }
    
    gestor.mostrarPuntajes();
    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    Nivel nivel;
    Puntaje puntaje;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Procesar input y actualizar
        nivel.procesarInput();
        nivel.update();
        
        // Getter devuelve puntero que accede a Jugador
        puntaje.update(*nivel.getJugador());


        // Dibujar todo
        window.clear();
        nivel.dibujarTodo(window);
        window.draw(puntaje);
        window.display();
    }

    return 0;
}
