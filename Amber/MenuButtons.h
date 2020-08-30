#pragma once
#include "MySprite.h"
class MenuButtons : public MySprite
{
public:
	MenuButtons();
	~MenuButtons();

	void loadTextures(const char* filename);
	void setTextures(std::string btnType);
	void createButton(sf::Vector2f btnPos, sf::Vector2f btnSize, std::string text);
	void buildButton();
	void Draw(sf::RenderWindow* window);

	sf::Vector2f getPosition() { return buttonPosition; };
	sf::Vector2f getSize() { return buttonSize * textures[0].getSize().x; };
	sf::FloatRect getCollision() { return sf::FloatRect(buttonPosition.x, buttonPosition.y, buttonSize.x * textures[0].getSize().x, buttonSize.y * textures[0].getSize().y); };

	std::string getButtonType() { return buttonType; };
	void setTextProperties(int size, sf::Color color, sf::Vector2f position);

private:
	sf::Texture texture;
	std::vector<MySprite> textures;
	std::vector<MySprite> level;
	std::vector<int> map;
	sf::Vector2f position;
	std::string buttonType;

	sf::Vector2f buttonPosition;
	sf::Vector2f buttonSize;

	sf::Font font;
	sf::Text buttonText;


};

