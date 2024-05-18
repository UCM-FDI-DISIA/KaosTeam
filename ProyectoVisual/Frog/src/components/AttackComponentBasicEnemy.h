#pragma once
#include <SDL.h>
#include "../ecs/Component.h"
/*
* Clase que gestiona el componente del ataque de enemigos.
* Se trata del ataque b�sico que consiste �nicamente en entrar en contacto con la rana
*/

class Collider;
class Entity;
class Box;
class AttackComponentBasicEnemy : public Component {
private:
	virtual ~AttackComponentBasicEnemy();
	void checkHit(Entity*, Collider);
	bool hitted;						// para saber si la rana acaba de ser atacada
	int damage;							// da�o que va a hacer a la rana, depende del enemigo
	Uint32 elapsedTime;					
	const Uint32 WAIT_ATTACK = 3000;	//tiempo de espera para volver a atacar
public:
	AttackComponentBasicEnemy(int damage);
	void update() override;
	void initComponent() override;
};

