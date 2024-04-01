#include "Menu.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"
#include "../game/Game.h"

Menu::Menu(Game* g, GameState* gs, Texture * path1, Texture * path2, int menu):
		Scene(), //
		gameState(gs), //
		imngr(im()), //
		game(g), // 
		bg(nullptr), //
		currSelec(sdlutils().images().at("fly")), //
		width(WIN_WIDTH), height(WIN_HEIGHT), //
		currButton(0) //
{
	menuToRender(menu); //Define que menu se renderizara
	SDL_Rect buttonStartDest, buttonEndDest; //Posiciones de botones en pantalla
	initButtons(buttonStartDest, buttonEndDest, path1, path2, menu);

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = buttonStartDest.x - offsetX - selecDest.w / 2;
	selecDest.y = buttonStartDest.y + buttonStartDest.h / 2 - currSelec.height() / 2;

	bgDest.x = bgDest.y = 0;
	bgDest.w = width;
	bgDest.h = height;
}

Menu::~Menu()
{
	delete bg;
	for (int i = 0; i < menuButton.size(); i++)
		delete menuButton[i];
}

void Menu::render() {
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

void Menu::initButtons(SDL_Rect & buttonStartDest, SDL_Rect & buttonEndDest, Texture* path1,
	Texture* path2, int menu)
{
	//Asignamos posicion a los botones
	switch (menu)
	{
	case INICIO:
		buttonStartDest.w = buttonEndDest.w = BUTTONSTART_W;
		buttonStartDest.h = buttonEndDest.h = BUTTONSTART_H;
		buttonStartDest.x = buttonEndDest.x = BUTTONSTART_X;
		buttonStartDest.y = BUTTONSTART_Y; buttonEndDest.y = BUTTONEND_Y;
		break;
	case PAUSA:

		break;
	case GAMEOVER:

		break;
	default:
		break;
	}

	//Boton de Start
	menuButton.push_back(new Button(path1, buttonStartDest));
	menuButton[0]->connect([this]() { gameState->enter(); }); 
	//Boton de exit
	menuButton.push_back(new Button(path2, buttonEndDest));
	menuButton[1]->connect([this]() { gameState->leave(); });
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
	selecDest.y = menuButton[currButton]->getRect().y + menuButton[currButton]->getRect().h / 2 
		- currSelec.height() / 2;
}

void Menu::menuToRender(int menu)
{
	switch (menu) {
	case INICIO:
		bg = &sdlutils().images().at("MenuInicio");
		break;
	case PAUSA:
		bg = &sdlutils().images().at("Pausa");
		break;
	case GAMEOVER:
		bg = &sdlutils().images().at("GameOver");
		break;
	default:
		cout << "Intentando renderizar menu inexistente." << endl;
	}
}

void Menu::callButton()
{
	menuButton[currButton]->perform();
}
