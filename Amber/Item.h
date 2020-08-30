#include "GameObject.h"
#include <string.h>
#pragma once
class Item : public GameObject
{
public:
	Item();
	~Item();

private:
	std::string name;
	int amount;
	std::string type;
	float durability;
	float quality;
};

