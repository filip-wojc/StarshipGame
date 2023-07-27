#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Menu.h"

class Game
{
	// Game states
	enum GameState       // possible game states
	{
		MainMenu,
		GameRunning,
		GameOver
	};
	int gameState;       // int value representing game state (the default is MainMenu)


	// // PRIVATE PARAMETERS // // PRIVATE PARAMETERS // // PRIVATE PARAMETERS // //


	sf::RenderWindow* window;      // pointer to a dynamically created window
	int bulletTimer;               // stores info about bullet spawn cooldown
	int enemySpawnTimer;           // stores the information about the time to spawn another enemy
	int enemyChangePoints;         // variable indicating how many points we need for the enemy to change

	sf::Vector2i mousePosWindow;   // storing mouse position as an integer
	sf::Vector2f mousePosView;     // used to convert integer mouse position to float

	// Game objects
	Player player;
	Menu menu;

	// Bullets
	sf::Texture* bulletTexture;      // bullet textures
	std::vector<Bullet*> bullets;    // vector holding all the spawned bullets until they collide with enemies

	// Enemies
	sf::Texture* enemyTexture;       // pointer to enemy textures file
	std::vector<Enemy*> enemies;     // vector holding spawned enemies until they die, that we use to manipulate them in loops
	
	// Resources
	sf::Sound bulletSound;                // spaceship attack sound
	sf::SoundBuffer* bulletSoundBuffer;   // spaceship attack buffer (they both work just like sf::Sprite and sf::Texture)
	sf::Text pointsText;                  // text representing number of points in the corner
	sf::Font* pointsFont;                 // pointer to a font for number of points
	sf::Sprite pointsIcon;                // sprite containing points icon as his texture
	sf::Texture* pointsIconTexture;       // texture for the points icon

	sf::Sprite background;                // sprite that loads background texture as his texture
	sf::Texture* backgroundTexture;		  // pointer to a background texture

	// Instruction overlay
	sf::Sprite mouseIcon;             // menu instruction left mouseclick icon sprite, loads the texture below as his texture
	sf::Texture* mouseIconTexture;    // pointer to a menu instruction icon (mouse left click)

	sf::Sprite WASDicon;              // WASD icon overlay sprite, loads the texture below as his texture
	sf::Texture* WASDiconTexture;     // pointer menu instruction icon (WASD keyboard icon)



    // // PRIVATE FUNCTIONS // // PRIVATE FUNCTIONS // // PRIVATE FUNCTIONS // // 


	// Private bullet functions
	void initBulletTexture();    // initializes bullet texture from filer
	void spawnBullet();          // function responsible for spawning bullets when left mouse button is clicked
	void updateBullet();         // uses spawnBullet() and updates the bullet position
	void renderBullet();         // renders the bullet to the window

	// Private enemy functions
	void initEnemyTexture();     // initializes enemy texture
	void spawnEnemy();           // spawns enemies
	void updateEnemy();          // uses spawnEnemy() above and updates the movement of enemies
	void renderEnemy();          // contains a loop that renders all the enemies in the vector

	// Private text functions
	void initPointsFont();           // initializes points font
	void initPointsIconTexture();    // initializes points icon texture
	void updateText();               // used to update the text in the main update loop
	void renderGUI();                // renders the Interface ( renderHP(), renderText(), pointsIcon, pointsText)

	// Private background functions
	void initBackgroundTexture();    // initializes background texture and sets up the parameters of the background
	void renderBackground();         // used to render background in the render() function

	// Instruction overlay
	void initInstructions();         // initializes game instruction
	void renderInstructions();       // render game instruction

	// Private audio functions
	void initAudio();                // initializes the shoot sound

	// Texture size calculator
	sf::IntRect enemyTextureSize();  

public:
	// Public parameters
	int points;      

	// Game constructor and destructor
	Game();
	virtual ~Game();

	// Public functions
	const bool running();	// checks if the game is running

	void pollEvents();		// event handling

	void bulletEnemyCollision();	// checks if bullet hit the enemy
	void playerEnemyCollision();	// checks if enemy hit the player
	void updateCollision();			// contains bulletEnemyCollision() and  playerEnemyCollision()

	void updateMousePositions();	// tracks mouse position
	void updateGameState();			// changes game state
	void update();					// updates all game objects

	void render();		    // render all game objects
};