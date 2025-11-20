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
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    sf::Vector2f getPosicion() const { return sf::Vector2f(posX, posY); }
    
    // Getters de dimensiones
    float getAncho() const { return ancho; }
    float getAlto() const { return alto; }
    sf::Vector2f getTamano() const { return sf::Vector2f(ancho, alto); }
    
    // Getters de velocidad
    float getVelX() const { return velX; }
    float getVelY() const { return velY; }
    sf::Vector2f getVelocidad() const { return sf::Vector2f(velX, velY); }
    
    // Setters de posición
    void setPosX(float x) { posX = x; }
    void setPosY(float y) { posY = y; }
    void setPosicion(float x, float y) { posX = x; posY = y; }
    void setPosicion(const sf::Vector2f& pos) { posX = pos.x; posY = pos.y; }
    
    // Setters de velocidad
    void setVelX(float vx) { velX = vx; }
    void setVelY(float vy) { velY = vy; }
    void setVelocidad(float vx, float vy) { velX = vx; velY = vy; }
    void setVelocidad(const sf::Vector2f& vel) { velX = vel.x; velY = vel.y; }
    
    // Métodos de colisión
    bool colisionaCon(const Entidad& otra) const;
    sf::FloatRect getRectanguloColision() const { 
        return sf::FloatRect(posX, posY, ancho, alto); 
    }

protected:
    float posX, posY;    // Posición
    float velX, velY;    // Velocidad
    float ancho, alto;   // Dimensiones
};