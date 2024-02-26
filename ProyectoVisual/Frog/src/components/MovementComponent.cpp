#include "MovementComponent.h"
#include <iostream>

Vector2D MovementComponent::getCasilla() {
	return posCasilla;
}

void MovementComponent::update() {
	if (im->getAction1()) {
		std::cout << "funks";
	}
}