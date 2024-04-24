#pragma once
#include "../ecs/Component.h"

class InteractableComponent :
    public Component
{
private:
	bool pulsed;

public:
	InteractableComponent();

	void update() override;
};

