#include "Box.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/CameraManager.h"

//El tama�o en pixeles de la casilla
const int TILE_SIZE = 80;

Box::Box(Vector2D casilla, float width, float height) : casilla(casilla), width(width), height(height) {
	offset = { 0,0 };
};
Box::Box(Vector2D casilla) : casilla(casilla) {
	offset = { 0, 0 };
	width = TILE_SIZE;
	height = TILE_SIZE;
};
//Usar este constructor SOLO si aun no conoces al box
Box::Box() {
	casilla = { 0, 0 };
	offset = { 0, 0 };
	width = TILE_SIZE;
	height = TILE_SIZE;
};

SDL_Rect Box::GetOnDisplayPosition() const{
	SDL_Rect dest;

	Vector2D mOffset = offset + Vector2D(width / 2, height / 2);//para que este centrado en la casilla
	Vector2D cameraPos = Camera::instance()->getCameraMovement();

	//Calcula la posici�n real en pantalla
	dest.x = casilla.getX() * TILE_SIZE + mOffset.getX() - cameraPos.getX();
	dest.y = casilla.getY() * TILE_SIZE + mOffset.getY() - cameraPos.getY();

	dest.w = width;
	dest.h = height;

	return dest;
}

Vector2D Box::getCasilla() const {
	return casilla;
}

float Box::getHeight() const {
	return height;
}

float Box::getWidth() const {
	return width;
}

void Box::setCasilla(Vector2D casilla) {
	this->casilla = casilla;
}

void Box::setWidth(float width) {
	this->width = width;
}

void Box::setHeight(float height) {
	this->height = height;
}