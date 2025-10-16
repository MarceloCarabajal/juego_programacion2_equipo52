#pragma once
#include <SFML/Graphics.hpp>

class Entidad {
public:
    Entidad(float posX, float posY, float ancho, float alto);
    virtual ~Entidad() = default;
    
    // Métodos virtuales puros (clase abstracta)
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
   
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getAncho() const { return ancho; }
    float getAlto() const { return alto; }
    float getVelX() const { return velX; }
    float getVelY() const { return velY; }
    
    void setPosX(float x) { posX = x; }
    void setPosY(float y) { posY = y; }
    void setVelX(float vx) { velX = vx; }
    void setVelY(float vy) { velY = vy; }
    
    // Metodo para verificar colisiones
    bool colisionaCon(const Entidad& otra) const;
    
    // Metodo para obtener el rectángulo de colisión
    sf::FloatRect getRectanguloColision() const;

protected:
    float posX, posY;    // Posición
    float velX, velY;    // Velocidad
    float ancho, alto;   // Dimensiones
};