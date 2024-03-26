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
	P //flonk extra para transiciones
};

// String switch paridgam   
struct flonkOrigMap : public std::map<std::string, flonkOrig>
{
	flonkOrigMap()
    {
        this->operator[]("N") = N;
        this->operator[]("S") = S;
        this->operator[]("E") = E;
        this->operator[]("W") = W;
        this->operator[]("P") = P;
    };
    ~flonkOrigMap() {}
};

class TransitionComponent :public Component
{
private:
	std::string nextMap;
	flonkOrig nextFlonk;
};

