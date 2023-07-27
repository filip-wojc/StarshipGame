#include "Game.h"

// CORE *************************************************


Game::Game()  // initializing starting variables and dynamically creating a new window
{
    this->gameState = this->GameState::MainMenu;
    this->points = 0;
    this->bulletTimer = 0;
    this->enemySpawnTimer = 0;
    this->enemyChangePoints = 20;
    this->window = new sf::RenderWindow(sf::VideoMode(1600, 800), "Spaceship", sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->initBulletTexture();
    this->initEnemyTexture();
    this->initPointsIconTexture();
    this->initPointsFont();
    this->initBackgroundTexture();
    this->initAudio();
	this->initInstructions();
}

Game::~Game()                   // destructor deletes the window
{
    delete this->window;
    delete this->bulletTexture;
    delete this->enemyTexture;
    delete this->pointsFont;
    delete this->pointsIconTexture;
    delete this->backgroundTexture;
    delete this->bulletSoundBuffer;

    for (Bullet* bullet : this->bullets)
    {
        delete bullet;
    }

    for (Enemy* enemy : this->enemies)
    {
        delete enemy;
    }
}

const bool Game::running()
{
    return this->window->isOpen();    // returns current game status(checks if it is over)
}

void Game::pollEvents()      // captures events and acts accordingly
{
    sf::Event ev;
    while (this->window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)         // checks if we want to close the window with X button
        {
            this->window->close();
            break;
        }
        if (ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Escape)  // checks if we want to close the game with escape
        {
            this->window->close();
            break;
        }
    }
}


// CORE *************************************************





//  GUI *************************************************


void Game::initInstructions()
{
	this->mouseIconTexture = new sf::Texture();
	this->WASDiconTexture = new sf::Texture();
	if (!this->mouseIconTexture->loadFromFile("Textures/mouseicon.png"))
	{
		std::cout << "ERROR::TEXTURES::INSTRUCTIONS::Could not load mouse icon texture!";
	}
	if (!this->WASDiconTexture->loadFromFile("Textures/WASDicon.png"))
	{
		std::cout << "ERROR::TEXTURES::INSTRUCTIONS::Could not load WASD icon texture!";
	}
	this->mouseIcon.setTexture(*this->mouseIconTexture);
	this->WASDicon.setTexture(*this->WASDiconTexture);

	this->mouseIcon.setPosition(250.0f, 600.0f);
	this->mouseIcon.setScale(0.3f, 0.3f);

	this->WASDicon.setPosition(20.0f, 550.0f);
	this->WASDicon.setScale(0.5f, 0.5f);
}

void Game::initAudio()
{
	this->bulletSoundBuffer = new sf::SoundBuffer();
	if (!this->bulletSoundBuffer->loadFromFile("Sounds/Gun.wav"))
	{
		std::cout << "ERROR::SOUND::BULLET::Could not load bullet sound!";
	}
	this->bulletSound.setBuffer(*this->bulletSoundBuffer);
	this->bulletSound.setVolume(0.8f);
}

void Game::initPointsFont()
{
    this->pointsFont = new sf::Font();
    if(!this->pointsFont->loadFromFile("Fonts/font.ttf"))
    {
        std::cout << "ERROR::FONT::Could not load points font!";
    }
    this->pointsText.setFont(*this->pointsFont);
	this->pointsText.setPosition(this->pointsIcon.getPosition().x + 57, this->pointsIcon.getPosition().y +4);
}

void Game::initPointsIconTexture()
{
    this->pointsIconTexture = new sf::Texture();
    if (!this->pointsIconTexture->loadFromFile("Textures/points.png"))
    {
        std::cout << "ERROR::TEXTURE::Could not load point texture!";
    }
    this->pointsIcon.setTexture(*this->pointsIconTexture);
    this->pointsIcon.setScale(0.1f, 0.1f);
    this->pointsIcon.setPosition(this->player.getHpIconPosition().x + 3, this->player.getHpIconPosition().y + 40);
	
}

void Game::updateText()
{
	this->pointsText.setString(std::to_string(this->points));
}


//  GUI   **********************************************





// BACKGROUND ******************************************


void Game::initBackgroundTexture()
{
    this->backgroundTexture = new sf::Texture();
    if (!this->backgroundTexture->loadFromFile("Textures/gamebackground.png"))
    {
        std::cout << "ERROR::BACKGROUND::TEXTURES::Could not load background texture!";
    }
    this->background.setTexture(*this->backgroundTexture);
    this->background.setScale(1.5f, 1.5f);
    this->background.setPosition(0, 0);
}

void Game::renderBackground()
{
    this->window->draw(this->background);
}


// BACKGROUND ******************************************





// BULLET **********************************************


void Game::initBulletTexture()
{
    // Loading bullet textures from a file
    this->bulletTexture = new sf::Texture();
    if (!this->bulletTexture->loadFromFile("Textures/bullet.png"))
    {
        std::cout << "ERROR::BULLET::TEXTURES::Could not load bullet texture!";
    }
}

void Game::spawnBullet()
{
    if (this->bulletTimer <= 25)   // timer controlling the speed of spawning bullets
    {
        this->bulletTimer++;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and this->bulletTimer > 25)
    {
		this->bulletSound.play();
        this->bullets.push_back(new Bullet(this->bulletTexture, this->player.getPosition().x + 100, this->player.getPosition().y + 65, 20.0));
        this->bulletTimer = 0;
    }
}

void Game::updateBullet()
{
    this->spawnBullet();

    int counter = 0;
    for(Bullet* bullet: this->bullets)
    {
        bullet->moveBullet();

        if(bullet->getBounds().left >= 1600.0f)
        {
            // Deleting bullet
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);

        }
        counter++;
    }
}

void Game::renderBullet()
{
    for(Bullet* bullet:this->bullets)
    {
        bullet->render(this->window);
    }
}


// BULLET **********************************************





// ENEMY **********************************************


void Game::initEnemyTexture()
{
    this->enemyTexture = new sf::Texture();
    if(!this->enemyTexture->loadFromFile("Textures/enemies.png"))
    {
        std::cout << "ERROR::ENEMY::TEXTURES::Could not load enemy texture!";
    }
}

void Game::spawnEnemy()
{
   
    if (this->enemySpawnTimer < 45)  // enemy spawn cooldown
    {
        this->enemySpawnTimer++;
    }
    if (this->enemySpawnTimer >= 45 )
    {
        /*
        // changes mobs every X points. X is a value of enemyChangePoints set in game constructor,
		// based on the number of points, the enemies get different paramenters
        */
        if(this->points < this->enemyChangePoints)  
        {                                           
			this->enemies.push_back(new Enemy(this->enemyTexture, 1600, rand() % 735, 7.f, 2, this->enemyTextureSize(), 10)); 
			this->enemySpawnTimer = 0;
        }

		else if (this->points >= this->enemyChangePoints and this->points < 2 * this->enemyChangePoints)
		{
			this->enemies.push_back(new Enemy(this->enemyTexture, 1600, rand() % 735, 7.f, 0, this->enemyTextureSize(), 20));
			this->enemySpawnTimer = 0;
		}

		else if (this->points >= 2*this->enemyChangePoints and this->points < 3 * this->enemyChangePoints)
		{
			this->enemies.push_back(new Enemy(this->enemyTexture, 1600, rand() % 735, 18.f, 6, this->enemyTextureSize(),10));
			this->enemySpawnTimer = 0;
		}

		else if (this->points >= 3 * this->enemyChangePoints)
		{
			this->enemies.push_back(new Enemy(this->enemyTexture, 1600, rand() % 735, 12.f, 1, this->enemyTextureSize(), 20));
			this->enemySpawnTimer = 0;
		}

    }
}

void Game::updateEnemy()     // updates stuff about enemies every loop
{
    this->spawnEnemy();
    int counter = 0;

    for(Enemy* enemy: this->enemies)
    {
        enemy->moveEnemy();
        if (enemy->getPosition().x < -50.f)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            this->player.health--;
        }
        
        else if (enemy->health <= 0)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            this->points++;
        }
       
        counter++;
    }
}

void Game::renderEnemy()               // renders enemies on the screen
{
    for(Enemy* enemy: this->enemies)
    {
        enemy->renderEnemy(this->window);
    }
}

sf::IntRect Game::enemyTextureSize()   
{
/*
// function returning size of one block of texture
(all enemies textures are located on the same texture PNG, separated by only a few pixels,
we calculate how big the size of a specific texture is and then we return it.
We use one texture size to then shift from one enemy's texture to another by jumping by the 
texture size length to the right.
*/

    sf::IntRect size;
    size.height = this->enemyTexture->getSize().y / 3;
    size.width = this->enemyTexture->getSize().x / 7;
    return size;
}


// ENEMY **********************************************





// COLLISIONS *****************************************


void Game::playerEnemyCollision()        // checks if we got hit by the enemy
{
    int counter = 0;
    for(Enemy* enemy: this->enemies)
    {
        if (this->player.getBounds().intersects(enemy->getBounds()))
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            this->player.health -= 3;
        }
        counter++;
    }
}

void Game::bulletEnemyCollision()          // checks if we hit an enemy with a bullet
{
    for(int i = 0; i < this->enemies.size();i++)
    {
        for (int j = 0; j < this->bullets.size(); j++)
        {
            if (this->bullets[j]->getBounds().intersects(this->enemies[i]->getBounds()))
            {
                delete this->bullets[j];
                this->bullets.erase(this->bullets.begin() + j);

                this->enemies[i]->loseHP(10);
            }
        }
    }
}


void Game::updateCollision()    // function used for checking both types of collision
{
	this->playerEnemyCollision();
	this->bulletEnemyCollision();
}


// COLLISIONS *****************************************





// UPDATE  *********************************


void Game::updateMousePositions()        // updates mouse positions and then stores them into int sf::vector, converts coordinates to float and stores them in another vector 
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::updateGameState()
{
    if(this->gameState == this->GameState::MainMenu)   // only works if we are in a menu
    {
		if (this->menu.getNewGameBounds().contains(this->mousePosView))   // checks if we want to click new game
		{
            this->menu.hoverNewGame();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->gameState = this->GameState::GameRunning;    // changes game state to game running
		}
        else
        {
            this->menu.setNewGameTexture();
        }

		if (this->menu.getExitButtonBounds().contains(this->mousePosView))  // checks if we are hovering exit button
		{
            this->menu.hoverExit();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))   // checks if we want to click the hovered exit button
				this->window->close();       // closes the window if we click exit
		}
        else
        {
			this->menu.setExitTexture();
        }
    }
    

    else if(this->player.playerIsDead)
    {
        this->gameState = this->GameState::GameOver;
    }
}


void Game::update()     // main loop where everything updates
{
    this->updateMousePositions();
    this->updateGameState();
   
    if (this->gameState == this->GameState::GameRunning)
    {

        this->player.update();
        this->updateEnemy();
        this->updateBullet();
        this->updateCollision();
        this->updateText();
    }
}


// UPDATE  *********************************





// RENDER **********************************


void Game::renderInstructions()             // rendering instruction icons on the screen
{
    this->window->draw(this->WASDicon);
    this->window->draw(this->mouseIcon);
}

void Game::renderGUI()                      // renders everything that's considered interface during the game
{
    this->player.renderHp(this->window);
    this->player.renderText(this->window);
    this->window->draw(this->pointsIcon);
    this->window->draw(this->pointsText);
}

void Game::render()          // rendering everything
{

    this->window->clear();

    if (this->gameState == this->GameState::MainMenu)
    {
        this->menu.render(this->window);
        this->renderInstructions();
    }

    else if (this->gameState == this->GameState::GameRunning)
    {
        this->renderBackground();
        this->player.renderPlayer(this->window);
        this->renderBullet();
        this->renderEnemy();
        this->renderGUI();
    }
   
    else if(this->gameState == this->GameState::GameOver)
    {
        this->menu.renderGameOver(this->window, this->points);
    }

    this->window->display();
}


// RENDER **********************************