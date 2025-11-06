#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

class Enemigo : public Entidad, public sf::Drawable {
private:
    sf::RectangleShape forma;
    bool vivo;
    int direccion; // 1 derecha, -1 izquierda
    float velocidadPatrullaje;
    float limiteIzquierdo;
    float limiteDerecho;

    sf::Color colorNormal;
    sf::Color colorMuerto;

public:
    Enemigo(); // Constructor por defecto para arrays
    //  Constructor con valores por defecto para ancho y alto
    Enemigo(float posX, float posY, float ancho = 50.f, float alto = 50.f);

    void update();
    void patrullar();
    void morir();
    bool colisionConJugador(const Entidad& jugador);
    void setLimitePatrullaje(float limiteIzq, float limiteDer);

    // nuevo getter para detectar colisiones (Jugador vs Enemigo)
    const sf::FloatRect getBounds() const { 
        return forma.getGlobalBounds(); 
    }

protected:
    // Sobrescribimos el método draw de sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
