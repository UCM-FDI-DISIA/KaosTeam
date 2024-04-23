#pragma once
#include <vector>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/TransformComponent.h"
#include "../components/ColliderComponent.h"

class RoomScene{};

const int MAX_TIME_ON_SHADOW = 3;
const int MAX_CUBIERTOS = 7;
const Vector2D BOSS_INIT_POS = Vector2D(12, 0);

enum bossState { MOVE, DETECT, ATTACK };
enum tipoCubierto { TENEDOR, CUCHILLO };
struct Cubierto {
	Entity* tipo;
	TransformComponent* tr;
	ColliderComponent* coll;
	Vector2D speed; //Velocidad
	Vector2D pos; //Posicion
	Texture* tex; //Imagen del cubierto (tenerdor o cuchillo)
	int spawnTime; //Tiempo en spawnear tras iniciar el ataque del Boss
};

class BossComponent: public Component
{	
private:
	std::pair<int, int> bossRange; //determina el rango de movimiento del boss
	short int lowerLimit; //Limite inferior de movimiento del Boss
	short int upperLimit; //Limite superior de movimiento del Boss
	bossState currState;
	std::vector<Cubierto*> cubiertos;
	std::vector<std::pair<Cubierto*, bool>> poolCubiertos; //El numero de cubiertos max instanciados depende de la zona

	int shadowTimer; //para saber cuanto tiempo ha pasado en la sombra
	int postAttackTimer; //para evitar que empiece a detectar tras un ataque

	float multiplier; //Se usa para reducir la velocidad de la sombra
	Vector2D speed; //Velocidad de la sombra
	Vector2D pos; //Posicion de la sombra
	Texture* sombra;
	TransformComponent* tr;

public:
	BossComponent();
	~BossComponent();

	void initComponent() override;
	void update() override;

	void move();
	void detect();
	void attack();

	void checkDirection(); //Comrprueba choques con los limites del mapa y cambia la direccion
	void darkenShadow();
	void resetShadow(); // para que e
	void createCutlery(); //Crear cubiertos
	void moveCutlery(); //Mover cubiertos
	void changeRange(); 

	//Getters
	bool isFlonkOnShadow() const;
	bool hasCrashed() const; //Comprueba si un cubierto ha chocado contra otro objeto
	bool isOutOfScreen(Vector2D pos) const; //Comprueba si un cubierto se ha salido de la pantalla
	bool isShadowAtSideLine(Vector2D pos) const; //Esta en el borde de la pantalla
	//Setters
	void setSpeed(Vector2D spd);
	void setLowerLimit(short int limit);
};

