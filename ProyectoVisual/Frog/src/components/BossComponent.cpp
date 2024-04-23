#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"

BossComponent::BossComponent() : currState(MOVE), shadowTimer(0), postAttackTimer(2), pos(BOSS_INIT_POS), //
	speed(Vector2D(-ent->getScene()->getMapReader()->getTileSize()/5,0)), multiplier(0.2), //
	lowerLimit(0), upperLimit(ent->getScene()->getMapReader()->getMapSize().getX())	//

{
	initComponent();
	createCutlery();
}

BossComponent::~BossComponent()
{
}

void BossComponent::initComponent()
{
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
	render = ent->getRenderComponent();
}

void BossComponent::update()
{
	switch (currState) {
	case MOVE:
		checkDirection();
		move();
		break;
	case DETECT:
		checkDirection();
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
		pos = pos + speed * multiplier;
	}
	else {
		pos = pos + speed;
	}
	//Logica de mover a la sombra -> Mover el Transform de la entidad Boss en base a su velocidad

}

void BossComponent::detect()
{
	if (isFlonkOnShadow()) {
		shadowTimer++;
		if (shadowTimer >= MAX_TIME_ON_SHADOW) {
			darkenShadow();
			currState = ATTACK;
			shadowTimer = 0;
		}
	}
	else {
		currState = MOVE;
		resetShadow();
		shadowTimer = 0;
	}
}

void BossComponent::attack()
{
	createCutlery();
	moveCutlery();
}

void BossComponent::checkDirection()
{
	if (isShadowAtSideLine(pos)) speed = speed * -1;
}

void BossComponent::darkenShadow()
{
	//L�gica de cambiar de la textura por la m�s oscura
}

void BossComponent::resetShadow()
{
}

void BossComponent::createCutlery()
{
	/* L�gica de crear los cubiertos.
		Usar randoms para la aparicion de cada uno, otro para decidir si se crea cuchillo o tenedor, otro para 
		la fila en la que spawnea, y otro para la velocidad que tendr�. */
}

void BossComponent::moveCutlery()
{
	//L�gica para mover los cubiertos que est�n activos en la pool de cubiertos
	for (auto cubierto : poolCubiertos)
		if(cubierto.second) cubierto.first->pos = cubierto.first->pos + cubierto.first->speed;
}

void BossComponent::changeRange()
{
}

bool BossComponent::isFlonkOnShadow() const
{
	//L�gica de comprobar si Flonk esta en cualquiera de las casillas que ocupa la sombra
	return false;
}

bool BossComponent::hasCrashed() const
{
	//L�gica de colision con otras entidades de la sala
	return false;
}

bool BossComponent::isOutOfScreen(Vector2D pos) const
{
	//L�gica para obtener la posicion del cubierto y ver si est� fuera de la pantalla
	return pos.getY() >= sdlutils().height();
}

bool BossComponent::isShadowAtSideLine(Vector2D pos) const
{
	return pos.getX() <= lowerLimit
		|| pos.getX() - sombra->width() >= sdlutils().width();
}

void BossComponent::setSpeed(Vector2D spd)
{
	speed = spd;
}

void BossComponent::setLowerLimit(short int limit)
{
	lowerLimit = limit;
}
