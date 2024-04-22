#pragma once
#include "../ecs/Component.h"
#include <string>
#include <map>

enum flonkOrig
{
	N,
	S,
	E,
	W,
	P,
	T//flonk extra para transiciones
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

class TransitionComponent :public Component
{
private:
	std::string nextMap;
	flonkOrig nextFlonk;

public:
	TransitionComponent(std::string nextMap, flonkOrig nextFlonk) : nextMap(nextMap), nextFlonk(nextFlonk) {};
	void changeMap();

};

