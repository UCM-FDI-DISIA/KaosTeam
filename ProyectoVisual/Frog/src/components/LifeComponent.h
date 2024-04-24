#pragma once
class LifeComponent
{
private:
	int vidaActual = 0; //Un  punto es media mosca
	int vidaMaxima = 0;
public:
	LifeComponent() {};
	LifeComponent(int actual, int maxima) :vidaActual(actual), vidaMaxima(maxima) {};
	~LifeComponent() {};
	int GetActual();
	int GetMax();
	void SetActual(int n);
	void SetMax(int n);
	bool alive();
};

