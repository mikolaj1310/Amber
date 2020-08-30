#pragma once
#include "GameObject.h"

// Static class provide collision detection functions.
class Collision
{
public:
	//AABB
	static bool checkBoundingBox(GameObject* sp1, GameObject* sp2);
	static bool checkBoundingBox(GameObject* sp1, sf::FloatRect* sp2);
	static bool checkBoundingBox(sf::FloatRect* sp1, sf::FloatRect* sp2);
	// Bounding circle
	static bool checkBoundingSphere(GameObject* sp1, GameObject* sp2);

};