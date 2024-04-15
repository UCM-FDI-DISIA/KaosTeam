#pragma once
//#include "../components/TransformComponent.h"
#include "../components/LifeComponent.h"
class DestructibleComponent
{
private:
	LifeComponent life;

	void selfDestruct();

public:
	DestructibleComponent();
	void update();

};

