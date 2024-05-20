#pragma once
#include "../sdlutils/SDLUtils.h"
#include <map>
#include <memory>

/**
* Singleton encargada de guardar y manejar todo tipo de información que se necesite durante cualquier parte de la partida.
* 
* 
*/

struct ObjEdit{
	bool interacted;
	Vector2D pos;
};

class DataManager
{
private:
	DataManager() { instance = nullptr; UpdateFrameTime(); };
	
	static std::unique_ptr<DataManager> instance;
	//static DataManager* instance;
	Uint32 frameTime;
	std::map<std::string, std::vector<ObjEdit>> interactedObjects; //Estructura para el guardado de escenas
	//Debe ser un singleton que guarda distintos datos generales del juego.
public:
	~DataManager() 
	{
		std::cout << "DATA MANAGER: DELETED" << std::endl;
	
	};
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
	std::vector<ObjEdit>& getInteractObj(std::string path);
	void addObjs(const std::string& path, const std::vector<ObjEdit>& interactObj);
};

