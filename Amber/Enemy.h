#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Renderer.h"

enum EnemyType {
	ET_SKELETON,
	ET_GOBLIN
};

class Enemy : public GameObject
{
public:
	

private:
	EnemyType enemyType;

	Animation idleAnimation;
	Animation runAnimation;
	Animation jumpAnimation;
	Animation fallAnimation;
	Animation attackAnimation;

	b2Body* enemyBody;
};

