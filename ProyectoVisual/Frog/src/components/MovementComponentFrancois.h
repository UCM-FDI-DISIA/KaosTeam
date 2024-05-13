#pragma once

#include "../utils/Vector2D.h"
#include "TransformComponent.h"
#include "MovementComponent.h"

const Vector2D BOSS_INIT_POS = Vector2D(12, 0);

class MovementComponentFrancois : public MovementComponent
{
private:
	short int lowerLimit; //Limite inferior de movimiento del Boss
	short int upperLimit; //Limite superior de movimiento del Boss

	float multiplier;

	Vector2D pos; //Posicion de la sombra

	TransformComponent* tr;
public:
	MovementComponentFrancois();
	~MovementComponentFrancois();

	void initComponent() override;

	void update() override;

	//Getters
	//Esta en el borde de la pantalla
	bool isShadowAtLimit(Vector2D pos) const { return  tr->getCasilla().getX() <= lowerLimit || tr->getCasilla().getX() >= upperLimit; };

	//Setters
	void setDirection() { if (isShadowAtLimit(pos)) velocity = velocity * -1; };
	void setLowerLimit(short int newLimit) { lowerLimit = newLimit; };
	void setSpeed(Vector2D newSpeed) { velocity = newSpeed; };
	void setMultiplier(float newMultiplier) { multiplier = newMultiplier; };
};

