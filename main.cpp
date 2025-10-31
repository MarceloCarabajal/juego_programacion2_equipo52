#include <SFML/Graphics.hpp>
//#include "juego/Pelotita.h"
#include "juego/Jugador.h"
#include "juego/Plataforma.h"
#include "juego/Enemigo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    Jugador jugador;
    Plataforma piso(0.f, 550.f, 800.f, 50.f);
    Enemigo enemigo(400.f, 500.f); // <-- agregado

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualización lógica
        jugador.update();
        piso.update();
        enemigo.update();

        // Dibujado
        window.clear();
        window.draw(piso);
        window.draw(jugador);
        window.draw(enemigo); // <-- agregado
        window.display();
    }

    return 0;
}
