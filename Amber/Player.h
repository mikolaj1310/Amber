#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Renderer.h"
#include <chrono>
class Player : public GameObject
{
	enum MoveState {
		MS_STOP,
		MS_LEFT,
		MS_RIGHT
	};

	enum FlyState {
		JS_FLYING,
		JS_FALLING,
		JS_GROUNDED
	};

	enum FaceDirState {
		FD_RIGHT,
		FD_LEFT
	};

public:
	Player();
	~Player();
	   
	void init(b2Body* gBody);
	b2World* initB2Body(b2World* world);
	void update(float dt);
	void handleInput(float dt, Input* input);
	b2Body* getB2Body() { return playerBody; };
	void initChasisAnimation();
	void initTreadsAnimation();
	void animatePlayer(float dt);

	float getRotation() { return rotation; };
	void setRotation(float rot) { rotation = rot; };

	b2Vec2 getGravity() { return gravity; };
	void setGravity(b2Vec2 grav, float gravF) { gravity = grav; gravForce = gravF; };

	void render(sf::RenderWindow* window);
protected:
	MoveState moveState;
	FlyState flyState;
	FaceDirState faceDirState;

	sf::Texture chasisIdle1Tex;

	GameObject treads;
	sf::Texture treadsTex;


	Animation chasisIdleAnimation;

	Animation treadsMovingAnimation;

	Animation* currentChasisAnimation;
	Animation* currentTreadsAnimation;

	Input* input;

	b2Body* playerBody;
	b2Body* groundBody;

	b2Vec2 gravity;
	float gravForce;
	float rotation;
	b2Vec2 maxVelocity;
};

