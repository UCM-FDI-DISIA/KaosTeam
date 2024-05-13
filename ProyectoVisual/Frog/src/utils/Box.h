#pragma once
#include "Vector2D.h"
const int TILE_SIZE = 80;
class SDL_Rect;
//Representa una caja en el espacio con tamaño
class Box
{
public:
	Box(Vector2D casilla, float width, float height);
	Box(Vector2D casilla, float width, float height, int scale);
	Box(Vector2D casilla);
	Box();
	SDL_Rect GetOnDisplayPosition() const;

	void setCasilla(Vector2D);
	void setWidth(float);
	void setHeight(float);
	Vector2D getCasilla() const;
	float getWidth() const;
	float getHeight() const;

protected:
	Vector2D casilla;
	float width;
	float height;
	float scale;
	//El offset dentro de la casilla
	Vector2D offset;
};

