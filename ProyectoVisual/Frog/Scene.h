#pragma once
class Scene
{
	/**
	* Clase abstracta de escena, todo lo que es programación debe ir en su clase hija.
	* Todas las clases deben ser implementadas.
	*/
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};