#pragma once

#include "GameState.h"

class Game;
class Menu;

class NewGameState : public GameState {
public:
	NewGameState(Game* game);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
	
	//Getters
	Scene* getScene() const override { return &currScene; };
private:
	Game* game;
	Menu* menu; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

