# pragma once

#include"Menu.h"

const int BUTTONSTART_W = WIN_WIDTH * 2 / 5;
const int BUTTONEND_W = WIN_WIDTH * 2 / 5;
const int BUTTONSTART_H = WIN_HEIGHT * 2 / 12;
const int BUTTONEND_H = WIN_HEIGHT * 2 / 13;
const int BUTTONSTART_X = WIN_WIDTH / 2 - BUTTONSTART_W * 2 / 5;
const int BUTTONEND_X = WIN_WIDTH / 2 - BUTTONSTART_W * 2 / 5;
const int BUTTONSTART_Y = WIN_HEIGHT * 4 / 9;
const int BUTTONEND_Y = WIN_HEIGHT * 5 / 8;

class Texture;
class InputManager;
class GameState;

class MenuInicio : public Menu
{
private:

public:
	MenuInicio(Game* g, GameState* gs, Texture* path1, Texture* path2);
	~MenuInicio() {};
};