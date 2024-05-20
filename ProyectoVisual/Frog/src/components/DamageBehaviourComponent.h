#pragma once
#include "../ecs/Component.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"


/* Este componente lleva acabo las acciones que haya que hacer cuando una entidad recibe da�o (que no sea quitar vida),
   como por ejemplo, reproducir su animaci�n de muerte o matener est�tica e inmmune a la entidad cuando se le hace da�o */

class DamageBehaviourComponent :public Component {
private:
	const Uint32 WAIT_TIME = 1000;
	AnimationComponent* animator;
	MovementComponent* move;
	std::string damageAnimation;

	Uint32 elapsedTime;
	bool isDead;
public:
	DamageBehaviourComponent(std::string damageAnim);
	virtual ~DamageBehaviourComponent();
	void manageDamage();
	void setDead(bool value);

	void initComponent() override;
	void update() override;
};

