#pragma once
#include "../ecs/Component.h"
#include "../managers/InputManager.h"
#include "../components/RenderComponentFrog.h"
#include "ColliderComponent.h"
#include "../scenes/RoomScene.h"

/*
* Clase que gestiona el componente del ataque de la rana.
* Esta va a comprobar la colision de su lengua con los enemigos y les va a quitar vida dependiendo del daño de la rana
* En esta clase tambien se va a hacer el drop del posible loot que suelten los enemigos al morir
*/

class Box;
class Entity;
class AttackComponentFrog : public Component
{
private:
	const Uint32 WAIT_ATTACK = 1000;							//tiempo de espera para volver a atacar
	int distance , distanceMoved ;
	int attackFrameTime , lastTimeChanged, attackCooldown ;
	//resting = 0, attacking = 1, retracting = 2
	int state = 0;
	InputManager* inputM;
	bool hasHook;
	Box* box;
	RoomScene* scen = nullptr;									//escena donde se encuentran
	bool hitted = true;											// "marca" al enemigo como dañado
	Uint32 elapsedTime;
	RandomNumberGenerator& rand_;							//Generador de numeros random
	void dropLoot(Vector2D pos);
public:
	AttackComponentFrog();
	virtual ~AttackComponentFrog();
	void initComponent() override;
	void update() override;
	int getDistanceMoved() { return distanceMoved; };
	void attack(bool withHook = false);
	void EndAttack();
	void tongueTouch(Entity* e, Collider c);
	void UpdateBox(Vector2D casilla, int w, int h);
	void setDistance(int d) { distance = d; }
	bool attackHasHook() { return hasHook; };
};

