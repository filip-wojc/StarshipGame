#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Bullet
{
	//Variables
	sf::Sprite bullet;	//bullet sprite

	float speed; // bullet speed

public:
	// Constructors / Destructors
	Bullet(sf::Texture* texture, float x, float y, float movement_speed); // parametric constructor 
			// texture - bullet texture
			// x, y - bullet position
			// movement_speed - bullet movement speed

	virtual ~Bullet();

	// Functions
	const sf::FloatRect getBounds() const;		// return bullet bounds
	const sf::Vector2f getPosition() const;		// return bullet actual position
	void moveBullet();							// moves bullet
	void render(sf::RenderWindow* target);		// renders bullets
};