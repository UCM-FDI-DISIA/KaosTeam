#pragma once

#include "../components/MovementComponent.h"

class MovementComponentFrancois : public MovementComponent
{
private:
	
public:
	MovementComponentFrancois();
	~MovementComponentFrancois();

	void update() override;
};

