#include "PopupMenu.h"



PopupMenu::PopupMenu()
{
}

PopupMenu::PopupMenu(Input* in)
{
	input = in;
}

PopupMenu::~PopupMenu()
{
}

void PopupMenu::createPopupMenu(sf::Vector2f rowCnt, sf::Vector2f pos, sf::Vector2f btnSize, sf::Vector2f size)
{
	rowCount = rowCnt;
	position = pos;
	popupSize = size;
	buttonSize = btnSize;
	background.setTexture(&backgroundTexture);
	background.setSize(popupSize);
	background.setPosition(0,  1200);

	int i = 0;
	for (int y = 0; y < rowCount.y; y++)
	{
		for (int x = 0; x < rowCount.x; x++)
		{
			MenuButton tempButton = MenuButton(input);
			
			tempButton.loadTextures(buttonTexture);
			tempButton.setTextures("BLACK");
			tempButton.createButton(sf::Vector2f(((buttonSize.x * 27) * x) + 15, 1200 + 10 + ((buttonSize.y * 27) * y)), buttonSize, 
				"File ");
			tempButton.buildButton();
			tempButton.setTextProperties(46, sf::Color::White, sf::Vector2f(25, 20));
			tempButton.setCollisionBox(sf::FloatRect(
				(((buttonSize.x * 27) * x) + 15) + position.x,
				(10 + ((buttonSize.y * 27) * y)) + position.y,
				tempButton.getSize().x,
				tempButton.getSize().y
				));
			buttons.push_back(tempButton);
			i++;
		}
	}

	
	popupView.setSize(popupSize);
	popupView.setCenter(sf::Vector2f(popupSize.x / 2, 1200 + (popupSize.y / 2)));
	popupView.setViewport(sf::FloatRect(position.x / 1920, position.y / 1080, popupSize.x / 1920, popupSize.y / 1080));
	
}

void PopupMenu::updatePopupMenu(float dt)
{
	if (init)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].setFont("font/BitPotion.ttf");
			buttons[i].setText("File: " + std::to_string(i + 1));
		}
		init = false;
	}

	if (input->getScroll() < 0)
		input->setScroll(0);
	if (input->getScroll() > ((buttonSize.y * 27 * rowCount.y) - popupSize.y + 30))
		input->setScroll(((buttonSize.y * 27) * rowCount.y) - popupSize.y + 30);

	popupView.setCenter(sf::Vector2f(popupSize.x / 2, 1200 + input->getScroll() + (popupSize.y / 2)));
	background.setPosition(0, 1200 + input->getScroll());


	



	sf::FloatRect mouseBound(input->getMouseX(), input->getMouseY(), 1, 1);

	

	
	int count = 0;
	for (int y = 0; y < rowCount.y; y++)
	{
		for (int x = 0; x < rowCount.x; x++)
		{
			buttons[count].setCollisionBox(sf::FloatRect(
				(((buttonSize.x * 27) * x) + 15) + position.x,
				(10 + ((buttonSize.y * 27) * y)) + position.y - input->getScroll(),
				buttons[count].getSize().x,
				buttons[count].getSize().y
			));
			count++;
		}
	}
	

	//Button Hover
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].buildButton();
		buttons[i].update(dt);
	}
}

void PopupMenu::Draw(sf::RenderWindow* window)
{
	sf::View defaultView = window->getView();
	window->setView(popupView);
	window->draw(background);
	for (int i = 0; i < buttons.size(); i++)
	{
		
		buttons[i].Draw(window);
	}
	window->setView(defaultView);
}

void PopupMenu::loadBackgroundTexture(const char* backgroundFile, const char* btnFile)
{ 
	backgroundTexture.loadFromFile(backgroundFile);
	buttonTexture = btnFile;
}