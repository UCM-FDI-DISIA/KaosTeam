# pragma once

#include"Menu.h"

class Texture;
class InputManager;
class GameState;

//Constantes de los botones (Menu Pausa)
const int BUTTONCONTINUE_W = WIN_WIDTH * 4 / 8;
const int BUTTONOUT_W = WIN_WIDTH * 2 / 9;
const int BUTTONCONTINUE_H = WIN_HEIGHT / 2;
const int BUTTONOUT_H = WIN_HEIGHT / 3;
const int BUTTONCONTINUE_X = WIN_WIDTH * 2 / 9;
const int BUTTONOUT_X = WIN_WIDTH * 3 / 9;
const int BUTTONCONTINUE_Y = WIN_HEIGHT * 2 / 10;
const int BUTTONOUT_Y = WIN_HEIGHT * 5 / 9;

class MenuPausa :public Menu
{
private:

public:
	MenuPausa(Game* g, GameState* gs, Texture* path1, Texture* path2);
	~MenuPausa() {};
};