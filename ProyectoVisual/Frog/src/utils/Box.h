#pragma once
#include "Vector2D.h"

class SDL_Rect;
//Representa una caja en el espacio con tamaño
class Box
{
public:
	Box(Vector2D casilla, float width, float height);
	//Con este constructor, se define la escala como de 1 casilla.
	Box(Vector2D casilla);
	Box();
	/*Devuelve como SDL_Rect la posición real en pantalla de la entidad a partir de su posición en las casillas y su offset*/
	SDL_Rect GetOnDisplayPosition() const;

	void setCasilla(Vector2D);
	void setWidth(float);
	void setHeight(float);
	Vector2D getCasilla() const;
	float getWidth() const;
	float getHeight() const;

protected:
	Vector2D casilla;
	//La anchura (en casillas) de la entidad
	float width;
	//La altura (en casillas) de la entidad
	float height;
	//La escala de la caja. Si es 1, mide 1 casilla. Si es 2 mide 2 casillas y etc.
	float scale;
	//El desplazamiento dentro de la casilla
	Vector2D offset;
};

