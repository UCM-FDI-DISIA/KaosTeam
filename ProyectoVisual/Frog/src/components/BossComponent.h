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
	Entity* ent;
	tipoCubierto tipo;
	TransformComponent* tr;
	RenderComponent* render;
	Box* box;
	Collider coll;
	ColliderComponent* collCmp;
	Vector2D pos;
	Vector2D speed;
	int spawnTime; //Tiempo en spawnear tras iniciar el ataque del Boss
};

class BossComponent: public Component
{	
private:
	bossState currState;
	RenderComponent* render;
	std::vector<Cubierto*> cubiertos;
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos; //El numero de cubiertos max instanciados depende de la zona
	Texture** texturasCubiertos; //Sprite tenedor

	int shadowTimer; //para saber cuanto tiempo ha pasado en la sombra
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque

	Texture* sombra;
	Texture* aviso; //Imagen aviso en que columna aparecera un cubierto
	TransformComponent* tr;
	MovementComponentFrancois* mov;

public:
	BossComponent();
	~BossComponent();

	void initComponent() override;
	void update() override;

	void move();
	void detect();
	void attack();

	void darkenShadow();
	void resetShadow(); // para que e
	void createCutlery(); //Crear cubiertos
	void moveCutlery(); //Mover cubiertos

	//Getters
	bool isFlonkOnShadow() const;
	bool hasCrashed() const; //Comprueba si un cubierto ha chocado contra otro objeto
	bool isOutOfScreen(Vector2D pos) const; //Comprueba si un cubierto se ha salido de la pantalla

};

