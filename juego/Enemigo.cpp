#include "Enemigo.h"
#include <iostream>
#include <cmath>

// Definiciones de constantes que necesitan definición en el .cpp
const float Enemigo::VELOCIDAD_ANIMACION = 10.f;
const int Enemigo::FRAMES_INACTIVO[2] = {0, 1};
const int Enemigo::FRAMES_CAMINANDO[4] = {2, 3, 4, 5};
const float Enemigo::TIEMPO_DESAPARICION = 0.8f; // 0.8 segundos para desaparecer

// Constructores
Enemigo::Enemigo() : Enemigo(0.f, 0.f) {}

Enemigo::Enemigo(float x, float y, float a, float h)
: Entidad(x, y, a, h),
  _vivo(true),
  _derrotado(false),
  _muriendo(false),
  _tiempoParaDesaparecer(0.f),
  _limiteIzquierdo(x - 60.f),
  _limiteDerecho(x + 60.f),
  _velocidadPatrullaje(1.0f),
  _moviendoDerecha(true),
  _frameInactivo(0),
  _frameCaminando(0),
  _mirandoDerecha(true),
  _estadoActual(EstadoAnimacionEnemigo::INACTIVO)
{
    cargarTexturas();

    // sprite inicial
    _sprite.setTexture(_texturaInactivo);
    _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_INACTIVO[0], _texturaInactivo));

    // Escala al tamaño de colisión
    sf::IntRect rect = _sprite.getTextureRect();
    if (rect.width > 0 && rect.height > 0) {
        float sx = _ancho / static_cast<float>(rect.width);
        float sy = _alto / static_cast<float>(rect.height);
        _sprite.setScale(sx, sy);
    }

    _sprite.setPosition(_posX, _posY);
}

// carga de texturas
void Enemigo::cargarTexturas() {

    const char* rutasBase[] = {
        "recursos/sprites/enemigo/",
        "../recursos/sprites/enemigo/",
        "../../recursos/sprites/enemigo/",
        "sprites/enemigo/",
        ""
    };

    bool inactivoOK = false, caminandoOK = false;

    for (int i = 0; i < 5; i++) {

        if (!inactivoOK &&
            _texturaInactivo.loadFromFile(std::string(rutasBase[i]) + "8 idle.png")) {
            inactivoOK = true;
            std::cout << "Enemigo inactivo cargado desde: " << rutasBase[i] << "8 idle.png\n";
        }

        if (!caminandoOK &&
            _texturaCaminando.loadFromFile(std::string(rutasBase[i]) + "8 walk.png")) {
            caminandoOK = true;
            std::cout << "Enemigo caminando cargado desde: " << rutasBase[i] << "8 walk.png\n";
        }

        if (inactivoOK && caminandoOK) break;
    }

    if (!inactivoOK) {
        std::cerr << "[ERROR] No se pudo cargar 8 idle.png — usando placeholder.\n";
        _texturaInactivo.create(32, 32);
        sf::Image img; img.create(32,32, sf::Color::Red);
        _texturaInactivo.update(img);
    }
    if (!caminandoOK) {
        std::cerr << "[ERROR] No se pudo cargar 8 walk.png — usando inactivo como fallback.\n";
        _texturaCaminando = _texturaInactivo;
    }
}

// update general
void Enemigo::update() {
    // Si esta muriendo, actualiza la animación de desvanecimiento
    if (_muriendo) {
        float tiempoTranscurrido = _relojMuerte.getElapsedTime().asSeconds();
        float progreso = tiempoTranscurrido / TIEMPO_DESAPARICION;
        
        if (progreso >= 1.0f) {
            // completamente desaparecido, marcar como muerto
            _vivo = false;
            _muriendo = false;
            return;
        }
        
        // calculo de alpha (transparencia) - va de 255 a 0
        int alpha = static_cast<int>(255 * (1.0f - progreso));
        _sprite.setColor(sf::Color(255, 255, 255, alpha));
        
        // hacer que el enemigo se mueva ligeramente hacia abajo mientras desaparece
        _posY += 0.5f; // movimiento suave hacia abajo
        
        _sprite.setPosition(_posX, _posY);
        return;
    }
    
    if (!_vivo) return;

    // asegurar que el color esté en blanco (sin transparencia) cuando esta vivo
    _sprite.setColor(sf::Color::White);

    patrullar();
    actualizarAnimacion();
    actualizarFrameAnimacion();

    // flip horizontal igual que en Jugador
    sf::IntRect rect = _sprite.getTextureRect();
    float w = static_cast<float>(rect.width);

    sf::Vector2f escala = _sprite.getScale();
    if (_moviendoDerecha) {
        _sprite.setScale(std::abs(escala.x), escala.y);
        _sprite.setOrigin(0.f, 0.f);
    } else {
        _sprite.setScale(-std::abs(escala.x), escala.y);
        _sprite.setOrigin(w, 0.f);
    }

    _sprite.setPosition(_posX, _posY);
}

// patrullaje
void Enemigo::patrullar() {

    float vx = _moviendoDerecha ? _velocidadPatrullaje : -_velocidadPatrullaje;
    _velX = vx;
    _posX += _velX;

    if (_posX < _limiteIzquierdo) {
        _posX = _limiteIzquierdo;
        _moviendoDerecha = true;
    }
    if (_posX > _limiteDerecho) {
        _posX = _limiteDerecho;
        _moviendoDerecha = false;
    }
}

void Enemigo::setLimitePatrullaje(float izq, float der) {
    _limiteIzquierdo = izq;
    _limiteDerecho = der;
}

// selección de animacion 
void Enemigo::actualizarAnimacion() {
    if (std::abs(_velX) > 0.2f)
        _estadoActual = EstadoAnimacionEnemigo::CAMINANDO;
    else
        _estadoActual = EstadoAnimacionEnemigo::INACTIVO;
}

// aplicar frame correcto 
void Enemigo::actualizarFrameAnimacion() {
    float t = _relojAnimacion.getElapsedTime().asSeconds();
    float tiempoPorFrame = 1.f / VELOCIDAD_ANIMACION;

    if (_estadoActual == EstadoAnimacionEnemigo::INACTIVO) {
        int idx = static_cast<int>(t / tiempoPorFrame) % FRAMES_POR_INACTIVO;
        _sprite.setTexture(_texturaInactivo);
        _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_INACTIVO[idx], _texturaInactivo));
    }
    else {
        int idx = static_cast<int>(t / tiempoPorFrame) % FRAMES_POR_CAMINANDO;
        _sprite.setTexture(_texturaCaminando);
        _sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_CAMINANDO[idx], _texturaCaminando));
    }

    // reescala al tamaño de colisión
    sf::IntRect rect = _sprite.getTextureRect();
    if (rect.width > 0 && rect.height > 0) {
        float sx = _ancho / static_cast<float>(rect.width);
        float sy = _alto / static_cast<float>(rect.height);
        _sprite.setScale(sx, sy);
    }
}

// calcular frame
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

    // seguridad limites
    if (x + anchoFrame > static_cast<int>(size.x)) anchoFrame = static_cast<int>(size.x) - x;
    if (y + altoFrame > static_cast<int>(size.y)) altoFrame = static_cast<int>(size.y) - y;

    return sf::IntRect(x, y, anchoFrame, altoFrame);
}

// colision
bool Enemigo::colisionConJugador(const Entidad& jugador) {
    return _sprite.getGlobalBounds().intersects(jugador.getRectanguloColision());
}

// morir
void Enemigo::morir() {
    if (!_vivo || _muriendo) return; // ya está muerto o muriendo
    
    _muriendo = true;
    _relojMuerte.restart();
    // no marcar como muerto inmediatamente, esperar a que termine la animación
}

// dibujar
void Enemigo::draw(sf::RenderTarget& t, sf::RenderStates s) const {
    // dibujar si está vivo o si está en proceso de desaparecer
    if (_vivo || _muriendo) {
        t.draw(_sprite, s);
    }
}

void Enemigo::derrotar() {
    _derrotado = true;
}

bool Enemigo::estaDerrotado() const {
    return _derrotado;
}

bool Enemigo::estaVivo() const {
    return _vivo;
}

bool Enemigo::estaMuriendo() const {
    return _muriendo;
}

void Enemigo::desaparecer() {
    _vivo = false;
    _posX = -1000.f;
    _posY = -1000.f;
    _sprite.setPosition(_posX, _posY);
}

const sf::FloatRect Enemigo::obtenerLimites() const {
    return _sprite.getGlobalBounds();
}
