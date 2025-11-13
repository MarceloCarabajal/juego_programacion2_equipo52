#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>  
#include "Entidad.h"

class Jugador : public Entidad, public sf::Drawable {
public:
    Jugador();

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void cmd();
    void checkCollision(const sf::FloatRect& platformBounds);
    bool estaSobrePlataforma(const sf::FloatRect& platformBounds) const;
    const sf::FloatRect getBounds() const { return getRectanguloColision(); }

    sf::Vector2f getVelocidad() const { return sf::Vector2f(velX, velY); }

    void setEnSuelo(bool enSuelo) { _enSuelo = enSuelo; }

    // getters y métodos de juego
    int getVidas() const { return _vidas; }
    int getPuntaje() const { return _puntaje; }
    void sumarPuntos(int p) { _puntaje += p; }
    void perderVida();  // implementación en .cpp

    bool isOnGround() const { return _enSuelo; }
    bool estaInvulnerable() const { return _invulnerable; }

private:
    sf::RectangleShape _body;
    float _gravedad;
    float _velocidadSalto;
    bool _enSuelo;
    int _vidas;
    int _puntaje;

    // ---- nuevos para invulnerabilidad ----
    bool _invulnerable;
    sf::Clock _relojInvulnerabilidad;
};
