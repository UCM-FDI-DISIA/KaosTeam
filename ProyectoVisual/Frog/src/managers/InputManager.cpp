#include "InputManager.h"
std::unique_ptr<InputManager> InputManager::instance;

//InputManager* InputManager::instance = nullptr;

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
		case SDLK_LSHIFT:
			DowntiCheck(BTN_SHIFT);
			break;
		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			DowntiCheck(BTN_ACTION1);
			break;
		case SDLK_x:
			DowntiCheck(BTN_ACTION2);
			break;
		case SDLK_c:
			DowntiCheck(BTN_ACTION3);
			break;
		case SDLK_v:	// Escudo
			DowntiCheck(BTN_ACTION4);
			break;
		case SDLK_ESCAPE:
			DowntiCheck(BTN_ESCAPE);
			break;
		default:
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
		case SDLK_LSHIFT:
			UptiCheck(BTN_SHIFT);
			break;
		case SDLK_z:	//escudo
			UptiCheck(BTN_ACTION1);
			break;
		case SDLK_x:	//ataque
			UptiCheck(BTN_ACTION2);
			break;
		case SDLK_c:    //gancho
			UptiCheck(BTN_ACTION3);
			break;
		case SDLK_v:	//bombas, orbes
			UptiCheck(BTN_ACTION4);
			break;
		case SDLK_ESCAPE:
			UptiCheck(BTN_ESCAPE);
			break;
		default:
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
InputButton InputManager::getAction3() {
	return buttons[BTN_ACTION3];
}
InputButton InputManager::getShift() {
	return buttons[BTN_SHIFT];
}
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
InputButton InputManager::getEscape() {
	return buttons[BTN_ESCAPE];
}
