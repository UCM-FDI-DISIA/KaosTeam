#pragma once
#include "../managers/MapManager.h"
#include "../sdlutils/SDLUtils.h"
#include "Entity.h"
//#include "../managers/DataManager.h"

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
	std::vector<Entity*> entityList;
	//MapManager* mapReader_;
	//Singleton que contiene datos generales del juego (vidas del jugador, entidades persistentes, etc)
	//DataManager* dataManager;
	
	//constructora
	Scene() {
	};

public:
	virtual ~Scene() {};
	virtual void render() = 0;
	virtual void update() = 0;

	MapManager* getMapReader();
};