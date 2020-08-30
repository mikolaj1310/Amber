#include "Menu.h"


Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, int isLoad)
{
	window = hwnd;
	input = in;
	gameState = gs;
	isLoadMap = isLoad;

	generateMapButton = MenuButton(input);
	loadMapButton = MenuButton(input);
	exitButton = MenuButton(input);
	loadSavePopup = PopupMenu(input);

	backgroundTexture.loadFromFile("gfx/Backgrounds/MainMenuBackground.png");
	fullScreenButtonTexture.loadFromFile("gfx/Buttons/FullScreenButton.png");

	background.setTexture(&backgroundTexture);
	background.setSize(sf::Vector2f(1920, 1080));
	background.setPosition(0, 0);

	fullScreenButton.setTexture(&fullScreenButtonTexture);
	fullScreenButton.setSize(sf::Vector2f(64, 64));
	fullScreenButton.setPosition(20, 20);
	fullScreenButton.setCollisionBox(0, 0, 64, 64);

	generateMapButton.loadTextures("gfx/buttons/buttonpress.png");
	generateMapButton.setTextures("BLACK");
	generateMapButton.createButton(sf::Vector2f(100, 800), sf::Vector2f(14, 4), "Generate Map");
	generateMapButton.setTextProperties(56, sf::Color::White, sf::Vector2f(50, 20));
	generateMapButton.buildButton();

	loadMapButton.loadTextures("gfx/buttons/buttonpress.png");
	loadMapButton.setTextures("BLACK");
	loadMapButton.createButton(sf::Vector2f(500, 800), sf::Vector2f(14, 4), "Load Map");
	loadMapButton.setTextProperties(56, sf::Color::White, sf::Vector2f(50, 20));
	loadMapButton.buildButton();

	exitButton.loadTextures("gfx/buttons/buttonpress.png");
	exitButton.setTextures("BLACK");
	exitButton.createButton(sf::Vector2f(1600, 50), sf::Vector2f(8, 4), "Exit");
	exitButton.setTextProperties(56, sf::Color::Black, sf::Vector2f(50, 20));
	exitButton.buildButton();

	
	loadSavePopup.loadBackgroundTexture("gfx/buttons/scrollBarBackground.png", "gfx/buttons/buttonpress.png");
	loadSavePopup.createPopupMenu(
		sf::Vector2f(2, 10), 
		sf::Vector2f(loadMapButton.getPosition().x, loadMapButton.getPosition().y - (11 * 27)),
		sf::Vector2f(6, 4),
		sf::Vector2f(12 * 27 + 40, 11 * 27));

	menuView.setSize(sf::Vector2f(1920, 1080));
	menuView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
	menuView.setViewport(sf::FloatRect(0, 0, 1, 1));	

	input->setMouseLeftDown(false);
}


Menu::~Menu()
{
}

void Menu::update(float dt)
{
	sf::FloatRect mouseBound(input->getMouseX(), input->getMouseY(), 1, 1);

	if (input->isKeyDown(sf::Keyboard::Num0))
	{
		gameState->setCurrentState(State::LEVEL);
		isLoadMap = 2;
	}

	if (Collision::checkBoundingBox(&generateMapButton.getCollisionBox(), &mouseBound))
	{
		if (input->isMouseLeftDown())
		{
			gameState->setCurrentState(State::LEVEL);
			isLoadMap = 0;
		}
	}

	if (input->isKeyDown(sf::Keyboard::Space))
		gameState->setCurrentState(State::LEVEL);

	if (Collision::checkBoundingBox(&loadMapButton.getCollisionBox(), &mouseBound))
		if (input->isMouseLeftDown())
			if (!saveFileList)
			{
				input->setMouseLeftDown(false);
				saveFileList = true;
			}
			else
			{
				input->setMouseLeftDown(false);
				saveFileList = false;
			}
	

	if (Collision::checkBoundingBox(&exitButton.getCollisionBox(), &mouseBound))
		if (input->isMouseLeftDown())
			isRunning = false;

	if(Collision::checkBoundingBox(&fullScreenButton, &mouseBound))
		if (input->isMouseLeftDown())
		{
			if (isFullScreen)
			{
				isFullScreen = false;
				input->setMouseLeftDown(false);
			}
			else
			{
				isFullScreen = true;
				input->setMouseLeftDown(false);
			}
		}

	generateMapButton.buildButton();
	loadMapButton.buildButton();
	exitButton.buildButton();

	generateMapButton.update(dt);
	loadMapButton.update(dt);
	exitButton.update(dt);

	if(saveFileList)
		loadSavePopup.updatePopupMenu(dt);

}		


void Menu::render()
{
	beginDraw();
	window->setView(menuView);
	window->draw(background);
	generateMapButton.Draw(window);
	loadMapButton.Draw(window);
	exitButton.Draw(window);
	window->draw(fullScreenButton);
	if (saveFileList)
	{		
		loadSavePopup.Draw(window);
	}
	
	endDraw();
}

void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Menu::endDraw()
{
	window->display();
}