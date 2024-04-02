#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

//Define el tamaño y posición de la entidad (si tiene)
//asdsd
class TransformComponent : public Component
{
public:
	TransformComponent(Vector2D position, float width, float height) : position(position), width(width), height(height) {}
	~TransformComponent() {};

	Vector2D& getPosition() {
		return position;
	}
	void setPosition(Vector2D position) {
		this->position = position;
	}

	float getWidth() {
		return width;
	}
	float getHeight() {
		return height;
	}

private:
	Vector2D position;
	float width;
	float height;
};

