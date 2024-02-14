#pragma once
#include "../components/MapComponent.h"
#include "../sdlutils/SDLUtils.h"

class Scene
{
	/**
	* Clase abstracta de escena, todo lo que es programación debe ir en su clase hija.
	* Todas las clases deben ser implementadas.
	* 
	* Las salas deberían ser una clase hija de Escena
	* Otras escenas pueden ser el menú de inicio y el menú de pausa.
	*/

protected:
	MapComponent* mapReader_;

	//constructora
	Scene() {};

public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};