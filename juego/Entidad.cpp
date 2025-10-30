#include "Entidad.h"

Entidad::Entidad(float posX, float posY, float ancho, float alto)
    : posX(posX), posY(posY), ancho(ancho), alto(alto), velX(0), velY(0) {
}

bool Entidad::colisionaCon(const Entidad& otra) const {
    return getRectanguloColision().intersects(otra.getRectanguloColision());
}

sf::FloatRect Entidad::getRectanguloColision() const {
    return sf::FloatRect(posX, posY, ancho, alto);
}