#pragma once
#include "Vector2D.h"

class SDL_Rect;
//Representa una caja en el espacio con tamaño
class Box
{
public:
	Box(Vector2D casilla, float width, float height);
	Box(Vector2D casilla);

	SDL_Rect GetOnDisplayPosition();
protected:
	Vector2D casilla;
	float width;
	float height;
	//El offset dentro de la casilla
	Vector2D offset;
};

