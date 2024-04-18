#include "MenuInicio.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"
MenuInicio::MenuInicio(Game* g, GameState* gs, Texture* path1, Texture* path2): Menu(g,gs,path1,path2)
{
	SDL_Rect button1Dest, button2Dest;

	button1Dest.w = button2Dest.w = BUTTONSTART_W;
	button1Dest.h = button2Dest.h = BUTTONSTART_H;
	button1Dest.x = button2Dest.x = BUTTONSTART_X;
	button1Dest.y = BUTTONSTART_Y; button2Dest.y = BUTTONEND_Y;
	//Fondo
	bgDest.x = bgDest.y = 0;
	bgDest.w = width;
	bgDest.h = height;

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = button1Dest.x - offset - selecDest.w / 2;
	selecDest.y = button1Dest.y + button1Dest.h / 2 - currSelec.height() / 2;

	bg = &sdlutils().images().at("MenuInicio");

	menuButton.push_back(new Button(path1, button1Dest));
	menuButton[0]->connect([this]() { gameState->enter(); });
	//Boton de exit
	menuButton.push_back(new Button(path2, button2Dest));
	menuButton[1]->connect([this]() { gameState->leave(); });
}
