#include "MovementComponent.h"

MovementComponent::MovementComponent(Vector2D casilla) {
	this->posCasilla = casilla;
}

Vector2D MovementComponent::getCasilla() {
	return posCasilla;
}