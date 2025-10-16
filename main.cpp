#include <SFML/Graphics.hpp>
#include "Pelotita.h"

int main()
{   

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60);

	Pelotita player;

    /// game loop
    while (window.isOpen())
    {
        /// eventos - input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		player.cmd();

        /// update - logica
        player.update();

		/// draw - render
        window.clear();
        window.draw(player);
        window.display();
    }

    /// liberar memoria

    return 0;
}