#pragma once
#include <SFML/Graphics.hpp>
#include "Entidad.h"
#include "EstadoAnimacionEnemigo.h"

class Enemigo : public Entidad, public sf::Drawable {
private:
    // sprite y texturas
    sf::Sprite _sprite;
    sf::Texture _texturaInactivo;
    sf::Texture _texturaCaminando;

    // animacion
    static const float VELOCIDAD_ANIMACION;
    static const int FRAMES_INACTIVO[2];
    static const int FRAMES_CAMINANDO[4];
    static const int FRAMES_POR_INACTIVO = 2;
    static const int FRAMES_POR_CAMINANDO = 4;

    int _frameInactivo;
    int _frameCaminando;
    EstadoAnimacionEnemigo _estadoActual;
    sf::Clock _relojAnimacion;
    bool _mirandoDerecha;

    // patrullaje
    float _limiteIzquierdo;
    float _limiteDerecho;
    float _velocidadPatrullaje;
    bool _moviendoDerecha;

    // estado
    bool _vivo;
    bool _derrotado;
    bool _muriendo;
    float _tiempoParaDesaparecer;
    sf::Clock _relojMuerte;
    static const float TIEMPO_DESAPARICION;

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

    void derrotar();
    bool estaDerrotado() const;
    bool estaVivo() const;
    bool estaMuriendo() const;

    void desaparecer();

    const sf::FloatRect obtenerLimites() const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

