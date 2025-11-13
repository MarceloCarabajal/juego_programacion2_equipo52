#include "Meta.h"

Meta::Meta(float posX, float posY, float ancho, float alto)
    : Entidad(posX, posY, ancho, alto), 
      alcanzada(false) {
    
    // Configurar el poste (vertical)
    float anchoPoste = ancho * 0.2f;
    poste.setSize(sf::Vector2f(anchoPoste, alto));
    poste.setPosition(posX, posY);
    
    // Configurar la bandera (parte superior del poste)
    float anchoBandera = ancho * 0.8f;
    float altoBandera = alto * 0.4f;
    bandera.setSize(sf::Vector2f(anchoBandera, altoBandera));
    bandera.setPosition(posX + anchoPoste, posY);
    
    // Colores
    colorPoste = sf::Color(139, 69, 19);  // Marrón (poste)
    colorBandera = sf::Color(50, 200, 50);  // Verde (bandera no alcanzada)
    colorAlcanzada = sf::Color(255, 215, 0);  // Dorado (bandera alcanzada)
    
    poste.setFillColor(colorPoste);
    bandera.setFillColor(colorBandera);
    
    // Borde para mejor visibilidad
    poste.setOutlineThickness(1.0f);
    poste.setOutlineColor(sf::Color::Black);
    bandera.setOutlineThickness(2.0f);
    bandera.setOutlineColor(sf::Color::Black);
}

void Meta::update() {
    // La meta no necesita actualizarse cada frame
}

void Meta::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar el poste primero (atrás)
    target.draw(poste, states);
    // Luego la bandera (adelante)
    target.draw(bandera, states);
}

bool Meta::verificarLlegada(const Entidad& jugador) {
    // Si ya fue alcanzada, retornar true
    if (alcanzada) {
        return true;
    }
    
    // Verificar colisión con el jugador
    if (colisionaCon(jugador)) {
        alcanzada = true;
        // Cambiar color de la bandera cuando se alcanza
        bandera.setFillColor(colorAlcanzada);
        return true;
    }
    
    return false;
}