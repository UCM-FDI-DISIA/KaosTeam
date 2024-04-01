#pragma once

#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class NewGameState;
class GameState;
class Game;

enum direction{ARRIBA, ABAJO};

const int offsetX = 50;

class Menu : public Scene
{
private:
	Texture* bg; //Textura de fondo
	Texture* currSelec; //Textura que apunta al boton seleccionado
	SDL_Rect dest; //resize de la mosca
	SDL_Rect bgDest; //resize del fondo
	GameState* newGSt;
	Game* game;
	InputManager& imngr;

	int width; //Ancho de la pantalla
	int height; //Alto de la pantalla
	int currButton; //Iterador del vector de botones
	
	std::vector <Button*> menuButton;
public:
	Menu(Game* g, GameState* nGS, std::string path,std::string path2, std::string bgKey);
	~Menu() {};

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

