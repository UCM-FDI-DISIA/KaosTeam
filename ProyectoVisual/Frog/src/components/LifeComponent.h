#pragma once
#include "../ecs/Component.h"
class LifeComponent:public Component
{
private:
	int currentLife = 0; //Un  punto es media mosca
	int maxLife = 0;
public:
	LifeComponent() {};
	LifeComponent(int current, int max) :currentLife(current), maxLife(max) {};
	int GetCurrent();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	bool alive();
};

