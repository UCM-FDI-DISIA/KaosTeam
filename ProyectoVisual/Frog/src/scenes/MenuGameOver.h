# pragma once

#include "Menu.h"


const int BUTTONRETRY_W = WIN_WIDTH * 2 / 5;
const int BUTTONEND_W = WIN_WIDTH * 2 / 5;

const int BUTTONRETRY_H = WIN_HEIGHT * 2 / 12;
const int BUTTONEXIT_H = WIN_HEIGHT * 2 / 13;

const int BUTTONRETRY_X = WIN_WIDTH / 2 - BUTTONRETRY_W * 2 / 5;
const int BUTTONEXIT_X = WIN_WIDTH / 2 - BUTTONRETRY_W * 2 / 5;

const int BUTTONRETRY_Y = WIN_HEIGHT * 4 / 9;
const int BUTTONEXIT_Y = WIN_HEIGHT * 5 / 8;

class Texture;
class InputManager;
class GameState;

class MenuGameOver : public Menu
{
public:
	MenuGameOver(Game* g, GameState* gs, Texture* p1, Texture* p2);
	~MenuGameOver();
};