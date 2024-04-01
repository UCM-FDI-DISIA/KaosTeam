#include "PausedState.h"
#include "../scenes/Menu.h"
#include "../sdlutils/SDLUtils.h"
#include "../managers/InputManager.h"
#include "../managers/HUDManager.h"
#include"Game.h"

PausedState::PausedState(Game* g): game(g), imngr(im()), 
				menu(new Menu(g, this, &sdlutils().images().at("BotonSeguirPausa"), 
				&sdlutils().images().at("BotonSalirPausa"), PAUSA)), currScene(*menu)
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
	game->changeGameState(game->RUNNING);
}

void PausedState::leave()
{
	sdlutils().virtualTimer().resume();
	game->changeGameState(game->NEWGAME);
}

void PausedState::update()
{
	if (imngr.getEscape())
	{
		game->changeGameState(game->RUNNING);
	}
}

