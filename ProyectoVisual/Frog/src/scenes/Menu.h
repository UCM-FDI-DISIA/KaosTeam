#pragma once

#include "../game/Game.h"
#include "../ecs/Scene.h"
#include"../utils/Button.h"

#include <string>
#include <vector>

class Texture;
class InputManager;
class GameState;

enum direction{ARRIBA, ABAJO};

const int offset = 50; //Offset de la seleccion

class Menu : public Scene
{
protected:
	Texture* bg; //Textura de fondo del menu
	//Texture* bgEffect; //Efecto para darle más personalidad a los menus
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
	Menu(GameState* nGS, Texture * path1, Texture * path2);
	virtual ~Menu();

	void render() override;
	void update() override;
	void changeButton(bool dir);
	void callButton();
};

