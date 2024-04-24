#pragma once

#include "../components/MovementComponent.h"
const Vector2D BOSS_INIT_POS = Vector2D(12, 0);

class MovementComponentFrancois : public MovementComponent
{
private:
	short int lowerLimit; //Limite inferior de movimiento del Boss
	short int upperLimit; //Limite superior de movimiento del Boss

	float multiplier;

	Vector2D speed; //Velocidad de la sombra
	Vector2D pos; //Posicion de la sombra

	TransformComponent* tr;
public:
	MovementComponentFrancois(int width);
	~MovementComponentFrancois();

	void initComponent() override;

 void update() override;

 
	void checkDirection();
	void setLowerLimit(short int newLimit);
	void setSpeed(Vector2D newSpeed);
	void setMultiplier(float newMultiplier);

	bool isShadowAtLimit(Vector2D pos) const; //Esta en el borde de la pantalla

 
};

