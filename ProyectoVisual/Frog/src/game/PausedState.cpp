#include "PausedState.h"
#include "../scenes/MenuPausa.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"
#include"Game.h"

PausedState::PausedState(Game* g): game(g), imngr(im()), 
				menu(new MenuPausa(g, this, &sdlutils().images().at("BotonSeguirPausa"), 
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
	game->setNextState(game->RUNNING);
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
	game->setNextState(game->NEWGAME);
}

void PausedState::update()
{
	if (imngr.getEscape())
	{
		game->setNextState(game->RUNNING);
	}
	currScene.update();
}

