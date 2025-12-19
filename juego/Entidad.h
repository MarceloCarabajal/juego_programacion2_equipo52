#pragma once
#include <SFML/Graphics.hpp>

/**
 * Clase base abstracta para todas las entidades del juego.
 * Proporciona funcionalidad básica de posición, velocidad, dimensiones y colisiones.
 */
class Entidad {
public:
    // Constructor
    Entidad(float posX, float posY, float ancho, float alto);
    virtual ~Entidad() = default;
    
    // Métodos virtuales puros (clase abstracta)
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
   
    // Getters de posición
    float getPosX() const { return _posX; }
    float getPosY() const { return _posY; }
    sf::Vector2f getPosicion() const { return sf::Vector2f(_posX, _posY); }
    
    // Getters de dimensiones
    float getAncho() const { return _ancho; }
    float getAlto() const { return _alto; }
    sf::Vector2f getTamano() const { return sf::Vector2f(_ancho, _alto); }
    
    // Getters de velocidad
    float getVelX() const { return _velX; }
    float getVelY() const { return _velY; }
    sf::Vector2f getVelocidad() const { return sf::Vector2f(_velX, _velY); }
    
    // Setters de posición
    void setPosX(float x) { _posX = x; }
    void setPosY(float y) { _posY = y; }
    void setPosicion(float x, float y) { _posX = x; _posY = y; }
    void setPosicion(const sf::Vector2f& pos) { _posX = pos.x; _posY = pos.y; }
    
    // Setters de velocidad
    void setVelX(float vx) { _velX = vx; }
    void setVelY(float vy) { _velY = vy; }
    void setVelocidad(float vx, float vy) { _velX = vx; _velY = vy; }
    void setVelocidad(const sf::Vector2f& vel) { _velX = vel.x; _velY = vel.y; }
    
    // Métodos de colisión
    bool colisionaCon(const Entidad& otra) const;
    sf::FloatRect getRectanguloColision() const { 
        return sf::FloatRect(_posX, _posY, _ancho, _alto); 
    }

protected:
    float _posX, _posY;    // Posición
    float _velX, _velY;    // Velocidad
    float _ancho, _alto;   // Dimensiones
};