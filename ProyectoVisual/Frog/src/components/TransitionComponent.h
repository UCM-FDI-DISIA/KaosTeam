#pragma once
#include "../ecs/Component.h"
#include "MovementComponentFrog.h"
#include <string>
#include <map>

enum flonkOrig
{
	N,
	S,
	E,
	W,
	P, //flonk extra para transiciones
	T  //flonk para la tienda
};

class RoomScene;

// String switch paridgam   
/*
struct flonkOrigMap : public std::map<std::string, flonkOrig>
{
	flonkOrigMap()
    {
        this->operator[]("FlonkN") = N;
        this->operator[]("FlonkS") = S;
        this->operator[]("FlonkE") = E;
        this->operator[]("FlonkW") = W;
        this->operator[]("FlonkP") = P;
    };
    ~flonkOrigMap() {}
};
*/
class Collider;
class TransitionComponent :public Component
{
private:
	std::string nextMap;
	flonkOrig nextFlonk;
	void CheckMapChange(Entity* e, Collider c);
public:
	TransitionComponent(std::string nextMap, flonkOrig nextFlonk);
	void changeMap();
	void initComponent() override;
};

