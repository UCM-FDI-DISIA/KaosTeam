#pragma once

#include "../utils/Vector2D.h"
#include "TransformComponent.h"
#include "MovementComponent.h"

class MovementComponentFrancois : public MovementComponent
{
private:
	short int lowerLimit; //Limite inferior de movimiento del Boss
	short int upperLimit; //Limite superior de movimiento del Boss

	float multiplier;

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
	void setDirection() { if (isShadowAtLimit(tr->getCasilla())) velocity = velocity * -1; };
	void setLowerLimit(short int newLimit) { lowerLimit = newLimit; };
	void setSpeed(Vector2D newSpeed) { velocity = newSpeed; };
	void setMultiplier(float newMultiplier) { multiplier = newMultiplier; };
};

