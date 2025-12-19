#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"

enum class EstadoAnimacionEnemigo {
    IDLE,
    CAMINANDO
};

class Enemigo : public Entidad, public sf::Drawable {
private:
    // Sprite y texturas
    sf::Sprite _sprite;
    sf::Texture _texturaIdle;
    sf::Texture _texturaWalk;

    // Animación
    static const float VELOCIDAD_ANIMACION;
    static const int FRAMES_IDLE[2];
    static const int FRAMES_WALK[4];
    static const int FRAMES_POR_IDLE = 2;
    static const int FRAMES_POR_WALK = 4;

    int _frameIdle;
    int _frameWalk;
    EstadoAnimacionEnemigo _estadoActual;
    sf::Clock _relojAnimacion;
    bool _mirandoDerecha;

    // Patrullaje
    float _limiteIzquierdo;
    float _limiteDerecho;
    float _velocidadPatrullaje;
    bool _moviendoDerecha;

    // Estado
    bool _vivo;
    bool _derrotado;
    bool _muriendo;
    float _tiempoParaDesaparecer;
    sf::Clock _relojMuerte;
    static const float TIEMPO_DESAPARICION; // Tiempo en segundos para desaparecer completamente

private:
    void cargarTexturas();
    void actualizarAnimacion();
    void actualizarFrameAnimacion();
    sf::IntRect obtenerRectanguloFrame(int frameIndex, const sf::Texture& textura);

public:
    Enemigo();
    Enemigo(float posX, float posY, float ancho = 50.f, float alto = 50.f);

    void update();
    void patrullar();
    void morir();
    bool colisionConJugador(const Entidad& jugador);
    void setLimitePatrullaje(float limiteIzq, float limiteDer);

    void derrotar() { _derrotado = true; }
    bool estaDerrotado() const { return _derrotado; }
    bool estaVivo() const { return _vivo; }
    bool estaMuriendo() const { return _muriendo; }

    void desaparecer() {
        _vivo = false;
        _posX = -1000.f;
        _posY = -1000.f;
        _sprite.setPosition(_posX, _posY);
    }

    const sf::FloatRect getBounds() const {
        return _sprite.getGlobalBounds();
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

