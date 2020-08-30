#include "LevelHub.h"
#include "Main.h"
#include "Input.h"
#include "GameState.h"
#include "Menu.h"

sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Gaem", sf::Style::Default);
bool isFullscreen = true;
bool isRunning = true;

void switchFullScreen()
{
	if (isFullscreen == true)
	{
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Gaem", sf::Style::Default);
		isFullscreen = false;
		window.setFramerateLimit(60);
	}
	else
	{
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Gaem", sf::Style::Fullscreen);
		isFullscreen = true;
		window.setFramerateLimit(60);
	}
}

void main()
{
	// Create window
	

	int loadMap = 0;
	// Initialise level object
	Input input;
	GameState gameState;

	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;

	LevelHub levelHub(&window, &input);
	Menu menu(&window, &input, &gameState, loadMap);
	
	//Delta time
	sf::Clock clock;
	float deltaTime;

	gameState.setCurrentState(State::MENU);

	// Game loop
	while (window.isOpen() && isRunning == true)
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f,
					(float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				{
					isRunning = false;
					break;
				}
				case sf::Keyboard::Return:
				{
					switchFullScreen();
					break;
				}
				}
				break;
			case sf::Event::MouseMoved:
				//update input class
				/*pixelPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				worldPos = sf::Vector2f(window.mapPixelToCoords(pixelPos));
				input.setMousePosition(worldPos.x, worldPos.y);*/
				break;
			case sf::Event::MouseWheelScrolled:
				input.incrementScroll(event.mouseWheelScroll.delta);
				
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
					input.setMouseLeftDown(true);
				if (event.mouseButton.button == sf::Mouse::Right)
					input.setMouseRightDown(true);
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
					input.setMouseLeftDown(false);
				if (event.mouseButton.button == sf::Mouse::Right)
					input.setMouseRightDown(false);
				break;
			default:
				// don't handle other events
				break;
			}
		}

		pixelPos = sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		worldPos = sf::Vector2f(window.mapPixelToCoords(pixelPos));
		input.setMousePosition(worldPos.x, worldPos.y);

		deltaTime = clock.restart().asSeconds();
		
		switch (gameState.getCurrentState())
		{
		case (State::MENU):
			menu.update(deltaTime);
			menu.render();
			isRunning = menu.getIsRunning();
			if (isFullscreen != menu.getIsFullScreen())
			{
				isFullscreen = menu.getIsFullScreen();
				switchFullScreen();
			}
			break;
		case (State::LEVEL):
			levelHub.handleInput(deltaTime);
			levelHub.update(deltaTime, menu.getIsLoadMap());
			levelHub.render();
			break;
		}

		
	}
}

