#include <SFML/Graphics.hpp>
//#include "juego/Pelotita.h"
#include "juego/Jugador.h"
#include "juego/Enemigo.h"
#include "juego/Plataforma.h"
#include "juego/Meta.h"
#include "juego/Colisiones.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Mario Bros");
    window.setFramerateLimit(60);

    Jugador jugador;
    Plataforma piso(0.f, 550.f, 800.f, 50.f);
    Enemigo enemigo(400.f, 500.f);
    Meta meta(700.0f, 450.0f, 40.0f, 100.0f); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

         // === ENTRADAS DEL JUGADOR ===
        //player.cmd();
        jugador.cmd();
        
        // === LÓGICA ===
        //player.update();
        jugador.update();
        piso.update();
        enemigo.update();
        meta.update();

        // === SISTEMA DE COLISIONES ===
        Colisiones::jugadorVsPlataforma(jugador, piso);
        Colisiones::jugadorVsEnemigo(jugador, enemigo);

        // === DIBUJADO ===
        window.clear();
        window.draw(piso);
        window.draw(jugador);
        window.draw(enemigo);
        meta.draw(window, sf::RenderStates::Default);
        window.display();
    }

    return 0;
}
