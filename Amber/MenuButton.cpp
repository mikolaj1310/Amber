#include "MenuButton.h"


MenuButton::MenuButton()
{
}

MenuButton::MenuButton(Input* in)
{
	input = in;
}


MenuButton::~MenuButton()
{
}

void MenuButton::loadTextures(const char* filename)
{
	texture.loadFromFile(filename);

	GameObject tile;
	for (int i = 0; i < 9; i++)
	{
		tile.setSize(sf::Vector2f(27, 27));
		textures.push_back(tile);
	}
}

void MenuButton::setTextures(std::string btnType)
{
	buttonType = btnType;
	if (buttonType == "BLACK")
	{
		textures[0].setTextureRect(sf::IntRect(5, 9, 9, 9)); //top left corner
		textures[1].setTextureRect(sf::IntRect(14, 9, 9, 9)); //top wall
		textures[2].setTextureRect(sf::IntRect(63, 9, 9, 9)); //top right corner

		textures[3].setTextureRect(sf::IntRect(5, 18, 9, 9)); //left wall
		textures[4].setTextureRect(sf::IntRect(14, 18, 9, 9)); //background fill
		textures[5].setTextureRect(sf::IntRect(63, 18, 9, 9)); //right wall

		textures[6].setTextureRect(sf::IntRect(5, 35, 9, 9)); //bottom left corner
		textures[7].setTextureRect(sf::IntRect(14, 35, 9, 9)); //bottom wall
		textures[8].setTextureRect(sf::IntRect(63, 35, 9, 9)); //bottom right corner
	}

	if (buttonType == "GRAY")
	{
		textures[0].setTextureRect(sf::IntRect(7, 48, 9, 9)); //top left corner
		textures[1].setTextureRect(sf::IntRect(16, 48, 9, 9)); //top wall
		textures[2].setTextureRect(sf::IntRect(65, 48, 9, 9)); //top right corner

		textures[3].setTextureRect(sf::IntRect(7, 57, 9, 9)); //left wall
		textures[4].setTextureRect(sf::IntRect(15, 57, 9, 9)); //background fill
		textures[5].setTextureRect(sf::IntRect(65, 57, 9, 9)); //right wall

		textures[6].setTextureRect(sf::IntRect(7, 74, 9, 9)); //bottom left corner
		textures[7].setTextureRect(sf::IntRect(16, 74, 9, 9)); //bottom wall
		textures[8].setTextureRect(sf::IntRect(65, 74, 9, 9)); //bottom right corner
	}
}

void MenuButton::createButton(sf::Vector2f btnPos, sf::Vector2f btnSize, std::string text)
{
	position = btnPos;
	buttonSize = btnSize;

	for (int i = 0; i < buttonSize.y; i++)
	{
		for (int j = 0; j < buttonSize.x; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					map.push_back(0);
				}
				else if (j == buttonSize.x - 1)
					map.push_back(2);
				else
					map.push_back(1);
			}
			else if (i == buttonSize.y - 1)
			{
				if (j == 0)
					map.push_back(6);
				else if (j == buttonSize.x - 1)
					map.push_back(8);
				else
					map.push_back(7);
			}
			else
			{
				if (j == 0)
					map.push_back(3);
				else if (j == buttonSize.x - 1)
					map.push_back(5);
				else
					map.push_back(4);
			}
		}
	}

	font.loadFromFile("font/orange kid.ttf");
	buttonText.setFont(font);
	buttonText.setCharacterSize(56);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(position.x + 50, position.y + 50);
	buttonText.setString(text);

	collisionBox = sf::FloatRect(position.x, position.y, buttonSize.x * 27, buttonSize.y * 27);
}

void MenuButton::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < level.size(); i++)
	{
		window->draw(level[i]);
	}
	window->draw(buttonText);
}

void MenuButton::buildButton()
{
	sf::Vector2f tileSize(textures[0].getSize().x, textures[0].getSize().y);
	int x = 0, y = 0;

	level.clear();

	for (int i = 0; i < map.size(); i++)
	{
		textures[map[i]].setPosition(position.x + (x * textures[0].getSize().x), position.y + (y * textures[0].getSize().y));
		level.push_back(textures[map[i]]);
		level[i].setTexture(&texture);

		x++;

		if (x == buttonSize.x)
		{
			x = 0;
			y++;
		}
	}
}

void MenuButton::update(float dt)
{
	sf::FloatRect mouseBound(input->getMouseX(), input->getMouseY(), 1, 1);

	if (Collision::checkBoundingBox(&getCollisionBox(), &mouseBound))
	{
		setTextures("GRAY");
	}
	else
		setTextures("BLACK");
}

void MenuButton::setTextProperties(int size, sf::Color color, sf::Vector2f pos)
{
	buttonText.setCharacterSize(size);
	buttonText.setFillColor(color);
	buttonText.setPosition(position.x + pos.x, position.y + pos.y);
}