#include "MenuGameOver.h"

MenuGameOver::MenuGameOver(Game* g, GameState* gs, Texture* p1, Texture* p2) : Menu(g, gs, p1, p2) {
	SDL_Rect buttonRetryDest, buttonExitDest;

	//Boton de retry y de salir
	buttonRetryDest.w = buttonExitDest.w = BUTTONRETRY_W;
	buttonRetryDest.h = buttonExitDest.h = BUTTONRETRY_H;
	buttonRetryDest.x = buttonExitDest.x = BUTTONRETRY_X;
	buttonRetryDest.y = BUTTONRETRY_Y; buttonExitDest.y = BUTTONEXIT_Y;

	//Fondo
	bgDest.x = bgDest.y = 0;
	bgDest.w = width;
	bgDest.h = height;

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = buttonRetryDest.x - offset - selecDest.w / 2;
	selecDest.y = buttonRetryDest.y + buttonRetryDest.h / 2 - currSelec.height() / 2;

	bg = &sdlutils().images().at("GameOver");

	//Boton de retry
	menuButton.push_back(new Button(p1, buttonRetryDest));
	menuButton[0]->connect([this]() { gameState->enter(); });
	//Boton de exit
	menuButton.push_back(new Button(p2, buttonExitDest));
	menuButton[1]->connect([this]() { gameState->leave(); });
}

MenuGameOver::~MenuGameOver() {
}
