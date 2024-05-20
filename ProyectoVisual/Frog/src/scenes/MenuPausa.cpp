#include "MenuPausa.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"
MenuPausa::MenuPausa(GameState* gs, Texture* path1, Texture* path2):Menu(gs,path1,path2)
{
	SDL_Rect button1Dest, button2Dest;

	button1Dest.w = button2Dest.w = BUTTONCONTINUE_W;
	button1Dest.h = BUTTONCONTINUE_H; button2Dest.h = BUTTONOUT_H;
	button1Dest.x = BUTTONCONTINUE_X;  button2Dest.x = BUTTONOUT_X;
	button1Dest.y = BUTTONCONTINUE_Y; button2Dest.y = BUTTONOUT_Y;
	//Fondo
	bgDest.x = bgDest.y = 1 / 10;
	bgDest.w = width - 3 / 10;
	bgDest.h = height - 1 / 10;

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = button1Dest.x - offset - selecDest.w / 2;
	selecDest.y = button1Dest.y + button1Dest.h / 2 - currSelec.height() / 2;

	bg = &sdlutils().images().at("Pausa");

	menuButton.push_back(new Button(path1, button1Dest));
	menuButton[0]->connect([this]() { gameState->enter(); });
	//Boton de exit
	menuButton.push_back(new Button(path2, button2Dest));
	menuButton[1]->connect([this]() { gameState->leave(); });
}
