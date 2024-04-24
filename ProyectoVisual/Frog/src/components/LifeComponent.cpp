#include "LifeComponent.h"

void LifeComponent::initComponent() {
	animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	move = static_cast<MovementComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
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

	std::cout << "Vida de la entidad: " << vidaActual << std::endl;
};

void LifeComponent::SetMax(int n) {
	vidaMaxima += n;
}

bool LifeComponent::alive() {
	return vidaActual > 0;
}

void LifeComponent::update() {
	if (!alive()) {
		animator->playAnimation("DEATH");
	}
}
