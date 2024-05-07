#pragma once
#include "../ecs/Component.h"

//Datos sobre las mejoras que tiene la rana ahora mismo. Al principio de la partida empiezan a 0.
struct MejorasData {
	MejorasData();
	//Cada saltamontes a�ade una casilla al salto largo
	int saltamontes;
	//Cada mosca a�ade una vida (media mosca)
	int moscas;
	//Cada avispa aumenta en 1 el da�o de la rana
	int avispas;
	//Cada ciempies aumenta el alcance de la lengua en una casilla
	int ciempies;
	//Cuantas bombas tiene el jugador
	int bombas;
	//Cuantos orbes tiene el jugador
	int orbes;
};

//Datos sobre las habilidades que tiene la rana ahora mismo. Al principio de la partida empiezan como false (no las tiene).
struct HabilidadesData {
	HabilidadesData();
	bool gancho;
	bool sacoBombas;
};

//Enumerado con todos los items del juego
enum Items {
	SALTAMONTES,
	MOSCAS,
	MOSCAS_DE_VIDA,
	AVISPAS,
	CIEMPIES,
	GANCHO,
	BOMBAS, 
	MONEDAS,
	SACO_BOMBAS,
	ORBES,
	ROACH_HEAD
	//Indica la cantidad de llaves que lleva el jugador
	LLAVES
};

//Tipos de moneda
enum MonedaType {
	MONEDA_NARANJA,
	MONEDA_ROSA,
	MONEDA_MORADO
};

class InventoryComponent : public Component
{
public:
	InventoryComponent();
	//Gestion del dinero
	int GetMoney();
	void AddMoney(int n); //Metodo para a�adirle dinero a nuestro total
	bool TakeMoney(int price); //El metodo es un booleano por haber casos en donde no tengamos suficiente dinero.
	void PickUpItem(Items, int amm);
	void PickMoneda(int type);
	void MejoraMosca(int amm);
	void CurarVida(int amm);
	int GetLlaves();
	MejorasData mejoras;
	HabilidadesData habilidades;
private:
	int money;
	int llaves;
};
