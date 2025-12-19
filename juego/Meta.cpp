#include "Meta.h"

Meta::Meta(float posX, float posY, float ancho, float alto)
    : Entidad(posX, posY, ancho, alto), 
      _alcanzada(false) {
    
    // Configurar el poste (vertical)
    float anchoPoste = _ancho * 0.2f;
    _poste.setSize(sf::Vector2f(anchoPoste, _alto));
    _poste.setPosition(_posX, _posY);
    
    // Configurar la bandera (parte superior del poste)
    float anchoBandera = _ancho * 0.8f;
    float altoBandera = _alto * 0.4f;
    _bandera.setSize(sf::Vector2f(anchoBandera, altoBandera));
    _bandera.setPosition(_posX + anchoPoste, _posY);
    
    // Colores
    _colorPoste = sf::Color(139, 69, 19);  // Marrón (poste)
    _colorBandera = sf::Color(50, 200, 50);  // Verde (bandera no alcanzada)
    _colorAlcanzada = sf::Color(255, 215, 0);  // Dorado (bandera alcanzada)
    
    _poste.setFillColor(_colorPoste);
    _bandera.setFillColor(_colorBandera);
    
    // Borde para mejor visibilidad
    _poste.setOutlineThickness(1.0f);
    _poste.setOutlineColor(sf::Color::Black);
    _bandera.setOutlineThickness(2.0f);
    _bandera.setOutlineColor(sf::Color::Black);
}

void Meta::update() {
    // La meta no necesita actualizarse cada frame
}

void Meta::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar el poste primero (atrás)
    target.draw(_poste, states);
    // Luego la bandera (adelante)
    target.draw(_bandera, states);
}

bool Meta::verificarLlegada(const Entidad& jugador) {
    // Si ya fue alcanzada, retornar true
    if (_alcanzada) {
        return true;
    }
    
    // Verificar colisión con el jugador
    if (colisionaCon(jugador)) {
        _alcanzada = true;
        // Cambiar color de la bandera cuando se alcanza
        _bandera.setFillColor(_colorAlcanzada);
        return true;
    }
    
    return false;
}