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

	enum JumpState {
		JS_JUMPING,
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
	void initAnimation();
	void animatePlayer(float dt);

	float getRotation() { return rotation; };
	void setRotation(float rot) { rotation = rot; };

	b2Vec2 getGravity() { return gravity; };
	void setGravity(b2Vec2 grav, float gravF) { gravity = grav; gravForce = gravF; };

protected:
	MoveState moveState;
	JumpState jumpState;
	FaceDirState faceDirState;

	Animation idleAnimation;
	Animation runAnimation;
	Animation jumpAnimation;
	Animation fallAnimation;
	Animation attack1Animation;

	Animation* currentAnimation;

	Input* input;
	std::chrono::time_point<std::chrono::high_resolution_clock> startAttackTimer;

	b2Body* playerBody;
	b2Body* groundBody;

	b2Vec2 gravity;
	float gravForce;
	float rotation;
	b2Vec2 maxVelocity;
};

