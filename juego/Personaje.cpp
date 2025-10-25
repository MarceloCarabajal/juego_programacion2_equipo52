#include "Personaje.h"

Personaje::Personaje()
    : Entidad(100, 100, 32, 32), _body(16.f)
{
    _body.setFillColor(sf::Color::Red);
    _body.setOrigin(16, 16);
    _body.setPosition(posX, posY);
}

void Personaje::update()
{
    // Por ahora, no hace nada
    // Solo actualizar la posición del sprite
    _body.setPosition(posX, posY);
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_body, states);
}
