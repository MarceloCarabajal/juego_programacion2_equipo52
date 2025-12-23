#include "Meta.h"

Meta::Meta(float posX, float posY, float ancho, float alto)
    : Entidad(posX, posY, ancho, alto), 
      _alcanzada(false) {
    
    // configurar el poste (vertical)
    float anchoPoste = _ancho * 0.2f;
    _poste.setSize(sf::Vector2f(anchoPoste, _alto));
    _poste.setPosition(_posX, _posY);
    
    // configurar la bandera (parte superior del poste)
    float anchoBandera = _ancho * 0.8f;
    float altoBandera = _alto * 0.4f;
    _bandera.setSize(sf::Vector2f(anchoBandera, altoBandera));
    _bandera.setPosition(_posX + anchoPoste, _posY);
    
    // colores
    _colorPoste = sf::Color(139, 69, 19);  // Marrón (poste)
    _colorBandera = sf::Color(50, 200, 50);  // Verde (bandera no alcanzada)
    _colorAlcanzada = sf::Color(255, 215, 0);  // Dorado (bandera alcanzada)
    
    _poste.setFillColor(_colorPoste);
    _bandera.setFillColor(_colorBandera);
    
    // borde para mejor visibilidad
    _poste.setOutlineThickness(1.0f);
    _poste.setOutlineColor(sf::Color::Black);
    _bandera.setOutlineThickness(2.0f);
    _bandera.setOutlineColor(sf::Color::Black);
}

void Meta::update() {
    // la meta no necesita actualizarse cada frame
}

void Meta::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // dibujar el poste primero (atras)
    target.draw(_poste, states);
    // luego la bandera (adelante)
    target.draw(_bandera, states);
}

bool Meta::verificarLlegada(const Entidad& jugador) {
    // si ya fue alcanzada, retornar true
    if (_alcanzada) {
        return true;
    }
    
    // verificar colision con el jugador
    if (colisionaCon(jugador)) {
        _alcanzada = true;
        // Cambiar color de la bandera cuando se alcanza
        _bandera.setFillColor(_colorAlcanzada);
        return true;
    }
    
    return false;
}

bool Meta::estaAlcanzada() const {
    return _alcanzada;
}

void Meta::setAlcanzada(bool estado) {
    _alcanzada = estado;
}