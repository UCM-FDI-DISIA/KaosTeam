#pragma once

#include "../ecs/Component.h"
#include <iostream>

class LifeComponent : public Component {
private:
	int vidaActual; //Un  punto es media mosca
	int vidaMaxima;
public:
	LifeComponent() : vidaActual(0), vidaMaxima(0) {};
	LifeComponent(int actual, int maxima) :vidaActual(actual), vidaMaxima(maxima) {};
	~LifeComponent() {};
	int GetActual();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	bool alive();
};

