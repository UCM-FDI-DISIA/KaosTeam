#pragma once
#include "GameState.h"

class Game;
class EndingScene;
class EndingState:public GameState
{
public:
	EndingState(Game* g);
	virtual ~EndingState();
	void leave() override;
	void update() override;
	void enter() override;

	//Getters
	Scene* getScene() const override { return &currScene; };
private:
	Game* game;
	EndingScene* ending; //Puntero que gestiona la pantalla de MenuInicio
	Scene& currScene; //puede haber escenas d menu d opciones,etc.
};

