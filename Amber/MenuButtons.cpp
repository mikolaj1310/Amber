#include "MenuButtons.h"



MenuButtons::MenuButtons()
{

}


MenuButtons::~MenuButtons()
{
}

void MenuButtons::loadTextures(const char* filename)
{
	texture.loadFromFile(filename);

	MySprite tile;
	for (int i = 0; i < 9; i++)
	{
		tile.setSize(sf::Vector2f(27, 27));
		textures.push_back(tile);
	}
}

void MenuButtons::setTextures(std::string btnType)
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

void MenuButtons::createButton(sf::Vector2f btnPos, sf::Vector2f btnSize, std::string text)
{
	buttonPosition = btnPos;
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

	font.loadFromFile("font/Benja.otf");
	buttonText.setFont(font);
	buttonText.setCharacterSize(56);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(buttonPosition.x + 50, buttonPosition.y + 50);
	buttonText.setString(text);
}

void MenuButtons::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < (int)level.size(); i++)
	{
		window->draw(level[i]);
	}
	window->draw(buttonText);
}

void MenuButtons::buildButton()
{
	sf::Vector2f tileSize(textures[0].getSize().x, textures[0].getSize().y);
	int x = 0, y = 0;

	level.clear();

	for (int i = 0; i < map.size(); i++)
	{
		textures[map[i]].setPosition(buttonPosition.x + (x * textures[0].getSize().x), buttonPosition.y + (y * textures[0].getSize().y));
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

void MenuButtons::setTextProperties(int size, sf::Color color, sf::Vector2f position)
{
	buttonText.setCharacterSize(size);
	buttonText.setFillColor(color);
	buttonText.setPosition(buttonPosition.x + position.x, buttonPosition.y + position.y);
}