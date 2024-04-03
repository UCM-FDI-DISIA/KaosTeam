#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../scenes/RoomScene.h"

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
	//Por hacer
	TransformComponent(Vector2D casilla, float width, float height) : casilla(casilla), width(width), height(height) {}
	//Crea un transform cuadrado con escala determinada en funcion al tamaño de las casillas
	TransformComponent(Vector2D casilla, float scale) : casilla(casilla) {
		int tam = ent->getScene()->getMapReader()->getTileSize();
		width = tam;
		height = tam;
		offset = Vector2D(0, 0);
	}

	~TransformComponent() {};

	Vector2D& getCasilla() {
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

	SDL_Rect GetOnDisplayPosition();
};

