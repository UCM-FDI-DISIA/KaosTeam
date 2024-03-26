#pragma once

#include "GameState.h"

class Game;
class Menu;

class GameOverState :public GameState
{
public:
	GameOverState(Game* g/*Llamar a la constructora de la fachada del player*/);
	virtual ~GameOverState();
	void leave() override;
	void update() override;
	void enter() override;

	//Getters
	Scene* getScene() const override {return &currScene; };
private:
	Game* game;
	Menu* mGameOver; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

