#include "PausedState.h"
#include "../scenes/MenuPausa.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"
#include"Game.h"

PausedState::PausedState(): imngr(im()), 
				menu(new MenuPausa(Game::instance(), this, &sdlutils().images().at("BotonSeguirPausa"),
				&sdlutils().images().at("BotonSalirPausa"))), currScene(*menu)
{
}
PausedState::~PausedState()
{
	delete menu;
}
;
void PausedState::enter() //Asi no deberia de ser el enter pero por ahora funcionara como el callback para continuar 
{
	sdlutils().virtualTimer().resume();
	Game::instance()->setNextState(Game::instance()->RUNNING);
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
	Game::instance()->setNextState(Game::instance()->NEWGAME);
}

void PausedState::update()
{
	if (imngr.getEscape()) {
		Game::instance()->setNextState(Game::instance()->RUNNING);
	}
	currScene.update();
}

