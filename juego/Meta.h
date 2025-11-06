#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

class Meta : public Entidad, public sf::Drawable {
public:
    Meta(float posX, float posY, float ancho, float alto);
    virtual ~Meta() = default;
    
    // Métodos virtuales sobrescritos
    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Métodos específicos de Meta
    bool verificarLlegada(const Entidad& jugador);
    
    // Getters
    bool estaAlcanzada() const { return alcanzada; }
    
    // Setters
    void setAlcanzada(bool estado) { alcanzada = estado; }
    
private:
    bool alcanzada;
    
    // Representación visual
    sf::RectangleShape bandera;
    sf::RectangleShape poste;
    
    // Colores
    sf::Color colorBandera;
    sf::Color colorPoste;
    sf::Color colorAlcanzada;
};