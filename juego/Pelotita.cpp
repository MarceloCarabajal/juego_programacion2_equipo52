#include "Pelotita.h"

Pelotita::Pelotita()
	: _body(10.f), _velocity(0, 0), _weapon({ 5, 20 })
{
	_body.setFillColor(sf::Color::Cyan);
	_weapon.setFillColor(sf::Color::Red);

	_body.setOrigin(5, 5);
	_body.setPosition(0, 0);

	_weapon.setPosition(5, 5);
	_weapon.setOrigin(0, 0);
}

void Pelotita::cmd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_velocity.x = -5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_velocity.x = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		_velocity.y = -5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		_velocity.y = 5;
	}
}

void Pelotita::update()
{
	if (_velocity.x != 0) {
		_velocity.x += (_velocity.x > 0) ? -.05f : .05f;
	}
	if (_velocity.y != 0) {
		_velocity.y += (_velocity.y > 0) ? -.05f : .05f;
	}

	move(_velocity);

	if (getPosition().x > 800) {
		setPosition(0, getPosition().y);
	}

	if (getPosition().x < 0) {
		setPosition(800, getPosition().y);
	}

	if (getPosition().y > 600) {
		setPosition(getPosition().x, 0);
	}

	if (getPosition().y < 0) {
		setPosition(getPosition().x, 600);
	}
}


void Pelotita::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(_body, states);
	target.draw(_weapon, states);
}
