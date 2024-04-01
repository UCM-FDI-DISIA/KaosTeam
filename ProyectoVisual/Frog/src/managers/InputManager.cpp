#include "InputManager.h"
/*InputManager* InputManager::GetInstance() {
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return instance;
}*/

InputManager* InputManager::instance = nullptr;

void InputManager::PollEvents() {
	SDL_Event event;

	ClearStates();
	while (SDL_PollEvent(&event))
		UpdateStates(event);
}

void InputManager::ClearStates() {
	for (int i = 0; i < END; i++) {
		states[i] = false;
	}
}

void InputManager::UpdateStates(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			states[BTN_UP] = true;
			break;
		case SDLK_DOWN:
			states[BTN_DOWN] = true;
			break;
		case SDLK_LEFT:
			states[BTN_LEFT] = true;
			break;
		case SDLK_RIGHT:
			states[BTN_RIGHT] = true;
			break;

		//ahora para poder usar WASD
		case SDLK_a:
			states[BTN_LEFT] = true;
			break;
		case SDLK_w:
			states[BTN_UP] = true;
			break;
		case SDLK_s:
			states[BTN_DOWN] = true;
			break;
		case SDLK_d:
			states[BTN_RIGHT] = true;
			break;


		case SDLK_z:	//Se puede cambiar si queremos usar otra tecla
			states[BTN_ACTION1] = true;
			break;
		case SDLK_x:
			states[BTN_ACTION2] = true;
			break;
		case SDLK_c:
			states[BTN_ACTION3] = true;
			break;
		case SDLK_v:	// Escudo
			states[BTN_ACTION4] = true;
			break;
		case SDLK_ESCAPE:
			states[BTN_ESCAPE] = true;
			break;
		case SDLK_SPACE:
			states[BTN_SPACE] = true;
			break;
		}
	}
}

bool InputManager::getAction1() {
	return states[BTN_ACTION1];
}
bool InputManager::getAction2() {
	return states[BTN_ACTION2];
}
bool InputManager::getAction3() {
	return states[BTN_ACTION3];
}
bool InputManager::getAction4() {
	return states[BTN_ACTION4];
}
bool InputManager::getUp() {
	return states[BTN_UP];
}
bool InputManager::getDown() {
	return states[BTN_DOWN];
}
bool InputManager::getLeft() {
	return states[BTN_LEFT];
}
bool InputManager::getRight() {
	return states[BTN_RIGHT];
}
bool InputManager::getSpace()
{
	return states[BTN_SPACE];
}
