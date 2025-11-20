#include "Nivel3.h"

Nivel3::Nivel3()
    : _cantidadPlataformas(0), _cantidadEnemigos(0), _meta(720.f, 120.f, 50.f, 100.f)
{
    _nivelCompletado = false;   // ✔ importante
    _gameOver = false;          // ✔ importante

    cargarPlataformas();
    posicionarEnemigos();
    colocarMeta();

    _jugador.setPosX(50.f);
    _jugador.setPosY(518.f); // ✔ correcto
    _jugador.setEnSuelo(true);
}

void Nivel3::cargarPlataformas() {
    _cantidadPlataformas = 0;

    // Plataforma del suelo - color más oscuro
    sf::Color colorSuelo(40, 100, 60); // Verde más oscuro para el suelo
    _plataformas[_cantidadPlataformas] = Plataforma(0.f, 550.f, 800.f, 50.f);
    _plataformas[_cantidadPlataformas].setColor(colorSuelo);
    _cantidadPlataformas++;

    // Plataformas flotantes - con color diferente (marrón/beige)
    sf::Color colorPlataformaFlotante(139, 90, 43); // Color marrón/beige para plataformas flotantes

    _plataformas[_cantidadPlataformas] = Plataforma(150.f, 470.f, 80.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;
    
    _plataformas[_cantidadPlataformas] = Plataforma(280.f, 420.f, 70.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;
    
    _plataformas[_cantidadPlataformas] = Plataforma(380.f, 360.f, 60.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;

    _plataformas[_cantidadPlataformas] = Plataforma(500.f, 300.f, 80.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;
    
    _plataformas[_cantidadPlataformas] = Plataforma(620.f, 250.f, 80.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;

    _plataformas[_cantidadPlataformas] = Plataforma(680.f, 200.f, 80.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;
    
    _plataformas[_cantidadPlataformas] = Plataforma(710.f, 160.f, 70.f, 20.f);
    _plataformas[_cantidadPlataformas].setColor(colorPlataformaFlotante);
    _cantidadPlataformas++;
}

void Nivel3::posicionarEnemigos() {
    _cantidadEnemigos = 0;

    // Plataforma en 470 → enemigo en 470 - 50 = 420
    _enemigos[_cantidadEnemigos] = Enemigo(160.f, 470.f - 50.f);   // ✔ ARREGLADO
    _enemigos[_cantidadEnemigos++].setLimitePatrullaje(140.f, 210.f);

    // Plataforma en 420 → enemigo en 420 - 50 = 370
    _enemigos[_cantidadEnemigos] = Enemigo(300.f, 420.f - 50.f);   // ✔ ARREGLADO
    _enemigos[_cantidadEnemigos++].setLimitePatrullaje(260.f, 340.f);

    // Plataforma en 300 → enemigo en 250 (ya estaba bien)
    _enemigos[_cantidadEnemigos] = Enemigo(510.f, 300.f - 50.f); 
    _enemigos[_cantidadEnemigos++].setLimitePatrullaje(480.f, 560.f);

    // Plataforma en 160 → enemigo en 110 (ya estaba bien)
    _enemigos[_cantidadEnemigos] = Enemigo(700.f, 160.f - 50.f);
    _enemigos[_cantidadEnemigos++].setLimitePatrullaje(660.f, 740.f);
}

void Nivel3::colocarMeta() {
    
}

void Nivel3::procesarInput() {
    _jugador.cmd();
}

void Nivel3::update() {
    _jugador.update();

    for (int i = 0; i < _cantidadEnemigos; i++)
        _enemigos[i].update();

    for (int i = 0; i < _cantidadPlataformas; i++)
        _plataformas[i].update();

    verificarColisiones();
}

void Nivel3::verificarColisiones() {

    bool sobrePlataforma = false;

    for (int i = 0; i < _cantidadPlataformas; i++) {
        Colisiones::jugadorVsPlataforma(_jugador, _plataformas[i]);

        if (_jugador.estaSobrePlataforma(_plataformas[i].getBounds()))
            sobrePlataforma = true;
    }

    if (!sobrePlataforma && _jugador.isOnGround())
        _jugador.setEnSuelo(false);

    for (int i = 0; i < _cantidadEnemigos; i++)
        Colisiones::jugadorVsEnemigo(_jugador, _enemigos[i]);

    if (_meta.verificarLlegada(_jugador))
        _nivelCompletado = true;

    if (_jugador.getVidas() <= 0)
        _gameOver = true;
}

void Nivel3::dibujarTodo(sf::RenderTarget& target) {

    for (int i = 0; i < _cantidadPlataformas; i++)
        target.draw(_plataformas[i]);

    // Dibujar enemigos vivos o que están en proceso de desaparecer
    for (int i = 0; i < _cantidadEnemigos; i++) {
        if (_enemigos[i].estaVivo() || _enemigos[i].estaMuriendo()) {
            target.draw(_enemigos[i]);
        }
    }

    target.draw(_meta);
    target.draw(_jugador);
}
