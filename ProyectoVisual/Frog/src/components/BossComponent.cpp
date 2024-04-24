#include "BossComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../scenes/RoomScene.h"

BossComponent::BossComponent() : currState(MOVE), shadowTimer(0), postAttackTimer(2) //
{}

BossComponent::~BossComponent()
{
}

void BossComponent::initComponent()
{
	tr = ent->getComponent<TransformComponent>(TRANSFORM_COMPONENT);
	render = ent->getRenderComponent();
	mov = ent->getComponent<MovementComponentFrancois>(MOVEMENT_COMPONENT);

	//Creamos cubiertos
	for (int i = 0; i < MAX_CUBIERTOS; i++) {
		cubiertos[i]->tipo = new Entity(ent->getScene());
	}
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
		mov->setMultiplier(0.3);
		/*pos = pos + speed * multiplier;*/
	}
}

void BossComponent::detect()
{
	if (isFlonkOnShadow()) {
		shadowTimer++;
		if (shadowTimer >= MAX_TIME_ON_SHADOW) {
			darkenShadow();
			currState = ATTACK;
			mov->setMultiplier(0.0);
			shadowTimer = 0;
		}
	}
	else {
		currState = MOVE;
		resetShadow();
		mov->setMultiplier(1.0);
		shadowTimer = 0;
	}
}

void BossComponent::attack()
{
	createCutlery();
	moveCutlery();
}


void BossComponent::darkenShadow()
{
	//L�gica de cambiar alpha de la textura por la m�s oscura
}

void BossComponent::resetShadow()
{
	//Logica de cambiar alpha de textura a algo mas claro
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



