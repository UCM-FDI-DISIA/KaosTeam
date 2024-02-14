#pragma once
#include "../components/MapComponent.h"
#include "../sdlutils/SDLUtils.h"

class Scene
{
	/**
	* Clase abstracta de escena, todo lo que es programaci�n debe ir en su clase hija.
	* Todas las clases deben ser implementadas.
	* 
	* Las salas deber�an ser una clase hija de Escena
	* Otras escenas pueden ser el men� de inicio y el men� de pausa.
	*/

protected:
	MapComponent* mapReader_;

	//constructora
	Scene() {};

public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};