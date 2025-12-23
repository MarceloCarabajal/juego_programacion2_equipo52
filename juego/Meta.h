#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

class Meta : public Entidad, public sf::Drawable {
public:
    Meta(float posX, float posY, float ancho, float alto);
    virtual ~Meta() = default;
    
    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    

    bool verificarLlegada(const Entidad& jugador);
    
    bool estaAlcanzada() const;
    
    void setAlcanzada(bool estado);
    
private:
    bool _alcanzada;
    
    sf::RectangleShape _bandera;
    sf::RectangleShape _poste;
    
    sf::Color _colorBandera;
    sf::Color _colorPoste;
    sf::Color _colorAlcanzada;
};