#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>

//Comprueba colisiones de objetos, y envía un mensaje con la información relevante a los componentes suscritos
//La llamada a comporbar colisiones debe hacerse en el update del room antes o después del update de las entidades

/*Flonk tiene un collision component que en su update comprueba la interseccion de su SDLrect con el SDLrect de el resto de entidades colisionables.
- Los SDLrects estos se crean en cada iteración cogiendo la posición en MovementComponent y el width y height de la Textura * en RenderComponent.Feo pero cuando tengamos un componente transform ya se gestionará mejor.
- Las entidades colisionables son las que tengan un componente collideable(igual no se llama así), este componente recibe un método callback en su constructora al que se le llamará si Flonk detecta una collisión con el SDLrect de esta entidad.
De esta manera, provisional para este hito 2, flonk va a ser el que gestione con qué entidad ha collisionado y 
llamará al metodo callback que corresponda, es un for simplemente y así Diego implementa esto y la 
gente que ha estado haciendo enemigos puede hacer su método onCollision y meterlo en las constructoras y fuera : )
*/
//Es decir, al refactorizar en el hito 3 van a cambiar muchas cosas
class ColliderComponent : public Component
{
public:
	ColliderComponent() : funcion(nullptr) {};
	~ColliderComponent() {
		//No hay que eliminar function porque pertenece al objeto llamado
	};

	//Comprueba la colisión con la estidad e
	bool CheckCollision(Entity* e);
	void OnCollision();

	//Añade la funcion a llamar cuando hay colision
	//En el futuro molaria poder almacenas muchas funciones y llamar a todas
	void AddCall(std::function<void()>* func);
	
private:
	std::function<void()>* funcion;
};

