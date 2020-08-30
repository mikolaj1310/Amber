#include "ScrollMenu.h"



ScrollMenu::ScrollMenu()
{
}


ScrollMenu::~ScrollMenu()
{
}

void ScrollMenu::loadBackgroundTexture(const char* filename)
{
	backgroundTexture.loadFromFile(filename);
}

void ScrollMenu::createButtons(int btnCount, sf::Vector2f pos, sf::Vector2f size)
{

}
