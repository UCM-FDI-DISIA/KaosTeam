#include "BossComponent.h"

BossComponent::BossComponent() : currState(MOVE), shadowTimer(0), postAttackTimer(2), speed(1.5), multiplier(0.2),
		pos(Vector2D(0, 0))
{
	initComponent();
}

BossComponent::~BossComponent()
{
}

void BossComponent::initComponent()
{
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
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
	createCutlery();
	moveCutlery();
}

void BossComponent::darkenShadow()
{
	//Lógica de cambiar de la textura por la más oscura
}

void BossComponent::createCutlery()
{
	/* Lógica de crear los cubiertos.
		Usar randoms para la aparicion de cada uno, otro para decidir si se crea cuchillo o tenedor, otro para 
		la fila en la que spawnea, y otro para la velocidad que tendrá. */
}

void BossComponent::moveCutlery()
{
	//Lógica para mover los cubiertos que estén activos en la pool de cubiertos

	if (hasCrashed() || isOutOfScreen())
	{

	}
}

bool BossComponent::isFlonkOnShadow() const
{
	//Lógica de comprobar si Flonk esta en cualquiera de las casillas que ocupa la sombra
	return false;
}

bool BossComponent::hasCrashed() const
{
	//Lógica de colision con otras entidades de la sala
	return false;
}

bool BossComponent::isOutOfScreen() const
{
	//Lógica para obtener la posicion del cubierto y ver si está fuera de la pantalla
	return false;
}
