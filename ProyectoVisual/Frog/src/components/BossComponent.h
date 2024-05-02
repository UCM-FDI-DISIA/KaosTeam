#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "TransformComponent.h"
#include "../utils/Box.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "MovementComponent.h"
#include "MovementComponentFrancois.h"
#include <vector>

const int MAX_TIME_ON_SHADOW = 3;
const int MAX_CUBIERTOS = 4;

enum bossState { MOVE, DETECT, ATTACK };
enum tipoCubierto { CUCHARA, CUCHILLO, CUCHILLO_CARNICERO, TENEDOR };
struct Cubierto {
	Entity* ent_;
	tipoCubierto tipo_;
	TransformComponent* tr_;
	RenderComponent* render_;
	ColliderComponent* coll_;
	Vector2D speed_;
	int spawnTime_; //Tiempo en spawnear tras iniciar el ataque del Boss
};

class BossComponent: public Component
{	
private:
	bossState currState;
	RenderComponent* render;
	std::vector<Cubierto*> cubiertos;
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos; //El numero de cubiertos max instanciados depende de la zona
	Texture** texturasCubiertos; //Array de texturas de los cubiertos

	int shadowTimer; //para saber cuanto tiempo ha pasado en la sombra
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque
	int contDishes; //Platos contaminados en cada momento

	Texture* aviso; //Imagen aviso en que columna aparecera un cubierto
	TransformComponent* tr;
	MovementComponentFrancois* mov;
	ColliderComponent* coll;

public:
	BossComponent();
	~BossComponent();

	void initComponent() override;
	void update() override;

	void attack(Entity* e, Collider c);

	void createCutlery(); //Crear cubiertos
	void generateCutlery(); //Colocar cubiertos y avisos en el mapa
	void moveCutlery(); //Mover cubiertos

	//Getters
	bool hasCrashed() const; //Comprueba si un cubierto ha chocado contra otro objeto
	bool isOutOfScreen(Vector2D pos) const; //Comprueba si un cubierto se ha salido de la pantalla

	void setContaminatedDishes(int d) { contDishes += d; };
};

