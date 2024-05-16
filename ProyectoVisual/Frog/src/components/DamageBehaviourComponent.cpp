﻿#include "DamageBehaviourComponent.h"
#include "../scenes/RoomScene.h"

DamageBehaviourComponent::DamageBehaviourComponent(std::string damageAnim) : animator(nullptr), move(nullptr){
	damageAnimation = damageAnim;
}

DamageBehaviourComponent::~DamageBehaviourComponent() {
	animator = nullptr;
	move = nullptr;
}

void DamageBehaviourComponent::manageDamage() {
	animator->stopAnimation(); //Paramos la animaci�n que estuviese haciendo
	animator->playAnimation(damageAnimation); //Reproducimos animacion de muerte (si la tiene)
	move->setCanMove(false);
	elapsedTime = sdlutils().virtualTimer().currTime();
}

void DamageBehaviourComponent::initComponent() {
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	move = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT));
}

void DamageBehaviourComponent::update() {
	if(!move->getMoveState() && sdlutils().virtualTimer().currTime() > elapsedTime + 3000) {
		move->setCanMove(true);
	}

}