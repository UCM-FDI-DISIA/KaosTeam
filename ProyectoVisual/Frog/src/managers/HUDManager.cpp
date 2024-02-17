#include "HUDManager.h"
#include "../sdlutils/SDLUtils.h"


void
HUDManager::render()
{
	int i = 0;
	rectFly->x = xInicialFly;
	//vidas enteras
	for (i; i < vidasActuales-1; i += 2)
	{
		textFly->renderFrame(*rectFly, 0, 0);
		rectFly->x += rectFly->w;
	}
	//medias vidas
	if (vidasActuales % 2 != 0)
	{
		textFly->renderFrame(*rectFly, 0, 1);
		rectFly->x += rectFly->w;
		i += 2;
	}
	//vidas vacias
	for (i; i < vidasMax; i += 2)
	{
		textFly->renderFrame(*rectFly, 0, 2);
		rectFly->x += rectFly->w;
	}

	//y ahora la worm
	textWorm->render(xInicialWorm, yInicial);
}

HUDManager::HUDManager(Game* g, int vidasActuales, int VidasMaximas) : game(g), vidasActuales(vidasActuales), vidasMax(VidasMaximas), rectFly(new SDL_Rect())
{
	textFly = new Texture(sdlutils().renderer(), "resources/Sprites/moscaVidaSpritesheet.png", 1, 3);
	rectFly->y = yInicial;
	rectFly->w = textFly->width() / textFly->getCol();
	rectFly->h = textFly->height() / textFly->getRow();

	textWorm = new Texture(sdlutils().renderer(), "resources/Sprites/wormHUD.png", 1, 3);
}