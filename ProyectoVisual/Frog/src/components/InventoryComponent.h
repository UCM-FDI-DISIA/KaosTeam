#pragma once
#include "../ecs/Component.h"

//Datos sobre las mejoras que tiene la rana ahora mismo. Al principio de la partida empiezan a 0.
struct MejorasData {
	MejorasData();
	//Cada saltamontes añade una casilla al salto largo
	int saltamontes;
	//Cada mosca añade una vida (media mosca)
	int moscas;
	//Cada avispa aumenta en 1 el daño de la rana
	int avispas;
	//Cada ciempies aumenta el alcance de la lengua en una casilla
	int ciempies;
};

//Datos sobre las habilidades que tiene la rana ahora mismo. Al principio de la partida empiezan como false (no las tiene).
struct HabilidadesData {
	HabilidadesData();
	bool gancho;
	bool sacoBombas;
};

class InventoryComponent : public Component
{
public:
	InventoryComponent();

	//Gestion del dinero
	int GetMoney();
	void AddMoney(int n); //Metodo para añadirle dinero a nuestro total
	bool TakeMoney(int price); //El metodo es un booleano por haber casos en donde no tengamos suficiente dinero.
	MejorasData mejoras;
	HabilidadesData habilidades;
private:
	int money;
};
