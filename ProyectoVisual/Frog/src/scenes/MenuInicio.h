#pragma once

#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <vector>

class Texture;
class InputManager;
class NewGameState;
class Game;

enum direction{ARRIBA, ABAJO};

const int offsetX = 50;

class MenuInicio : public Scene
{
private:
	Texture* bg; //Textura de fondo
	Texture* currSelec; //Textura que apunta al boton seleccionado
	SDL_Rect dest; //resize de la mosca
	SDL_Rect bgDest; //resize del fondo
	NewGameState* newGSt;
	Game* game;
	InputManager& imngr;

	int width; //Ancho de la pantalla
	int height; //Alto de la pantalla
	int currButton; //Iterador del vector de botones
	
	std::vector <Button*> menuButton;
public:
	MenuInicio(Game* game, NewGameState* nGS);
	~MenuInicio() {};

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

