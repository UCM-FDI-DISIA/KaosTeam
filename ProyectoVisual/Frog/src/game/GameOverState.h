#pragma once

#include "GameState.h"
#include  "../managers/HUDManager.h"
#include "../ecs/Scene.h"
#include "Game.h"

class MenuGameOver;

class GameOverState :public GameState
{
public:
	GameOverState(Game* game/*Llamar a la constructora de la fachada del player*/);
	virtual ~GameOverState();
	void leave() override;
	void update() override;
	void enter() override;

	//Getters
	Scene* getScene() const override {return &currScene; };
private:
	MenuGameOver* mGameOver; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

