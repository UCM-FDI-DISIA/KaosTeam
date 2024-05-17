#include "LifeComponent.h"
#include "../scenes/RoomScene.h"

void LifeComponent::initComponent() {
	//animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	damageComp = static_cast<DamageBehaviourComponent*>(ent->getComponent(DAMAGE_COMPONENT));
}

LifeComponent::~LifeComponent() {
	//animator = nullptr;
}

int LifeComponent::GetActual() {
	return vidaActual;
}

int LifeComponent::GetMax() {
	return vidaMaxima;
}

void LifeComponent::AddActual(int n)
{
	if (vidaActual < vidaMaxima)
		vidaActual += n;
}

void LifeComponent::AddMax(int n) {
	vidaMaxima += n;
}

bool LifeComponent::alive() {
	return vidaActual > 0;
}

void LifeComponent::hit(int damage) {
	vidaActual -= damage;
	if (damageComp != nullptr) {
		damageComp->manageDamage();
	}
	//Si ya no tiene vidas (lo compruebo aqui para no tener que hacerlo todo el rato en el update)
	if (!alive()) {
		//animator->stopAnimation(); //Paramos la animaci�n que estuviese haciendo
		//animator->playAnimation("DEATH"); //Reproducimos animacion de muerte (si la tiene)
		timerforDelete.resume(); //Ponemos contador en marcha
	}
}

void LifeComponent::update() {
	if (timerforDelete.currTime() >= aliveTime) {
		ent->getScene()->removeEntity(this->ent); //Quitamos la entidad si esta ha muerto
	}
};


