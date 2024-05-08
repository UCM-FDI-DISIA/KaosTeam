#include "HUDManager.h"
#include"../game/Game.h"
#include "../sdlutils/SDLUtils.h"
#include <string>

using namespace std;

HUDManager::HUDManager() : vidasActuales(0), vidasMax(0), rectFly() {
	font = &sdlutils().fonts().at("COMICSANS");
	textFly = &sdlutils().images().at("flyLifeSheet");

	rectFly.y = yInicial;
	rectFly.w = textFly->width() / textFly->getCol();
	rectFly.h = textFly->height() / textFly->getRow();

	textWorm = &sdlutils().images().at("worm");
	textNumWorms = new Texture(sdlutils().renderer(), to_string(0), *font, colorFont);
	//std::cout << "HUD TEXTURE: " << textNumWorms << std::endl;
}

HUDManager::~HUDManager() {
	delete textNumWorms;
	//std::cout << "HUD TEXTURE AFTER DELETE: " << textNumWorms << std::endl;
	textWorm = nullptr;
	textFly = nullptr;
	game = nullptr;
	lives = nullptr;
	std::cout << Texture::count << std::endl;
}

void HUDManager::ChangeLives(int vidasToAdd) {
	vidasActuales += vidasToAdd;

	if (vidasActuales > vidasMax)
		vidasActuales = vidasMax;
}

void HUDManager::ChangeMaxLife(int maxLifeToAdd)
{
	vidasMax += maxLifeToAdd;
}

void HUDManager::setWorms(const int worms)
{
	delete textNumWorms;
	textNumWorms = new Texture(sdlutils().renderer(), to_string(worms), *font, colorFont);
}

void HUDManager::render() {
	int i = 0;
	rectFly.x = xInicialFly;
	//vidas enteras
	for (i; i < vidasActuales - 1; i += 2)
	{
		textFly->renderFrame(rectFly, 0, 0);
		rectFly.x += rectFly.w;
	}
	//medias vidas
	if (vidasActuales % 2 != 0)
	{
		textFly->renderFrame(rectFly, 0, 1);
		rectFly.x += rectFly.w;
		i += 2;
	}
	//vidas vacias
	for (i; i < vidasMax; i += 2)
	{
		textFly->renderFrame(rectFly, 0, 2);
		rectFly.x += rectFly.w;
	}

	//y ahora la worm
	textWorm->render(xInicialWorm, yInicial - 10);
	//y el numero de worms
	textNumWorms->render(xInicialWorm + 50, yInicial + 30);
}

void HUDManager::update() {
	if (lives != nullptr) { //Si se ha enlazado con el LifeComponent del player
		vidasActuales = lives->GetActual();
		vidasMax = lives->GetMax();
	}
}

void HUDManager::LinkLives(LifeComponent* playerLife) {
	lives = playerLife;
}
