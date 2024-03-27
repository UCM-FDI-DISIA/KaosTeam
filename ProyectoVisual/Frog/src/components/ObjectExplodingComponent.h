#pragma once
#include "../ecs/Component.h"
//Tendrá un booleano que determina si explota o no y un timer que cuando llegue a cero, explota

class ObjectExplodingComponent : public Component
{
private:
	bool explode;
public:
};