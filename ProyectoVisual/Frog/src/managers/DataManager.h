#pragma once
#include "../sdlutils/SDLUtils.h"
#include <map>
#include <memory>

/**
* Singleton encargada de guardar y manejar todo tipo de información que se necesite durante cualquier parte de la partida.
* 
* 
*/

class DataManager
{
private:
	DataManager() { instance = nullptr; UpdateFrameTime(); };
	
	static std::unique_ptr<DataManager> instance;
	//static DataManager* instance;
	Uint32 frameTime;
	std::map<std::string, std::vector<bool>> interactedObjects; //Estructura para el guardado de escenas
	//Debe ser un singleton que guarda distintos datos generales del juego.
public:
	~DataManager() {};
	DataManager(DataManager&) = delete;
	void operator=(const DataManager&) = delete;

	static DataManager* GetInstance() {
		if (instance == nullptr) {
			instance.reset(new DataManager());
		}
		return instance.get();
	};
	//Actualiza el valor de la variable frameTime
	void UpdateFrameTime();
	Uint32 getFrameTime();

	//Métodos para el guardado de escenas
	std::vector<bool> getInteractObj(const std::string& path);
	void addObjs(const std::string& path, const std::vector<bool>& interactObj);
};

