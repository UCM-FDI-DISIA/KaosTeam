#pragma once
#include "MovementComponent.h"
#include "MovementComponentFrog.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

class AnimationComponent;

class MovementComponentBomb : public MovementComponent {
private:
	Directions direction;
	MovementComponentFrog* moveFrog  = nullptr; //para acceder a la dirección a la que mira FLonk en ese instante
	AnimationComponent* animator = nullptr;   //para acceder a su animador
	TransformComponent* tr = nullptr;
	ColliderComponent* coll = nullptr;

	Vector2D velocity = Vector2D(0, 0);
	bool isLaunched;				//Booleano para indicar si la bomba se ha lanzado


	void moveBomb();
	void checkShock();
	void checkEntityShock(Entity* ent);
public:
	MovementComponentBomb();
	void update() override;
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};

