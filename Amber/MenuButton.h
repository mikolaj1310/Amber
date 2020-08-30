#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Collision.h"
class MenuButton : public GameObject
{
public:
	MenuButton();
	MenuButton(Input* in);
	~MenuButton();

	void loadTextures(const char* filename);
	void setTextures(std::string btnType);
	void createButton(sf::Vector2f btnPos, sf::Vector2f btnSize, std::string text);
	void buildButton();
	void update(float dt);
	void Draw(sf::RenderWindow* window);

	sf::Vector2f getPosition() { return position; };
	sf::Vector2f getSize() { return sf::Vector2f(buttonSize.x * textures[0].getSize().x, buttonSize.y * textures[0].getSize().y); };

	std::string getButtonType() { return buttonType; };
	void setTextProperties(int size, sf::Color color, sf::Vector2f position);
	void setText(std::string text) { buttonText.setString(text); };
	void setFont(std::string fnt) {	font.loadFromFile(fnt);	buttonText.setFont(font); };

private:
	Input* in;
	sf::Texture texture;
	std::vector<GameObject> textures;
	std::vector<GameObject> level;
	std::vector<int> map;
	std::string buttonType;

	sf::Vector2f buttonSize;
	sf::Vector2f position;
	sf::Font font;
	sf::Text buttonText;
};

