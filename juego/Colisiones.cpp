#include "Colisiones.h"
#include <iostream>

void Colisiones::jugadorVsPlataforma(Jugador& jugador, const Plataforma& plataforma) {
    jugador.verificarColision(plataforma.obtenerLimites());
}

void Colisiones::jugadorVsEnemigo(Jugador& jugador, Enemigo& enemigo) {
    // verificar que el enemigo este vivo y no este muriendo antes de procesar colisiones
    if (!enemigo.estaVivo() || enemigo.estaMuriendo()) {
        return;
    }
    
    sf::FloatRect jugadorBounds = jugador.obtenerLimites();
    sf::FloatRect enemigoBounds = enemigo.obtenerLimites();

    if (jugadorBounds.intersects(enemigoBounds)) {
        sf::Vector2f velocidad = jugador.getVelocidad();
        
        // colision desde arriba: jugador cae sobre el enemigo
        if (jugadorBounds.top + jugadorBounds.height - 10 < enemigoBounds.top &&
            velocidad.y > 0) {
            enemigo.morir();
            jugador.sumarPuntos(100);
            std::cout << "Enemigo derrotado! +100 puntos" << std::endl;
        } else {
            // colision lateral o inferior: jugador pierde vida
            jugador.perderVida();
            std::cout << "Jugador golpeado por enemigo! Vidas: " << jugador.getVidas() << std::endl;
        }
    }
}
