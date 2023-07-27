#include "Player.h"
#include <iostream>

// Constructors / Destructors
Player::Player() // constructor
{
	// setting up variables and using the initializing functions
	this->playerIsDead = false;
	this->health = 30;
	this->movementSpeed = 10.f;
	this->initPlayerTexture();
	this->initPlayerSprite();
	this->initHpTexture();
	this->initHpSprite();
	this->initFont();
}

Player::~Player()  // destructor
{
	delete this->hpFont;
	delete this->hpTexture;
	delete this->playerTexture;
}

// Initializing functions
void Player::initPlayerTexture()
{
	this->playerTexture = new sf::Texture();
	// Loading player textures from a file
    if(!this->playerTexture->loadFromFile("Textures/spaceship.png"))
	{
		std::cout << "ERROR::PLAYER::TEXTURES::Could not load player texture!";
	}
}

void Player::initPlayerSprite()
{
	// Calculating the size of 1 player ship from texture file (there's multiple)
	
	// initializing and changing the position/textures and scale
	this->player.setTexture(*this->playerTexture); 
	this->player.setPosition(30, 300);  
	this->player.setScale(0.3f, 0.3f);
}

void Player::initHpTexture()
{
	this->hpTexture = new sf::Texture();
	if (!this->hpTexture->loadFromFile("Textures/heart.png"))
	{
		std::cout << "ERROR::HEART::TEXTURES::Could not load heart texture!";
	}
}

void Player::initHpSprite()
{
	this->hp.setTexture(*this->hpTexture);
	this->hp.setScale(0.008f, 0.008f);
	this->hp.setPosition(20, 10);
}

void Player::initFont()
{
	this->hpFont = new sf::Font();
	if (!this->hpFont->loadFromFile("Fonts/font.ttf"))
	{
		std::cout << "ERROR::HP::FONTS::Could not load HP font!";
	}
	this->hpText.setFont(*this->hpFont);
	this->hpText.setPosition(this->hp.getPosition().x + 60, this->hp.getPosition().y);
	
}

// Accessors
const sf::Vector2f Player::getPosition() const  // public position accessor
{
	return this->player.getPosition();
}
 
const sf::Vector2f Player::getHpIconPosition() const
{
	return this->hp.getPosition();
}

// Functions
const sf::FloatRect Player::getBounds() const
{
	return this->player.getGlobalBounds();
}


void Player::move()   // checks for movement actions and moves the player accordingly
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (this->player.getPosition().y - 10 >= 0)
		{
			this->player.move(0, -this->movementSpeed);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (this->player.getPosition().y + 60 <= 700)
		{
			this->player.move(0, this->movementSpeed);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (this->player.getPosition().x  >= 0)
		{
			this->player.move(-this->movementSpeed, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->player.getPosition().x + this->player.getGlobalBounds().width <= 1600)
		{
			this->player.move(this->movementSpeed, 0);
		}
	}
}

void Player::update()   // updates the state of player and bullets
{

	if (this->health <= 0)
	{
		this->playerIsDead = true;   
	}

	this->move();
	this->hpText.setString(std::to_string(this->health));

}

void Player::renderPlayer(sf::RenderWindow* target)
{
	target->draw(this->player);
}

void Player::renderHp(sf::RenderWindow* target)
{
	target->draw(this->hp);
}

void Player::renderText(sf::RenderWindow* target)
{
	target->draw(this->hpText);
}
