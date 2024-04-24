#pragma once

#include "../ecs/Component.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include <iostream>

class LifeComponent : public Component {
private:
	int vidaActual; //Un  punto es media mosca
	int vidaMaxima;

	AnimationComponent* animator;
	MovementComponent* move;
public:
	LifeComponent() : vidaActual(0), vidaMaxima(0), animator(nullptr), move(nullptr) {};
	LifeComponent(int actual, int maxima) :vidaActual(actual), vidaMaxima(maxima), animator(nullptr), move(nullptr) {};
	~LifeComponent();
	int GetActual();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	bool alive();

	void initComponent() override;
	void update() override;
};

