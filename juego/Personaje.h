#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

class Personaje : public Entidad, public sf::Drawable {
public:
    Personaje();
    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape _body;
};
