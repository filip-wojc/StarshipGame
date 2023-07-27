#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Menu
{
	// Interface variables 
	sf::Sprite menuBackground;
	sf::Texture* menuBackgroundTexture;

	sf::Sprite newGame;
	sf::Texture* newGameTexture;
	sf::Texture* newGameHighlightTexture;

	sf::Sprite exitButton;
	sf::Texture* exitButtonTexture;
	sf::Texture* exitButtonHighlightTexture;

	sf::Sprite menuBanner;
	sf::Texture* menuBannerTexture;

	sf::Sprite gameOver;
	sf::Texture* gameOverBackgroundTexture;

	sf::Sprite gameOverText;
	sf::Texture* gameOverTextTexture;

	// Text variables
	sf::Font* finalScoreFont;
	sf::Text finalScore;

	// Private functions
	void initMenuTextures();	// initializes all menu textures
	void setMenu();				// sets menu parameters

public:

	// Constructor / Destructor
	Menu();
	~Menu();

	// Accessors
	sf::FloatRect getNewGameBounds();         // returns "New Game" menu button bounds 
	sf::FloatRect getExitButtonBounds();      // return "Exit" menu button bounds
	void setNewGameTexture();       // sets new game button texture
	void setExitTexture();			// sets exit button texture
	void hoverNewGame();            // swaps textures to hover texture of new game button
	void hoverExit();               // swaps textures to hover texture of exit button

	// Rendering
	void renderGameOver(sf::RenderWindow* window,int points);   // renders game over screen
	void render(sf::RenderWindow* window);						// renders game menu screen

};