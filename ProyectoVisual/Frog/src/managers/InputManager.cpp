#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() { 
	//buttons[END] = {}; 

	for (int i = 0; i < END; i++) {
		InputButton b;
		b.keyDOWN = false;
		b.keyUP = false;
		buttons.push_back(b);
		//El pressed (que esta activo mientras este pulsado el boton) no se restablece aqui
		//Sino en el propio evento del key up
	}
	PollEvents(); 
}

void InputManager::UpdateStates(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			DowntiCheck(BTN_UP);
			break;
		case SDLK_DOWN:
			DowntiCheck(BTN_DOWN);
			break;
		case SDLK_LEFT:
			DowntiCheck(BTN_LEFT);
			break;
		case SDLK_RIGHT:
			DowntiCheck(BTN_RIGHT);
			break;
		//case SDLK_LSHIFT:
		//	btnShift = true;
		//	break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			DowntiCheck(BTN_ACTION1);
			break;
		case SDLK_x:
			DowntiCheck(BTN_ACTION2);
			break;
		case SDLK_v:	// Escudo
			DowntiCheck(BTN_ACTION4);
			break;
		case SDLK_ESCAPE:
			DowntiCheck(BTN_ESCAPE);
			break;
		case SDLK_SPACE:
			DowntiCheck(BTN_SPACE);
			break;
		case SDLK_b:	//comprar
			DowntiCheck(BTN_ACTIONBUY);
			break;
		case SDLK_a:	//izq en tienda
			DowntiCheck(BTN_LEFTSHOP);
			break;
		case SDLK_d:	//derecha en tienda
			DowntiCheck(BTN_RIGHTSHOP);
			break;
		}
		
	}
	else if (event.type == SDL_KEYUP)
	{
	/*	if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
	//btnShift = false;*/
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			UptiCheck(BTN_UP);
			break;
		case SDLK_DOWN:
			UptiCheck(BTN_DOWN);
			break;
		case SDLK_LEFT:
			UptiCheck(BTN_LEFT);
			break;
		case SDLK_RIGHT:
			UptiCheck(BTN_RIGHT);
			break;
		//case SDLK_LSHIFT:
		//	btnShift = true;
		//	break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			UptiCheck(BTN_ACTION1);
			break;
		case SDLK_x:
			UptiCheck(BTN_ACTION2);
			break;
		case SDLK_v:	// Escudo
			UptiCheck(BTN_ACTION4);
			break;
		case SDLK_ESCAPE:
			UptiCheck(BTN_ESCAPE);
			break;
		case SDLK_SPACE:
			UptiCheck(BTN_SPACE);
			break;
		case SDLK_b:	
			UptiCheck(BTN_ACTIONBUY);
			break;
		case SDLK_a:	
			UptiCheck(BTN_LEFTSHOP);
			break;
		case SDLK_d:	
			UptiCheck(BTN_RIGHTSHOP);
			break;
		}
	}
}

void InputManager::UptiCheck(btnEnum btn) {
	buttons[btn].keyUP = true;
	buttons[btn].pressed = false;
}

void InputManager::DowntiCheck(btnEnum btn) {
	if (!buttons[btn].pressed) {
		buttons[btn].keyDOWN = true;
		buttons[btn].pressed = true;
	}
}

void InputManager::ClearStates() {

	for (auto& b : buttons) {
		b.keyDOWN = false;
	}
	for (int i = 0; i < END; i++) {
		buttons[i].keyDOWN = false;
		buttons[i].keyUP = false;
		//El pressed (que esta activo mientras este pulsado el boton) no se restablece aqui
		//Sino en el propio evento del key up
	}
}

void InputManager::PollEvents() {
	SDL_Event event;

	ClearStates();
	while (SDL_PollEvent(&event))
		UpdateStates(event);
}

InputButton InputManager::getAction1() {
	return buttons[BTN_ACTION1];
}
InputButton InputManager::getAction2() {
	return buttons[BTN_ACTION2];
}
//InputButton InputManager::getShift() {
//	return btnShift;
//}
InputButton InputManager::getAction4() {
	return buttons[BTN_ACTION4];
}
InputButton InputManager::getActionBuy() {
	return buttons[BTN_ACTIONBUY];
}
InputButton InputManager::getActionRightShop() {
	return buttons[BTN_RIGHTSHOP];
}
InputButton InputManager::getActionLeftShop() {
	return buttons[BTN_LEFTSHOP];
}
InputButton InputManager::getUp() {
	return buttons[BTN_UP];
}
InputButton InputManager::getDown() {
	return buttons[BTN_DOWN];
}
InputButton InputManager::getLeft() {
	return buttons[BTN_LEFT];
}
InputButton InputManager::getRight() {
	return buttons[BTN_RIGHT];
}
InputButton InputManager::getSpace()
{
	return buttons[BTN_SPACE];
}
InputButton InputManager::getEscape()
{
	return buttons[BTN_ESCAPE];
}
