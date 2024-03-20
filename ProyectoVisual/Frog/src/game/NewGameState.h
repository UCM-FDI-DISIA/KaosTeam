#pragma once

#include "GameState.h"

class Game;
class MenuInicio;

class NewGameState : public GameState {
public:
	NewGameState(Game* game);//*Llamar a la constructora de la fachada del player*/);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
	
	//Getters
	Scene* getScene() const override { return &currScene; };
private:
	Game* game;
	MenuInicio* mStart; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
	Game& game;
};

