#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"
#include "juego/Puntaje.h"


int main()
{
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
