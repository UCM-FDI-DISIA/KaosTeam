#pragma once
#include "../ecs/Component.h"
class InventoryComponent : public Component
{
public:
	InventoryComponent();
	~InventoryComponent();
	void update() override;

	//getters y setters
	bool getAttackUpgrade(){ return attackUpgrade; }
	void buyAttackUpgrade() { attackUpgrade = true; }
	bool getDamageUpgrade() { return damageUpgrade; }
	void buyDamageUpgrade() { damageUpgrade = true; }
	bool getJumpUpgrade() { return jumpUpgrade; }
	void buyJumpUpgrade() { jumpUpgrade = true; }

	void eatEntity(Entity* e) { entityActual = e; }
	Entity* eatenEntity() { return entityActual; }

private:
	
	bool damageUpgrade;
	bool attackUpgrade;
	bool jumpUpgrade;
	Entity* entityActual;
};

