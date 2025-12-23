#include "Entidad.h"

Entidad::Entidad(float posX, float posY, float ancho, float alto)
    : _posX(posX), _posY(posY), _ancho(ancho), _alto(alto), _velX(0), _velY(0) {
}

// Getters de posición
float Entidad::getPosX() const {
    return _posX;
}

float Entidad::getPosY() const {
    return _posY;
}

sf::Vector2f Entidad::getPosicion() const {
    return sf::Vector2f(_posX, _posY);
}

// Getters de dimensiones
float Entidad::getAncho() const {
    return _ancho;
}

float Entidad::getAlto() const {
    return _alto;
}

sf::Vector2f Entidad::getTamano() const {
    return sf::Vector2f(_ancho, _alto);
}

// Getters de velocidad
float Entidad::getVelX() const {
    return _velX;
}

float Entidad::getVelY() const {
    return _velY;
}

sf::Vector2f Entidad::getVelocidad() const {
    return sf::Vector2f(_velX, _velY);
}

// Setters de posición
void Entidad::setPosX(float x) {
    _posX = x;
}

void Entidad::setPosY(float y) {
    _posY = y;
}

void Entidad::setPosicion(float x, float y) {
    _posX = x;
    _posY = y;
}

void Entidad::setPosicion(const sf::Vector2f& pos) {
    _posX = pos.x;
    _posY = pos.y;
}

// Setters de velocidad
void Entidad::setVelX(float vx) {
    _velX = vx;
}

void Entidad::setVelY(float vy) {
    _velY = vy;
}

void Entidad::setVelocidad(float vx, float vy) {
    _velX = vx;
    _velY = vy;
}

void Entidad::setVelocidad(const sf::Vector2f& vel) {
    _velX = vel.x;
    _velY = vel.y;
}

// Métodos de colisión
bool Entidad::colisionaCon(const Entidad& otra) const {
    return getRectanguloColision().intersects(otra.getRectanguloColision());
}

sf::FloatRect Entidad::getRectanguloColision() const {
    return sf::FloatRect(_posX, _posY, _ancho, _alto);
}