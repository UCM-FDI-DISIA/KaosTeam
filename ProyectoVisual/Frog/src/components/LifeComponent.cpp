#include "LifeComponent.h"
#include "../scenes/RoomScene.h"

void LifeComponent::initComponent() {
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
}
LifeComponent::~LifeComponent() {
	animator = nullptr;
	move = nullptr;
}
int LifeComponent::GetActual() {
	return vidaActual;
}

int LifeComponent::GetMax() {
	return vidaMaxima;
}

void LifeComponent::SetActual(int n) {
	vidaActual += n;
	if (vidaActual > vidaMaxima)
		vidaActual = vidaMaxima;

	//Si ya no tiene vidas (lo compruebo aqui para no tener que hacerlo todo el rato en el update)
	if (!alive()) {
		animator->stopAnimation(); //Paramos la animación que estuviese haciendo
		animator->playAnimation("DEATH"); //Reproducimos animacion de muerte (si la tiene)
		timerforDelete.resume(); //Ponemos contador en marcha
	}

	//std::cout << "Vida de la entidad: " << vidaActual << std::endl;
};

void LifeComponent::SetMax(int n) {
	vidaMaxima += n;
}

bool LifeComponent::alive() {
	return vidaActual > 0;
}

void LifeComponent::update() {
	if (timerforDelete.currTime() >= aliveTime) {
		ent->getScene()->removeEntity(this->ent); //Quitamos la entidad si esta ha muerto
	}
};
