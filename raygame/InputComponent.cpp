#include "InputComponent.h"

MathLibrary::Vector2 InputComponent::getMoveAxis()
{
	float moveDirectionX = -RAYLIB_H::IsKeyDown(RAYLIB_H::KEY_A) + RAYLIB_H::IsKeyDown(RAYLIB_H::KEY_D);
	float moveDirectionY = -RAYLIB_H::IsKeyDown(RAYLIB_H::KEY_W) + RAYLIB_H::IsKeyDown(RAYLIB_H::KEY_S);

	//Returns
	return MathLibrary::Vector2(moveDirectionX, moveDirectionY);
}
