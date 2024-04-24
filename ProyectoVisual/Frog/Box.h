#pragma once
//Representa una caja en el espacio con tamaño
class Box
{
private:
	Vector2D casilla;
	float width;
	float height;
	//El offset dentro de la casilla
	Vector2D offset;
};

