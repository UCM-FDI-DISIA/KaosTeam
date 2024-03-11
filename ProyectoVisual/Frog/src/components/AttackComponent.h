#pragma once
#include "../ecs/Component.h"

class MovementComponent;

//Componente de ataque para TODOS los enemigos. Si NECESITA algún tipo de funcionalidad especial, heredar.
class AttackComponent : public Component
{
protected:
	int atkDistance; //La distancia de ataque (en casillas)
	int atkDamage;   //El daño que hace al golpear (media mosca por cada)
	bool attacking; //Booleano que indica si está atacando
public:
	AttackComponent(int atkDistance, int atkDamage);
	void update() override;
	void initComponent() override;
	void attack(); //El metodo a ser llamado para lanzar el ataque
	bool isAttacking(); //Getter de si está atacando
};