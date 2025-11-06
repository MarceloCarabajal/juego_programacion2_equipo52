#include "Colisiones.h"
#include <iostream>

void Colisiones::jugadorVsPlataforma(Jugador& jugador, const Plataforma& plataforma) {
    jugador.checkCollision(plataforma.getBounds());
}

void Colisiones::jugadorVsEnemigo(Jugador& jugador, Enemigo& enemigo) {
    sf::FloatRect jugadorBounds = jugador.getBounds();
    sf::FloatRect enemigoBounds = enemigo.getBounds();

    if (jugadorBounds.intersects(enemigoBounds)) {
        if (jugadorBounds.top + jugadorBounds.height - 10 < enemigoBounds.top &&
            jugador.getVelocidad().y > 0) {
            enemigo.morir();
            std::cout << "Enemigo derrotado!" << std::endl;
        } else {
            std::cout << "Jugador golpeado por enemigo!" << std::endl;
            // Luego: jugador.restarVida();
        }
    }
}
