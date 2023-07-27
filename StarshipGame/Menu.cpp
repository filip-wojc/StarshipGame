#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	initMenuTextures();
	setMenu();
}

Menu::~Menu()
{
	delete menuBackgroundTexture;
	delete newGameTexture;
	delete exitButtonTexture;
	delete menuBannerTexture;
	delete newGameHighlightTexture;
	delete exitButtonHighlightTexture;
	delete gameOverBackgroundTexture;
	delete gameOverTextTexture;
	delete finalScoreFont;
}

void Menu::setNewGameTexture()
{
	this->newGame.setTexture(*this->newGameTexture);
}

void Menu::setExitTexture()
{
	this->exitButton.setTexture(*this->exitButtonTexture);
}

void Menu::hoverNewGame()
{
	this->newGame.setTexture(*this->newGameHighlightTexture);
}

void Menu::hoverExit()
{
	this->exitButton.setTexture(*this->exitButtonHighlightTexture);
}
void Menu::initMenuTextures()
{
	this->menuBackgroundTexture = new sf::Texture();
	if(!this->menuBackgroundTexture->loadFromFile("Textures/menubackground.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load menu background texture!";
	}

	this->newGameTexture = new sf::Texture();
	if (!this->newGameTexture->loadFromFile("Textures/newgametext.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load new game texture!";
	}

	this->exitButtonTexture = new sf::Texture();
	if (!this->exitButtonTexture->loadFromFile("Textures/exittext.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load exit texture!";
	}

	this->menuBannerTexture = new sf::Texture();
	if (!this->menuBannerTexture->loadFromFile("Textures/menubaner.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load menu baner texture!";
	}

	this->exitButtonHighlightTexture = new sf::Texture();
	if (!this->exitButtonHighlightTexture->loadFromFile("Textures/exithighlight.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load exit highlight texture!";
	}

	this->newGameHighlightTexture = new sf::Texture();
	if (!this->newGameHighlightTexture->loadFromFile("Textures/newgamehighlight.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load new game highlight texture!";
	}

	this->gameOverBackgroundTexture = new sf::Texture();
	if (!this->gameOverBackgroundTexture->loadFromFile("Textures/gameoverbackground.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load game over background texture!";
	}

	this->gameOverTextTexture = new sf::Texture();
	if (!this->gameOverTextTexture->loadFromFile("Textures/gameovertext.png"))
	{
		std::cout << "ERROR::MENU::TEXTURE::Could not load game over text texture!";
	}

	this->finalScoreFont = new sf::Font();
	if (!this->finalScoreFont->loadFromFile("Fonts/font.ttf"))
	{
		std::cout << "ERROR::MENU::FONT::Could not load final score font!";
	}
}

sf::FloatRect Menu::getNewGameBounds()
{
	return this->newGame.getGlobalBounds();
}

sf::FloatRect Menu::getExitButtonBounds()
{
	return this->exitButton.getGlobalBounds();
}

void Menu::setMenu()
{
	this->menuBackground.setTexture(*this->menuBackgroundTexture);
	this->menuBackground.setPosition(0, 0);
	this->menuBackground.setScale(0.9f, 0.9f);

	this->setNewGameTexture();
	this->newGame.setPosition(550, 350);
	this->newGame.setScale(0.7f, 0.7f);

	this->setExitTexture();
	this->exitButton.setPosition(550, 550);
	this->exitButton.setScale(0.7f, 0.7f);

	this->menuBanner.setTexture(*this->menuBannerTexture);
	this->menuBanner.setPosition(550, 50);
	this->menuBanner.setScale(1.f, 1.f);

	this->gameOver.setTexture(*this->gameOverBackgroundTexture);
	this->gameOver.setPosition(0.0, 0.0);
	this->gameOver.setScale(0.9f, 0.9f);

	this->gameOverText.setTexture(*this->gameOverTextTexture);
	this->gameOverText.setPosition(450, 200);
	this->gameOverText.setScale(1.5f, 1.5f);

	this->finalScore.setPosition(560, 350);
	this->finalScore.setScale(1.5f, 1.5f);
	this->finalScore.setFont(*this->finalScoreFont);
	this->finalScore.setFillColor(sf::Color::White);
	this->finalScore.setOutlineThickness(2);
	this->finalScore.setOutlineColor(sf::Color::Black);
}

void Menu::renderGameOver(sf::RenderWindow* window, int points)
{
	this->finalScore.setString("        Points: " + std::to_string(points) +"\n\n\n" + "Press ESC to exit :)");
	window->draw(this->gameOver);
	window->draw(this->gameOverText);
	window->draw(this->finalScore);
}
void Menu::render(sf::RenderWindow* window)
{
	window->draw(this->menuBackground);
	window->draw(this->menuBanner);
	window->draw(this->newGame);
	window->draw(this->exitButton);
}