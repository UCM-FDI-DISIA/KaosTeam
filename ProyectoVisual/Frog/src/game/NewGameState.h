#pragma once

#include "GameState.h"

class Game;
class MenuInicio;

class NewGameState : public GameState {
public:
	NewGameState();
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
	
	//Getters
	Scene* getScene() const override { return &currScene; };
private:
	Game* game;
	MenuInicio* menu; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

