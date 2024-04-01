#include "Menu.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../managers/InputManager.h"
#include "../game/GameState.h"


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
	SDL_Rect button1Dest, button2Dest; //Posiciones de botones en pantalla
	initButtons(button1Dest, button2Dest, path1, path2, menu);

	selecDest.w = currSelec.width();
	selecDest.h = currSelec.height();
	selecDest.x = button1Dest.x - offset - selecDest.w / 2;
	selecDest.y = button1Dest.y + button1Dest.h / 2 - currSelec.height() / 2;
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

void Menu::initButtons(SDL_Rect & button1Dest, SDL_Rect & button2Dest, Texture* path1,
	Texture* path2, int menu)
{
	//Asignamos posicion a los botones
	switch (menu)
	{
	case INICIO:
		//Botones
		button1Dest.w = button2Dest.w = BUTTONSTART_W;
		button1Dest.h = button2Dest.h = BUTTONSTART_H;
		button1Dest.x = button2Dest.x = BUTTONSTART_X;
		button1Dest.y = BUTTONSTART_Y; button2Dest.y = BUTTONEND_Y;
		//Fondo
		bgDest.x = bgDest.y = 0;
		bgDest.w = width;
		bgDest.h = height;
		break;
	case PAUSA:
		//Botones
		button1Dest.w = button2Dest.w = BUTTONCONTINUE_W;
		button1Dest.h = BUTTONCONTINUE_H; button2Dest.h = BUTTONOUT_H;
		button1Dest.x = BUTTONCONTINUE_X;  button2Dest.x = BUTTONOUT_X;
		button1Dest.y = BUTTONCONTINUE_Y; button2Dest.y = BUTTONOUT_Y;
		//Fondo
		bgDest.x = bgDest.y = 1 / 10;
		bgDest.w = width - 3 / 10;
		bgDest.h = height - 1 / 10;
		break;
	case GAMEOVER:
		//Botones
		/*button1Dest.w = button2Dest.w = BUTTONSTART_W;
		button1Dest.h = button2Dest.h = BUTTONSTART_H;
		button1Dest.x = button2Dest.x = BUTTONSTART_X;
		button1Dest.y = BUTTONSTART_Y; button2Dest.y = BUTTONEND_Y;*/
		//Fondo
		/*bgDest.x = bgDest.y = 0;
		bgDest.w = width;
		bgDest.h = height;*/
		break;
	default:
		break;
	}

	//Boton de Start
	menuButton.push_back(new Button(path1, button1Dest));
	menuButton[0]->connect([this]() { gameState->enter(); }); 
	//Boton de exit
	menuButton.push_back(new Button(path2, button2Dest));
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
	selecDest.x = menuButton[currButton]->getRect().x - offset - selecDest.w / 2;
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
