#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Texture* texture, int x, int y, float movement_speed,int type,sf::IntRect textureSize, int hp)
{
	// loading textures
	this->speed = movement_speed;
	this->health = hp;
	// setting up textures
	textureSize.left = textureSize.width * type;
	this->enemy.setPosition(x, y);
	this->enemy.setTextureRect(textureSize);	
	this->enemy.setScale(0.50, 0.50);
	this->enemy.setTexture(*texture);
	
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->enemy.getGlobalBounds();
}

const sf::Vector2f Enemy::getPosition() const
{
	return this->enemy.getPosition();
}

void Enemy::loseHP(int damage)
{
	this->health -= damage;
}

void Enemy::moveEnemy()
{
	this->enemy.move(-this->speed, 0.f);
}


void Enemy::renderEnemy(sf::RenderWindow* target)
{
	target->draw(this->enemy);
}


