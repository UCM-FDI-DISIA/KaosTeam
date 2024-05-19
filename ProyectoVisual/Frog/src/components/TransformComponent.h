#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../utils/Box.h"

class SDL_Rect;
//Define el tama�o y posici�n de la entidad (si tiene)
class TransformComponent : public Component, public Box
{
public:
	TransformComponent(Vector2D casilla, float width, float height);
	//Crea un transform cuadrado con escala determinada en funcion al tama�o de las casillas
	TransformComponent(Vector2D casilla);
	~TransformComponent() {};

	//Comprueba si se puede colocar en esa posici�n. En caso de que se pueda, cambia la posici�n de casilla del transform.
	void changePos(Vector2D v);

	Vector2D getCasilla() {
		return casilla;
	}

	void setCasilla(Vector2D casilla) {
		this->casilla = casilla;
	}

	float getWidth() {
		return width;
	}

	float getHeight() {
		return height;
	}

	Vector2D getOffset() {
		return offset;
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


	Vector2D* getCasillaPointer() {
		return &casilla;
	}
};
