#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class SDL_Rect;
//Define el tamaño y posición de la entidad (si tiene)
class TransformComponent : public Component
{
private:
	Vector2D casilla;
	float width;
	float height;
	//El offset dentro de la casilla
	Vector2D offset;

public:
	TransformComponent(Vector2D casilla, float width, float height) : casilla(casilla), width(width), height(height) {
		offset = { 0,0 };
	}
	//Crea un transform cuadrado con escala determinada en funcion al tamaño de las casillas
	TransformComponent(Vector2D casilla);
	~TransformComponent() {};

	SDL_Rect GetOnDisplayPosition();

	void changePos(Vector2D v);
	void resetPos(Vector2D v);

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
