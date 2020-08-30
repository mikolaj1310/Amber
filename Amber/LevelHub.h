#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Input.h"
#include "GameObject.h"
#include "Player.h"
#include "Collision.h"
#include "Renderer.h"

class LevelHub {
public:
	LevelHub(sf::RenderWindow * hwnd, Input * in);
	~LevelHub();
	void handleInput(float dt);
	void update(float dt, int load);
	void updateSim();
	void initCube();
	void initGround();
	void render();
private:
	bool mapGenerated = false;
	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();
	int mapSizeX, mapSizeY;

	Input* input;
	int camPosX = 0, camPosY = 0;
	std::vector<GameObject> gameObject; //items
	//TileMap tileMap;

	//physics world
	b2World* world;
		
	GameObject background;
	sf::Texture bgTex;

	Player player;
	sf::Clock generationTime;
	sf::Time time;