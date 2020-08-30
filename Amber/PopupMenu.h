#pragma once
#include "GameObject.h"
#include "MenuButton.h"
#include "Input.h"
#include "Collision.h"
class PopupMenu : public GameObject
{
public:
	PopupMenu();
	PopupMenu(Input* in);
	~PopupMenu();

	void loadBackgroundTexture(const char* backgroundFile, const char* btnFile);
	void createPopupMenu(sf::Vector2f rowCnt, sf::Vector2f pos, sf::Vector2f btnSize, sf::Vector2f size);
	void updatePopupMenu(float dt);
	void Draw(sf::RenderWindow* window);
private:
	sf::Texture backgroundTexture;
	GameObject background;

	const char* buttonTexture;
	std::vector<MenuButton> buttons;
	sf::Vector2f buttonSize;
	sf::Vector2f rowCount;

	sf::Vector2f position;
	sf::Vector2f popupSize;

	sf::View popupView;
	bool init = true;

	Input* input;
	Collision collision;
};

