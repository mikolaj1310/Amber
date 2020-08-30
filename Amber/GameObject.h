#pragma once
#include "SFML\Graphics.hpp"
#include "Input.h"
#include "Renderer.h"

enum ObjectType
{
	PLAYER,
	GROUND,
	CUBE,
};

class GameObject : public sf::RectangleShape
{
public:
	GameObject();
	~GameObject();

	virtual void update(float dt);

	// sprite speed and direction
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	// sprite state
	void setAlive(bool live) { alive = live; };
	bool isAlive() { return alive; };

	// for sprite collision
	std::string isCollider() { return collider; };
	void setCollider(std::string b) { collider = b; };
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect fr) { collisionBox = fr; };
	virtual void collisionResponse(GameObject* sp);


	void setType(ObjectType type) { objectType = type; };
	enum ObjectType getType() { return objectType; };

	void updateFromSimulation(const b2Body* body);

	// input component
	void setInput(Input* in) { input = in; };
protected:
	// Sprite properties
	sf::Vector2f velocity;
	bool alive;
	std::string name;
	ObjectType objectType;

	float angle;
	sf::Vector2f translation;

	// Collision vars
	sf::FloatRect collisionBox;
	std::string collider;

	// input component
	Input* input;
};