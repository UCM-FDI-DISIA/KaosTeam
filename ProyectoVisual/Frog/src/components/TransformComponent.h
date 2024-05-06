#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../utils/Box.h"

class SDL_Rect;
//Define el tamaño y posición de la entidad (si tiene)
class TransformComponent : public Component, public Box
{
public:
	TransformComponent(Vector2D casilla, float width, float height);
	//Crea un transform cuadrado con escala determinada en funcion al tamaño de las casillas
	TransformComponent(Vector2D casilla);
	~TransformComponent() {};

	void changePos(Vector2D v);
	void resetPos(Vector2D v);

	//Getters
	float getWidth() {
		return width;
	}

	float getHeight() {
		return height;
	}

	Vector2D getOffset() {
		return offset;
	}

	Vector2D getCasilla() {
		return casilla	;
	}

	Vector2D* getCasillaPointer() {
		return &casilla;
	}

	//Setters
	void setCasilla(Vector2D casilla) {
		this->casilla = casilla;
	}

	void setOffset(Vector2D offset) {
		this->offset = offset;
	}

	void setOffsetY(float y) {
		this->offset.setY(y);
	}

	void setOffsetX(float x) {
		this->offset.setX(x);
	}
};
