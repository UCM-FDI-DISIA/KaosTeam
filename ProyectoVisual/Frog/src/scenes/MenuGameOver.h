# pragma once

#include"Menu.h"


const int BUTTONRETRY_W = WIN_WIDTH * 2 / 5;
const int BUTTONRETRY_X = WIN_WIDTH / 2 - BUTTONRETRY_W * 2 / 5;
const int BUTTONRETRY_Y = WIN_HEIGHT * 4 / 9;
const int BUTTONRETRY_H = WIN_HEIGHT * 2 / 12;

const int BUTTONEND_X = WIN_WIDTH / 2 - BUTTONRETRY_W * 2 / 5;
const int BUTTONEND_Y = WIN_HEIGHT * 5 / 8;
const int BUTTONEND_W = WIN_WIDTH * 2 / 5;
const int BUTTONEND_H = WIN_HEIGHT * 2 / 13;

const int GAMEOVERTEXT_X = WIN_WIDTH / 2 - BUTTONRETRY_W * 2 / 5;
const int GAMEOVERTEXT_Y = WIN_HEIGHT / 2;
const int GAMEOVERTEXT_W = WIN_WIDTH * 2 / 5;
const int GAMEOVERTEXT_H = WIN_HEIGHT * 2 / 13;

class Texture;
class InputManager;
class GameState;

class MenuGameOver : public Menu
{
private:

public:
	MenuGameOver(Game* g, GameState* gs, Texture* p1, Texture* p2);
	~MenuGameOver();
};