#pragma once
#include "../ecs/Component.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "../sdlutils/VirtualTimer.h"
#include <iostream>

class LifeComponent : public Component{
private:
	int vidaActual; //Un  punto es media mosca
	int vidaMaxima;

	AnimationComponent* animator;
	MovementComponent* move;

	VirtualTimer timerforDelete; //Timer para borrar la entidad pasado cada cierto tiempo
	Uint32 aliveTime;			 //Tiempo de vida antes de que la entidad se elimine
public:
	LifeComponent() : vidaActual(0), vidaMaxima(0),
		animator(nullptr), move(nullptr), aliveTime(2000) {
		timerforDelete.pause();
	};
	LifeComponent(int actual, int maxima) :vidaActual(actual), vidaMaxima(maxima),
		animator(nullptr), move(nullptr), aliveTime(2000) {
		timerforDelete.pause();
	};
	~LifeComponent();
	int GetActual();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	bool alive();
	void hit(int damage); //A llamar cuando se daña a la entidad

	void initComponent() override;
	void update() override;
};

