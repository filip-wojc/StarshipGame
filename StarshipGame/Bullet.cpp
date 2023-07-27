#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float x, float y, float movement_speed)
{
	this->bullet.setTexture(*texture);
	this->bullet.setScale(0.045f, 0.045f);
	this->bullet.setPosition(x,y);
	this->speed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const	 // accessing bounds
{
	return this->bullet.getGlobalBounds();
}

const sf::Vector2f Bullet::getPosition() const	// access to bullet position
{
	return this->bullet.getPosition();
}

void Bullet::moveBullet()						// updating movement
{
	this->bullet.move(this->speed, 0.0f);
}

void Bullet::render(sf::RenderWindow* target)	// rendering bullet to the target
{
	target->draw(this->bullet);
}