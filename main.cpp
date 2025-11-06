#include <SFML/Graphics.hpp>
#include "juego/Nivel.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    Nivel nivel;

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

        // Dibujar todo
        window.clear();
        nivel.dibujarTodo(window);
        window.display();
    }

    return 0;
}
