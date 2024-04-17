#include "BossComponent.h"

BossComponent::BossComponent()
{
	initComponent();
}

BossComponent::~BossComponent()
{
}

void BossComponent::initComponent()
{

}

void BossComponent::update()
{
	switch (currState) {
	case MOVE:
		move();
		break;
	case DETECT:
		detect();
		break;
	case ATTACK:
		attack();
		break;
	default:
		break;
	}
}

void BossComponent::move()
{
	if (isFlonkOnShadow()) {
		currState = DETECT;
	}
	//Logica de mover a la sombra -> Mover el Transform de la entidad Boss en base a su velocidad

}

void BossComponent::detect()
{
	if (isFlonkOnShadow()) {
		shadowTimer++;
		if (shadowTimer >= MAX_TIME_ON_SHADOW) {
			currState = ATTACK;
			shadowTimer = 0;
		}
	}
	else {
		currState = MOVE;
		shadowTimer = 0;
	}
}

void BossComponent::attack()
{
	darkenShadow();

}

void BossComponent::darkenShadow()
{
	//Lógica de cambiar de la textura por la más oscura
}

bool BossComponent::isFlonkOnShadow() const
{
	//Lógica de comprobar si Flonk esta en cualquiera de las casillas que ocupa la sombra
	return false;
}
