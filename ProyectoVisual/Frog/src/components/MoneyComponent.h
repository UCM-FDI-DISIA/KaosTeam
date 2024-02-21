#include "../ecs/Component.h"
class MoneyComponent:public Component
{
private:
	int money;
public:
	MoneyComponent() :money(0) {};
	MoneyComponent(int n) :money(n) {};
	int GetMoney();
	void AddMoney(int n);
	bool TakeMoney(int price);
};