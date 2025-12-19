#include "Entidad.h"

Entidad::Entidad(float posX, float posY, float ancho, float alto)
    : _posX(posX), _posY(posY), _ancho(ancho), _alto(alto), _velX(0), _velY(0) {
}

bool Entidad::colisionaCon(const Entidad& otra) const {
    return getRectanguloColision().intersects(otra.getRectanguloColision());
}