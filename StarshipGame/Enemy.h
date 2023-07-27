#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Enemy
{
	sf::Sprite enemy;    // enemy sprite
	float speed;		 // enemy speed


public:
    // Public parameters
	int health;		// enemy health

    // Constructors / Destructors
	Enemy(sf::Texture* texture, int x, int y, float movement_speed, int type, sf::IntRect textureSize, int hp);

	~Enemy();
	// Public functions
	void loseHP(int damage);					 // reduces the enemy's health
	void moveEnemy();							 // moves the enemy 
	void renderEnemy(sf::RenderWindow* target);  // renders enemy to the target window

	const sf::FloatRect getBounds() const;	// returns enemy bounds
	const sf::Vector2f getPosition() const; // returns enemy position
};