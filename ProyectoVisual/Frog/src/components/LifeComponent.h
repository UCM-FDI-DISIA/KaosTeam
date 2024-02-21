#pragma once
#include "../ecs/Component.h"
class LifeComponent:public Component
{
private:
	int currentLife; //Un  punto es media mosca
	int maxLife;
public:
	LifeComponent(int maxLife) : maxLife(maxLife), currentLife(maxLife) {};
	LifeComponent(int current, int max) :currentLife(current), maxLife(max) {};
	int GetCurrent();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	void AddLife(int n);
	void RemoveLife(int n);
	bool Alive();
};

