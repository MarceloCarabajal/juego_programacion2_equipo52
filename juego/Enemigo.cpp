#include "Enemigo.h"

Enemigo::Enemigo(float posX, float posY, float ancho, float alto) // Inicializa la clase base Entidad con posiciones y dimensiones
    : Entidad(posX, posY, ancho, alto), 
      vivo(true), // configura estado inicial
      direccion(1), //derecha
      velocidadPatrullaje(50.0f),
      limiteIzquierdo(posX - 100.0f),
      limiteDerecho(posX + 100.0f) {
    
    // Configurar la forma visual del enemigo
    forma.setSize(sf::Vector2f(ancho, alto));
    forma.setPosition(posX, posY);
    
    // Colores para estados
    colorNormal = sf::Color(180, 50, 50);  // Rojo oscuro (Goomba)
    colorMuerto = sf::Color(100, 100, 100);  // Gris
    
    forma.setFillColor(colorNormal);
    forma.setOutlineThickness(2.0f);
    forma.setOutlineColor(sf::Color::Black);
}

void Enemigo::update() {
    if (!vivo) {
        return;  // Si está muerto, no hace nada
    }
    
    patrullar(); // si esta vivo ejecuta patrullar
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(forma, states);
}

void Enemigo::patrullar() {
    if (!vivo) return;
    
    // Mover el enemigo en la dirección actual
    float desplazamiento = velocidadPatrullaje * direccion * (1.0f / 60.0f); 
    posX += desplazamiento;
    
    // Verificar límites y cambiar dirección si es necesario
    if (posX <= limiteIzquierdo) {
        posX = limiteIzquierdo;
        direccion = 1;  // Cambiar a derecha
    } else if (posX >= limiteDerecho) {
        posX = limiteDerecho;
        direccion = -1;  // Cambiar a izquierda
    }
    
    // Actualizar posición de la forma visual
    forma.setPosition(posX, posY);
}

void Enemigo::morir() {
    if (vivo) {
        vivo = false;
        forma.setFillColor(colorMuerto);
        // Opcional: hacer el enemigo más chico cuando muere
        forma.setSize(sf::Vector2f(ancho, alto * 0.5f));
        posY += alto * 0.5f;  // Ajustar posición para que "aplaste"
        forma.setPosition(posX, posY);
    }
}

bool Enemigo::colisionConJugador(const Entidad& jugador) {
    if (!vivo) return false;
    
    return colisionaCon(jugador);
}

void Enemigo::setLimitePatrullaje(float limiteIzq, float limiteDer) {
    limiteIzquierdo = limiteIzq;
    limiteDerecho = limiteDer;
}