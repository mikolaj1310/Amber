#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "GameObject.h"
#include "GameState.h"
#include "Collision.h"
#include "MenuButton.h"
#include "PopupMenu.h"
class Menu
{
public:
	Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, int isLoad);
	~Menu();

	void update(float dt);
	void render();
	int getIsLoadMap() { return isLoadMap; };

	bool getIsFullScreen() { return isFullScreen; };
	bool getIsRunning() { return isRunning; };

private:
	int isLoadMap = 0;
	GameState* gameState;
	Input* input;
	
	sf::RenderWindow* window;

	GameObject background;
	sf::Texture backgroundTexture;

	GameObject fullScreenButton;
	sf::Texture fullScreenButtonTexture;

	sf::View menuView;

	MenuButton generateMapButton;
	MenuButton loadMapButton;
	MenuButton exitButton;

	PopupMenu loadSavePopup;

	void beginDraw();
	void endDraw();

	bool isFullScreen = true;
	bool isRunning = true;
	bool saveFileList = false;
};

