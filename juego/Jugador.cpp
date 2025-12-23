#include "Jugador.h"
#include <iostream>
#include <sstream>

const float Jugador::VELOCIDAD_ANIMACION = 10.0f; // 10 frames por segundo
const int Jugador::FRAMES_INACTIVO[2] = {0, 3}; // Primera columna: frames 0 y 3
const int Jugador::FRAMES_CAMINANDO[4] = {2, 5, 8, 11}; // Columna 3: frames 2, 5, 8, 11 (asumiendo 4 filas x 3 columnas)
const int Jugador::FRAMES_SALTANDO[3] = {2, 5, 8}; // Columna 3: primeros 3 frames (2, 5, 8)

Jugador::Jugador(int numeroPersonaje) 
	: Entidad(100.f, 100.f, 32.f, 32.f), 
	  _gravedad(0.8f), 
	  _velocidadSalto(-12.0f), 
	  _enSuelo(false),
	  _frameActualInactivo(0),
	  _frameActualCaminando(0),
	  _frameActualSaltando(0),
	  _estadoAnimacionActual(EstadoAnimacionJugador::INACTIVO),
	  _mirandoDerecha(true) {
	_vidas = 3;
	_puntaje = 0;
	_invulnerable = false;
	
	// Cargar las texturas del personaje seleccionado
	cargarTexturas(numeroPersonaje);
	
	// Configurar sprite inicial
	_sprite.setTexture(_texturaInactivo);
	_sprite.setPosition(_posX, _posY);
	
	// Establecer el primer frame de la animación inactivo (frame 0, primera columna)
	_sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_INACTIVO[0], _texturaInactivo));
	
	// Ajustar tamaño del sprite al tamaño de colisión (32x32)
	sf::IntRect rectFrame = _sprite.getTextureRect();
	if (rectFrame.width > 0 && rectFrame.height > 0) {
		float escalaX = _ancho / static_cast<float>(rectFrame.width);
		float escalaY = _alto / static_cast<float>(rectFrame.height);
		_sprite.setScale(escalaX, escalaY);
	}
}

void Jugador::procesarComandos() {
	// movimiento horizontal
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_velX = -5.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_velX = 5.0f;
	}
	else {
		_velX = 0.0f;
	}
	
	// salto
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
		 sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && _enSuelo) {
		_velY = _velocidadSalto;
		_enSuelo = false;
	}
}

void Jugador::update() {
	// Aplicar gravedad
	if (!_enSuelo) {
		_velY += _gravedad;
	}
	
	// Limitar velocidad de caída
	if (_velY > 15.0f) {
		_velY = 15.0f;
	}
	
	// Actualizar posición usando velocidad de Entidad
	_posX += _velX;
	_posY += _velY;
	
	// Limitar a los bordes de la pantalla
	if (_posX < 0) {
		_posX = 0;
		_velX = 0;
	}
	if (_posX + _ancho > 800) {
		_posX = 800 - _ancho;
		_velX = 0;
	}
	if (_posY < 0) {
		_posY = 0;
		_velY = 0;
	}
	if (_posY + _alto > 600) {
		_posY = 600 - _alto;
		_velY = 0;
		_enSuelo = true;
	}

	// Control de invulnerabilidad
	if (_invulnerable && _relojInvulnerabilidad.getElapsedTime().asSeconds() > 1.5f) {
		_invulnerable = false;
		_relojInvulnerabilidad.restart();
	}
	
	// Actualizar animación según el estado del jugador
	actualizarAnimacion();
	actualizarFrameAnimacion();
	
	// Guardar posición antes de cambiar el origen (para evitar desfase)
	sf::Vector2f posicionAntes = _sprite.getPosition();
	
	// Actualizar dirección del sprite
	if (_velX > 0) {
		_mirandoDerecha = true;
	} else if (_velX < 0) {
		_mirandoDerecha = false;
	}
	
	// Voltear sprite horizontalmente si mira hacia la izquierda
	// Usar el ancho del frame actual, no el de la textura completa
	sf::IntRect rectFrameActual = _sprite.getTextureRect();
	float anchoFrameActual = static_cast<float>(rectFrameActual.width);
	
	sf::Vector2f escala = _sprite.getScale();
	if (!_mirandoDerecha) {
		_sprite.setScale(-std::abs(escala.x), escala.y);
		_sprite.setOrigin(anchoFrameActual, 0.0f);
	} else {
		_sprite.setScale(std::abs(escala.x), escala.y);
		_sprite.setOrigin(0.0f, 0.0f);
	}
	
	// Restaurar posición después de cambiar el origen para evitar desfase
	_sprite.setPosition(posicionAntes);
	
	// Efecto de parpadeo durante invulnerabilidad
	if (_invulnerable) {
		float tiempo = _relojInvulnerabilidad.getElapsedTime().asSeconds();
		int alpha = (static_cast<int>(tiempo * 10) % 2 == 0) ? 128 : 255;
		_sprite.setColor(sf::Color(255, 255, 255, alpha));
	} else {
		_sprite.setColor(sf::Color::White);
	}
	
	// Sincronizar sprite con posición de Entidad
	_sprite.setPosition(_posX, _posY);
}

void Jugador::verificarColision(const sf::FloatRect& platformBounds) {
	sf::FloatRect jugadorBounds = getRectanguloColision();
	
	if (jugadorBounds.intersects(platformBounds)) {
		if (_velY > 0 && jugadorBounds.top < platformBounds.top) {
			_posY = platformBounds.top - _alto;
			_velY = 0;
			_enSuelo = true;
			_sprite.setPosition(_posX, _posY);
		}
	}
}


void Jugador::perderVida() {
    if (!_invulnerable && _vidas > 0) {
        _vidas--;
        _invulnerable = true;
        _relojInvulnerabilidad.restart();
        // El efecto visual de daño se maneja en update() con el parpadeo
    }
}

bool Jugador::estaSobrePlataforma(const sf::FloatRect& platformBounds) const {
	sf::FloatRect jugadorBounds = getRectanguloColision();
	
	float jugadorBottom = jugadorBounds.top + jugadorBounds.height;
	float plataformaTop = platformBounds.top;
	float tolerancia = 5.0f;
	
	bool sobreVerticalmente = (jugadorBottom >= plataformaTop - tolerancia) && 
	                           (jugadorBottom <= plataformaTop + tolerancia);
	
	bool sobreHorizontalmente = (jugadorBounds.left < platformBounds.left + platformBounds.width) &&
	                            (jugadorBounds.left + jugadorBounds.width > platformBounds.left);
	
	return sobreVerticalmente && sobreHorizontalmente;
}


void Jugador::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}

const sf::FloatRect Jugador::obtenerLimites() const {
	return getRectanguloColision();
}

sf::Vector2f Jugador::getVelocidad() const {
	return sf::Vector2f(_velX, _velY);
}

void Jugador::setEnSuelo(bool enSuelo) {
	_enSuelo = enSuelo;
}

int Jugador::getVidas() const {
	return _vidas;
}

int Jugador::getPuntaje() const {
	return _puntaje;
}

void Jugador::sumarPuntos(int p) {
	_puntaje += p;
}

void Jugador::setPuntaje(int p) {
	_puntaje = p;
}

bool Jugador::estaEnSuelo() const {
	return _enSuelo;
}

bool Jugador::estaInvulnerable() const {
	return _invulnerable;
}

void Jugador::cargarTexturas(int numeroPersonaje) {
	// Construir rutas a las texturas
	std::string rutaInactivo = construirRuta("idle", numeroPersonaje);
	std::string rutaCaminando = construirRuta("walk", numeroPersonaje);
	
	const char* rutasBase[] = {
		"recursos/sprites/jugador/",      // Ruta relativa desde el ejecutable (Debug/recursos/sprites/jugador/)
		"../recursos/sprites/jugador/",   // Ruta relativa desde Debug/
		"../../recursos/sprites/jugador/", // Ruta relativa desde Debug/juego/
		"sprites/jugador/",                // Fallback: directorio actual
		""                                 // Último fallback: directorio raíz
	};
	
	bool inactivoCargada = false, caminandoCargada = false;
	
	for (int i = 0; i < 5; i++) {
		std::string rutaCompletaInactivo = rutasBase[i] + rutaInactivo;
		std::string rutaCompletaCaminando = rutasBase[i] + rutaCaminando;
		
		if (!inactivoCargada && _texturaInactivo.loadFromFile(rutaCompletaInactivo)) {
			inactivoCargada = true;
			std::cout << "Textura inactivo cargada desde: " << rutaCompletaInactivo << std::endl;
		}
		if (!caminandoCargada && _texturaCaminando.loadFromFile(rutaCompletaCaminando)) {
			caminandoCargada = true;
			std::cout << "Textura caminando cargada desde: " << rutaCompletaCaminando << std::endl;
		}
		
		if (inactivoCargada && caminandoCargada) {
			break;
		}
	}
	
	if (!inactivoCargada || !caminandoCargada) {
		std::cerr << "Warning: No se pudieron cargar todas las texturas del personaje " << numeroPersonaje << std::endl;
		if (!inactivoCargada) std::cerr << "  - No se pudo cargar: " << rutaInactivo << std::endl;
		if (!caminandoCargada) std::cerr << "  - No se pudo cargar: " << rutaCaminando << std::endl;
		
		// Crear texturas placeholder si no se cargaron
		if (!inactivoCargada) {
			_texturaInactivo.create(32, 32);
			sf::Image img;
			img.create(32, 32, sf::Color::Blue);
			_texturaInactivo.update(img);
		}
		if (!caminandoCargada) _texturaCaminando = _texturaInactivo;
	}
}

std::string Jugador::construirRuta(const std::string& tipoAnimacion, int numeroPersonaje) {
	std::stringstream ss;
	ss << numeroPersonaje << " " << tipoAnimacion << ".png";
	return ss.str();
}

void Jugador::actualizarAnimacion() {
	EstadoAnimacionJugador nuevoEstado;
	
	// Determinar el estado de animación según el estado del jugador
	if (!_enSuelo) {
		// Está en el aire (saltando o cayendo)
		nuevoEstado = EstadoAnimacionJugador::SALTANDO;
	} else if (_velX != 0.0f) {
		// Está en el suelo y moviéndose
		nuevoEstado = EstadoAnimacionJugador::CAMINANDO;
	} else {
		// Está en el suelo y quieto
		nuevoEstado = EstadoAnimacionJugador::INACTIVO;
	}
	
	// Cambiar de estado si es necesario
	if (nuevoEstado != _estadoAnimacionActual) {
		_estadoAnimacionActual = nuevoEstado;
		_relojAnimacion.restart(); // Reiniciar el reloj al cambiar de estado
	}
}

void Jugador::actualizarFrameAnimacion() {
	float tiempoTranscurrido = _relojAnimacion.getElapsedTime().asSeconds();
	float tiempoPorFrame = 1.0f / VELOCIDAD_ANIMACION;
	
	// Actualizar el frame según el estado actual
	switch (_estadoAnimacionActual) {
		case EstadoAnimacionJugador::INACTIVO: {
			int indiceAnimacion = static_cast<int>(tiempoTranscurrido / tiempoPorFrame) % FRAMES_POR_ANIMACION_INACTIVO;
			_frameActualInactivo = indiceAnimacion;
			_sprite.setTexture(_texturaInactivo);
			_sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_INACTIVO[indiceAnimacion], _texturaInactivo));
			break;
		}
		case EstadoAnimacionJugador::CAMINANDO: {
			int indiceAnimacion = static_cast<int>(tiempoTranscurrido / tiempoPorFrame) % FRAMES_POR_ANIMACION_CAMINANDO;
			_frameActualCaminando = indiceAnimacion;
			_sprite.setTexture(_texturaCaminando);
			_sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_CAMINANDO[indiceAnimacion], _texturaCaminando));
			break;
		}
		case EstadoAnimacionJugador::SALTANDO: {
			int indiceAnimacion = static_cast<int>(tiempoTranscurrido / tiempoPorFrame) % FRAMES_POR_ANIMACION_SALTANDO;
			_frameActualSaltando = indiceAnimacion;
			// Usar caminando.png para el salto también (sabemos que funciona bien)
			_sprite.setTexture(_texturaCaminando);
			_sprite.setTextureRect(obtenerRectanguloFrame(FRAMES_SALTANDO[indiceAnimacion], _texturaCaminando));
			break;
		}
	}
	
	// Reajustar escala después de cambiar frame (por si el tamaño del frame cambió)
	sf::IntRect rectFrame = _sprite.getTextureRect();
	if (rectFrame.width > 0 && rectFrame.height > 0) {
		float escalaX = _ancho / static_cast<float>(rectFrame.width);
		float escalaY = _alto / static_cast<float>(rectFrame.height);
		_sprite.setScale(escalaX, escalaY);
	}
}

sf::IntRect Jugador::obtenerRectanguloFrame(int frameIndex, const sf::Texture& textura) {
	sf::Vector2u tamanoTextura = textura.getSize();
	int anchoFrame = tamanoTextura.x / 3; // Siempre 3 columnas
	
	// Detectar el número de filas basándose en el tamaño de la textura
	// Calcular la relación altura/ancho para determinar número de filas
	float relacionAlturaAncho = static_cast<float>(tamanoTextura.y) / static_cast<float>(tamanoTextura.x / 3);
	
	int numFilas;
	if (relacionAlturaAncho >= 3.5f) {
		// Es un sprite sheet de 4 filas (12 frames)
		numFilas = 4;
	} else {
		// Es un sprite sheet de 2 filas (6 frames)
		numFilas = 2;
	}
	
	int altoFrame = tamanoTextura.y / numFilas;
	
	// Calcular fila y columna correctamente
	int fila = frameIndex / 3;
	int columna = frameIndex % 3;
	
	// Calcular posición exacta del frame
	int x = columna * anchoFrame;
	int y = fila * altoFrame;
	
	// Asegurarse de que el rectángulo no se salga de los límites de la textura
	if (x + anchoFrame > static_cast<int>(tamanoTextura.x)) {
		anchoFrame = tamanoTextura.x - x;
	}
	if (y + altoFrame > static_cast<int>(tamanoTextura.y)) {
		altoFrame = tamanoTextura.y - y;
	}
	
	return sf::IntRect(x, y, anchoFrame, altoFrame);
}
