#pragma once
//#include "../components/TransformComponent.h"
#include "../components/LifeComponent.h"
class DestructibleComponent
{
private:
	LifeComponent life = LifeComponent(1,1);

	void selfDestruct();

public:
	DestructibleComponent();
	void update();
};

