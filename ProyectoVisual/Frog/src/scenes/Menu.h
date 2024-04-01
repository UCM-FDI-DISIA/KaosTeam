#pragma once

#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class GameState;
class Game;

enum direction{ARRIBA, ABAJO};

const int offsetX = 50;

class Menu : public Scene
{
private:
	Texture* bg; //Textura de fondo del menu
	Texture& currSelec; //Textura que apunta al boton seleccionado
	SDL_Rect selecDest; //resize de la mosca
	SDL_Rect bgDest; //resize del fondo
	GameState* gameState;
	Game* game;
	InputManager& imngr;

	int width; //Ancho de la pantalla
	int height; //Alto de la pantalla
	int currButton; //Iterador del vector de botones
	
	std::vector <Button*> menuButton;
public:
	Menu(Game* g, GameState* nGS, Texture * path1, Texture * path2, int menu);
	~Menu();

	void render() override;
	void update() override;
	void initButtons(SDL_Rect & buttonStartDest, SDL_Rect & buttonEndDest, Texture* path1, Texture* path2, int menu);
	void changeButton(bool dir);
	void menuToRender(int menu);
	void callButton();
};
