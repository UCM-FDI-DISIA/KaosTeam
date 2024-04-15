#pragma once
#include "MovementComponent.h"
#include "MovementComponentFrog.h"
#include "TransformComponent.h"

class AnimationComponent;

class MovementComponentBomb : public MovementComponent {
private:
	Directions direction;
	MovementComponentFrog* moveFrog  = nullptr; //para acceder a la dirección a la que mira FLonk en ese instante
	AnimationComponent* animator = nullptr;   //para acceder a su animador
	TransformComponent* tr = nullptr;
	bool isLaunched;				//Booleano para indicar si la bomba se ha lanzado

	void moveBomb(Directions dir);

public:
	MovementComponentBomb();
	void update() override;
	void initComponent() override;  //Aqui inicializamos los punteros a otros componentes que vayamos a utilizar
};

