#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>

//Comprueba colisiones de objetos, y env�a un mensaje con la informaci�n relevante a los componentes suscritos
//La llamada a comporbar colisiones debe hacerse en el update del room antes o despu�s del update de las entidades

/*Flonk tiene un collision component que en su update comprueba la interseccion de su SDLrect con el SDLrect de el resto de entidades colisionables.
- Los SDLrects estos se crean en cada iteraci�n cogiendo la posici�n en MovementComponent y el width y height de la Textura * en RenderComponent.Feo pero cuando tengamos un componente transform ya se gestionar� mejor.
- Las entidades colisionables son las que tengan un componente collideable(igual no se llama as�), este componente recibe un m�todo callback en su constructora al que se le llamar� si Flonk detecta una collisi�n con el SDLrect de esta entidad.
De esta manera, provisional para este hito 2, flonk va a ser el que gestione con qu� entidad ha collisionado y 
llamar� al metodo callback que corresponda, es un for simplemente y as� Diego implementa esto y la 
gente que ha estado haciendo enemigos puede hacer su m�todo onCollision y meterlo en las constructoras y fuera : )
*/
//Es decir, al refactorizar en el hito 3 van a cambiar muchas cosas
class ColliderComponent : public Component
{
public:
	ColliderComponent() : funcion(nullptr) {};
	~ColliderComponent() {
		//No hay que eliminar function porque pertenece al objeto llamado
	};

	//Comprueba la colisi�n con la estidad e
	bool CheckCollision(Entity* e);
	void OnCollision();

	//A�ade la funcion a llamar cuando hay colision
	//En el futuro molaria poder almacenas muchas funciones y llamar a todas
	void AddCall(std::function<void()>* func);
	
private:
	std::function<void()>* funcion;
};

