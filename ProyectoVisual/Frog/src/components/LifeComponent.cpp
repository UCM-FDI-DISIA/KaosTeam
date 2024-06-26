#include "LifeComponent.h"
#include "../scenes/RoomScene.h"
#include "../sdlutils/RandomNumberGenerator.h"
void LifeComponent::initComponent() {
	//animator = static_cast<AnimationComponent*>(ent->getComponent(ANIMATION_COMPONENT));
	damageComp = static_cast<DamageBehaviourComponent*>(ent->getComponent(DAMAGE_COMPONENT));
}

LifeComponent::~LifeComponent() {
	//animator = nullptr;
}

int LifeComponent::GetActual() {
	return vidaActual;
}

int LifeComponent::GetMax() {
	return vidaMaxima;
}

void LifeComponent::AddActual(int n)
{
	vidaActual += n;
	if (vidaActual > vidaMaxima)
		vidaActual = vidaMaxima;
}

void LifeComponent::AddMax(int n) {
	vidaMaxima += n;
}

bool LifeComponent::alive() {
	return vidaActual > 0;
}

void LifeComponent::hit(int damage) {
	vidaActual -= damage;
	if (damageComp != nullptr) {
		damageComp->manageDamage();
	}
	if (vidaActual < 0)
		vidaActual = 0; //para q no de errores al revivir a flonk

	//Si ya no tiene vidas (lo compruebo aqui para no tener que hacerlo todo el rato en el update)
	if (!alive()) {

		timerforDelete.resume(); //Ponemos contador en marcha
		if (damageComp != nullptr) {
			damageComp->setDead(true); //la entidad esta muerta
		}
	}
	if (this->ent->getName() == FROG_ENTITY) {
		sdlutils().soundEffects().at("DamageFrog").play();
	}
}

void LifeComponent::update() {

	if (timerforDelete.currTime() >= aliveTime) {
		TransformComponent* transform = static_cast<TransformComponent*>(ent->getComponent(TRANSFORM_COMPONENT));
		////en el caso de la cucaracha cuando esta muere suelta su cabeza en la escena en la que se encuentren
		if (ent->getName() == COCKROACH_ENTITY) {
			if (transform != nullptr) {
				ent->getScene()->createHeadCockroach(transform->getCasilla(), false);
			}
		}
		//posibilidad de dropear loot al morir
		if (transform != nullptr)
			dropLoot(transform->getCasilla());
		ent->getScene()->removeEntity(this->ent); //Quitamos la entidad si esta ha muerto
	}
}

/* Este metodo se utiliza para resetear el timer que boorra la entidad cada x tiempo y pausarlo.
En un principio solo se usa en el player, debido a que si revive Flonk, esto timer debe resetearse,
de lo contrario, nunca se iniciaría una nueva partida.*/
void LifeComponent::resetTimer(){
	timerforDelete.reset();
	timerforDelete.pause();
}
//soltar un loop random al matar un enemigo
//puede no soltar nada
void LifeComponent::dropLoot(Vector2D pos) {

	int prob = rand_.nextInt(0, 100);
	if (prob > 0 && prob <= 30) {
		ent->getScene()->createMoneda(pos, MONEDA_ROSA);
	}
	else if (prob > 30 && prob <= 50) {
		ent->getScene()->createMoneda(pos, MONEDA_MORADO);
	}
	else if (prob > 50 && prob <= 60) {
		ent->getScene()->createMoneda(pos, MONEDA_NARANJA);
	}
	else if (prob > 60 && prob <= 70) {
		ent->getScene()->createLifeFly(pos);
	}
}


