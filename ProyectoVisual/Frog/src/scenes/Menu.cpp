#include "Menu.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"
#include "SDL.h"


Menu::Menu(Game* g, GameState* gs, Texture * path1, Texture * path2):
		Scene(), //
		gameState(gs), //
		imngr(im()), //
		game(g), // 
		bg(nullptr), //
		currSelec(sdlutils().images().at("fly")), //
		width(WIN_WIDTH), height(WIN_HEIGHT), //
		currButton(0) //
{
	
}

Menu::~Menu()
{
	game = nullptr;
	gameState = nullptr;
	bg = nullptr;

	for (auto it : menuButton)
	{
		delete it;
	}
}

void Menu::render() {
	bgEffect->render(bgDest);
	bg->render(bgDest); 
	currSelec.render(selecDest);
	for (auto it : menuButton)
		it->render();
}

void Menu::update() {
	if (imngr.getAction1()) callButton();
	else if (imngr.getUp()) changeButton(ARRIBA);
	else if (imngr.getDown()) changeButton(ABAJO);
}

void Menu::changeButton(bool dir)
{
	if (ARRIBA)
	{
		if (currButton < 0) currButton = menuButton.size() - 1;
		else currButton -= 1;
	}
	else currButton = (currButton + 1) % menuButton.size();
	
	//Modifico la pos de la seleccion actual (mosca)
	selecDest.x = menuButton[currButton]->getRect().x - offset - selecDest.w / 2;
	selecDest.y = menuButton[currButton]->getRect().y + menuButton[currButton]->getRect().h / 2 
		- currSelec.height() / 2;
}

void Menu::callButton()
{
	menuButton[currButton]->perform();
}
