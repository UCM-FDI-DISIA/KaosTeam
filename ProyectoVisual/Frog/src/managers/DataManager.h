#pragma once
#include "../sdlutils/SDLUtils.h"

/**
* Singleton encargada de guardar y manejar todo tipo de información que se necesite durante cualquier parte de la partida.
* 
* 
*/
class DataManager
{
private:
	DataManager() { instance = nullptr; UpdateFrameTime(); };
	~DataManager() {};
	static DataManager* instance;
	Uint32 frameTime;
	//Debe ser un singleton que guarda distintos datos generales del juego.
public:
	DataManager(DataManager&) = delete;
	void operator=(const DataManager&) = delete;

	static DataManager* GetInstance() {
		if (instance == nullptr) {
			instance = new DataManager();
		}
		return instance;
	};
	//Actualiza el valor de la variable frameTime
	void UpdateFrameTime();
	Uint32 getFrameTime();
};

