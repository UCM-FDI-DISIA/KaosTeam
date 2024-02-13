#pragma once
#include "utils/MapReader.h"
#include "sdlutils/SDLUtils.h"

class Scene
{
	/**
	* Clase abstracta de escena, todo lo que es programación debe ir en su clase hija.
	* Todas las clases deben ser implementadas.
	*/

protected:
	MapReader* mapReader_;

	//constructora
	Scene() {};

public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};