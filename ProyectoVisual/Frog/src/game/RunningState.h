#pragma once

#include "GameState.h"
#include "../managers/HUDManager.h"
#include "../ecs/Scene.h"
#include <vector>
//const int numRooms = 100;

class Game;
class InputManager;
class RunningState: public GameState
{
public:
	RunningState(Game* game);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
	void changeScene(int id); //Este metodo se usará para el cambio de habitaciones en el estado;
	//Getters
	Scene* getScene() const override { return currScene; };
	HUDManager* getHUD()const { return hud; }
private:
	Game* game;
	HUDManager* hud; //Puntero que gestiona la pantalla de MenuInicio
	Scene* currScene; //puede haber escenas d menu d opciones,etc.
	std::vector<Scene*> allRooms; //NO SE UTILIZA
	InputManager& imngr;
	//void se presiona el boton d pausa {llama al game change estate a pause y le pasa la currScene y el hud
};
