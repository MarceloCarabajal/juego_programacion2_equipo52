#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>  
#include "Entidad.h"
#include "EstadoAnimacionJugador.h"

class Jugador : public Entidad, public sf::Drawable {
public:
    Jugador(int numeroPersonaje = 1);

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void procesarComandos();
    void verificarColision(const sf::FloatRect& platformBounds);
    bool estaSobrePlataforma(const sf::FloatRect& platformBounds) const;
    const sf::FloatRect obtenerLimites() const;

    sf::Vector2f getVelocidad() const;

    void setEnSuelo(bool enSuelo);

    // getters y métodos de juego
    int getVidas() const;
    int getPuntaje() const;
    void sumarPuntos(int p);
    void setPuntaje(int p);
    void perderVida(); 

    bool estaEnSuelo() const;
    bool estaInvulnerable() const;

private:
    // Sprite y texturas
    sf::Sprite _sprite;
    sf::Texture _texturaInactivo;
    sf::Texture _texturaCaminando;
    
    // Animación de frames
    int _frameActualInactivo;
    int _frameActualCaminando;
    int _frameActualSaltando;
    sf::Clock _relojAnimacion;
    static const int FRAMES_POR_ANIMACION_INACTIVO = 2; // 2 frames para inactivo
    static const int FRAMES_POR_ANIMACION_CAMINANDO = 4; // 4 frames para caminando (columna 3)
    static const int FRAMES_POR_ANIMACION_SALTANDO = 3; // 3 frames para saltando (columna 3, primeros 3)
    static const int FRAMES_INACTIVO[2]; // Frames para inactivo: 0 y 3 (primera columna)
    static const int FRAMES_CAMINANDO[4]; // Frames para caminando: columna 3 (4 frames)
    static const int FRAMES_SALTANDO[3]; // Frames para saltando: columna 3, primeros 3 frames (2, 5, 8)
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
