#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() { 
	buttons[END] = {}; 
	PollEvents(); 
}

void InputManager::UpdateStates(const SDL_Event& event) {
	if (event.key.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			buttons[BTN_UP].keyDOWN = true;
			break;
		case SDLK_DOWN:
			buttons[BTN_DOWN].keyDOWN = true;
			break;
		case SDLK_LEFT:
			buttons[BTN_LEFT].keyDOWN = true;
			break;
		case SDLK_RIGHT:
			buttons[BTN_RIGHT].keyDOWN = true;
			break;
		//case SDLK_LSHIFT:
		//	btnShift = true;
		//	break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			buttons[BTN_ACTION1].keyDOWN = true;
			break;
		case SDLK_x:
			buttons[BTN_ACTION2].keyDOWN = true;
			break;
		case SDLK_v:	// Escudo
			buttons[BTN_ACTION4].keyDOWN = true;
			break;
		case SDLK_ESCAPE:
			buttons[BTN_ESCAPE].keyDOWN = true;
			break;
		case SDLK_SPACE:
			buttons[BTN_SPACE].keyDOWN = true;
			break;
		}
	}
	else if (event.key.type == SDL_KEYUP)
	{
	/*	if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT)
			btnShift = false;*/
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			buttons[BTN_UP].keyUP = true;
			break;
		case SDLK_DOWN:
			buttons[BTN_DOWN].keyUP = true;
			break;
		case SDLK_LEFT:
			buttons[BTN_LEFT].keyUP = true;
			break;
		case SDLK_RIGHT:
			buttons[BTN_RIGHT].keyUP = true;
			break;
		//case SDLK_LSHIFT:
		//	btnShift = true;
		//	break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			buttons[BTN_ACTION1].keyUP = true;
			break;
		case SDLK_x:
			buttons[BTN_ACTION2].keyUP = true;
			break;
		case SDLK_v:	// Escudo
			buttons[BTN_ACTION4].keyUP = true;
			break;
		case SDLK_ESCAPE:
			buttons[BTN_ESCAPE].keyUP = true;
			break;
		case SDLK_SPACE:
			buttons[BTN_SPACE].keyUP = true;
			break;
		}
	}
	else if (event.key.state == SDL_PRESSED) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			buttons[BTN_UP].pressed = true;
			break;
		case SDLK_DOWN:
			buttons[BTN_DOWN].pressed = true;
			break;
		case SDLK_LEFT:
			buttons[BTN_LEFT].pressed = true;
			break;
		case SDLK_RIGHT:
			buttons[BTN_RIGHT].pressed = true;
			break;
			//case SDLK_LSHIFT:
			//	btnShift = true;
			//	break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			buttons[BTN_ACTION1].pressed = true;
			break;
		case SDLK_x:
			buttons[BTN_ACTION2].pressed = true;
			break;
		case SDLK_v:	// Escudo
			buttons[BTN_ACTION4].pressed = true;
			break;
		case SDLK_ESCAPE:
			buttons[BTN_ESCAPE].pressed = true;
			break;
		case SDLK_SPACE:
			buttons[BTN_SPACE].pressed = true;
			break;
		}
	}
}

void InputManager::ClearStates() {
	for (int i = 0; i < END; i++) {
		buttons[i].keyDOWN = false;
		buttons[i].keyUP = false;
		buttons[i].pressed = false;

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
