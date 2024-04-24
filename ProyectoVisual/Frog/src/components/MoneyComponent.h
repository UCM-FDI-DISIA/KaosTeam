#pragma once
#include "../ecs/Component.h"
class MoneyComponent:public Component
{
private:
	int money;
public:
	MoneyComponent() :money(0) {};
	MoneyComponent(int n) :money(n) {};
	~MoneyComponent() {};
	int GetMoney(); 
	void AddMoney(int n); //Metodo para añadirle dinero a nuestro total
	bool TakeMoney(int price); //El metodo es un booleano por haber casos en donde no tengamos suficiente dinero.
};