#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Bullet.h"


class Player
{
	// Player
	sf::Sprite player;
	sf::Texture* playerTexture;    // pointer to a player texture

	//variables
	
	float movementSpeed;	       // player movement speed
	

	// Mob health variables
	sf::Sprite hp;				// sprite holding a health icon and position parameters
	sf::Texture* hpTexture;		// health icon texture
	sf::Font* hpFont;			// pointer to a dynamically created sf::Font type variable, stores font
	sf::Text hpText;			// text that renders on screen to shop current hp


	// Private functions
	void initPlayerTexture();   // initializes textures from file
	void initPlayerSprite();    // initializes the player sprite
	void initHpTexture();		// initializes hp icon texture
	void initHpSprite();        // sets up the variables of health icon sprite
	void initFont();            // initializes the text font
	

public:
	bool playerIsDead;          // state of the player

	// Constructor / Destructor
	Player();  
	~Player();

	int health; // player health

	// Accessors
	const sf::Vector2f getPosition() const;         // returns player position 
	const sf::Vector2f getHpIconPosition() const;   // returns hp icon position

	// Functions
	const sf::FloatRect getBounds() const;    // gets the global bounds of a rectangle of player
	void move();                              // moves the player
	void update();                            // updates the player every loop

	void renderPlayer(sf::RenderWindow* target); // renders the player on the screen
	void renderHp(sf::RenderWindow* target);	 // renders hp icon
	void renderText(sf::RenderWindow* targer);	 // renders player current hp

};
