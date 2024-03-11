#include "AttackComponent.h"

AttackComponent::AttackComponent(int atkDistance, int atkDamage) : atkDistance(atkDistance), atkDamage(atkDamage)
{
	attacking = false;
}

void AttackComponent::update() {
	// Primero recibe la llamada de atacar
	// Hace los calculos necesarios para coger la/las casillas a golpear
	// Llamar al renderizado para la animaci�n de ataque
	// Hacer el da�o que sea 
}

void AttackComponent::initComponent() {

}

void AttackComponent::attack() {
	attacking = true;
}

bool AttackComponent::isAttacking() {
	return attacking;
}