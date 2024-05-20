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
#include <utility>

const int TYPES_OF_CUTLERY = 4;
const int MAX_CUTLERY = 6;
const int TIME_AFTER_ATTACK = 100;
const int MINIMUM_CUTLERY_PER_ATTACK = 2;

enum bossState { MOVE, ATTACK };	
enum tipoCubierto { CUCHARA, CUCHILLO, CUCHILLO_CARNICERO, TENEDOR };
struct Cubierto {
	Entity* ent_;
	tipoCubierto tipo_;
	TransformComponent* tr_;
	RenderComponent* render_;
	ColliderComponent* coll_;
	Vector2D speed_;
	int spawnTime_; //Tiempo en spawnear tras iniciar el ataque del Boss
	SDL_Rect dest_; //Lugar donde va el aviso para avisar de que un cubierto atravesara esa fila
};

class BossComponent: public Component
{	
private:
	
	Texture* aviso; //Imagen aviso en que columna aparecera un cubierto
	std::vector<Cubierto*> cubiertos;
	int numCubiertos; //Contador del vector poolCubiertos
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos; //El numero de cubiertos max instanciados depende de la zona
	Texture** texturasCubiertos; //Array de texturas de los cubiertos
	bool addToList; //Determines if cutlery is added to entity list

	int attackStartTime; //Definde en que momento empieza un ataque
	bool isAttacking; //Para determinar el estado de francois
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque
	int contDishes; //Platos contaminados en cada momento

	bossState currState;
	TransformComponent* tr;
	RenderComponent* rnd;
	MovementComponentFrancois* mov;
	ColliderComponent* coll;

public:
	BossComponent();
	virtual ~BossComponent();

	void initComponent() override;
	void update() override;
	void render() ;

	void attack(Entity* e, Collider c);

	void createCutlery(); //Crear cubiertos
	void generateCutlery(); //Colocar cubiertos y avisos en el mapa
	void addCutlery(); //Añadir cubiertos a la lista de entidades
	void moveCutlery(); //Mover cubiertos
	void cleanPool(); //Elminamos cubiertos que se han salido de la pantalla
	void onCutleryCollision(Entity* e, Collider c); //Gestion de restar vida a Flonk si es golpeado

	//Getters
	bool isOutOfScreen(float y) const; //Comprueba si un cubierto se ha salido de la pantalla
	bool theresCutleryToAdd() const { return addToList; };
	bool isDetectingFlonk() const;
	bool isAttackingFlonk() const { return isAttacking; }; //Devuelve si esta atacando a Flonk
	bool hasTimerPostAttackEnded() const { return postAttackTimer > TIME_AFTER_ATTACK; }
	//Setters
	void setContaminatedDishes(int d) { contDishes += d; };
};
