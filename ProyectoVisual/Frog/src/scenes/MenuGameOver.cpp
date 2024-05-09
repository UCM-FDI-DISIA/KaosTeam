#include "MenuGameOver.h"

MenuGameOver::MenuGameOver(Game* g, GameState* gs, Texture* p1, Texture* p2) : Menu(g, gs, p1, p2) {
	
	SDL_Rect gameOverTextDest, button1Dest, button2Dest;

	//Boton de Game Over
	gameOverTextDest.w = GAMEOVERTEXT_W;
	gameOverTextDest.h = GAMEOVERTEXT_H;
	gameOverTextDest.x = GAMEOVERTEXT_X;
	gameOverTextDest.y = GAMEOVERTEXT_Y;

	//Boton de retry y de salir
	button1Dest.w = button2Dest.w = BUTTONRETRY_W;
	button1Dest.h = button2Dest.h = BUTTONRETRY_H;
	button1Dest.x = button2Dest.x = BUTTONRETRY_X;
	button1Dest.y = BUTTONRETRY_Y; button2Dest.y = BUTTONEND_Y;

	//Fondo
	bgDest.x = bgDest.y = 0;
	bgDest.w = width;
	bgDest.h = height;

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = button1Dest.x - offset - selecDest.w / 2;
	selecDest.y = button1Dest.y + button1Dest.h / 2 - currSelec.height() / 2;

	bg = &sdlutils().images().at("MenuInicio");

	//Boton de retry
	menuButton.push_back(new Button(p1, button1Dest));
	menuButton[0]->connect([this]() { gameState->enter(); });
	//Boton de exit
	menuButton.push_back(new Button(p2, button2Dest));
	menuButton[1]->connect([this]() { gameState->leave(); });
}

MenuGameOver::~MenuGameOver() {



}
