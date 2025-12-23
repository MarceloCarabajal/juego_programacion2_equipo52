#pragma once
#include <SFML/Graphics.hpp>

class Entidad {
public:
    Entidad(float posX, float posY, float ancho, float alto);
    virtual ~Entidad() = default;
    
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
   
    float getPosX() const;
    float getPosY() const;
    sf::Vector2f getPosicion() const;
    
    float getAncho() const;
    float getAlto() const;
    sf::Vector2f getTamano() const;
    
    float getVelX() const;
    float getVelY() const;
    sf::Vector2f getVelocidad() const;
    
    void setPosX(float x);
    void setPosY(float y);
    void setPosicion(float x, float y);
    void setPosicion(const sf::Vector2f& pos);
    
    void setVelX(float vx);
    void setVelY(float vy);
    void setVelocidad(float vx, float vy);
    void setVelocidad(const sf::Vector2f& vel);
    
    bool colisionaCon(const Entidad& otra) const;
    sf::FloatRect getRectanguloColision() const;

protected:
    float _posX, _posY;    // posicion
    float _velX, _velY;    // velocidad
    float _ancho, _alto;   // dimension
};