#include "Enemigo.h"
#include <iostream>
#include <cmath>

// Definiciones de constantes que necesitan definición en el .cpp
const float Enemigo::VELOCIDAD_ANIMACION = 10.f;
const int Enemigo::FRAMES_IDLE[2] = {0, 1};
const int Enemigo::FRAMES_WALK[4] = {2, 3, 4, 5};
const float Enemigo::TIEMPO_DESAPARICION = 0.8f; // 0.8 segundos para desaparecer

// Constructores
Enemigo::Enemigo() : Enemigo(0.f, 0.f) {}

Enemigo::Enemigo(float x, float y, float a, float h)
: Entidad(x, y, a, h),
  vivo(true),
  _derrotado(false),
  _muriendo(false),
  tiempoParaDesaparecer(0.f),
  limiteIzquierdo(x - 60.f),
  limiteDerecho(x + 60.f),
  velocidadPatrullaje(1.0f),
  moviendoDerecha(true),
  _frameIdle(0),
  _frameWalk(0),
  _mirandoDerecha(true),
  _estadoActual(EstadoAnimacionEnemigo::IDLE)
{
    cargarTexturas();

    // Sprite inicial
    _sprite.setTexture(_texturaIdle);
    _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_IDLE[0], _texturaIdle));

    // Escala al tamaño de colisión
    sf::IntRect rect = _sprite.getTextureRect();
    if (rect.width > 0 && rect.height > 0) {
        float sx = ancho / static_cast<float>(rect.width);
        float sy = alto / static_cast<float>(rect.height);
        _sprite.setScale(sx, sy);
    }

    _sprite.setPosition(posX, posY);
}

// Carga de texturas
void Enemigo::cargarTexturas() {

    const char* rutasBase[] = {
        "recursos/sprites/enemigo/",
        "../recursos/sprites/enemigo/",
        "../../recursos/sprites/enemigo/",
        "sprites/enemigo/",
        ""
    };

    bool idleOK = false, walkOK = false;

    for (int i = 0; i < 5; i++) {

        if (!idleOK &&
            _texturaIdle.loadFromFile(std::string(rutasBase[i]) + "8 idle.png")) {
            idleOK = true;
            std::cout << "Enemigo idle cargado desde: " << rutasBase[i] << "8 idle.png\n";
        }

        if (!walkOK &&
            _texturaWalk.loadFromFile(std::string(rutasBase[i]) + "8 walk.png")) {
            walkOK = true;
            std::cout << "Enemigo walk cargado desde: " << rutasBase[i] << "8 walk.png\n";
        }

        if (idleOK && walkOK) break;
    }

    if (!idleOK) {
        std::cerr << "[ERROR] No se pudo cargar 8 idle.png — usando placeholder.\n";
        _texturaIdle.create(32, 32);
        sf::Image img; img.create(32,32, sf::Color::Red);
        _texturaIdle.update(img);
    }
    if (!walkOK) {
        std::cerr << "[ERROR] No se pudo cargar 8 walk.png — usando idle como fallback.\n";
        _texturaWalk = _texturaIdle;
    }
}

// Update general
void Enemigo::update() {
    // Si está muriendo, actualizar la animación de desvanecimiento
    if (_muriendo) {
        float tiempoTranscurrido = _relojMuerte.getElapsedTime().asSeconds();
        float progreso = tiempoTranscurrido / TIEMPO_DESAPARICION;
        
        if (progreso >= 1.0f) {
            // Completamente desaparecido, marcar como muerto
            vivo = false;
            _muriendo = false;
            return;
        }
        
        // Calcular alpha (transparencia) - va de 255 a 0
        int alpha = static_cast<int>(255 * (1.0f - progreso));
        _sprite.setColor(sf::Color(255, 255, 255, alpha));
        
        // Opcional: hacer que el enemigo se mueva ligeramente hacia abajo mientras desaparece
        posY += 0.5f; // Movimiento suave hacia abajo
        
        _sprite.setPosition(posX, posY);
        return;
    }
    
    if (!vivo) return;

    // Asegurar que el color esté en blanco (sin transparencia) cuando está vivo
    _sprite.setColor(sf::Color::White);

    patrullar();
    actualizarAnimacion();
    actualizarFrameAnimacion();

    // Flip horizontal igual que en Jugador
    sf::IntRect rect = _sprite.getTextureRect();
    float w = static_cast<float>(rect.width);

    sf::Vector2f escala = _sprite.getScale();
    if (moviendoDerecha) {
        _sprite.setScale(std::abs(escala.x), escala.y);
        _sprite.setOrigin(0.f, 0.f);
    } else {
        _sprite.setScale(-std::abs(escala.x), escala.y);
        _sprite.setOrigin(w, 0.f);
    }

    _sprite.setPosition(posX, posY);
}

// Patrullaje
void Enemigo::patrullar() {

    float vx = moviendoDerecha ? velocidadPatrullaje : -velocidadPatrullaje;
    velX = vx;
    posX += velX;

    if (posX < limiteIzquierdo) {
        posX = limiteIzquierdo;
        moviendoDerecha = true;
    }
    if (posX > limiteDerecho) {
        posX = limiteDerecho;
        moviendoDerecha = false;
    }
}

void Enemigo::setLimitePatrullaje(float izq, float der) {
    limiteIzquierdo = izq;
    limiteDerecho = der;
}

// Selección de animación 
void Enemigo::actualizarAnimacion() {
    if (std::abs(velX) > 0.2f)
        _estadoActual = EstadoAnimacionEnemigo::CAMINANDO;
    else
        _estadoActual = EstadoAnimacionEnemigo::IDLE;
}

// Aplicar frame correcto 
void Enemigo::actualizarFrameAnimacion() {
    float t = _relojAnimacion.getElapsedTime().asSeconds();
    float tiempoPorFrame = 1.f / VELOCIDAD_ANIMACION;

    if (_estadoActual == EstadoAnimacionEnemigo::IDLE) {
        int idx = static_cast<int>(t / tiempoPorFrame) % FRAMES_POR_IDLE;
        _sprite.setTexture(_texturaIdle);
        _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_IDLE[idx], _texturaIdle));
    }
    else {
        int idx = static_cast<int>(t / tiempoPorFrame) % FRAMES_POR_WALK;
        _sprite.setTexture(_texturaWalk);
        _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_WALK[idx], _texturaWalk));
    }

    // reescala al tamaño de colisión
    sf::IntRect rect = _sprite.getTextureRect();
    if (rect.width > 0 && rect.height > 0) {
        float sx = ancho / static_cast<float>(rect.width);
        float sy = alto / static_cast<float>(rect.height);
        _sprite.setScale(sx, sy);
    }
}

// Calcular frame
sf::IntRect Enemigo::obtenerRectanguloFrame(int frameIndex, const sf::Texture& tex) {

    sf::Vector2u size = tex.getSize();
    int anchoFrame = static_cast<int>(size.x / 3u);

    int filas;
    float relacion = static_cast<float>(size.y) / static_cast<float>(anchoFrame);

    filas = (relacion > 3.0f ? 4 : 2);
    int altoFrame = static_cast<int>(size.y / filas);

    int fila = frameIndex / 3;
    int col = frameIndex % 3;

    int x = col * anchoFrame;
    int y = fila * altoFrame;

    // seguridad límites
    if (x + anchoFrame > static_cast<int>(size.x)) anchoFrame = static_cast<int>(size.x) - x;
    if (y + altoFrame > static_cast<int>(size.y)) altoFrame = static_cast<int>(size.y) - y;

    return sf::IntRect(x, y, anchoFrame, altoFrame);
}

// Colisión
bool Enemigo::colisionConJugador(const Entidad& jugador) {
    return _sprite.getGlobalBounds().intersects(jugador.getRectanguloColision());
}

// Morir
void Enemigo::morir() {
    if (!vivo || _muriendo) return; // Ya está muerto o muriendo
    
    _muriendo = true;
    _relojMuerte.restart();
    // No marcar como muerto inmediatamente, esperar a que termine la animación
}

// Dibujar
void Enemigo::draw(sf::RenderTarget& t, sf::RenderStates s) const {
    // Dibujar si está vivo o si está en proceso de desaparecer
    if (vivo || _muriendo) {
        t.draw(_sprite, s);
    }
}
