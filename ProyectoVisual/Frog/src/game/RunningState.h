#pragma once

#include "GameState.h"
#include "../managers/HUDManager.h"
#include "../ecs/Scene.h"
#include "Game.h"
#include <vector>
const int numRooms = 100;
class RunningState: public GameState
{
public:
	RunningState(Game* game/*Llamar a la constructora de la fachada del player*/);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
	void changeScene(int id); //Este metodo se usará para el cambio de habitaciones en el estado;
	//Getters
	Scene* getScene() const override { return currScene; };
	HUDManager* getHUD()const { return hud; }
private:
	HUDManager* hud; //Puntero que gestiona la pantalla de MenuInicio
	Scene* currScene; //puede haber escenas d menu d opciones,etc.
	vector<Scene*> allRooms;
	//void se presiona el boton d pausa {llama al game change estate a ause y le pasa la currScene y el hud
};


