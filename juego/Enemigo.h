#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidad.h"

class Enemigo : public Entidad {
public:
    Enemigo(float posX, float posY, float ancho, float alto);
    virtual ~Enemigo() = default;
    
    // Métodos virtuales sobrescritos
    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Métodos específicos del enemigo
    void patrullar();
    void morir();
    bool colisionConJugador(const Entidad& jugador);
    
    // Getters
    bool estaVivo() const { return vivo; }
    int getDireccion() const { return direccion; }
    
    // Setters
    void setDireccion(int dir) { direccion = dir; }
    void setLimitePatrullaje(float limiteIzq, float limiteDer);
    
private:
    bool vivo;
    int direccion;  // -1 = izquierda, 1 = derecha
    float velocidadPatrullaje;
    float limiteIzquierdo;
    float limiteDerecho;
    
    // Para animación básica
    sf::RectangleShape forma;
    sf::Color colorNormal;
    sf::Color colorMuerto;
};