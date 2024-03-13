#pragma once

#include "GameState.h"

class MenuInicio;

class NewGameState : public GameState {
public:
	NewGameState(/*Llamar a la constructora de la fachada del player*/);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	MenuInicio* m_inicio; //Puntero que gestiona la pantalla de MenuInicio
};

