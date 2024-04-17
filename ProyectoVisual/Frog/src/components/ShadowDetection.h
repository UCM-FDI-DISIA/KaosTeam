#pragma once
#include "../ecs/Component.h"
const int TIME_DETECTION=3;
class ShadowDetection:public Component
{
private:
	bool active;
	
public:
	void initComponent();
	void update();
};

