#pragma once
class Scene
{
	/**
	* Clase abstracta de escena, todo lo que es programaci�n debe ir en su clase hija.
	* Todas las clases deben ser implementadas.
	* 
	* Las salas deber�an ser una clase hija de Escena
	* Otras escenas pueden ser el men� de inicio y el men� de pausa.
	*/
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};