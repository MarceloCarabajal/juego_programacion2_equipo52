#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Background : public sf::Drawable {
public:
    Background();
    Background(const std::string& nombreImagen);
    
    void cargarImagen(const std::string& nombreImagen);
    void setTamanoVentana(float ancho, float alto);
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    sf::Texture _textura;
    sf::Sprite _sprite;
    float _anchoVentana;
    float _altoVentana;
};

