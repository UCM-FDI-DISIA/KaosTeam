#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include <vector>

class AttackComponentFranšois:public Component
{
private:
	bool active;
	bool detected; //para cuando detecte a Flonk
	std::vector<Entity*> cubiertos;

public:
	
};

