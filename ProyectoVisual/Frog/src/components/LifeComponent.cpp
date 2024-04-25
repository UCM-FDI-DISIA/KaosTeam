#include "LifeComponent.h"

void LifeComponent::initComponent() {
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	move = static_cast<MovementComponent*>(ent->getComponent(MOVEMENT_COMPONENT));
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

	//Si ya no tiene vida
	if (!alive()) {
		move->setStatic(); //Paramos a la entidad
		animator->stopAnimation();
		animator->playAnimation("DEATH"); //Reproducimos animacion de muerte (si la tiene)
	}

	std::cout << "Vida de la entidad: " << vidaActual << std::endl;
};

void LifeComponent::SetMax(int n) {
	vidaMaxima += n;
}

bool LifeComponent::alive() {
	return vidaActual > 0;
}

void LifeComponent::update() {

}
