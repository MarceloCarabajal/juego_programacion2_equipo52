#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

class Enemigo : public Entidad, public sf::Drawable {
private:
    sf::RectangleShape forma;
    bool vivo;
    bool _derrotado = false;
    int direccion; // 1 derecha, -1 izquierda
    float velocidadPatrullaje;
    float limiteIzquierdo;
    float limiteDerecho;
    float tiempoParaDesaparecer = 0.f;

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
    void derrotar() { _derrotado = true; }
    bool estaDerrotado() const { return _derrotado; }
    bool estaVivo() const { return vivo; }
   
    void desaparecer() {
    vivo = false;
    posX = -1000.f;
    posY = -1000.f;
    forma.setPosition(posX, posY);
}



// nuevo getter para detectar colisiones Jugador vs Enemigo
const sf::FloatRect getBounds() const { 
        return forma.getGlobalBounds(); 
}

protected:
    // Sobrescribimos el método draw de sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
