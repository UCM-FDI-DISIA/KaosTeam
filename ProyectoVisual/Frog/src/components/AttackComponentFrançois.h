#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include <vector>

class AttackComponentFran�ois:public Component
{
private:
	bool detected; //para cuando detecte a Flonk
	std::vector<Entity*> cubiertos;

public:
	
};

