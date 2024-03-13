#pragma once

#include "GameState.h"
#include "Game.h"

class MenuInicio;

class NewGameState : public GameState {
public:
	NewGameState(Game* game/*Llamar a la constructora de la fachada del player*/);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;

	MenuInicio* getMenuInicio() const { return mInicio; }
private:
	MenuInicio* mInicio; //Puntero que gestiona la pantalla de MenuInicio
};

