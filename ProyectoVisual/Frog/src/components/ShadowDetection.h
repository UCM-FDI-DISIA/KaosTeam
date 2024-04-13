#pragma once
#include "../ecs/Component.h"
const int TIME_DETECTION=3;
class ShadowDetection:public Component
{
private:
	bool active;
	int timer; //para saber cuanto tiempo ha pasado en la sombra
public:
};

