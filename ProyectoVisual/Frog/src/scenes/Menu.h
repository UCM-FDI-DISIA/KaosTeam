#pragma once

#include "../game/Game.h"
#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class GameState;

enum direction{ARRIBA, ABAJO};

//Constantes de los botones (Menu Inicio)
const int BUTTONSTART_W = WIN_WIDTH * 2 / 5;
const int BUTTONEND_W = WIN_WIDTH * 2 / 5;
const int BUTTONSTART_H = WIN_HEIGHT * 2 / 12;
const int BUTTONEND_H = WIN_HEIGHT * 2 / 12;
const int BUTTONSTART_X = WIN_WIDTH / 2 - BUTTONSTART_W / 2;
const int BUTTONEND_X = WIN_WIDTH / 2 - BUTTONSTART_W / 2;
const int BUTTONSTART_Y = WIN_HEIGHT * 4 / 8;
const int BUTTONEND_Y = WIN_HEIGHT * 5 / 7;
//Constantes de los botones (Menu Pausa)
const int BUTTONCONTINUE_W = WIN_WIDTH * 3 / 5;
const int BUTTONOUT_W = WIN_WIDTH * 3 / 5;
const int BUTTONCONTINUE_H = WIN_HEIGHT * 6 / 12;
const int BUTTONOUT_H = WIN_HEIGHT * 6 / 12;
const int BUTTONCONTINUE_X = WIN_WIDTH / 2 - BUTTONSTART_W * 3 / 2;
const int BUTTONOUT_X = WIN_WIDTH / 2;
const int BUTTONCONTINUE_Y = WIN_HEIGHT * 3 / 8;
const int BUTTONOUT_Y = WIN_HEIGHT * 5 / 7;



const int offsetX = 50; //Offset de la seleccion

class Menu : public Scene
{
private:
	Texture* bg; //Textura de fondo del menu
	Texture& currSelec; //Textura que apunta al boton seleccionado
	SDL_Rect selecDest; //resize de la mosca
	SDL_Rect bgDest; //resize del fondo
	GameState* gameState;
	Game* game;
	InputManager& imngr;

	int width; //Ancho de la pantalla
	int height; //Alto de la pantalla
	int currButton; //Iterador del vector de botones
	
	std::vector <Button*> menuButton;
public:
	Menu(Game* g, GameState* nGS, Texture * path1, Texture * path2, int menu);
	~Menu();

	void render() override;
	void update() override;
	void initButtons(SDL_Rect & buttonStartDest, SDL_Rect & buttonEndDest, Texture* path1, Texture* path2, int menu);
	void changeButton(bool dir);
	void menuToRender(int menu);
	void callButton();
};

