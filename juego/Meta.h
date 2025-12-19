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
    bool estaAlcanzada() const { return _alcanzada; }
    
    // Setters
    void setAlcanzada(bool estado) { _alcanzada = estado; }
    
private:
    bool _alcanzada;
    
    // Representación visual
    sf::RectangleShape _bandera;
    sf::RectangleShape _poste;
    
    // Colores
    sf::Color _colorBandera;
    sf::Color _colorPoste;
    sf::Color _colorAlcanzada;
};