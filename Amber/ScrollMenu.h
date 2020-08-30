#pragma once
#include "MySprite.h"
#include "MenuButton.h"
class ScrollMenu : public MySprite
{
public:
	ScrollMenu();
	~ScrollMenu();

	void loadBackgroundTexture(const char* filename);
	void createButtons(int btnCount, sf::Vector2f pos, sf::Vector2f btnSize);
private:
	std::vector<MenuButton> buttons[];
	sf::Vector2f buttonSize;
	sf::Texture backgroundTexture;
};

