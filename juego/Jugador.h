#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>  
#include "Entidad.h"
#include "EstadoAnimacionJugador.h"

class Jugador : public Entidad, public sf::Drawable {
public:
    Jugador(int numeroPersonaje = 1); // Número del personaje (1-10)

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void cmd();
    void checkCollision(const sf::FloatRect& platformBounds);
    bool estaSobrePlataforma(const sf::FloatRect& platformBounds) const;
    const sf::FloatRect getBounds() const { return getRectanguloColision(); }

    sf::Vector2f getVelocidad() const { return sf::Vector2f(_velX, _velY); }

    void setEnSuelo(bool enSuelo) { _enSuelo = enSuelo; }

    // getters y métodos de juego
    int getVidas() const { return _vidas; }
    int getPuntaje() const { return _puntaje; }
    void sumarPuntos(int p) { _puntaje += p; }
    void setPuntaje(int p) { _puntaje = p; }
    void perderVida();  // implementación en .cpp

    bool isOnGround() const { return _enSuelo; }
    bool estaInvulnerable() const { return _invulnerable; }

private:
    // Sprite y texturas
    sf::Sprite _sprite;
    sf::Texture _texturaIdle;
    sf::Texture _texturaWalk; // También se usa para salto
    
    // Animación de frames
    int _frameActualIdle;
    int _frameActualWalk;
    int _frameActualJump;
    sf::Clock _relojAnimacion;
    static const int FRAMES_POR_ANIMACION_IDLE = 2; // 2 frames para idle
    static const int FRAMES_POR_ANIMACION_WALK = 4; // 4 frames para walk (columna 3)
    static const int FRAMES_POR_ANIMACION_JUMP = 3; // 3 frames para jump (columna 3, primeros 3)
    static const int FRAMES_IDLE[2]; // Frames para idle: 0 y 3 (primera columna)
    static const int FRAMES_WALK[4]; // Frames para walk: columna 3 (4 frames)
    static const int FRAMES_JUMP[3]; // Frames para jump: columna 3, primeros 3 frames (2, 5, 8)
    static const float VELOCIDAD_ANIMACION; // Frames por segundo
    
    EstadoAnimacionJugador _estadoAnimacionActual;
    bool _mirandoDerecha; // true = derecha, false = izquierda
    
    // Física
    float _gravedad;
    float _velocidadSalto;
    bool _enSuelo;
    
    // Estado del juego
    int _vidas;
    int _puntaje;

    // Invulnerabilidad
    bool _invulnerable;
    sf::Clock _relojInvulnerabilidad;
    
    // Métodos privados
    void cargarTexturas(int numeroPersonaje);
    void actualizarAnimacion();
    void actualizarFrameAnimacion();
    sf::IntRect obtenerRectanguloFrame(int frameIndex, const sf::Texture& textura);
    std::string construirRuta(const std::string& tipoAnimacion, int numeroPersonaje);
};
